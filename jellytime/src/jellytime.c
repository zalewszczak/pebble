#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

#include "build_config.h"

#define MY_UUID { 0x54, 0xF4, 0x35, 0xAB, 0xC0, 0x2A, 0x40, 0x5F, 0x9F, 0xD6, 0x52, 0x39, 0x0F, 0xD8, 0x81, 0x9D }
PBL_APP_INFO(MY_UUID,
             "Jelly Time", "Zalew",
             1, 3, /* App version */
             RESOURCE_ID_IMAGE_MENU_ICON,
             APP_INFO_WATCH_FACE);

#define HOUR_VIBRATION true
#define HOUR_VIBRATION_START 8
#define HOUR_VIBRATION_END 20

Window window;

TextLayer thick_time_layer;
TextLayer thin_time_layer;
TextLayer date_layer;
TextLayer mode12h_layer;

static char date_text[] = "WED, SEPTEMBER 13";
static char hour_text[] = "12";
static char minute_text[] = ":46";
static char mode12h_text[] = "  ";

GFont roboto;
GFont roboto_bold;
GFont roboto_small;
GFont roboto_12h;

PropertyAnimation prop_animation_thick;
PropertyAnimation prop_animation_thin;
PropertyAnimation prop_animation_12h;

bool aligned_to_single = false;

static const char* const MODES[] = {
  "AM", 
  "PM",
};

#include "lang.h"

/*
void draw_date(PblTm* t) {
  get_date_formatted(date_text, t);

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


  char day[] = "14";
  string_format_time(day, sizeof(day), "%d", t);
  
  size_t size = sizeof(date_text);
  memset(date_text, 0, size);
  
  strncat(date_text, DAYS[t->tm_wday], size);
  size -= strlen(DAYS[t->tm_wday]);
  strncat(date_text, ", ", size);
  size -= strlen(", ");
  strncat(date_text, day, size);
  size -= strlen(day);
  strncat(date_text, " ", size);
  size -= strlen(" ");
  strncat(date_text, MONTHS[t->tm_mon], size);
  text_layer_set_text(&date_layer, date_text);
}
*/

void align_time_double(){
   if(aligned_to_single)
   {
      GRect to_rect_thick = GRect(0, 40, 68, 55);
      GRect to_rect_thin = GRect(68, 40, 76, 55);
      GRect to_rect_12h = GRect(104, 51, 40, 20);

      property_animation_init_layer_frame(&prop_animation_thick, &thick_time_layer.layer, NULL, &to_rect_thick);
      property_animation_init_layer_frame(&prop_animation_thin, &thin_time_layer.layer, NULL, &to_rect_thin);
      property_animation_init_layer_frame(&prop_animation_12h, &mode12h_layer.layer, NULL, &to_rect_12h);
      
      animation_schedule(&prop_animation_thick.animation);
      animation_schedule(&prop_animation_thin.animation);
      animation_schedule(&prop_animation_12h.animation);


      aligned_to_single = false;
   }
}

void align_time_single(){
   if(!aligned_to_single)
   {
      GRect to_rect_thick = GRect(-14, 40, 68, 55);
      GRect to_rect_thin = GRect(54, 40, 76, 55);
      GRect to_rect_12h = GRect(90, 51, 40, 20);

      property_animation_init_layer_frame(&prop_animation_thick, &thick_time_layer.layer, NULL, &to_rect_thick);
      property_animation_init_layer_frame(&prop_animation_thin, &thin_time_layer.layer, NULL, &to_rect_thin);
      property_animation_init_layer_frame(&prop_animation_12h, &mode12h_layer.layer, NULL, &to_rect_12h);
      
      animation_schedule(&prop_animation_thick.animation);
      animation_schedule(&prop_animation_thin.animation);
      animation_schedule(&prop_animation_12h.animation);
      aligned_to_single = true;
   }
}

