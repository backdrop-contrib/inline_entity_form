Inline Entity Form
==================

Provides a widget for inline management (creation, modification, removal) of referenced entities.
The primary use case is the parent -> children one (product display -> products, order -> line items, etc.),
where the child entities are never managed outside the parent form.
Existing entities can also be referenced.

Supports commerce_product_reference, commerce_line_item_reference and entityreference fields.
Requires integration code to be provided for each entity type that can be referenced.
Supports the commerce_product (including Commerce AutoSKU integraton),
commerce_line_item, node, taxonomy_term entity types out of the box.

Getting started
---------------

Edit the reference field for which you want to use this module
(for example, the Product field on a product display node, or the Line Items
one on commerce_order) and select one of the "Inline entity form" widgets.

Widgets
-------

Two widgets are provided:

- "Inline entity form - Single value" - Shows the inline form in a fieldset
on the parent entity form. No additional action buttons are added.
This widget assumes that it is operating on a single-value required reference
field with one selected bundle.
- "Inline entity form - Multiple values" - Shows an advanced widget
for inline management of entities.
Has optimal UX when there's only one bundle selected (this is the
"Product types that can be referenced" setting on product reference fields).

Integrating with Inline Entity Form
-----------------------------------

An entity type can add support for this module by declaring the
inline entity form controller class in its entity info:

```
$entity_info['commerce_line_item']['inline entity form'] = array(
  'controller' => 'CommerceLineItemInlineEntityFormController',
);
```

The controller needs to extend `EntityInlineEntityFormController` and at least
override `entityForm()` to provide a functioning entity form.

Issues
------

To submit bug reports and feature suggestions, or to track changes:
  <https://github.com/backdrop-contrib/inline_entity_form/issues>

Current Maintainers
-------------------

- [Herb v/d Dool](https://github.com/herbdool/)
- Seeking co-maintainers.

Credits
-------

- Ported to Backdrop by [Herb v/d Dool](https://github.com/herbdool/)
  and [Docwilmot](https://github.com/docwilmot).
- Originally developed for Backdrop by [geek-merlin](https://www.drupal.org/u/geek-merlin), 
  [joachim](https://www.drupal.org/u/joachim), [oknate](https://www.drupal.org/u/oknate), 
  [kaythay](https://www.drupal.org/u/kaythay) and 
  [jsacksick](https://www.drupal.org/u/jsacksick).

License
-------

This project is GPL v2 software. See the LICENSE.txt file in this directory for
complete text.
