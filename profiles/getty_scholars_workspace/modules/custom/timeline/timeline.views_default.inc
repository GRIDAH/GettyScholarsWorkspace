<?php
/**
 * @file
 * timeline.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function timeline_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'project_timeline';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Timeline';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Timeline';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'og_context';
  $handler->display->display_options['access']['perm'] = 'unsubscribe';
  $handler->display->display_options['access']['group_id_arg'] = '1';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
  $handler->display->display_options['exposed_form']['options']['bef'] = array(
    'general' => array(
      'allow_secondary' => 0,
      'secondary_label' => 'Advanced options',
      'collapsible_label' => NULL,
      'combine_rewrite' => NULL,
      'reset_label' => NULL,
    ),
    'secondary_label' => NULL,
    'collapsible_label' => NULL,
    'combine_rewrite' => NULL,
    'reset_label' => NULL,
  );
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'timelinejs';
  $handler->display->display_options['style_options']['timeline_config']['hash_bookmark'] = TRUE;
  $handler->display->display_options['style_options']['timeline_config']['start_at_end'] = 0;
  $handler->display->display_options['style_options']['additional_config']['start_at_current'] = 0;
  $handler->display->display_options['style_options']['timeline_fields']['caption'] = 'field_image_caption';
  $handler->display->display_options['style_options']['timeline_fields']['credit'] = 'field_image_credit';
  $handler->display->display_options['style_options']['timeline_fields']['media'] = 'field_timeline_media_image';
  $handler->display->display_options['style_options']['timeline_fields']['start_date'] = 'field_timeline_start_date';
  $handler->display->display_options['style_options']['timeline_fields']['end_date'] = 'field_timeline_end_date';
  $handler->display->display_options['style_options']['timeline_fields']['display_date'] = 'field_timeline_end_date_1';
  $handler->display->display_options['style_options']['timeline_fields']['text'] = 'body';
  $handler->display->display_options['style_options']['timeline_fields']['headline'] = 'edit_node';
  $handler->display->display_options['style_options']['timeline_fields']['unique_id'] = 'counter';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'There are no timeline dates entered for this project.';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  /* Relationship: OG membership: OG membership from Node */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['required'] = TRUE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '[title][edit_node]';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = '';
  $handler->display->display_options['fields']['edit_node']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['edit_node']['alter']['text'] = '[title]';
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['edit_node']['empty'] = '[title]';
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['type'] = 'text_plain';
  /* Field: Content: Start Date */
  $handler->display->display_options['fields']['field_timeline_start_date']['id'] = 'field_timeline_start_date';
  $handler->display->display_options['fields']['field_timeline_start_date']['table'] = 'field_data_field_timeline_start_date';
  $handler->display->display_options['fields']['field_timeline_start_date']['field'] = 'field_timeline_start_date';
  $handler->display->display_options['fields']['field_timeline_start_date']['click_sort_column'] = 'timestamp';
  $handler->display->display_options['fields']['field_timeline_start_date']['settings'] = array(
    'use_override' => 'none',
    'format' => 'medium',
    'component_settings' => array(
      'meridiem' => 'a',
      'year_designation' => 'ce',
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
          'format' => 'M',
          'empty' => '',
          'weight' => '1',
        ),
        'day' => array(
          'format' => 'j-S',
          'empty' => '',
          'weight' => '2',
        ),
        'hour' => array(
          'format' => 'h',
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
    ),
    'field_formatter_class' => '',
  );
  /* Field: Content: End Date */
  $handler->display->display_options['fields']['field_timeline_end_date']['id'] = 'field_timeline_end_date';
  $handler->display->display_options['fields']['field_timeline_end_date']['table'] = 'field_data_field_timeline_end_date';
  $handler->display->display_options['fields']['field_timeline_end_date']['field'] = 'field_timeline_end_date';
  $handler->display->display_options['fields']['field_timeline_end_date']['click_sort_column'] = 'timestamp';
  $handler->display->display_options['fields']['field_timeline_end_date']['settings'] = array(
    'use_override' => 'none',
    'format' => 'medium',
    'component_settings' => array(
      'meridiem' => 'a',
      'year_designation' => 'ce',
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
          'format' => 'M',
          'empty' => '',
          'weight' => '1',
        ),
        'day' => array(
          'format' => 'j-S',
          'empty' => '',
          'weight' => '2',
        ),
        'hour' => array(
          'format' => 'h',
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
    ),
    'field_formatter_class' => '',
  );
  /* Field: Content: Start Date */
  $handler->display->display_options['fields']['field_timeline_start_date_1']['id'] = 'field_timeline_start_date_1';
  $handler->display->display_options['fields']['field_timeline_start_date_1']['table'] = 'field_data_field_timeline_start_date';
  $handler->display->display_options['fields']['field_timeline_start_date_1']['field'] = 'field_timeline_start_date';
  $handler->display->display_options['fields']['field_timeline_start_date_1']['label'] = 'Human Start Date';
  $handler->display->display_options['fields']['field_timeline_start_date_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_timeline_start_date_1']['click_sort_column'] = 'timestamp';
  $handler->display->display_options['fields']['field_timeline_start_date_1']['settings'] = array(
    'use_override' => 'none',
    'format' => 'long',
    'component_settings' => array(
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
    ),
    'field_formatter_class' => '',
  );
  /* Field: Content: End Date */
  $handler->display->display_options['fields']['field_timeline_end_date_1']['id'] = 'field_timeline_end_date_1';
  $handler->display->display_options['fields']['field_timeline_end_date_1']['table'] = 'field_data_field_timeline_end_date';
  $handler->display->display_options['fields']['field_timeline_end_date_1']['field'] = 'field_timeline_end_date';
  $handler->display->display_options['fields']['field_timeline_end_date_1']['label'] = 'Human End Date';
  $handler->display->display_options['fields']['field_timeline_end_date_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_timeline_end_date_1']['alter']['text'] = '[field_timeline_start_date_1] - [field_timeline_end_date_1]';
  $handler->display->display_options['fields']['field_timeline_end_date_1']['empty'] = '[field_timeline_start_date_1]';
  $handler->display->display_options['fields']['field_timeline_end_date_1']['click_sort_column'] = 'timestamp';
  $handler->display->display_options['fields']['field_timeline_end_date_1']['settings'] = array(
    'use_override' => 'none',
    'format' => 'long',
    'component_settings' => array(
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
    ),
    'field_formatter_class' => '',
  );
  /* Field: Content: Timeline Image */
  $handler->display->display_options['fields']['field_timeline_media_image']['id'] = 'field_timeline_media_image';
  $handler->display->display_options['fields']['field_timeline_media_image']['table'] = 'field_data_field_timeline_media_image';
  $handler->display->display_options['fields']['field_timeline_media_image']['field'] = 'field_timeline_media_image';
  $handler->display->display_options['fields']['field_timeline_media_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_timeline_media_image']['settings'] = array(
    'image_style' => 'large',
    'image_link' => '',
    'field_formatter_class' => '',
  );
  /* Field: Content: Image Caption */
  $handler->display->display_options['fields']['field_image_caption']['id'] = 'field_image_caption';
  $handler->display->display_options['fields']['field_image_caption']['table'] = 'field_data_field_image_caption';
  $handler->display->display_options['fields']['field_image_caption']['field'] = 'field_image_caption';
  $handler->display->display_options['fields']['field_image_caption']['settings'] = array(
    'field_formatter_class' => '',
  );
  /* Field: Content: Image Credit */
  $handler->display->display_options['fields']['field_image_credit']['id'] = 'field_image_credit';
  $handler->display->display_options['fields']['field_image_credit']['table'] = 'field_data_field_image_credit';
  $handler->display->display_options['fields']['field_image_credit']['field'] = 'field_image_credit';
  $handler->display->display_options['fields']['field_image_credit']['settings'] = array(
    'field_formatter_class' => '',
  );
  /* Field: Global: View result counter */
  $handler->display->display_options['fields']['counter']['id'] = 'counter';
  $handler->display->display_options['fields']['counter']['table'] = 'views';
  $handler->display->display_options['fields']['counter']['field'] = 'counter';
  $handler->display->display_options['fields']['counter']['exclude'] = TRUE;
  $handler->display->display_options['fields']['counter']['counter_start'] = '1';
  $handler->display->display_options['fields']['counter']['reverse'] = 0;
  /* Contextual filter: Field: Groups audience (og_group_ref) */
  $handler->display->display_options['arguments']['og_group_ref_target_id']['id'] = 'og_group_ref_target_id';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['field'] = 'og_group_ref_target_id';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['exception']['value'] = '';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'timeline_date' => 'timeline_date',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'project/%/timeline';
  $export['project_timeline'] = $view;

  return $export;
}
