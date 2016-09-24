<?php

/**
 *  @class:
 *    This class provides getty projects with a complete xml request from the server
 */
class getty_project {
  public $project_nid;
  public $format;
  public $nodes = array();
  public $project_node;
  private $cache_id;
  private $raw_nodes = array();
  private $include_images = array();

  /**
   *  @method:
   *    constructor for class
   */
  function __construct($nid = null, $format = 'json') {
    if (!empty($nid)) {
      if (is_numeric($nid)) {
        $this->set_nodes_by_project($nid);
      }
      elseif (is_array($nid)) {
        $this->set_nodes($nid);
      }
    }
    $this->format = $format;
  }

  public function set_nodes($nids) {
    $this->cache_id = implode(',', $nids);
    $contents = array();
    $nodes = node_load_multiple($nids);
    foreach ($nodes as $node) {
      $contents[$node->type][] = $node;
    }
    $this->raw_nodes = unserialize(serialize($contents));
    $this->nodes = $this->_parse_nodes($contents);
  }

  public function set_nodes_by_project($project_nid) {
    $this->cache_id = $project_nid;
    $this->project_nid = $project_nid;
    $this->_load_project_node();
    $contents = $this->_load_project_contents();
    $this->raw_nodes = unserialize(serialize($contents));
    $this->nodes = $this->_parse_nodes($contents);
  }

  /**
   *  @method:
   *    Public method that is used to get the output based on the request
   */
  public function get_output($download = FALSE) {
    $break_cache = (isset($_GET['break_cache'])) ? $_GET['break_cache'] : FALSE;
    //only cache if break_cache is not set
    if (!$break_cache) {
      $cached = $this->_cache();
      $data = $cached;
    }

    //switches based on the format requested
    switch ($this->format) {
      case 'xml':
        drupal_add_http_header('Content-Type', 'application/xml; charset=utf-8');
        if (empty($cached)) {
          $data = $this->_array_to_xml($this);
        }
        break;
      case 'csv':
        drupal_add_http_header('Content-Type', 'text/csv');
        if (empty($cached)) {
          $data = $this->_array_to_csv($this);
        }
        break;
      case 'json':
        // drupal_add_http_header('Content-Type', 'application/json');
        $download = TRUE;
        if (empty($cached)) {
          $data = $this->_array_to_json($this);
        }
        break;
      default:
        $data = '';
    }

    //adds data into the cache
    if (empty($cached)) {
      $data = json_decode(json_encode($data), true);
      $this->_cache('set', $data);
    }

    //download the files once the parameter is set
    if (!empty($download) || (isset($_GET['download']) && $_GET['download'])) {
      //generates the download portion once download is required
      if ($this->format == 'json') {
        $file_path = $this->_download_json($data);
      }
      else {
        $file_path = $this->_download_project($data);
      }
      $filename = explode('/', $file_path);
      $filename = $filename[count($filename) - 1];

      //sets all the headers for the download to work
      header("Pragma: public");
      header("Expires: 0");
      header("Cache-Control: must-revalidate, post-check=0, pre-check=0");
      header("Cache-Control: private",false); // required for certain browsers
      header('Content-Disposition: attachment; filename="' . $filename . '"');
      header("Content-Transfer-Encoding: binary");
      header("Content-Length: " . filesize($file_path));
      readfile("$file_path");
      drupal_exit();
    }

    $output = $data;
    return $output;
  }

