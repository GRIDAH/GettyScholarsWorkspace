<div id="upload-images-page">
  <div class="messages"></div>
  <div id="upload-images-page-splash">
    <h3>Drag and drop images here</h3>
    <p>- OR -</p>
    <a href="#">Select a photo from your computer</a>
  </div>
  <div id="upload-images-page-edit">
    <div class="toolbar">
      <div>
        <a id="upload-images-page-cancel" href="#">Cancel</a>
      </div>
      <div>
        <a id="upload-images-page-add" href="#">Add</a>
        <a id="upload-images-page-remove" href="#">Remove</a>
      </div>
      <div>
        <a id="upload-images-page-select-all" href="#">select all</a>
        <a id="upload-images-page-deselect-all" href="#">deselect all</a>
      </div>
      <a id="upload-images-page-submit" href="#">UPLOAD IMAGES</a>
    </div>
    <div class="content-container">
      <div id="upload-images-content"></div>
      <div id="upload-images-page-template" style="display: none">
        <div class="item" data-file="">
          <form method="post" enctype="multipart/form-data">
            <div class="thumbnail"></div>
            <label>
              Title
              <input type="text" name="title[]">
            </label>
            <input type="hidden" name="caption[]">
            <input type="hidden" name="creator[]">
            <input type="hidden" name="creation_date[]">
            <input type="hidden" name="medium[]">
            <input type="hidden" name="dimensions[]">
            <input type="hidden" name="location[]">
            <input type="hidden" name="description[]">
            <input type="hidden" name="tags[]">
          </form>
        </div>
      </div>
    </div>
    <div class="form-container">
      <div class="default-message">Select images to add metadata</div>
      <div id="upload-images-page-form" style="display: none;">
        <div class="editing-message">Editing 1 image</div>
        <div class="form-item">
          <label for="field-title">Title</label>
          <input type="text" class="title" id="field-title">
        </div>
        <!--
        <div class="form-item">
          <label for="field-caption">Caption</label>
          <input type="text" class="caption" id="field-caption">
        </div>
        -->
        <div class="form-item">
          <label for="field-creator">Creator</label>
          <input type="text" class="creator" id="field-creator">
          <div class="description">e.g. Vincent van Gogh, Bernard Picart</div>
        </div>
        <div class="form-item">
          <label for="field-creation_date">Object Creation Date</label>
          <input type="text" class="creation_date" id="field-creation_date">
          <div class="description">e.g. c. 1400</div>
        </div>
        <div class="form-item">
          <label for="field-medium">Medium</label>
          <input type="text" class="medium" id="field-medium">
          <div class="description">e.g. gelatin silver paper, pastel, wood</div>
        </div>
        <div class="form-item">
          <label for="field-dimensions">Dimensions</label>
          <input type="text" class="dimensions" id="field-dimensions">
          <div class="description">e.g. 71 x 93 cm, 1532 p. 23 cm</div>
        </div>
        <div class="form-item">
          <label for="field-location">Current Location</label>
          <input type="text" class="location" id="field-location">
          <div class="description">e.g. Getty Research Institute, artist's private collection</div>
        </div>
        <div class="form-item">
          <label for="field-description">Description</label>
          <textarea class="description" id="field-description"></textarea>
          <div class="description">Tell us about this object.</div>
        </div>
        <!--
        <div class="form-item">
          <label>Tags</label>
          <div class="tags">
            <label><input type="checkbox" class="tags" value="Sculpture"> Sculpture</label>
            <label><input type="checkbox" class="tags" value="Painting"> Painting</label>
            <label><input type="checkbox" class="tags" value="Demons"> Demons</label>
          </div>
        </div>
        -->
      </div>
    </div>
  </div>

  <div style="display: none;" id="upload-images-page-files"></div>
</div>
