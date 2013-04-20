#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID { 0x54, 0xF4, 0x35, 0xAB, 0xC0, 0x2A, 0x40, 0x5F, 0x9F, 0xD6, 0x52, 0x39, 0x0F, 0xD8, 0x81, 0x9D }
PBL_APP_INFO(MY_UUID,
             "Jellly Time", "Zalew",
             1, 0, /* App version */
             RESOURCE_ID_IMAGE_MENU_ICON,
             APP_INFO_WATCH_FACE);

Window window;

TextLayer thick_time_layer;
TextLayer thin_time_layer;
TextLayer date_layer;

static char date_text[] = "WED, NOVEMBER 14";
static char hour_text[] = "17:";
static char minute_text[] = "46";

//week starts with sunday!
static const char* const DAYS[] = {
  "SUN", 
  "MON",
  "TUE",
  "WED",
  "THU",
  "FRI",
  "SAT"
};

static const char* const MONTHS[] = {
  "JANUARY",
  "FEBRUARY",
  "MARCH",
  "APRIL",
  "MAY",
  "JUNE",
  "JULY",
  "AUGUST",
  "SEPTEMBER",
  "OCTOBER",
  "NOVEMBER",
  "DECEMBER"
};

void draw_date(PblTm* t) {
  char day[] = "14";
  string_format_time(day, sizeof(day), "%d", t);
  
  size_t size = sizeof(date_text);
  memset(date_text, 0, size);
  
  strncat(date_text, DAYS[t->tm_wday], size);
  size -= strlen(DAYS[t->tm_wday]);
  strncat(date_text, ", ", size);
  size -= strlen(", ");
  strncat(date_text, MONTHS[t->tm_mon], size);
  size -= strlen(MONTHS[t->tm_mon]);
  strncat(date_text, " ", size);
  size -= strlen(" ");
  strncat(date_text, day, size);
  text_layer_set_text(&date_layer, date_text);
}

void set_time(PblTm* t) {
  
  // section based on Simplicity by Pebble Team begins
    char *time_format;
    if (clock_is_24h_style()) {
    	time_format = "%H:";
    } else {
    	time_format = "%I:";
    }
    
    string_format_time(hour_text, sizeof(hour_text), time_format, t);
    
    if (!clock_is_24h_style() && (hour_text[0] == '0')) {
    	memmove(hour_text, &hour_text[1], sizeof(hour_text) - 1);
    }
  // section ends
  string_format_time(minute_text, sizeof(hour_text), "%M", t);

  if(t->tm_min==0&&t->tm_hour==0){
     draw_date(t);
  }
  text_layer_set_text(&thick_time_layer, hour_text);
  text_layer_set_text(&thin_time_layer, minute_text);

}

void handle_init(AppContextRef ctx) {
  (void)ctx;
  window_init(&window, "Window Name");
  window_stack_push(&window, true /* Animated */);

  resource_init_current_app(&APP_RESOURCES);

  GFont roboto = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ROBOTO_THIN_40));
  GFont roboto_bold = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ROBOTO_BOLD_40));
  GFont roboto_small = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ROBOTO_REGULAR_12));

  window_set_background_color(&window, GColorBlack);

  text_layer_init(&thick_time_layer, GRect(0, 45, 76, 45));
  text_layer_set_text_alignment(&thick_time_layer, GTextAlignmentRight);
  text_layer_set_text_color(&thick_time_layer, GColorWhite);
  text_layer_set_background_color(&thick_time_layer, GColorClear);
  text_layer_set_font(&thick_time_layer, roboto_bold);
  layer_add_child(&window.layer, &thick_time_layer.layer);

  text_layer_init(&thin_time_layer, GRect(76, 45, 68, 45));
  text_layer_set_text_alignment(&thin_time_layer, GTextAlignmentLeft);
  text_layer_set_text_color(&thin_time_layer, GColorWhite);
  text_layer_set_background_color(&thin_time_layer, GColorClear);
  text_layer_set_font(&thin_time_layer, roboto);
  layer_add_child(&window.layer, &thin_time_layer.layer);

  text_layer_init(&date_layer, GRect(0, 100, 144, 15));
  text_layer_set_text_alignment(&date_layer, GTextAlignmentCenter);
  text_layer_set_text_color(&date_layer, GColorWhite);
  text_layer_set_background_color(&date_layer, GColorClear);
  text_layer_set_font(&date_layer, roboto_small);
  layer_add_child(&window.layer, &date_layer.layer);

  PblTm t;
  get_time(&t);
  set_time(&t);
  draw_date(&t);
}

void handle_minute_tick(AppContextRef ctx, PebbleTickEvent *t) {
  (void)t;
  (void)ctx;
	
  set_time(t->tick_time);
}

void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
    .tick_info = {
			.tick_handler = &handle_minute_tick,
			.tick_units = MINUTE_UNIT
		}
  };
  app_event_loop(params, &handlers);
}
