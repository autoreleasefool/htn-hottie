#include <pebble.h>
#include "utils.h"

#define GUY_GIRL_BOTH_KEY 0
#define LATITUDE 2
#define LONGITUDE 3

// Primitives
int g_guys_girls_both = -1;
bool g_from_wakeup = false;

char* g_most_recent_latitude;
char* g_most_recent_longitude;

void load_prefs(void) {
  // Retrieving user preferences from previous sessions
  if (persist_exists(GUY_GIRL_BOTH_KEY))
    g_guys_girls_both = persist_read_int(GUY_GIRL_BOTH_KEY);
}

void save_prefs(void) {
  // Saving user preference for guys/girls/both
  persist_write_int(GUY_GIRL_BOTH_KEY, g_guys_girls_both);
}

void load_default_pref_values(void) {
  g_guys_girls_both = PREF_BOTH;
}

char* get_hottie_text(int hottie_pref) {
  switch (hottie_pref) {
    case PREF_GUYS:
      return "guys";
    case PREF_GIRLS:
      return "girls";
    case PREF_BOTH:
      return "guys or girls";
    default:
      return "";
  }
}

char* get_hottie_text_capitalized(int hottie_pref) {
  switch (hottie_pref) {
    case PREF_GUYS:
      return "Guys";
    case PREF_GIRLS:
      return "Girls";
    case PREF_BOTH:
      return "Any";
    default:
      return "";
  }
}

static void post_answer(int yesNo) {
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);
  dict_write_int(iter, KEY_POST_ANSWER, &yesNo, sizeof(int), true);
  dict_write_int(iter, KEY_GUY_GIRL_BOTH, &g_guys_girls_both, sizeof(int), true);
  app_message_outbox_send();
}

void post_hotties(void) {
  post_answer(KEY_POST_YES);
}

void post_notties(void) {
  post_answer(KEY_POST_NO);
}

static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Message received!");
  // Get the first pair
  Tuple *t = dict_read_first(iterator);

  // Process all pairs present
  while(t != NULL) {
    // Process this pair's key
    switch (t->key) {
      case LATITUDE:
        APP_LOG(APP_LOG_LEVEL_INFO, "LATITUDE received");
        g_most_recent_latitude = t->value->cstring;
        break;
      case LONGITUDE:
        APP_LOG(APP_LOG_LEVEL_INFO, "LONGITUDE received");
        g_most_recent_longitude= t->value->cstring;
        break;
    }

    // Get next pair, if any
    t = dict_read_next(iterator);
  }
}

static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}

void register_app_message_callbacks(void) {
  // Register callbacks
  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);

  // Open AppMessage
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
}
