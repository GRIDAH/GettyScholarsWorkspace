(function($) {

Drupal.behaviors.exposeProjectSelectForm = {
	attach: function(context) {
    var $form = $('#getty-expose-project-select-form', context);
    var $tables = $('#getty-expose-project-select-form table:not(.sticky-header)', $form);

    // Data Tables for sorting
    $tables.each(function() {
      var columns = [];
      var sortable_cols = ['Title', 'Date Created', 'User'];
      $('th', this).each(function(i) {
        columns[i] = {};
        columns[i].orderable = (sortable_cols.indexOf($(this).text().trim()) !== -1);
      });
      $(this).dataTable({
        paging: false,
        searching: false,
        info: false,
        columns: columns
      });
    });

    // Chosen
    $('#edit-filter select').chosen();

    $('#edit-filter').find('input, select').on('change keyup', function() {
      $('.type-container, tr[data-author]', $form).show();

      // Content type filter
      var content_type = $('.form-item-content-type select', $form).val();
      if ((content_type != null) && !(content_type.length == 1 && content_type[0] == "")) {
        $('.type-container', $form).hide();
        content_type.forEach(function(key) {
          $('#section-' + key).show();
        });
      }

      // Author filter
      var author = $('.form-item-users select', $form).val();
      if ((author != null) && !(author.length == 1 && author[0] == "")) {
        $('tr[data-author]', $form).hide();
        author.forEach(function(key) {
          $('tr[data-author=' + key + ']').show();
        });
      }

      // Search filter
      var search_text = $('.form-item-search input', $form).val();
      if (search_text.length > 0) {
        $('tr[data-author]:visible').each(function() {
          if ($(this).text().toLowerCase().search(search_text.toLowerCase()) == -1) {
            $(this).hide();
          }
        })
      }

      $('.type-container:not(:has(tr[data-author]:visible))', $form).hide();
    });
	}
};

})(jQuery);
