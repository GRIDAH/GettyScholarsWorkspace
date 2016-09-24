<?php

/**
 *  @function:
 *    Takepart oembed admin form
 */
function getty_expose_project_admin_form($form, &$form_state)  {
  $form = array();

  //intro message
  $form['getty_expose_project_intro'] = array(
    '#markup' => t("
      Configuration for project service for Getty.<br/>
      Flush cache to clear out all stale cache.<br/><br/>
      Uses: service/project/[format=json|xml]?project=[project_nid][&download=1][&break_cache=1]<br/></br>
      format = json or xml<br/>
      break_cache = true to rebuild cache data<br/><br/>
    "),
  );

  //service url
  $form['getty_expose_project_service_url'] = array(
    '#type' => 'textfield',
    '#title' => t('URL Service Path'),
    '#description' => t('URL service. Empty value will disable service for oembed after menu path rebuilds.'),
    '#default_value' => variable_get('getty_expose_project_service_url', 'service/projects')
  );

  //set up cache time
  $form['getty_expose_project_cache_time'] = array(
    '#type' => 'select',
    '#title' => t('Cache Time for API service'),
    '#options' => array(
      0 => 0,
      5 => 5,
      10 => 10,
      15 => 15,
      30 => 30,
      60 => 60
    ),
    '#default_value' => variable_get('getty_expose_project_cache_time', 0)
  );

  return system_settings_form($form);
}

function getty_expose_project_select_form($form, &$form_state, $project_nid) {
  $sections = array(
    'bibliography' => array(
      'name' => t('Citations'),
    ),
    'comparison' => array(
      'name' => t('Comparisons'),
      'extra_fields' => array(
        'image_uri' => array(
          'name' => t('Image References'),
          'query' => array(
            array('leftJoin', array('field_data_field_image_reference_info', 'image_reference_info', 'n.nid = image_reference_info.entity_id')),
            array('leftJoin', array('field_data_field_image_reference', 'image_reference', 'image_reference_info.field_image_reference_info_value = image_reference.entity_id')),
            array('leftJoin', array('file_managed', 'file_image_reference', 'image_reference.field_image_reference_target_id = file_image_reference.fid')),
            array('addField', array('file_image_reference', 'uri', 'image_uri')),
          ),
        ),
      ),
    ),
    'essay' => array(
      'name' => t('Essays'),
    ),
    'image' => array(
      'name' => t('Images'),
      'extra_fields' => array(
        'image_uri' => array(
          'name' => t('Image'),
          'query' => array(
            array('leftJoin', array('field_data_field_image', 'image', 'n.nid = image.entity_id')),
            array('leftJoin', array('file_managed', 'file_image', 'image.field_image_fid = file_image.fid')),
            array('addField', array('file_image', 'uri', 'image_uri')),
          ),
        ),
      ),
    ),
    'timeline_date' => array(
      'name' => t('Timeline Events'),
      'extra_fields' => array(
        'image_uri' => array(
          'name' => t('Image'),
          'query' => array(
            array('leftJoin', array('field_data_field_timeline_media_image', 'timeline_media_image', 'n.nid = timeline_media_image.entity_id')),
            array('leftJoin', array('file_managed', 'file_timeline_media_image', 'timeline_media_image.field_timeline_media_image_fid = file_timeline_media_image.fid')),
            array('addField', array('file_timeline_media_image', 'uri', 'image_uri')),
          ),
        ),
      ),
    ),
    'manuscript' => array(
      'name' => t('Transcriptions'),
    ),
  );

  $users = array();
  $options = array();

  foreach ($sections as $type => $section) {
    $query = db_select('node', 'n');
    $query->join('og_membership', 'og', 'n.nid = og.etid');
    $query->join('users', 'u', 'n.uid = u.uid');
    $query
      ->fields('n', array('nid', 'uid', 'title', 'created'))
      ->fields('u', array('name'))
      ->condition('og.entity_type', 'node')
      ->condition('og.field_name', 'og_group_ref')
      ->condition('og.gid', $project_nid, '=')
      ->condition('n.type', $type)
      ->addTag('node_access')
      ->orderBy('nid', 'ASC')
      ->distinct(TRUE);

    if (!empty($section['extra_fields'])) {
      foreach ($section['extra_fields'] as $field => $info) {
        foreach ($section['extra_fields'][$field]['query'] as $command) {
          call_user_func_array(array($query, $command[0]), $command[1]);
        }
      }
    }

    $result = $query->execute()->fetchAll();
    foreach ($result as $row) {
      $users[$row->uid] = $row->name;
    }

    $options[$type]['header'] = array();
    $options[$type]['header']['title'] = t('Title');
    if (!empty($section['extra_fields'])) {
      foreach ($section['extra_fields'] as $field => $info) {
        $options[$type]['header'][$field] = $info['name'];
      }
    }
    $options[$type]['header']['created'] = t('Date Created');
    $options[$type]['header']['name'] = t('User');

    foreach ($result as $row) {
      if (empty($options[$type]['rows'][$row->nid])) {
        $options[$type]['rows'][$row->nid] = array();
      }
      $options[$type]['rows'][$row->nid]['title'] = l($row->title, 'node/' . $row->nid);
      if (!empty($section['extra_fields'])) {
        foreach ($section['extra_fields'] as $field => $info) {
          $rendered = $row->{$field};
          if ($field == 'image_uri') {
            $rendered = theme('image_style', array('style_name' => 'thumbnail', 'path' => $row->{$field}));
          }
          if (empty($options[$type]['rows'][$row->nid][$field])) {
            $options[$type]['rows'][$row->nid][$field] = $rendered;
          }
          else {
            $options[$type]['rows'][$row->nid][$field] .= ' ' . $rendered;
          }
        }
      }
      $options[$type]['rows'][$row->nid]['created'] = date('n/j/Y', $row->created);
      $options[$type]['rows'][$row->nid]['name'] = l($row->name, 'user/' . $row->uid);
      $options[$type]['rows'][$row->nid]['#attributes']['data-author'] = $row->uid;
    }
  }

  $form = array();

  $form['format'] = array(
    '#prefix' => '
      <div class="export-menu dropdown-container">
        <a href="#" class="dropdown-trigger">Export</a>
        <div class="dropdown-content">
    ',
    '#suffix' => '
        </div>
      </div>
    ',
    '#options' => array(),
  );
  $form['format']['json'] = array(
    '#type' => 'submit',
    '#value' => t('JSON'),
  );
  $form['format']['csv'] = array(
    '#type' => 'submit',
    '#value' => t('CSV'),
  );
  $form['format']['xml'] = array(
    '#type' => 'submit',
    '#value' => t('XML'),
  );

  $form['filter'] = array(
    '#type' => 'fieldset',
    '#title' => t('Show only:'),
    '#collapsible' => FALSE,
  );
  $form['filter']['content_type'] = array(
    '#type' => 'select',
    '#multiple' => TRUE,
    '#options' => array(
      'bibliography' => t('Citations'),
      'comparison' => t('Comparisons'),
      'essay' => t('Essays'),
      'image' => t('Images'),
      'timeline_date' => t('Timeline Events'),
      'manuscript' => t('Transcriptions'),
    ),
    '#attributes' => array(
      'data-placeholder' => t('- Select Content Type -'),
    ),
  );
  $form['filter']['users'] = array(
    '#type' => 'select',
    '#multiple' => TRUE,
    '#options' => $users,
    '#attributes' => array(
      'data-placeholder' => t('- Select User -'),
    ),
  );
  $form['filter']['search'] = array(
    '#type' => 'textfield',
    '#attributes' => array('placeholder' => t('Enter search terms')),
  );

  $form['nids'] = array('#tree' => TRUE);
  foreach ($sections as $type => $group) {
    if (empty($options[$type]['rows'])) {
      continue;
    }
    $form['nids'][$type] = array(
      '#type' => 'tableselect',
      '#header' => $options[$type]['header'],
      '#prefix' => '<div class="type-container" id="section-' . $type . '"><h3>' . $group['name'] . '</h3>',
      '#suffix' => '</div>',
      '#options' => $options[$type]['rows'],
      '#attributes' => array(
        'class' => array( 'tableheader-processed' ),
      ),
    );
  }

  return $form;
}
