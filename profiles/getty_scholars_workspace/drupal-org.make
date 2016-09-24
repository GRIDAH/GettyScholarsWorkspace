; getty_scholars_workspace make file for d.o. usage
core = "7.x"
api = "2"

; +++++ Modules +++++

defaults[projects][subdir] = "contrib"

projects[] = "admin_menu"
projects[] = "backup_migrate"
projects[] = "better_exposed_filters"
projects[] = "chain_menu_access"
projects[] = "colorbox"
projects[] = "context"
projects[] = "ctools"
projects[] = "date"
projects[] = "diff"
projects[] = "entity"
projects[] = "entityreference"
projects[] = "facetapi"
projects[] = "features"
projects[] = "feeds"
projects[] = "field_collection"
projects[] = "field_collection_fieldset"
projects[] = "field_group"
projects[] = "file_entity"
projects[] = "flexslider"
projects[] = "imagecache_actions"
projects[] = "job_scheduler"
projects[] = "jquery_update"
projects[] = "libraries"
projects[] = "link"
projects[] = "module_filter"
projects[] = "partial_date"
projects[] = "popup"
projects[] = "profiler_builder"
projects[] = "strongarm"
projects[] = "views"
projects[] = "views_bulk_operations"
projects[administerusersbyrole][version] = "2.0"
projects[comment_og][version] = "1.0"
projects[field_formatter_class][version] = "1.1"
projects[field_formatter_settings][version] = "1.1"
projects[footnotes][version] = "2.5"
projects[image_field_caption][version] = "2.x-dev"
projects[og][version] = "2"
projects[restws][version] = "2"
projects[role_delegation][version] = "1.1"
projects[views_fluid_grid][version] = "3.0"
projects[views_timelinejs][version] = "3"
projects[wysiwyg][version] = "2.x-dev"

projects[comment_og][patch][] = "https://www.drupal.org/files/comment_og-OG7.x-2.x-compatibility-1833006-36_0.patch"
; projects[og][patch][] = "https://www.drupal.org/files/issues/og-field-query-1507608-22.patch"

; +++++ Themes +++++

projects[omega][version] = "3"
projects[omega][subdir] = ""

; +++++ Libraries +++++

defaults[libraries][type] = "library"
defaults[libraries][destination] = "libraries"

; Annotorious
libraries[annotorious][directory_name] = "annotorious"
libraries[annotorious][download][type] = "get"
libraries[annotorious][download][url] = "https://github.com/annotorious/annotorious/archive/v0.4.zip"

; CKEditor
libraries[ckeditor][directory_name] = "ckeditor"
libraries[ckeditor][download][type] = "get"
libraries[ckeditor][download][url] = "http://download.cksource.com/CKEditor/CKEditor/CKEditor%204.5.11/ckeditor_4.5.11_full.zip"

; CKEditor Footnotes
libraries[ckeditor_footnotes][directory_name] = "footnotes"
libraries[ckeditor_footnotes][destination] = "libraries/ckeditor/plugins"
libraries[ckeditor_footnotes][download][type] = "get"
libraries[ckeditor_footnotes][download][url] = "http://download.ckeditor.com/footnotes/releases/footnotes_1.0.10.zip"

; CKEditor Line Utils
libraries[ckeditor_lineutils][directory_name] = "lineutils"
libraries[ckeditor_lineutils][destination] = "libraries/ckeditor/plugins"
libraries[ckeditor_lineutils][download][type] = "get"
libraries[ckeditor_lineutils][download][url] = "http://download.ckeditor.com/lineutils/releases/lineutils_4.5.11.zip"

; CKEditor Widget
libraries[ckeditor_widget][directory_name] = "widget"
libraries[ckeditor_widget][destination] = "libraries/ckeditor/plugins"
libraries[ckeditor_widget][download][type] = "get"
libraries[ckeditor_widget][download][url] = "http://download.ckeditor.com/widget/releases/widget_4.5.11.zip"

; ColorBox
libraries[colorbox][directory_name] = "colorbox"
libraries[colorbox][download][type] = "get"
libraries[colorbox][download][url] = "https://github.com/jackmoore/colorbox/archive/1.x.zip"

; Chosen
libraries[chosen][directory_name] = "chosen"
libraries[chosen][download][type] = "get"
libraries[chosen][download][url] = "https://github.com/harvesthq/chosen/releases/download/v1.1.0/chosen_v1.1.0.zip"

; DataTables
libraries[datatables][directory_name] = "datatables"
libraries[datatables][download][type] = "get"
libraries[datatables][download][url] = "https://datatables.net/releases/DataTables-1.10.12.zip"

; Flexslider
libraries[flexslider][directory_name] = "flexslider"
libraries[flexslider][download][type] = "get"
libraries[flexslider][download][url] = "https://github.com/woothemes/FlexSlider/archive/version/2.1.zip"

; Markdownify
libraries[markdownify][directory_name] = "markdownify"
libraries[markdownify][download][type] = "get"
libraries[markdownify][download][url] = "https://github.com/Elephant418/Markdownify/archive/v2.1.11.zip"

; OpenSeadragon
libraries[openseadragon][directory_name] = "openseadragon"
libraries[openseadragon][download][type] = "get"
libraries[openseadragon][download][url] = "https://github.com/openseadragon/openseadragon/releases/download/v2.1.0/openseadragon-bin-2.1.0.zip"

; Views TimelineJS
libraries[timeline][directory_name] = "timeline"
libraries[timeline][download][type] = "get"
libraries[timeline][download][url] = "https://github.com/NUKnightLab/TimelineJS/archive/2.36.0.zip"

; Waypoints
libraries[waypoints][directory_name] = "waypoints"
libraries[waypoints][download][type] = "get"
libraries[waypoints][download][url] = "https://github.com/imakewebthings/waypoints/archive/4.0.1.zip"
