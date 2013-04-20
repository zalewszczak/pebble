#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID { 0x74, 0xCC, 0x3E, 0x33, 0xCF, 0x64, 0x4F, 0xEF, 0x99, 0x45, 0xC0, 0xD1, 0x21, 0xFE, 0xFD, 0x5F }
PBL_APP_INFO(MY_UUID,
             "Basic 12h", "Zalew",
             1, 0, /* App version */
             RESOURCE_ID_IMAGE_MENU_ICON,
             APP_INFO_WATCH_FACE);

Window window;

BmpContainer background_image_container;

TextLayer date_layer;
TextLayer time_layer;
TextLayer seconds_layer;
TextLayer bottom_layer;

static char date_text[] = "Monday\nNovember 13, 2013";
static char time_text[] = "11:44";
static char seconds_text[] = "pm\n31";

void set_time_second(PblTm* t) {
  
    char *seconds_format;
    if (clock_is_24h_style()) {
    	seconds_format = "\n%S";
    } else {
    	seconds_format = "%p\n%S";
    }
    
    string_format_time(seconds_text, sizeof(seconds_text), seconds_format, t);

  text_layer_set_text(&seconds_layer, seconds_text);
}


void set_time_minute(PblTm* t) {
  
    char *time_format;
    if (clock_is_24h_style()) {
    	time_format = "%R";
    } else {
    	time_format = "%I:%M";
    }
    
    string_format_time(time_text, sizeof(time_text), time_format, t);
    
    if (!clock_is_24h_style() && (time_text[0] == '0')) {
    	memmove(time_text, &time_text[1], sizeof(time_text) - 1);
    }

  text_layer_set_text(&time_layer, time_text);
  
  set_time_second(t);
}
void set_time(PblTm* t) {
  string_format_time(date_text, sizeof(date_text), "%A\n%B %d, %Y", t);
  text_layer_set_text(&date_layer, date_text);

  set_time_minute(t);
}

void handle_init(AppContextRef ctx) {
  (void)ctx;
  window_init(&window, "Window Name");
  window_stack_push(&window, true /* Animated */);

  resource_init_current_app(&APP_RESOURCES);

  GFont roboto_date = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ROBOTO_REGULAR_16));
  GFont roboto_time = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ROBOTO_CONDENSED_49));
  GFont roboto_seconds = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ROBOTO_CONDENSED_20));
  GFont roboto_bottom = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ROBOTO_REGULAR_21));

  window_set_background_color(&window, GColorWhite);

  bmp_init_container(RESOURCE_ID_IMAGE_BACKGROUND, &background_image_container);
  layer_add_child(&window.layer, &background_image_container.layer.layer);

  text_layer_init(&date_layer, GRect(0, 0, 144, 40));
  text_layer_set_text_alignment(&date_layer, GTextAlignmentCenter);
  text_layer_set_text_color(&date_layer, GColorBlack);
  text_layer_set_background_color(&date_layer, GColorClear);
  text_layer_set_font(&date_layer, roboto_date);
  layer_add_child(&window.layer, &date_layer.layer);

  text_layer_init(&time_layer, GRect(0, 52, 114, 70));
  text_layer_set_text_alignment(&time_layer, GTextAlignmentRight);
  text_layer_set_text_color(&time_layer, GColorBlack);
  text_layer_set_background_color(&time_layer, GColorClear);
  text_layer_set_font(&time_layer, roboto_time);
  layer_add_child(&window.layer, &time_layer.layer);

  text_layer_init(&seconds_layer, GRect(111, 61, 33, 50));
  text_layer_set_text_alignment(&seconds_layer, GTextAlignmentCenter);
  text_layer_set_text_color(&seconds_layer, GColorBlack);
  text_layer_set_background_color(&seconds_layer, GColorClear);
  text_layer_set_font(&seconds_layer, roboto_seconds);
  layer_add_child(&window.layer, &seconds_layer.layer);

  text_layer_init(&bottom_layer, GRect(0, 136, 144, 30));
  text_layer_set_text_alignment(&bottom_layer, GTextAlignmentCenter);
  text_layer_set_text_color(&bottom_layer, GColorBlack);
  text_layer_set_background_color(&bottom_layer, GColorClear);
  text_layer_set_font(&bottom_layer, roboto_bottom);
  layer_add_child(&window.layer, &bottom_layer.layer);
  text_layer_set_text(&bottom_layer, "3ATM   Pebble");

  PblTm t;
  get_time(&t);
  set_time(&t);
}

void handle_deinit(AppContextRef ctx) {
  (void)ctx;

  bmp_deinit_container(&background_image_container);
}

void handle_second_tick(AppContextRef ctx, PebbleTickEvent *t) {
  (void)t;
  (void)ctx;
	
  if(t->tick_time->tm_sec!=0)
  {
      //refreshing only seconds
      set_time_second(t->tick_time);
  }
  else if(t->tick_time->tm_min!=0&&t->tick_time->tm_hour!=0)
  {
      //refreshing time and second
      set_time_minute(t->tick_time);
  }
  else
  {
      //midnight - refreshing all
      set_time(t->tick_time);
  }
}

void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
    .deinit_handler = &handle_deinit,
    .tick_info = {
			.tick_handler = &handle_second_tick,
			.tick_units = SECOND_UNIT
		}
  };
  app_event_loop(params, &handlers);
}
