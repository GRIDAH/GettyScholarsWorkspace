<?php
$show_annotation_help = FALSE;
if (in_array($type, array('essay', 'manuscript')) && empty($node->is_export)) {
  if (@ $gid = $og_group_ref[LANGUAGE_NONE][0]['target_id']) {
    $show_annotation_help = og_user_access('node', $gid, 'create annotation');
  }
}
?>
<article<?php print $attributes; ?>>
  <?php print render($title_prefix); ?>
  <?php if (!$page && $title): ?>
  <header>
    <h2<?php print $title_attributes; ?>><a href="<?php print $node_url ?>" title="<?php print $title ?>"><?php print $title ?></a></h2>
  </header>
  <?php endif; ?>
  <?php print render($title_suffix); ?>

  <div<?php print $content_attributes; ?>>
    <?php if ($show_annotation_help): ?>
      <div class ="annotation-help">Click and drag to annotate text.</div>
    <?php endif ?>
    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      print render($content);
    ?>
  </div>

  <?php if ($display_submitted): ?>
  <footer class="submitted"><?php print $submitted; ?></footer>
  <?php endif; ?>

  <div class="clearfix">
    <?php if (!empty($content['links'])): ?>
      <nav class="links node-links clearfix"><?php print render($content['links']); ?></nav>
    <?php endif; ?>

    <?php print render($content['comments']); ?>
  </div>
</article>
