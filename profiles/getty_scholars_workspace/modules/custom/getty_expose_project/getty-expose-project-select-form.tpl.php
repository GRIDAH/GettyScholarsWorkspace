<div class="sticky-container">
  <div class="jump-menu">
    Jump to:
    <a href="#section-bibliography">Citations</a>
    |
    <a href="#section-comparison">Comparisons</a>
    |
    <a href="#section-essay">Essays</a>
    |
    <a href="#section-image">Images</a>
    |
    <a href="#section-timeline_date">Timeline Events</a>
    |
    <a href="#section-manuscript">Transcriptions</a>
  </div>
  <?php print render($form['format']) ?>
</div>

<?php print render($form['filter']) ?>

<?php print drupal_render_children($form) ?>
