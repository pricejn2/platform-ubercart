<?php

/**
 * @file
 * All theming functions
 */

function theme_uc_ajax_cart_cart_links() {
  $items[] = array(
    'data' => l(t('View cart'), 'cart', array('attributes' => array('rel' => 'nofollow'))),
    'class' => 'cart-block-view-cart',
  );
  // Only add the checkout link if checkout is enabled.
  if (variable_get('uc_checkout_enabled', TRUE)) {
    $items[] = array(
      'data' => l(t('Checkout'), 'cart/checkout', array('attributes' => array('rel' => 'nofollow'))),
      'class' => 'cart-block-checkout',
    );
  }
  return theme('item_list', $items, NULL, 'ul', array('class' => 'links'));
}

function theme_uc_ajax_cart_block_content_cached() {
  return '<div id="ajax-cart-view-handler">' . t('<a href="!url">View</a> your shopping cart.', array('!url' => url('cart'))) . '</div>';
}


function _theme_uc_ajax_cart_block_header($title) {
  if (variable_get('uc_ajax_cart_closed', 0) != 0) {
     $title = '<a href="#" id="ajaxCartToggleView">' . $title . '</a>';
  }
  return '<span class="title block-title" id="ajax-cart-headline">' . $title . '</span>';

}


function theme_uc_ajax_cart_block_header() {
  return _theme_uc_ajax_cart_block_header(t('Shopping cart'));
}



function uc_ajax_cart_preprocess_uc_ajax_cart_block_content(&$vars) {
  $content = $vars['items'];
  $items = array();

  $context = array(
    'revision' => 'themed',
    'type' => 'price',
  );

  $total = 0;
  $total_items = 0;
  foreach ($content as $item) {
    $display_item = module_invoke($item->module, 'cart_display', $item);
    if (!empty($display_item)) {
          $attributes = $item->data['attributes'];
          $total += $display_item['#total'];
          $total_items += $display_item['qty']['#default_value'];
            $items[] = array(
              'nid'      => $display_item['nid']['#value'],
              'qty'      => t('@qty&times;', array('@qty' => $display_item['qty']['#default_value'])),
              'title'    => $display_item['title']['#value'],
              'descr'    => isset($display_item['description']['#value']) ? $display_item['description']['#value'] : FALSE,
              'link'     => url('node/' . $item->nid),
              'item'     => $item,
              'image'    => uc_product_get_picture($display_item['nid']['#value'], 'cart'),
              'node'     => node_load($item->nid),
              'total'    => uc_price($display_item['#total'], array(
                'revision' => 'themed-original',
                'type' => 'amount',
                )),
              'remove_link' => l(t('Remove product'),
                                  UC_AJAX_CART_REMOVE_CALLBACK,
                                  array(
                                  'attributes' => array(
                                                    'onclick' => "ajaxCartBlockUIRemove(this.href); return false;",
                                                    'class'    => 'remove-cart-link remove-cart-link-' . $display_item['nid']['#value'],
                                                  ),
                                  'query' => array(
                                    'nid' => $display_item['nid']['#value'],
                                    'destination' => $_GET['q'],
                                    'data' => base64_encode($display_item['data']['#value']),
                                    'action' => 'remove',
                                  ),
                                )
                              ),
            );
    }
  }

  if (module_exists('uc_discounts')) {  
    // Calculate discounts, if necessary. Calculation code copied from 
    // uc_discounts_cart_pane_output
    global $user;
    //Create phony order object to call to get_discounts_for_order
    $order           = new stdClass();
    $order->uid      = $user->uid;
    $order->products = $content;

    $errors    = array();
    $warnings  = array();
    $messages  = array();
    $discounts = get_discounts_for_order($order, $errors, $warnings, $messages);

    if (count($discounts) > 0) {
      $discount_total = 0;
      foreach ($discounts as $discount) {
        $discount_total += $discount->amount;
      };

      if ($discount_total) {
        $vars['total_no_discount'] = uc_price($total, $context);
        $total = $total - $discount_total;
        $vars['discount_amount'] = uc_price($discount_total * -1, $context);
      }
    }
  }



  $vars['total'] = uc_price($total, $context);
  $vars['items'] = $items;
  $vars['item_count'] = $total_items;
  $vars['cart_links'] = theme('uc_ajax_cart_cart_links');
  $vars['items_text'] = format_plural( $total_items , '<span class="num-items">@count</span> Item', '<span class="num-items">@count</span> Items');

}
