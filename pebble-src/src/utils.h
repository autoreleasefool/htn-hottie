#define APP_NAME "Hottie Alert"

#define PREF_GUYS 0
#define PREF_GIRLS 1
#define PREF_BOTH 2

#define WAKEUP_REASON 0
#define WAKEUP_ID_KEY 0

#define KEY_POST_ANSWER 0
#define KEY_GUY_GIRL_BOTH 1

#define KEY_POST_YES 0
#define KEY_POST_NO 1

extern int g_guys_girls_both;
extern bool g_from_wakeup;

void load_prefs(void);
void save_prefs(void);
void load_default_pref_values(void);
char* get_hottie_text(int hottie_pref);
char* get_hottie_text_capitalized(int hottie_pref);
void post_hotties(void);
void post_notties(void);
void register_app_message_callbacks(void);
