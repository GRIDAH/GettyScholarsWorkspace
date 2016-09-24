<?php
if (!empty($row->{'field_' . $field->field})) {
  $raw_date = $row->{'field_' . $field->field}[0]['raw']['from'];
  $year = (int) $raw_date['year'];
  $month = !empty($raw_date['month']) ? (int) $raw_date['month'] : 1;
  $day = !empty($raw_date['day']) ? (int) $raw_date['day'] : 1;
  if ($year > 9999) {
    $year = 9999;
  }
  elseif ($year < -9999) {
    $year = -9999;
  }
  $output = sprintf("%+05d-%02d-%02d", $year, $month, $day);
}
?>
<?php print $output ?>
