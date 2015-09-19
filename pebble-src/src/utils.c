#include <pebble.h>
#include "utils.h"

#define GUY_GIRL_BOTH_KEY 0

int g_guys_girls_both = -1;

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
  g_guys_girls_both = 2;
}
