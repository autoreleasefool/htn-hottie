#include <pebble.h>
#include "main_menu.h"
#include "utils.h"

// Main UI
static Window *s_main_window;
static GFont s_res_gothic_24_bold;
static GFont s_res_gothic_24;

// Labels
static TextLayer *s_textlayer_label_see_hotties;

// Graphics
static GBitmap *s_bitmap_check;
static GBitmap *s_bitmap_x;

// Input
static ActionBarLayer *s_action_bar_hotties;

// Text output
static char see_hottie_text[300] = "";

// Forward declarations
static void click_config_provider(void *context);

static void initialise_ui(void) {
  s_main_window = window_create();
  #ifdef PBL_COLOR
    window_set_background_color(s_main_window, GColorCeleste);
  #endif

  // Loading fonts
  s_res_gothic_24 = fonts_get_system_font(FONT_KEY_GOTHIC_24);

  // Initialising labels
  snprintf(see_hottie_text, sizeof(see_hottie_text), "Do you see any hot %s%s", get_hottie_text(), "?");
  s_textlayer_label_see_hotties = text_layer_create(GRect(0, 0, 144 - ACTION_BAR_WIDTH, 168));
  text_layer_set_text(s_textlayer_label_see_hotties, see_hottie_text);
  text_layer_set_text_alignment(s_textlayer_label_see_hotties, GTextAlignmentLeft);
  text_layer_set_font(s_textlayer_label_see_hotties, s_res_gothic_24);
  layer_add_child(window_get_root_layer(s_main_window), (Layer *)s_textlayer_label_see_hotties);

  // Creating graphics
  s_bitmap_check = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_CHECK);
  s_bitmap_x = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_X);

  // Initialising action bar
  s_action_bar_hotties = action_bar_layer_create();
  action_bar_layer_add_to_window(s_action_bar_hotties, s_main_window);
  action_bar_layer_set_click_config_provider(s_action_bar_hotties, click_config_provider);
  action_bar_layer_set_icon(s_action_bar_hotties, BUTTON_ID_UP, s_bitmap_check);
  action_bar_layer_set_icon(s_action_bar_hotties, BUTTON_ID_DOWN, s_bitmap_x);
}

static void destroy_ui() {
  window_destroy(s_main_window);

  // Destroying labels
  text_layer_destroy(s_textlayer_label_see_hotties);

  // Destroying outputs
  action_bar_layer_destroy(s_action_bar_hotties);

  // Destroying graphics
  gbitmap_destroy(s_bitmap_check);
  gbitmap_destroy(s_bitmap_x);
}

static void main_window_unload(Window *window) {
  destroy_ui();
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  show_main_menu();
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  show_main_menu();
}

static void click_config_provider(void *context) {
  // Register click handlers
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

void show_pop_the_question(void) {
  initialise_ui();
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .unload = main_window_unload,
  });
  window_stack_push(s_main_window, true);
}

void hide_pop_the_question(void) {
  window_stack_remove(s_main_window, true);
}