  /**
   *  @method:
   *    This method is used to download the project
   */
  public function _download_project($output = '') {
    //default variables
    $zip = new ZipArchive();
    $DelFilePath = "project_" . $this->format . ".zip";
    $public = variable_get('file_public_path', 'sites/default/files');
    $path = DRUPAL_ROOT . '/' . $public . '/';

    //ensures that we delete the old file
    if(file_exists($path . $DelFilePath)) {
      unlink ($path . $DelFilePath);
    }

    //creates the zip file and starts to append
    if ($zip->open($path . $DelFilePath, ZIPARCHIVE::CREATE) != TRUE) {
      watchdog('getty project', "Could not open archive at " . print_r($path . $DelFilePath, 1));
    }

    //appends the format requested
    $zip->addFromString('project.' . $this->format, $output);

    //does for each image included to download
    foreach ($this->include_images as $key => $images) {
      $site_path = explode($public, $images);
      $image_path = explode('/', $site_path[1]);
      $file_name = $image_path[count($image_path) - 1];
      //ensures that the file exists on the server before adding
      if (file_exists($images)) {
        $zip->addFile($images, $public . $site_path[1]);
      }
    }

    // close and save archive
    $zip->close();

    //returns the path of the zip
    return $path . $DelFilePath;
  }

  /**
   *  @method:
   *    This method is used to download the project for static sites
   */
  public function _download_json($items) {
    //default variables
    $zip = new ZipArchive();
    $DelFilePath = "project.zip";
    $public = variable_get('file_public_path', 'sites/default/files');
    $path = DRUPAL_ROOT . '/' . $public . '/';

    //ensures that we delete the old file
    if(file_exists($path . $DelFilePath)) {
      unlink ($path . $DelFilePath);
    }

    //creates the zip file and starts to append
    if ($zip->open($path . $DelFilePath, ZIPARCHIVE::CREATE) != TRUE) {
      watchdog('getty project', "Could not open archive at " . print_r($path . $DelFilePath, 1));
    }

    //appends the format requested
    foreach ($items as $id => $output) {
      $zip->addFromString('source/' . $id . '.html.md.erb', $output);
    }

    //does for each image included to download
    foreach ($this->include_images as $key => $images) {
      //ensures that the file exists on the server before adding
      if (file_exists($images)) {
        $zip->addFile($images, 'source/assets/images/' . drupal_basename($images));
      }
    }

    // close and save archive
    $zip->close();

    //returns the path of the zip
    return $path . $DelFilePath;
  }

  /**
   *  @method:
   *    This method is used to retrive a cache from drupal if one is available
   */
  private function _cache($action = 'get', $data = array()) {
    $width = '';

    //sets a cache version
    if (empty($this->cache_id)) {
      $cache_cid = 'no_project_cache';
    }
    else {
      $cache_cid = 'getty_project_cache_' . $this->cache_id . '_' . $this->format;
    }

    //calls the cache time
    $cache_time = variable_get('getty_expose_project_cache_time', 0);

    //switch based on action
    switch ($action) {
      //sets the cached and cache for x minutes
      case 'set':
        $cached = cache_set($cache_cid, $data, 'cache', REQUEST_TIME + ($cache_time * 60));
        break;
      //returns cache if available
      default:
        $cached = cache_get($cache_cid, 'cache');

        if (isset($cached->data)) {
          return $cached->data;
        }
        return $cached;
        break;
    }
  }

  /**
   *  @method:
   *    Private method that is used to load the project node
   */
  private function _load_project_node() {
    $project_nid = $this->project_nid;
    if (is_numeric($project_nid)) {
      $project_node = node_load($project_nid);

      if (is_object($project_node) && isset($project_node->type) && $project_node->type == 'project') {
        $this->project_node = $project_node;
      }
      else {
        $this->project_node = 'NID Provided is not a project';
      }
    }
    else {
      $this->project_node = 'No Project NID Provided';
    }
  }

  /**
   *  @method:
   *    this private method is used to load all content related to a project
   */
  private function _load_project_contents() {
    $contents = array();
    $nids = array();

    $db_result = db_select('og_membership', 'og_content')
      ->fields('og_content', array('etid'));
    $db_result->leftJoin('node', 'n', 'n.nid = og_content.etid');
    $db_result->fields('n', array('type'));
    $db_result->condition('entity_type', 'node', '=');
    $db_result->condition('og_content.gid', $this->project_nid, '=');
    $result = $db_result->execute()->fetchAll();

    //maps the to the correct type
    foreach ($result as $key => $value) {
      $nids[$value->type][] = $value->etid;
    }

    //loads all the nodes
    foreach ($nids as $type => $values) {
      $nids[$type] = node_load_multiple($values);
    }

    return $nids;
  }

