#include <pebble.h>
#include "nearby.h"
#include "utils.h"

// Main UI
static Window *s_main_window;
static GFont s_res_gothic_24;

// Labels
static TextLayer *s_textlayer_label_nearby_hotties;

// Text output
static char nearby_hottie_text[300] = "";

bool g_nearby_shown = false;

void nearby_received(void) {
  if (g_nearby_shown) {
    snprintf(nearby_hottie_text, sizeof(nearby_hottie_text), "Hotties found! Head to (%s, %s)", g_most_recent_latitude, g_most_recent_longitude);
    text_layer_set_text(s_textlayer_label_nearby_hotties, nearby_hottie_text);
  }
}

static void post_nothing(void) {
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);
  dict_write_int(iter, 3, 0, sizeof(int), true);
  app_message_outbox_send();
}

static void initialise_ui(void) {
  s_main_window = window_create();
  #ifdef PBL_COLOR
    window_set_background_color(s_main_window, GColorCeleste);
  #endif

  // Loading fonts
  s_res_gothic_24 = fonts_get_system_font(FONT_KEY_GOTHIC_24);

  // Initialising labels
  s_textlayer_label_nearby_hotties = text_layer_create(GRect(5, 5, 134 - ACTION_BAR_WIDTH, 158));
  text_layer_set_text(s_textlayer_label_nearby_hotties, "Checking for hotties in your area. Please wait...");
  text_layer_set_text_alignment(s_textlayer_label_nearby_hotties, GTextAlignmentLeft);
  text_layer_set_font(s_textlayer_label_nearby_hotties, s_res_gothic_24);
  layer_add_child(window_get_root_layer(s_main_window), (Layer *)s_textlayer_label_nearby_hotties);
}

static void destroy_ui() {
  window_destroy(s_main_window);

  // Destroying labels
  text_layer_destroy(s_textlayer_label_nearby_hotties);
}

static void main_window_unload(Window *window) {
  destroy_ui();
}

static void main_window_appear(Window *window) {
  post_nothing();
}

void show_nearby(void) {
  initialise_ui();
  g_nearby_shown = true;
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .unload = main_window_unload,
    .appear = main_window_appear,
  });
  window_stack_push(s_main_window, true);
}

void hide_nearby(void) {
  g_nearby_shown = false;
  window_stack_remove(s_main_window, true);
}
