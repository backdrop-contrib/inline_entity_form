/**
 * @file
 * Provides JavaScript for Inline Entity Form.
 */

(function ($) {

/**
 * Allows submit buttons in entity forms to trigger uploads by undoing
 * work done by Backdrop.behaviors.fileButtons.
 */
Backdrop.behaviors.inlineEntityForm = {
  attach: function (context) {
    if (Backdrop.file) {
      $('input.ief-entity-submit', context).unbind('mousedown', Backdrop.file.disableFields);
    }
  },
  detach: function (context) {
    if (Backdrop.file) {
      $('input.form-submit', context).bind('mousedown', Backdrop.file.disableFields);
    }
  }
};

})(jQuery);
