#define APP_NAME "Hottie Alert"
#define PREF_GUYS 0
#define PREF_GIRLS 1
#define PREF_BOTH 2

extern int g_guys_girls_both;

void load_prefs(void);
void save_prefs(void);
void load_default_pref_values(void);
char* get_hottie_text(int hottie_pref);
char* get_hottie_text_capitalized(int hottie_pref);
