(function($) {
  Drupal.behaviors.uploadImagesPage = {
    attach: function(context) {
      $('#upload-images-page', context).once('upload-images-page', function() {
        var
          $container = $(this),
          $messageContainer = $('.messages'),
          $splashPage = $('#upload-images-page-splash'),
          $splashFileButton = $('#upload-images-page-splash a'),
          $cancelButton = $('#upload-images-page-cancel'),
          $addButton = $('#upload-images-page-add'),
          $removeButton = $('#upload-images-page-remove'),
          $selectAllButton = $('#upload-images-page-select-all'),
          $deselectAllButton = $('#upload-images-page-deselect-all'),
          $submitButton = $('#upload-images-page-submit'),
          $contentContainer = $('#upload-images-page-edit .content-container'),
          $itemContainer = $('#upload-images-content'),
          $itemTemplate = $('#upload-images-page-template .item'),
          $editingMessage = $('#upload-images-page-form .editing-message'),
          $fieldTitle = $('#field-title'),
          $fieldCaption = $('#field-caption'),
          $fieldCreator = $('#field-creator'),
          $fieldCreationDate = $('#field-creation_date'),
          $fieldMedium = $('#field-medium'),
          $fieldDimensions = $('#field-dimensions'),
          $fieldLocation = $('#field-location'),
          $fieldDescription = $('#field-description'),
          $fileContainer = $('#upload-images-page-files')
        ;


        // Selecting items
        $contentContainer.on('click', function(e) {
          e.stopPropagation();
          e.preventDefault();
          $deselectAllButton.trigger('click');
        });
        $itemTemplate.on('click', function(e) {
          e.stopPropagation();
          e.preventDefault();
          saveEditStatus();
          if (!e.metaKey) {
            // Non command-click. Remove all items so only one gets selected.
            $itemContainer.find('.item').removeClass('selected');
          }
          $(this).toggleClass('selected');
          $messageContainer.empty();
          updateEditStatus();
        });
        $itemTemplate.find('input[type="text"]')
          .on('focus', function(e) {
            $(this).closest('.item').trigger('click');
          })
          .on('blur', function(e) {
            $fieldTitle.val($(this).val());
          })
        ;
        $fieldTitle.on('blur', function() {
          $itemContainer.find('.selected input[type="text"]').val($fieldTitle.val());
        });
        $selectAllButton.on('click', function(e) {
          e.stopPropagation();
          e.preventDefault();
          saveEditStatus();
          $itemContainer.find('.item').addClass('selected');
          updateEditStatus();
        });
        $deselectAllButton.on('click', function(e) {
          e.stopPropagation();
          e.preventDefault();
          saveEditStatus();
          $itemContainer.find('.item').removeClass('selected');
          updateEditStatus();
        });

        function saveEditStatus() {
          var fieldMap = {
            'title': $fieldTitle,
            'caption': $fieldCaption,
            'creator': $fieldCreator,
            'creation_date': $fieldCreationDate,
            'medium': $fieldMedium,
            'dimensions': $fieldDimensions,
            'location': $fieldLocation,
            'description': $fieldDescription
          };
          for (var name in fieldMap) {
            var $field = fieldMap[name];
            $itemContainer.find('.selected input[name="' + name + '[]"]').each(function(i) {
              if ($field.attr('disabled')) return;
              $(this).val($field.val());
            });
          }
        }

        function updateEditStatus() {
          var selected_count = $itemContainer.find('.selected').length;
          $container.toggleClass('has-selection', selected_count > 0);
          $editingMessage.text(selected_count <= 1 ? 'Editing 1 image' : 'Editing ' + selected_count + ' images');

          // Save form values to selected

          // Load new selection into form
          var fieldMap = {
            'title': $fieldTitle,
            'caption': $fieldCaption,
            'creator': $fieldCreator,
            'creation_date': $fieldCreationDate,
            'medium': $fieldMedium,
            'dimensions': $fieldDimensions,
            'location': $fieldLocation,
            'description': $fieldDescription
          };
          for (var name in fieldMap) {
            var $field = fieldMap[name];
            $field.val('').attr('disabled', false);
            $itemContainer.find('.selected input[name="' + name + '[]"]').each(function(i) {
              if (i == 0) {
                $field.val($(this).val());
                return;
              }
              if ($field.val() != $(this).val()) {
                $field.val('multiple values').attr('disabled', true);
                return false;
              }
            });
          }
        }


        // Adding images
        $splashFileButton.on('click', function(e) {
          e.stopPropagation();
          e.preventDefault();
          $addButton.trigger('click');
        });
        $addButton.on('click', function(e) {
          e.stopPropagation();
          e.preventDefault();
          $deselectAllButton.trigger('click');
          var $newFileElement = $('<input type="file" multiple accept="image/*">').on('change', function() {
            handleFiles(this.files);
            $(this).remove();
          });
          $newFileElement
            .appendTo($fileContainer)
            .trigger('click')
          ;
        });


        // Removing images
        $removeButton.on('click', function(e) {
          e.stopPropagation();
          e.preventDefault();
          $itemContainer.find('.selected').remove();
          if ($itemContainer.find('.item').length == 0) {
            $container.removeClass('has-images');
          }
          $deselectAllButton.trigger('click');
        });
        $cancelButton.on('click', function(e) {
          e.stopPropagation();
          e.preventDefault();
          $selectAllButton.trigger('click');
          $removeButton.trigger('click');
        });


        // File drag & drop
        $splashPage.on('dragenter dragover', function(e) {
          e.stopPropagation();
          e.preventDefault();
        });
        $splashPage.on('drop', function(e) {
          e.stopPropagation();
          e.preventDefault();
          handleFiles(e.originalEvent.dataTransfer.files);
        });

        function handleFiles(files) {
          for (var i = 0; i < files.length; i++) {
            addNewItem(files[i]);
          }
        }

        function addNewItem(file) {
          var $newItem = $itemTemplate.clone(true);
          $newItem
            .data('file', file)
            .prependTo($itemContainer)
          ;
          var reader = new FileReader();
          reader.onload = (function($thumbnail) {
            return function(e) {
              $thumbnail.css('background-image', 'url("' + e.target.result + '")');
            };
          })($newItem.find('.thumbnail'));
          reader.readAsDataURL(file);
          $container.addClass('has-images');
          return $newItem;
        }


        // Form submit
        $submitButton.on('click', function(e) {
          e.stopPropagation();
          e.preventDefault();

          if ($(this).is('.disabled')) return;
          $deselectAllButton.trigger('click');
          if (validateInput() === false) return;

          $(this).addClass('loading disabled');
          $itemTemplate.remove();

          var uploadQueue = [];
          var totalUploaded = 0;

          $itemContainer.find('.item').each(function() {
            var that = this;
            var formData = new FormData($(this).find('form')[0]);
            formData.append('files[]', $(this).data('file'));
            uploadQueue.push({
              url: location.pathname,
              type: 'POST',
              data: formData,
              processData: false,
              contentType: false,
              success: function(data, textStatus, jqXHR) {
                totalUploaded++;
                $(that).addClass('uploaded');
                if (uploadQueue.length > 0) {
                  $.ajax(uploadQueue.shift());
                }
                else {
                  window.location = Drupal.settings.basePath + location.pathname.match(/project\/\d+\/images/)[0] + '?u=' + totalUploaded;
                }
              }
            });
          });

          if (uploadQueue.length > 0) {
            $.ajax(uploadQueue.shift());
          }
        });

        function validateInput() {
          var $items = $itemContainer.find('input[name="title[]"]');
          for (var i = 0; i < $items.length; i++) {
            if ($items.eq(i).val() == '') {
              $messageContainer.html('Field <em>Title</em> is required for all uploads.</div>');
              return false;
            }
          }
        }
      });
    }
  }
})(jQuery);
