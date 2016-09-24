<?php
/**
 * @file
 * timeline.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function timeline_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_timeline_date';
  $strongarm->value = 0;
  $export['comment_anonymous_timeline_date'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_timeline_date';
  $strongarm->value = 1;
  $export['comment_default_mode_timeline_date'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_timeline_date';
  $strongarm->value = '50';
  $export['comment_default_per_page_timeline_date'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_timeline_date';
  $strongarm->value = 1;
  $export['comment_form_location_timeline_date'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_timeline_date';
  $strongarm->value = '1';
  $export['comment_preview_timeline_date'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_timeline_date';
  $strongarm->value = 1;
  $export['comment_subject_field_timeline_date'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_timeline_date';
  $strongarm->value = '2';
  $export['comment_timeline_date'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__timeline_date';
  $strongarm->value = array(
    'view_modes' => array(
      'teaser' => array(
        'custom_settings' => TRUE,
      ),
      'full' => array(
        'custom_settings' => FALSE,
      ),
      'rss' => array(
        'custom_settings' => FALSE,
      ),
      'search_index' => array(
        'custom_settings' => FALSE,
      ),
      'search_result' => array(
        'custom_settings' => FALSE,
      ),
      'diff_standard' => array(
        'custom_settings' => FALSE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '0',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__timeline_date'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_timeline_date';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_timeline_date'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_timeline_date';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_timeline_date'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_timeline_date';
  $strongarm->value = array(
    0 => 'status',
    1 => 'promote',
  );
  $export['node_options_timeline_date'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_timeline_date';
  $strongarm->value = '0';
  $export['node_preview_timeline_date'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_timeline_date';
  $strongarm->value = 1;
  $export['node_submitted_timeline_date'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'partial_date_component_field_txt_inline_styles';
  $strongarm->value = '';
  $export['partial_date_component_field_txt_inline_styles'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'partial_date_format_long';
  $strongarm->value = array(
    'meridiem' => 'a',
    'year_designation' => 'bce',
    'display' => array(
      'year' => 'estimate_label',
      'month' => 'estimate_label',
      'day' => 'estimate_label',
      'hour' => 'estimate_label',
      'minute' => 'estimate_label',
      'second' => 'estimate_label',
      'timezone' => 'date_only',
    ),
    'separator' => array(
      'date' => ' ',
      'time' => ':',
      'datetime' => ', ',
      'other' => ' ',
      'range' => '',
    ),
    'components' => array(
      'year' => array(
        'format' => 'Y-ce',
        'empty' => '',
        'weight' => '-7',
      ),
      'month' => array(
        'format' => 'F',
        'empty' => '',
        'weight' => '-9',
      ),
      'day' => array(
        'format' => 'j-S',
        'empty' => '',
        'weight' => '-8',
      ),
      'hour' => array(
        'format' => 'h',
        'empty' => '',
        'weight' => '-6',
      ),
      'minute' => array(
        'format' => 'i',
        'empty' => '',
        'weight' => '-5',
      ),
      'second' => array(
        'format' => 's',
        'empty' => '',
        'weight' => '-4',
      ),
      'timezone' => array(
        'format' => 'e',
        'empty' => '',
        'weight' => '-3',
      ),
      'c1' => array(
        'value' => '',
        'weight' => '-2',
      ),
      'c2' => array(
        'value' => '',
        'weight' => '-1',
      ),
      'c3' => array(
        'value' => '',
        'weight' => '0',
      ),
      'approx' => array(
        'value' => '',
        'weight' => '-10',
      ),
    ),
  );
  $export['partial_date_format_long'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'partial_date_format_medium';
  $strongarm->value = array(
    'meridiem' => 'a',
    'year_designation' => 'sign',
    'display' => array(
      'year' => 'date_or',
      'month' => 'date_or',
      'day' => 'date_or',
      'hour' => 'date_or',
      'minute' => 'date_or',
      'second' => 'date_or',
      'timezone' => 'date_only',
    ),
    'separator' => array(
      'date' => '-',
      'time' => ':',
      'datetime' => ' ',
      'other' => ' ',
      'range' => '',
    ),
    'components' => array(
      'year' => array(
        'format' => 'Y-ce',
        'empty' => '',
        'weight' => '0',
      ),
      'month' => array(
        'format' => 'm',
        'empty' => '',
        'weight' => '1',
      ),
      'day' => array(
        'format' => 'd',
        'empty' => '',
        'weight' => '2',
      ),
      'hour' => array(
        'format' => 'H',
        'empty' => '',
        'weight' => '3',
      ),
      'minute' => array(
        'format' => 'i',
        'empty' => '',
        'weight' => '4',
      ),
      'second' => array(
        'format' => 's',
        'empty' => '',
        'weight' => '5',
      ),
      'timezone' => array(
        'format' => 'T',
        'empty' => '',
        'weight' => '6',
      ),
      'c1' => array(
        'value' => '',
        'weight' => '7',
      ),
      'c2' => array(
        'value' => '',
        'weight' => '8',
      ),
      'c3' => array(
        'value' => '',
        'weight' => '9',
      ),
      'approx' => array(
        'value' => '',
        'weight' => '-1',
      ),
    ),
  );
  $export['partial_date_format_medium'] = $strongarm;

  return $export;
}
