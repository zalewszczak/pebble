#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"
#include "string.h"


#define MY_UUID { 0xD4, 0x2C, 0xC1, 0xBF, 0x7A, 0xD3, 0x49, 0x64, 0x8B, 0x38, 0xC8, 0x9C, 0xD7, 0x85, 0x35, 0x69 }
PBL_APP_INFO(MY_UUID,
             "Godzina", "Zalew",
             1, 0, /* App version */
             RESOURCE_ID_IMAGE_MENU_ICON,
             APP_INFO_WATCH_FACE);

Window window;

TextLayer warstwa_godzina1;
TextLayer warstwa_godzina2;
TextLayer warstwa_minuta1;
TextLayer warstwa_minuta2;
TextLayer warstwa_data;

GFont roboto;
GFont roboto_bold;
GFont roboto_small;

static char data_tekst[] = "poniedziałek 00-00-00";
static char dd_mm_rr[] = "00-00-00";

static const char* const GODZINKI[] = {
  "zero", /*???*/
  "pierwsza",
  "druga",
  "trzecia",
  "czwarta",
  "piąta",
  "szósta",
  "siódma",
  "ósma",
  "dziewiąta",
  "dziesiąta",
  "jedenasta",
  "dwunasta",
  "trzynasta",
  "czternasta",
  "piętnasta",
  "szesnasta",
  "siedemnasta",
  "osiemnasta",
  "dziewiętnasta",
  "dwudziesta"
};

static const char* const JEDYNKI[] = {
  "zero",
  "jeden",
  "dwa",
  "trzy",
  "cztery",
  "pięć",
  "szesć",
  "siedem",
  "osiem",
  "dziewięć",
  "dziesięć",
  "jedenascie",
  "dwanascie",
  "trzynascie",
  "czternascie",
  "piętnascie",
  "szesnascie",
  "siedemnascie",
  "osiemanscie",
  "dziewiętnascie"
};

static const char* const DZIESIATKI[] = {
  "dwadziescia",
  "trzydziesci",
  "czterdziesci",
  "pięćdziesiąt"
};

static const char* const DZIONKI[] = {
  "niedziela",
  "poniedzialek",
  "wtorek",
  "czwartek",
  "piątek",
  "sobota"
};

void set_time(PblTm* t) {

  if(t->tm_hour>20)
  {
      text_layer_set_text(&warstwa_godzina1, GODZINKI[20]);
  }
  else
  {
      if(t->tm_hour==19)
       {
            text_layer_set_text(&warstwa_godzina1, "dziwięt-");
       }
       else
       {
            text_layer_set_text(&warstwa_godzina1, " ");
       }
  }
  if(t->tm_hour>20)
  {
       text_layer_set_text(&warstwa_godzina2, GODZINKI[t->tm_hour-20]);
  }
  else
  {
       if(t->tm_hour==19)
       {
            text_layer_set_text(&warstwa_godzina2, "nasta");
       }
       else
       {
            text_layer_set_text(&warstwa_godzina2, GODZINKI[t->tm_hour]);
       }
  }
  if(t->tm_min>19)
  {
       text_layer_set_text(&warstwa_minuta1, DZIESIATKI[(t->tm_min/10)-2]);
  }
  else
  {
       if(t->tm_min==0)
       {
            text_layer_set_text(&warstwa_minuta1, " ");
       }
       else
       {
            text_layer_set_text(&warstwa_minuta1, JEDYNKI[t->tm_min]);
       }
  }
  if(t->tm_min<20||t->tm_min%10==0)
  {
       text_layer_set_text(&warstwa_minuta2, " ");
  }
  else
  {
       text_layer_set_text(&warstwa_minuta2, JEDYNKI[t->tm_min%10]);
  }
  
  string_format_time(dd_mm_rr, sizeof(dd_mm_rr), "%d-%m-%y", t);
  size_t rozmiar = sizeof(data_tekst);
  memset(data_tekst, 0, rozmiar);
  
  strncat(data_tekst, DZIONKI[t->tm_wday], rozmiar);
  rozmiar -= strlen(DZIONKI[t->tm_wday]);
  strncat(data_tekst, " ", rozmiar);
  rozmiar -= strlen(" ");
  strncat(data_tekst, dd_mm_rr, rozmiar);
  
  text_layer_set_text(&warstwa_data, data_tekst);
  /*text_layer_set_text(&warstwa_data, dd_mm_rr);*/

}

