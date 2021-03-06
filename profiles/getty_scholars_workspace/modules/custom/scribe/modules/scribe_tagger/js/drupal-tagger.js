// Generated by CoffeeScript 1.6.2
(function() {
  var $, Settings, _ref,
    __bind = function(fn, me){ return function(){ return fn.apply(me, arguments); }; },
    __hasProp = {}.hasOwnProperty,
    __extends = function(child, parent) { for (var key in parent) { if (__hasProp.call(parent, key)) child[key] = parent[key]; } function ctor() { this.constructor = child; } ctor.prototype = parent.prototype; child.prototype = new ctor(); child.__super__ = parent.prototype; return child; };

  $ = jQuery;

  Settings = Drupal.settings.scribe_tagger;

  if (typeof Annotator === "undefined" || Annotator === null) {
    return;
  }

  Annotator.Plugin.DrupalTags = (function(_super) {
    __extends(DrupalTags, _super);

    function DrupalTags() {
      this.setAnnotationTags = __bind(this.setAnnotationTags, this);
      this.updateField = __bind(this.updateField, this);      _ref = DrupalTags.__super__.constructor.apply(this, arguments);
      return _ref;
    }

    DrupalTags.prototype.options = {
      parseTags: function(string) {
        var tags;

        string = $.trim(string);
        tags = [];
        if (string) {
          tags = string.split(/,\s*/);
        }
        return tags;
      },
      stringifyTags: function(array) {
        return array.join(",");
      }
    };

    DrupalTags.prototype.field = null;

    DrupalTags.prototype.input = null;

    DrupalTags.prototype.pluginInit = function() {
      if (!Annotator.supported()) {
        return;
      }
      this.field = this.annotator.editor.addField({
        label: Annotator._t('Add some tags here') + '\u2026',
        load: this.updateField,
        submit: this.setAnnotationTags
      });
      this.annotator.viewer.addField({
        load: this.updateViewer
      });
      if (this.annotator.plugins.Filter) {
        this.annotator.plugins.Filter.addFilter({
          label: Annotator._t('Tag'),
          property: 'tags',
          isFiltered: Annotator.Plugin.Tags.filterCallback
        });
      }
      return this.input = $(this.field).find(':input');
    };

    DrupalTags.prototype.parseTags = function(string) {
      return this.options.parseTags(string);
    };

    DrupalTags.prototype.stringifyTags = function(array) {
      return this.options.stringifyTags(array);
    };

    DrupalTags.prototype.updateField = function(field, annotation) {
      var value;

      value = '';
      if (annotation.tags) {
        value = this.stringifyTags(annotation.tags);
      }
      return this.input.val(value);
    };

    DrupalTags.prototype.setAnnotationTags = function(field, annotation) {
      return annotation.field_annotation_tags = this.tagListToReferences(this.input.val());
    };

    DrupalTags.prototype.updateViewer = function(field, annotation) {
      field = $(field);
      if (annotation.tags && $.isArray(annotation.tags) && annotation.tags.length) {
        return field.addClass('annotator-tags').html(function() {
          var string;

          return string = $.map(annotation.tags, function(tag) {
            return '<span class="annotator-tag">' + Annotator.$.escape(tag) + '</span>';
          }).join(' ');
        });
      } else {
        return field.remove();
      }
    };

    DrupalTags.prototype.tagListToReferences = function(list) {
      var submitTerms, term, terms, _i, _len;

      submitTerms = [];
      terms = this.options.parseTags(list);
      for (_i = 0, _len = terms.length; _i < _len; _i++) {
        term = terms[_i];
        if (Settings.term_map[term] != null) {
          submitTerms.push({
            id: Settings.term_map[term],
            name: term,
            machine_name: Settings.vocabulary.machine_name,
            vocabulary: {
              vid: Settings.vocabulary.vid
            }
          });
        }
      }
      return submitTerms;
    };

    return DrupalTags;

  })(Annotator.Plugin);

  Annotator.Plugin.Tags.filterCallback = function(input, tags) {
    var keyword, keywords, matches, tag, _i, _j, _len, _len1;

    if (tags == null) {
      tags = [];
    }
    matches = 0;
    keywords = [];
    if (input) {
      keywords = input.split(/\s+/g);
      for (_i = 0, _len = keywords.length; _i < _len; _i++) {
        keyword = keywords[_i];
        if (tags.length) {
          for (_j = 0, _len1 = tags.length; _j < _len1; _j++) {
            tag = tags[_j];
            if (tag.indexOf(keyword) !== -1) {
              matches += 1;
            }
          }
        }
      }
    }
    return matches === keywords.length;
  };

}).call(this);
