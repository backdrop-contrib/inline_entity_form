<?php

/**
 * @file
 * Defines the inline entity form controller for Files.
 */

class FileInlineEntityFormController extends EntityInlineEntityFormController {

  /**
   * Overrides EntityInlineEntityFormController::defaultLabels().
   */
  public function defaultLabels() {
    $labels = array(
      'singular' => t('file'),
      'plural' => t('files'),
    );
    return $labels;
  }

  /**
   * Overrides EntityInlineEntityFormController::entityForm().
   */
  public function entityForm($entity_form, &$form_state) {
    $file = $entity_form['#entity'];
    $extra_fields = field_info_extra_fields('file', $file->type, 'form');

    $defaults = array(
      'filename' => '',
      'fid' => NULL,
      'weight' => 0,
    );
    foreach ($defaults as $key => $value) {
      if (!isset($file->$key)) {
        $file->$key = $value;
      }
    }

    $entity_form['filename'] = array(
      '#type' => 'textfield',
      '#title' => t('File Display Title'),
      '#default_value' => $file->filename,
      '#maxlength' => 255,
      '#required' => TRUE,
      // The label might be missing if the Title module has replaced it.
      '#weight' => !empty($extra_fields['filename']) ? $extra_fields['filename']['weight'] : -5,
    );

    $options = array();
    $type = file_type_get_type($file);
    $options['file_extensions'] = implode(' ', file_type_get_valid_extensions($type));
    if (empty($file->filename)) {
      module_load_include('inc', 'file', 'file.pages');
      $entity_form['upload'] = array(
        '#type' => 'managed_file',
        '#title' => t('Upload a new file'),
        '#upload_location' => file_upload_destination_uri($options),
        '#upload_validators' => file_get_upload_validators($options),
        '#progress_indicator' => 'bar',
        '#pre_render' => array('file_managed_file_pre_render', 'file_upload_validators_pre_render'),
        '#default_value' => isset($form_state['storage']['upload']) ? $form_state['storage']['upload'] : NULL,
      );
    }
    else {
      // Add a 'replace this file' upload field if the file is writeable.
      if (file_is_writeable($file)) {
        // Set up replacement file validation.
        $replacement_options = array();

        // The replacement file must have the same extension as the original file.
        $replacement_options['file_extensions'] = pathinfo($file->uri, PATHINFO_EXTENSION);

        $form['replace_upload'] = array(
          '#type' => 'managed_file',
          '#title' => t('Replace file'),
          '#description' => t('This file will replace the existing file. This action cannot be undone.'),
          '#upload_validators' => file_get_upload_validators($replacement_options),
        );
      }
    }

    $langcode = $file->langcode;
    field_attach_form('file', $file, $entity_form, $form_state, $langcode);

    return $entity_form;
  }

  /**
   * Overrides EntityInlineEntityFormController::save().
   */
  public function save($entity, $context) {
    file_save($entity);
  }

}
