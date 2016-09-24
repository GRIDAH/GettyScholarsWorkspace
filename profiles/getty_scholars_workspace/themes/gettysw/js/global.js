(function($) {
  Drupal.behaviors.gettyswDropdownMenus = {
    attach: function(context) {
      $('.dropdown-container', context).once('gettysw-dropdown-menu', function() {
        var
          timeout,
          $that = $(this)
        ;
        $(this)
          .on('mouseover', function() {
            clearTimeout(timeout);
            $that.addClass('open');
          })
          .on('mouseout', function() {
            clearTimeout(timeout);
            timeout = setTimeout(function() {
              $that.removeClass('open');
            }, 300);
          })
        ;
        $('.dropdown-trigger', this).on('click', function(e) {
          e.preventDefault();
          $that.trigger('mouseover');
        });
      })
    }
  };

  Drupal.behaviors.gettyswShowHide = {
    attach: function(context) {
      $('.show-hide-trigger', context).on('click', function(e) {
        e.preventDefault();
        $(this).closest('.show-hide-container').toggleClass('open');
      });
    }
  };

  Drupal.behaviors.gettyswSticky = {
    attach: function(context) {
      $('.sticky-container', context).once('gettysw-sticky', function() {
        $(this).each(function() {
          var sticky = new Waypoint.Sticky({ element: this });
        });
      });
      $(window).on('resize', function() {
        $('.sticky-wrapper').each(function() {
          $(this).find('.sticky-container').width($(this).width());
        });
      });
      $(window).trigger('resize');
    }
  };

  Drupal.behaviors.gettyswScrollTo = {
    attach: function(context) {
      $('.jump-menu a', context).on('click', function(e) {
        e.preventDefault();
        var target_id = $(this).attr('href').split('#')[1];
        var sticky_height = $('.sticky-container').height();
        var position = $('#' + target_id).offset().top - $('.sticky-container').height() - $('#admin-menu').height() - 10;
        $('html, body').animate({ scrollTop: position }, 300);
      });
    }
  }
})(jQuery)