void set_time(PblTm* t) {
  
  // section based on Simplicity by Pebble Team begins
    char *time_format;
    if (clock_is_24h_style()) {
    	time_format = "%H";
    } else {
    	time_format = "%I";
    }
    
    string_format_time(hour_text, sizeof(hour_text), time_format, t);
    
    if (!clock_is_24h_style() && (hour_text[0] == '0')) {
    	memmove(hour_text, &hour_text[1], sizeof(hour_text) - 1);
        align_time_single();
    }
    else
    {
        align_time_double();
    }
  // section ends
  string_format_time(minute_text, sizeof(minute_text), ":%M", t);

   if(clock_is_24h_style())
   {
      text_layer_set_text(&mode12h_layer, mode12h_text);
   }
   else
   {
      //string_format_time(mode12h_text, sizeof(mode12h_text), ":%P", t);
      //string format doesnt give us capitalized letters, this will be easier:
      if (t->tm_hour < 12)
      {
         text_layer_set_text(&mode12h_layer, MODES[0]);
      }
      else
      {
         text_layer_set_text(&mode12h_layer, MODES[1]);
      }
   }

   if(t->tm_min==0&&t->tm_hour==0){
      draw_date(t);
   }
#if HOUR_VIBRATION
   if(t->tm_min==0&&t->tm_sec==0&&t->tm_hour>=HOUR_VIBRATION_START&&t->tm_hour<=HOUR_VIBRATION_END)
   {
      vibes_double_pulse();
   }
#endif
   text_layer_set_text(&thick_time_layer, hour_text);
   text_layer_set_text(&thin_time_layer, minute_text);


}

void handle_init(AppContextRef ctx) {
  (void)ctx;
  window_init(&window, "Window Name");
  window_stack_push(&window, true /* Animated */);

  resource_init_current_app(&APP_RESOURCES);

  GFont roboto = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ROBOTO_THIN_49));
  GFont roboto_bold = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ROBOTO_BOLD_49));
  GFont roboto_small = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ROBOTO_REGULAR_12));
  GFont roboto_12h = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ROBOTO_REGULAR_10));

  window_set_background_color(&window, GColorBlack);

  text_layer_init(&thick_time_layer, GRect(0, 40, 68, 55));
  text_layer_set_text_alignment(&thick_time_layer, GTextAlignmentRight);
  text_layer_set_text_color(&thick_time_layer, GColorWhite);
  text_layer_set_background_color(&thick_time_layer, GColorClear);
  text_layer_set_font(&thick_time_layer, roboto_bold);
  layer_add_child(&window.layer, &thick_time_layer.layer);

  text_layer_init(&thin_time_layer, GRect(68, 40, 76, 55));
  text_layer_set_text_alignment(&thin_time_layer, GTextAlignmentLeft);
  text_layer_set_text_color(&thin_time_layer, GColorWhite);
  text_layer_set_background_color(&thin_time_layer, GColorClear);
  text_layer_set_font(&thin_time_layer, roboto);
  layer_add_child(&window.layer, &thin_time_layer.layer);

  text_layer_init(&date_layer, GRect(0, 100, 144, 20));
  text_layer_set_text_alignment(&date_layer, GTextAlignmentCenter);
  text_layer_set_text_color(&date_layer, GColorWhite);
  text_layer_set_background_color(&date_layer, GColorClear);
  text_layer_set_font(&date_layer, roboto_small);
  layer_add_child(&window.layer, &date_layer.layer);

  text_layer_init(&mode12h_layer, GRect(104, 51, 40, 20));
  text_layer_set_text_alignment(&mode12h_layer, GTextAlignmentRight);
  text_layer_set_text_color(&mode12h_layer, GColorWhite);
  text_layer_set_background_color(&mode12h_layer, GColorClear);
  text_layer_set_font(&mode12h_layer, roboto_12h);
  layer_add_child(&window.layer, &mode12h_layer.layer);

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

void handle_deinit(AppContextRef ctx) {
  (void)ctx;

  fonts_unload_custom_font(roboto);
  fonts_unload_custom_font(roboto_bold);
  fonts_unload_custom_font(roboto_small);
  fonts_unload_custom_font(roboto_12h);
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
