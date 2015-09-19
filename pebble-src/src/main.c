#include <pebble.h>
#include "guysorgirls.h"
#include "utils.h"

static void init(void) {
  load_prefs();

  if (g_guys_girls_both == -1)
    load_default_pref_values();

  show_guys_or_girls();
}

static void deinit(void) {
  save_prefs();
  hide_guys_or_girls();
}

int main(void) {
  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window");

  app_event_loop();
  deinit();
}
