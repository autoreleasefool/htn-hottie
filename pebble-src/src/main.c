#include <pebble.h>
#include "guysorgirls.h"
#include "pop_the_question.h"
#include "main_menu.h"
#include "utils.h"

static void wakeup_handler(WakeupId id, int32_t reason) {
  // A wakeup event has occurred
  show_pop_the_question();

  // Delete the ID
  persist_delete(WAKEUP_ID_KEY);
}

static void init(void) {
  load_prefs();
  wakeup_service_subscribe(wakeup_handler);

  // Was this a wakeup launch?
  if (launch_reason() == APP_LAUNCH_WAKEUP) {
    g_from_wakeup = true;
    // The app was started by a wakeup
    WakeupId id = 0;
    int32_t reason = 0;

    // Get details and handle the wakeup
    wakeup_get_launch_event(&id, &reason);
    wakeup_handler(id, reason);
  } else {
    g_from_wakeup = false;
    if (g_guys_girls_both == -1) {
      load_default_pref_values();
      show_guys_or_girls();
    } else {
      show_main_menu();
    }
  }
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