  /**
   *  @method:
   *    Process all list of nodes.
   *
   *    This is where all the fields are handled
   */
  private function _parse_nodes($nodes = array()) {
    global $base_url;

    //does for each for each of the node types
    foreach ($nodes as $type => $values) {
      $fields = field_info_instances("node", $type);

      //does for each of the nodes
      foreach ($values as $node => $node_values) {
        //loads all scribe attachment
        $scribe = entity_load('scribe_attachment', FALSE, array('entity_id' => $node_values->nid));
        $nodes[$type][$node]->scribe = $scribe;

        //does for each of the field
        foreach ($fields as $field_name => $field_value) {
          $field_items = field_get_items('node', $node_values, $field_name);

          if (!empty($field_items)) {
            //does for each of them.
            foreach ($field_items as $item => $item_value) {
              switch ($field_value['field_name']) {
                case 'og_group_ref':
                  break;
                //makes the images relative to the node
                case 'field_image':
                case 'field_timeline_media_image':
                  if (!isset($item_value['fid'])) {
                    break;
                  }

                  //changes over to allow the image refence to use the same formatting
                  $item_value['target_id'] = $item_value['fid'];
                case 'field_image_references':

                  //conversion to relative path for images
                  if (isset($item_value['target_id'])) {
                    $fid = (int)$item_value['target_id'];
                    $file = file_load($fid);

                    //only does this for the file if its not empty
                    if (!empty($file)) {
                      $file->server_path = drupal_realpath($file->uri);
                      $file->relative_path = str_replace('public:/', variable_get('file_public_path', 'sites/default/files'), $file->uri);
                      $field_items[$item] = (array)$file;
                      $this->include_images[] = $file->server_path;
                    }
                  }
                  break;
                case 'field_reference':
                  break;
                //handler for the body section
                case 'body':
                  //variables
                  $body_value = $item_value['value'];

                  //does for the following attribtes
                  $this->_add_images_regex('href', $body_value);
                  $this->_add_images_regex('src', $body_value);

                  //does a simple replacement from the domain
                  $field_items[$item]['value'] = str_replace($base_url, '', $field_items[$item]['value']);
                  $field_items[$item]['safe_value'] = str_replace($base_url, '', $field_items[$item]['safe_value']);

                  break;
              }

              $nodes[$type][$node]->$field_name = $field_items;
            }
          }
        }
      }
    }

    return $nodes;
  }

  /**
   *  @method:
   *    This method is used to add the following attr into the images
   */
  private function _add_images_regex($attr = 'href', $haystack) {
    $public_path = variable_get('file_public_path', 'sites/default/files');

    //a attr processing
    $pattern = '/' . $attr . '=["\']?([^"\'>]+)["\']?/';
    preg_match($pattern, $haystack, $matches);
    if (isset($matches[1]) && !empty($matches[1])) {
      $info = parse_url($matches[1]);

      //only need to do on one of the values and not both
      if (!empty($info['path']) && stripos($info['path'], $public_path) !== FALSE && preg_match('/(\.jpg|\.png|\.bmp)$/', $info['path'])) {
        $schema_path = str_replace($public_path, 'public:/', $info['path']);
        $image_path = drupal_realpath(substr($schema_path, 1)); //use substr to remove first /
        $this->include_images[] = $image_path; //adds the image into the included images
      }
    }
  }