void handle_init(AppContextRef ctx) {
  (void)ctx;

  window_init(&window, "Window Name");
  window_stack_push(&window, true /* Animated */);

  resource_init_current_app(&APP_RESOURCES);

  roboto = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ROBOTO_CONDENSED_25));
  roboto_bold = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ROBOTO_BOLD_25));
  roboto_small = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ROBOTO_CONDENSED_13));

  window_set_background_color(&window, GColorBlack);

  text_layer_init(&warstwa_godzina1, GRect(0, 15, 144, 30));
  text_layer_set_text_alignment(&warstwa_godzina1, GTextAlignmentLeft);
  text_layer_set_text_color(&warstwa_godzina1, GColorWhite);
  text_layer_set_background_color(&warstwa_godzina1, GColorClear);
  text_layer_set_font(&warstwa_godzina1, roboto_bold);
  layer_add_child(&window.layer, &warstwa_godzina1.layer);

  text_layer_init(&warstwa_godzina2, GRect(0, 45, 144, 30));
  text_layer_set_text_alignment(&warstwa_godzina2, GTextAlignmentLeft);
  text_layer_set_text_color(&warstwa_godzina2, GColorWhite);
  text_layer_set_background_color(&warstwa_godzina2, GColorClear);
  text_layer_set_font(&warstwa_godzina2, roboto_bold);
  layer_add_child(&window.layer, &warstwa_godzina2.layer);

  text_layer_init(&warstwa_minuta1, GRect(0, 75, 144, 30));
  text_layer_set_text_alignment(&warstwa_minuta1, GTextAlignmentLeft);
  text_layer_set_text_color(&warstwa_minuta1, GColorWhite);
  text_layer_set_background_color(&warstwa_minuta1, GColorClear);
  text_layer_set_font(&warstwa_minuta1, roboto);
  layer_add_child(&window.layer, &warstwa_minuta1.layer);

  text_layer_init(&warstwa_minuta2, GRect(0, 105, 144, 30));
  text_layer_set_text_alignment(&warstwa_minuta2, GTextAlignmentLeft);
  text_layer_set_text_color(&warstwa_minuta2, GColorWhite);
  text_layer_set_background_color(&warstwa_minuta2, GColorClear);
  text_layer_set_font(&warstwa_minuta2, roboto);
  layer_add_child(&window.layer, &warstwa_minuta2.layer);

  text_layer_init(&warstwa_data, GRect(0, 155, 144, 20));
  text_layer_set_text_alignment(&warstwa_data, GTextAlignmentCenter);
  text_layer_set_text_color(&warstwa_data, GColorWhite);
  text_layer_set_background_color(&warstwa_data, GColorClear);
  text_layer_set_font(&warstwa_data, roboto_small);
  layer_add_child(&window.layer, &warstwa_data.layer);
  
  PblTm t;
  get_time(&t);
  set_time(&t);
}

void handle_deinit(AppContextRef ctx) {
  (void)ctx;

  fonts_unload_custom_font(roboto);
  fonts_unload_custom_font(roboto_bold);
  fonts_unload_custom_font(roboto_small);
}

void handle_minute_tick(AppContextRef ctx, PebbleTickEvent *t) {
   (void)t;
   (void)ctx;
	
   set_time(t->tick_time);
}


void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
    .deinit_handler = &handle_deinit,
    .tick_info = {
			.tick_handler = &handle_minute_tick,
			.tick_units = MINUTE_UNIT
		}
  };
  app_event_loop(params, &handlers);
}
