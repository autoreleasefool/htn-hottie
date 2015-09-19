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
