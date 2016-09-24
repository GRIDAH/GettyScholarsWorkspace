<?php
/**
 * @file
 * bibliography_support.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function bibliography_support_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'clear bibliography feeds'.
  $permissions['clear bibliography feeds'] = array(
    'name' => 'clear bibliography feeds',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'feeds',
  );

  // Exported permission: 'import bibliography feeds'.
  $permissions['import bibliography feeds'] = array(
    'name' => 'import bibliography feeds',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'feeds',
  );

  // Exported permission: 'unlock bibliography feeds'.
  $permissions['unlock bibliography feeds'] = array(
    'name' => 'unlock bibliography feeds',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'feeds',
  );

  return $permissions;
}
