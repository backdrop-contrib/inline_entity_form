<?php

/**
 * @file
 * Defines the inline entity form controller for Taxonomy terms.
 */

class TaxonomyTermInlineEntityFormController extends EntityInlineEntityFormController {

  /**
   * Overrides EntityInlineEntityFormController::defaultLabels().
   */
  public function defaultLabels() {
    $labels = array(
      'singular' => t('term'),
      'plural' => t('terms'),
    );
    return $labels;
  }

  /**
   * Overrides EntityInlineEntityFormController::entityForm().
   */
  public function entityForm($entity_form, &$form_state) {
    $term = $entity_form['#entity'];
    $extra_fields = field_info_extra_fields('taxonomy_term', $term->vocabulary, 'form');

    $defaults = array(
      'name' => '',
      'description' => '',
      'format' => NULL,
      'tid' => NULL,
      'weight' => 0,
    );
    foreach ($defaults as $key => $value) {
      if (!isset($term->$key)) {
        $term->$key = $value;
      }
    }

    $entity_form['name'] = array(
      '#type' => 'textfield',
      '#title' => t('Name'),
      '#default_value' => $term->name,
      '#maxlength' => 255,
      '#required' => TRUE,
      // The label might be missing if the Title module has replaced it.
      '#weight' => !empty($extra_fields['name']) ? $extra_fields['name']['weight'] : -5,
    );
    $entity_form['description'] = array(
      '#type' => 'text_format',
      '#title' => t('Description'),
      '#default_value' => $term->description,
      '#format' => $term->format,
      '#weight' => !empty($extra_fields['description']) ? $extra_fields['description']['weight'] : -4,
    );

    $langcode = $term->langcode;
    field_attach_form('taxonomy_term', $term, $entity_form, $form_state, $langcode);

    return $entity_form;
  }


  /**
   * Overrides EntityInlineEntityFormController::entityFormSubmit().
   */
  public function entityFormSubmit(&$entity_form, &$form_state) {
    parent::entityFormSubmit($entity_form, $form_state);

    $entity = $entity_form['#entity'];

    // Separate the description and format.
    $entity->format = $entity->description['format'];
    $entity->description = $entity->description['value'];
  }

  /**
   * Overrides EntityInlineEntityFormController::save().
   */
  public function save($entity, $context) {
    taxonomy_term_save($entity);
  }

}
