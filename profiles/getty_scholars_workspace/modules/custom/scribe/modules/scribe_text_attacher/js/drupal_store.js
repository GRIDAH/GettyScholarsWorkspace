// Generated by CoffeeScript 1.7.1
(function() {
  var $, Range, Scribe,
    __bind = function(fn, me){ return function(){ return fn.apply(me, arguments); }; },
    __hasProp = {}.hasOwnProperty,
    __extends = function(child, parent) { for (var key in parent) { if (__hasProp.call(parent, key)) child[key] = parent[key]; } function ctor() { this.constructor = child; } ctor.prototype = parent.prototype; child.prototype = new ctor(); child.__super__ = parent.prototype; return child; },
    __indexOf = [].indexOf || function(item) { for (var i = 0, l = this.length; i < l; i++) { if (i in this && this[i] === item) return i; } return -1; };

  $ = jQuery;

  Scribe = Drupal.settings.scribe;

  Range = Annotator.Range;

  Annotator.Plugin.DrupalStore = (function(_super) {
    __extends(DrupalStore, _super);

    DrupalStore.prototype.events = {
      'annotationCreated': 'annotationCreated',
      'annotationDeleted': 'annotationDeleted',
      'annotationUpdated': 'annotationUpdated'
    };

    DrupalStore.prototype.fields = {
      annotation: ['text', 'annotation_id', 'type', 'parent_id', 'field_parent_ref'],
      attachment: ['attachment_id', 'entity_id', 'entity_type', 'bundle', 'field_name'],
      text_attachment_info: ['quote', 'ranges', 'annotator_schema_version']
    };

    DrupalStore.prototype.options = {
      annotationType: 'text',
      annotationData: {},
      urls: {
        create: Drupal.settings.basePath + 'scribe_annotation.json',
        create_attachment: Drupal.settings.basePath + 'scribe_attachment.json',
        read: Drupal.settings.basePath + 'scribe_annotation.json/:id',
        update: Drupal.settings.basePath + 'scribe_annotation.json/:id',
        update_attachment: Drupal.settings.basePath + 'scribe_attachment.json/:id',
        destroy: Drupal.settings.basePath + 'scribe_annotation.json/:id',
        destroy_attachment: Drupal.settings.basePath + 'scribe_attachment.json/:id',
        search: Drupal.settings.basePath + 'scribe_attachment.json'
      }
    };

    function DrupalStore(element, options) {
      this._onError = __bind(this._onError, this);
      this._onLoadAnnotationsFromSearch = __bind(this._onLoadAnnotationsFromSearch, this);
      this._onLoadAnnotations = __bind(this._onLoadAnnotations, this);
      this.scribePrepareData = __bind(this.scribePrepareData, this);
      this._getAnnotations = __bind(this._getAnnotations, this);
      DrupalStore.__super__.constructor.apply(this, arguments);
      this.annotations = [];
    }

    DrupalStore.prototype.pluginInit = function() {
      if (!Annotator.supported()) {
        return;
      }
      this.annotator.setupAnnotation = this.setupAnnotation;
      this._getAnnotations();
      return this.annotator.onEditorSubmit = this.onEditorSubmit;
    };

    DrupalStore.prototype.onEditorSubmit = function(annotation) {
      this.publish('annotationEditorSubmit', [this.editor, annotation]);
      if (annotation.annotation_id == null) {
        return this.setupAnnotation(annotation);
      } else {
        return this.updateAnnotation(annotation);
      }
    };

    DrupalStore.prototype.setupAnnotation = function(annotation, fireEvents) {
      var $field, annotation_entity_id, data, e, entity_data, entity_id, normed, normedRanges, r, root, _i, _j, _k, _len, _len1, _len2, _ref;
      if (fireEvents == null) {
        fireEvents = true;
      }
      root = this.wrapper[0];
      annotation.ranges || (annotation.ranges = this.selectedRanges);
      if (annotation.attachment_id) {
        $field = $(this.wrapper.context).parent();
        entity_data = ['entity_type', 'bundle', 'field_name'];
        for (_i = 0, _len = entity_data.length; _i < _len; _i++) {
          data = entity_data[_i];
          if ($field.data(data) !== annotation[data]) {
            return annotation;
          }
        }
        entity_id = Number($field.data('entity_id'));
        annotation_entity_id = Number(annotation.entity_id);
        if (entity_id !== annotation_entity_id) {
          return annotation;
        }
      }
      normedRanges = [];
      _ref = annotation.ranges;
      for (_j = 0, _len1 = _ref.length; _j < _len1; _j++) {
        r = _ref[_j];
        try {
          normedRanges.push(Range.sniff(r).normalize(root));
        } catch (_error) {
          e = _error;
          if (e instanceof Range.RangeError) {
            this.publish('rangeNormalizeFail', [annotation, r, e]);
          } else {
            throw e;
          }
        }
      }
      annotation.quote = [];
      annotation.ranges = [];
      annotation.highlights = [];
      for (_k = 0, _len2 = normedRanges.length; _k < _len2; _k++) {
        normed = normedRanges[_k];
        annotation.quote.push($.trim(normed.text()));
        annotation.ranges.push(normed.serialize(this.wrapper[0], '.annotator-hl'));
        $.merge(annotation.highlights, this.highlightRange(normed));
      }
      annotation.quote = annotation.quote.join(' / ');
      $(annotation.highlights).data('annotation', annotation);
      if (fireEvents) {
        this.publish('annotationCreated', [annotation]);
      }
      return annotation;
    };

    DrupalStore.prototype._getAnnotations = function() {
      var annotations;
      annotations = [];
      $.each(Scribe.attachments, function(index) {
        if (this.type === 'text') {
          $.extend(this, this.text_attachment_info);
          delete this.text_attachment_info;
          $.extend(this, this.annotation);
          delete this.annotation;
          return annotations.push(this);
        }
      });
      this.annotations = this.annotations.concat(annotations);
      return this.annotator.loadAnnotations(annotations);
    };

    DrupalStore.prototype.scribePrepareData = function(type, annotation) {
      var attachmentKey, field, new_obj, _i, _len, _ref;
      attachmentKey = this.options.annotationType + '_attachment_info';
      new_obj = {};
      _ref = this.fields[type];
      for (_i = 0, _len = _ref.length; _i < _len; _i++) {
        field = _ref[_i];
        if (annotation[field] != null) {
          new_obj[field] = annotation[field];
        }
      }
      if (type === 'attachment') {
        $.extend(new_obj, this.scribeEntityData(annotation));
        new_obj[attachmentKey] = this.scribePrepareData(attachmentKey, annotation);
      }
      if (new_obj.annotation_create != null) {
        delete new_obj.annotation_create;
      }
      new_obj.type = this.options.annotationType;
      return new_obj;
    };

    DrupalStore.prototype.scribeEntityData = function(annotation) {
      var field;
      field = $(annotation.highlights[0]).parents('.field');
      return field.data();
    };

    DrupalStore.prototype.annotationCreated = function(annotation) {
      var annotation_data, attachment_data;
      if (__indexOf.call(this.annotations, annotation) < 0) {
        if (annotation.parent_id == null) {
          this.registerAnnotation(annotation);
        }
        annotation_data = this.scribePrepareData('annotation', annotation);
        attachment_data = this.scribePrepareData('attachment', annotation);
        if (!annotation_data.parent_id) {
          return this._apiRequest('create_attachment', attachment_data, (function(_this) {
            return function(attach_data) {
              annotation_data.field_parent_ref = attach_data;
              return _this._apiRequest('create', annotation_data, function(data) {
                _this.updateAnnotation(annotation, data);
                if (data.id == null) {
                  return console.warn(Annotator._t("Warning: No ID returned from server for annotation "), annotation);
                }
              });
            };
          })(this));
        } else {
          return this._apiRequest('create', annotation_data, (function(_this) {
            return function(data) {
              return _this.updateAnnotation(annotation, data);
            };
          })(this));
        }
      } else {
        return this.updateAnnotation(annotation, {});
      }
    };

    DrupalStore.prototype.annotationUpdated = function(annotation) {
      var updated_annotation;
      if (__indexOf.call(this.annotations, annotation) >= 0 || (annotation.parent_id != null)) {
        updated_annotation = this.scribePrepareData('annotation', annotation);
        return this._apiRequest('update', updated_annotation, ((function(_this) {
          return function(data) {
            return _this.updateAnnotation(annotation, data);
          };
        })(this)));
      }
    };

    DrupalStore.prototype.annotationDeleted = function(annotation) {
      var annotation_data, attachment_data;
      if ((annotation.parent_id != null) && (parseInt(annotation.parent_id, 10) !== 0)) {
        annotation_data = this.scribePrepareData('annotation', annotation);
        return this._apiRequest('destroy', annotation_data);
      } else if (__indexOf.call(this.annotations, annotation) >= 0) {
        attachment_data = this.scribePrepareData('attachment', annotation);
        return this._apiRequest('destroy_attachment', attachment_data, ((function(_this) {
          return function() {
            return _this.unregisterAnnotation(annotation);
          };
        })(this)));
      }
    };

    DrupalStore.prototype.registerAnnotation = function(annotation) {
      return this.annotations.push(annotation);
    };

    DrupalStore.prototype.unregisterAnnotation = function(annotation) {
      return this.annotations.splice(this.annotations.indexOf(annotation), 1);
    };

    DrupalStore.prototype.updateAnnotation = function(annotation, data) {
      var tag, _i, _len, _ref;
      if (annotation.parent_id == null) {
        if (__indexOf.call(this.annotations, annotation) < 0) {
          console.error(Annotator._t("Trying to update unregistered annotation!"));
        } else {
          if (data.resource === 'scribe_annotation') {
            data.annotation_id = data.id;
          } else if (data.resource === 'scribe_attachment') {
            data.attachment_id = data.id;
          }
          delete data.id;
          $.extend(annotation, data);
        }
        if (annotation.type == null) {
          annotation.type = this.options.annotationType;
        }
      } else {
        data.annotation_id = data.id;
        delete data.id;
        $.extend(annotation, data);
      }
      if (annotation.field_annotation_tags != null) {
        annotation.tags = [];
        _ref = annotation.field_annotation_tags;
        for (_i = 0, _len = _ref.length; _i < _len; _i++) {
          tag = _ref[_i];
          annotation.tags.push(tag.name);
        }
      }
      return this.updateAnnotationData(annotation);
    };

    DrupalStore.prototype.updateAnnotationData = function(annotation) {
      return $(annotation.highlights).data('annotation', annotation);
    };

    DrupalStore.prototype.loadAnnotations = function() {
      return this._apiRequest('read', null, this._onLoadAnnotations);
    };

    DrupalStore.prototype._onLoadAnnotations = function(data) {
      if (data == null) {
        data = [];
      }
      this.annotations = this.annotations.concat(data);
      return this.annotator.loadAnnotations(data.list);
    };

    DrupalStore.prototype.loadAnnotationsFromSearch = function(searchOptions) {
      return this._apiRequest('search', searchOptions, this._onLoadAnnotationsFromSearch);
    };

    DrupalStore.prototype._onLoadAnnotationsFromSearch = function(data) {
      if (data == null) {
        data = {};
      }
      return this._onLoadAnnotations(data.rows || []);
    };

    DrupalStore.prototype.dumpAnnotations = function() {
      var ann, _i, _len, _ref, _results;
      _ref = this.annotations;
      _results = [];
      for (_i = 0, _len = _ref.length; _i < _len; _i++) {
        ann = _ref[_i];
        _results.push(JSON.parse(this._dataFor(ann)));
      }
      return _results;
    };

    DrupalStore.prototype._apiRequest = function(action, obj, onSuccess) {
      var id, options, request, url;
      if (obj.attachment_id) {
        id = obj.attachment_id;
      } else if (obj.annotation_id) {
        id = obj.annotation_id;
      } else {
        id = obj && obj.id;
      }
      url = this._urlFor(action, id);
      options = this._apiRequestOptions(action, obj, onSuccess);
      request = $.ajax(url, options);
      request._id = id;
      request._action = action;
      return request;
    };

    DrupalStore.prototype._apiRequestOptions = function(action, obj, onSuccess) {
      var data, headers, method, opts;
      method = this._methodFor(action);
      headers = {
        'X-CSRF-Token': Drupal.settings.scribe.csrf_token
      };
      opts = {
        type: method,
        headers: headers,
        dataType: "json",
        success: onSuccess || function() {},
        error: this._onError
      };
      if (this.options.emulateHTTP && (method === 'PUT' || method === 'DELETE')) {
        opts.headers = $.extend(opts.headers, {
          'X-HTTP-Method-Override': method
        });
        opts.type = 'POST';
      }
      if (action === "search") {
        opts = $.extend(opts, {
          data: obj
        });
        return opts;
      }
      data = obj && this._dataFor(obj);
      if (this.options.emulateJSON) {
        opts.data = {
          json: data
        };
        if (this.options.emulateHTTP) {
          opts.data._method = method;
        }
        return opts;
      }
      opts = $.extend(opts, {
        data: data,
        contentType: "application/json; charset=utf-8"
      });
      return opts;
    };

    DrupalStore.prototype._urlFor = function(action, id) {
      var url;
      url = this.options.prefix != null ? this.options.prefix : '';
      url += this.options.urls[action];
      url = url.replace(/\/:id/, id != null ? '/' + id : '');
      url = url.replace(/:id/, id != null ? id : '');
      return url;
    };

    DrupalStore.prototype._methodFor = function(action) {
      var table;
      table = {
        'create': 'POST',
        'create_attachment': 'POST',
        'read': 'GET',
        'update': 'PUT',
        'update_attachment': 'PUT',
        'destroy': 'DELETE',
        'destroy_attachment': 'DELETE',
        'search': 'GET'
      };
      return table[action];
    };

    DrupalStore.prototype._dataFor = function(annotation) {
      var data, highlights;
      highlights = annotation.highlights;
      delete annotation.highlights;
      $.extend(annotation, this.options.annotationData);
      data = JSON.stringify(annotation);
      if (highlights) {
        annotation.highlights = highlights;
      }
      return data;
    };

    DrupalStore.prototype._onError = function(xhr) {
      var action, message;
      action = xhr._action;
      message = Annotator._t("Sorry we could not ") + action + Annotator._t(" this annotation");
      if (xhr._action === 'search') {
        message = Annotator._t("Sorry we could not search the store for annotations");
      }
      switch (xhr.status) {
        case 401:
          message = Annotator._t("Sorry you are not allowed to ") + action + Annotator._t(" this annotation");
          break;
        case 500:
          message = Annotator._t("Sorry something went wrong with the annotation store");
      }
      if (xhr.status !== 404) {
        Annotator.showNotification(message, Annotator.Notification.ERROR);
        return console.error(Annotator._t("API request failed:") + (" '" + xhr.status + "'"));
      } else {
        return console.log(Annotator._t("No annotations were found on this page."));
      }
    };

    return DrupalStore;

  })(Annotator.Plugin);

}).call(this);