  /**
   *  @method:
   *    Simple functionality to convert array to json
   */
  private function _array_to_json($array) {
    include_once DRUPAL_ROOT . '/sites/all/libraries/markdownify/src/Markdownify/Parser.php';
    include_once DRUPAL_ROOT . '/sites/all/libraries/markdownify/src/Markdownify/Converter.php';

    $items = array();

    $nodes = array();
    if (!empty($array->project_node)) $nodes[] = $array->project_node;
    foreach (array('essay', 'manuscript', 'comparison', 'image', 'bibliography') as $type) {
      // Put content in order from page 1 to page n for book export
      if (empty($array->raw_nodes[$type])) continue;
      foreach ($array->raw_nodes[$type] as $node) {
        $nodes[] = $node;
      }
    }

    foreach ($nodes as $i => $node) {
      $rendered = "---
title: '" . str_replace("'", "''", $node->title) . "'
layout: " . ($node->type == 'project' ? 'cover' : 'page') . "
sort_order: $i
---
";
      $rendered .= $this->_node_to_markdown($node);

      if ($i == 0) {
        $id = 'index';
      }
      else {
        $clean_title = trim(preg_replace('/[^a-z]+/i', '-', $node->title), '-');
        $id = "node-{$node->nid}-" . $clean_title;
      }
      $items[$id] = $rendered;
    }

    return $items;
  }

  /**
   *  @method:
   *    Simple functionality that uses another library to convert array to xml
   */
  private function _array_to_xml($array) {
    $array = json_decode(json_encode($array), true);
    $xml = Array2XML::createXML('project', $array);
    return $xml->saveXML();
  }

  /**
   *  @method:
   *    Flatten and render content to a CSV
   */
  private function _array_to_csv($array) {
    $node_types = array_keys($array->raw_nodes);
    array_unshift($node_types, 'project');
    $fields = array();
    $field_names = array();
    foreach ($node_types as $type) {
      $fields[$type] = field_info_instances('node', $type);
      unset($fields[$type]['group_access'], $fields[$type]['group_group'], $fields[$type]['og_group_ref']);
      $field_names = array_merge($field_names, array_keys($fields[$type]));
    }
    $field_names = array_unique($field_names);

    $header = $field_names;
    $rows = array();

    if (!empty($array->project_node)) {
      $rows[] = $this->_csv_node_to_row($array->project_node, $field_names);
    }
    foreach ($array->raw_nodes as $subnodes) {
      foreach ($subnodes as $node) {
        $rows[] = $this->_csv_node_to_row($node, $field_names);
      }
    }

    array_unshift($header, 'title');

    ob_start();

    $fh = fopen('php://output', 'w');
    fputcsv($fh, $header);
    foreach ($rows as $row) {
      fputcsv($fh, $row);
    }
    fclose($fh);

    $csv = ob_get_contents();
    ob_end_clean();

    return $csv;
  }

  function _node_to_markdown($node) {
    $node->page = TRUE;
    $content = node_view($node, ($node->type == 'manuscript' ? 'teaser' : 'full'));
    $content['links']['#access'] = FALSE;
    unset($content['export_link'], $content['#contextual_links']);

    // Set flag for theme layer to identify
    $node->is_export = TRUE;
    $rendered = render($content);

    $converter = new Markdownify\Converter(Markdownify\Converter::LINK_IN_PARAGRAPH, FALSE, FALSE);
    $markdown = strip_tags($converter->parseString($rendered));
    $markdown = str_replace("\xc2\xa0", ' ', $markdown);
    $markdown = preg_replace('/^[ \t]+|[ \t]+$/m', '', $markdown);

    return $markdown;
  }

  private function _csv_node_to_row($node, $field_names) {
    $node_type = $node->type;
    $row = array($node->title);
    foreach ($field_names as $field_name) {
      if (empty($node->{$field_name})) {
        $row[] = '';
        continue;
      }
      $display = array('label' => 'hidden');
      switch ($field_name) {
        case 'field_facsimile':
        case 'field_image':
        case 'field_timeline_media_image':
          $items = array();
          foreach ($node->{$field_name}['und'] as $delta => $item) {
            $url_parts = parse_url(file_create_url('public://timeline_images/600.jpg'));
            $items[] = $url_parts['path'];
          }
          $row[] = implode(', ', $items);
          break;
        default:
          $element = field_view_field('node', $node, $field_name, array('label' => 'hidden'));
          $row[] = strip_tags(render($element));
      }
    }
    return $row;
  }
}
