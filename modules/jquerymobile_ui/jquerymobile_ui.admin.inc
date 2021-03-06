<?php

/**
 * @file
 * Creates the admin settings form for the module.
 */

/**
 * Form builder function for module settings.
 */
function jquerymobile_ui_admin() {

  $jquerymobile_ui_plugin_path = variable_get('jquerymobile_ui_plugin_path', JQUERYMOBILE_UI_PLUGIN_PATH);
  $jquerymobile_ui_plugin_js_file = variable_get('jquerymobile_ui_plugin_js_file', JQUERYMOBILE_UI_PLUGIN_JS_FILE);
  $jquerymobile_ui_plugin_css_file = variable_get('jquerymobile_ui_plugin_css_file', JQUERYMOBILE_UI_PLUGIN_CSS_FILE);
  $jquerymobile_ui_plugin_jq_file = variable_get('jquerymobile_ui_plugin_jq_file', JQUERYMOBILE_UI_PLUGIN_JQ_FILE);

  $transitions = array(
    '' => t('default'),
    'slide' => t('slide'),
    'slideup' => t('slideup'),
    'slidedown' => t('slidedown'),
    'pop' => t('pop'),
    'fade' => t('fade')
  );
  $booleans = array(
    'true' => t('True'), 
    'false' => t('False')
  );
  
  $form['jquerymobile_ui_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('jQuery Mobile UI Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE
  );
   
  $form['jquerymobile_ui_settings']['jquerymobile_ui_plugin_jq_file'] = array(
    '#type' => 'textfield',
    '#title' => t('jQuery JavaScript'),
    '#default_value' => $jquerymobile_ui_plugin_jq_file,
    '#description' => t('Enter the path and filename, relative to Drupal root, where the jQuery JavaScript file is located.'),
  );
  $form['jquerymobile_ui_settings']['jquerymobile_ui_plugin_path'] = array(
    '#type' => 'textfield',
    '#title' => t('jQuery Mobile Plug-in'),
    '#default_value' => $jquerymobile_ui_plugin_path,
    '#description' => t('Enter the path, relative to Drupal root, where the jQuery Mobile plugin directory is located. NO trailing slash!'),
  );  
  $form['jquerymobile_ui_settings']['jquerymobile_ui_plugin_js_file'] = array(
    '#type' => 'textfield',
    '#title' => t('jQuery Mobile JavaScript'),
    '#default_value' => $jquerymobile_ui_plugin_js_file,
    '#description' => t('Enter the filename of the jQuery Mobile JavaScript file. Assumes jQuery Mobile Plug-in path. NO leading slashes!'),
  );  
  $form['jquerymobile_ui_settings']['jquerymobile_ui_plugin_css_file'] = array(
    '#type' => 'textfield',
    '#title' => t('jQuery Mobile CSS'),
    '#default_value' => $jquerymobile_ui_plugin_css_file,
    '#description' => t('Enter the filename of the jQuery Mobile CSS file. Assumes jQuery Mobile Plug-in path. NO leading slashes!'),
  ); 
      
  $form['jquerymobile_ui'] = array(
    '#type' => 'fieldset',
    '#title' => t('jQuery Mobile UI'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE
  );
  $form['jquerymobile_ui']['jquerymobile_ui_front'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Front Page - River of News'),
    '#description'   => t('If the front page the default river of news, this option will create a link list.'),
    '#default_value' => variable_get('jquerymobile_ui_front', TRUE),
  );
  
  $form['jquerymobile_ui']['jquerymobile_ui_custom_themes'] = array(
    '#type' => 'textarea',
    '#default_value' => variable_get('jquerymobile_ui_custom_themes', ''),
    '#title' => t('Custom Mobile Themes'),
    '#description' => t('Enter the extension(s) of your custom theme(s) seperated by an new line.'),
  );
  
  $form['jquerymobile_ui']['ajax_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('AJAX Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE    
  );

/* ns */
  $form['jquerymobile_ui']['ajax_settings']['jquerymobile_ui_ns'] = array(
    '#type' => 'textfield',
    '#title' => 'ns',
    '#default_value' => variable_get('jquerymobile_ui_ns', ''),
    '#description' => t('The namespace used in data- attributes, for example, data-role. Can be set to anything, including a blank string which is the default. When using, it\'s clearest if you include a trailing dash, such as "mynamespace-" which maps to data-mynamespace-foo="...".<br>NOTE: if you\'re using data- namespacing, you\'ll need to manually update/override one selector in the theme CSS. The following data selectors should incorporate the namespace you\'re using:<br>.ui-mobile [data-mynamespace-role=page], .ui-mobile [data-mynamespace-role=dialog], .ui-page { ...'),
  );

/* autoInitializePage */
  $form['jquerymobile_ui']['ajax_settings']['jquerymobile_ui_autoInitializePage'] = array(
    '#type' => 'radios',
    '#title' => 'autoInitializePage',
    '#default_value' => variable_get('jquerymobile_ui_autoInitializePage', 'true'),
    '#description' => t('When the DOM is ready, the framework should automatically call $.mobile.initializePage. If false, page will not initialize, and will be visually hidden until until $.mobile.initializePage is manually called.'),
    '#options' => $booleans,
  );
  
/* subPageUrlKey */
  $form['jquerymobile_ui']['ajax_settings']['jquerymobile_ui_subPageUrlKey'] = array(
    '#type' => 'textfield',
    '#title' => 'subPageUrlKey',
    '#default_value' => variable_get('jquerymobile_ui_subPageUrlKey', 'ui-page'),
    '#description' => t('The url parameter used for referencing widget-generated sub-pages (such as those generated by nested listviews). Translates to to example.html&ui-page=subpageIdentifier. The hash segment before &ui-page= is used by the framework for making an Ajax request to the URL where the sub-page exists.'),
  );
  
/* activePageClass */
  $form['jquerymobile_ui']['ajax_settings']['jquerymobile_ui_activePageClass'] = array(
    '#type' => 'textfield',
    '#title' => 'activePageClass',
    '#default_value' => variable_get('jquerymobile_ui_activePageClass', 'ui-page-active'),
    '#description' => t('The class assigned to page currently in view, and during transitions'),
  );
  
/* activeBtnClass */
  $form['jquerymobile_ui']['ajax_settings']['jquerymobile_ui_activeBtnClass'] = array(
    '#type' => 'textfield',
    '#title' => 'activeBtnClass',
    '#default_value' => variable_get('jquerymobile_ui_activeBtnClass', 'ui-btn-active'), 
    '#description' => t('The class used for "active" button state, from CSS framework.'),
  );
  
/* ajaxEnabled */
  $form['jquerymobile_ui']['ajax_settings']['jquerymobile_ui_ajaxEnabled'] = array(
    '#type' => 'radios',
    '#title' => 'ajaxEnabled',
    '#default_value' => variable_get('jquerymobile_ui_ajaxEnabled', 'true'),
    '#description' => t('(jQuery Mobile will automatically handle link clicks and form submissions through Ajax, when possible. If false, url hash listening will be disabled as well, and urls will load as regular http requests.'),
    '#options' => $booleans,
  );
  
/* hashListeningEnabled */
  $form['jquerymobile_ui']['ajax_settings']['jquerymobile_ui_hashListeningEnabled'] = array(
    '#type' => 'radios',
    '#title' => 'hashListeningEnabled',
    '#default_value' => variable_get('jquerymobile_ui_hashListeningEnabled', 'true'),
    '#description' => t('jQuery Mobile will automatically listen and handle changes to the location.hash. Disabling this will prevent jQuery Mobile from handling hash changes, which allows you to handle them yourself, or simply to use simple deep-links within a document that scroll to a particular ID.'),
    '#options' => $booleans,
  );
  
/* defaultPageTransition */
  $form['jquerymobile_ui']['ajax_settings']['jquerymobile_ui_defaultPageTransition'] = array(
    '#type' => 'select',
    '#title' => 'defaultPageTransition',
    '#default_value' => variable_get('jquerymobile_ui_defaultPageTransition', 'slide'),
    '#description' => t('Set the default transition for page changes that use Ajax. Set to \'none\' for no transitions by default.'),
    '#options' => $transitions,
  );
/* defaultDialogTransition */
  $form['jquerymobile_ui']['ajax_settings']['jquerymobile_ui_defaultDialogTransition'] = array(
    '#type' => 'select',
    '#title' => 'defaultDialogTransition',
    '#default_value' => variable_get('jquerymobile_ui_defaultDialogTransition', 'pop'),
    '#description' => t('Set the default transition for dialog changes that use Ajax. Set to \'none\' for no transitions by default.'),
    '#options' => $transitions,
  );
/* minScrollBack */
  $form['jquerymobile_ui']['ajax_settings']['jquerymobile_ui_minScrollBack'] = array(
    '#type' => 'textfield',
    '#title' => 'minScrollBack',
    '#default_value' => variable_get('jquerymobile_ui_loadingMessage', '150'),
    '#description' => t('Minimum scroll distance that will be remembered when returning to a page.'),
  );
/* loadingMessage */  
  $form['jquerymobile_ui']['ajax_settings']['jquerymobile_ui_loadingMessage'] = array(
    '#type' => 'textfield',
    '#title' => 'loadingMessage',
    '#default_value' => variable_get('jquerymobile_ui_loadingMessage', 'loading'),
    '#description' => t('Set the text that appears when a page is loading. If set to false, the message will not appear at all.'),
  );
  
/* pageLoadErrorMessage */
  $form['jquerymobile_ui']['ajax_settings']['jquerymobile_ui_pageLoadErrorMessage'] = array(
    '#type' => 'textfield',
    '#title' => 'pageLoadErrorMessage',
    '#default_value' => variable_get('jquerymobile_ui_pageLoadErrorMessage', 'Error Loading Page'),
    '#description' => t('Set the text that appears when a page fails to load through Ajax.'),
  );
  /* gradeA */
    
  $form = system_settings_form($form);

  return $form;
}
