#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID { 0x9B, 0x89, 0xF4, 0xB8, 0x2B, 0xEB, 0x4F, 0xBA, 0x9A, 0xE9, 0xAB, 0xA6, 0x6E, 0x45, 0xA7, 0xDA }
PBL_APP_INFO(MY_UUID,
             "Modern", "Zalew",
             2, 1, /* App version */
             RESOURCE_ID_IMAGE_MENU_ICON,
             APP_INFO_WATCH_FACE);
/*preprocessor conditions:
DISPLAY_SECONDS - draws seconds hand
DISPLAY_DATE_* - draws date PICK ONLY ONE
            +ANALOG - box in place of number 3 with number
            +DIGITAL - text with month and day on top
            +DIGITAL_DAY - text with day and month on top
DISPLAY_LOGO - draws logo at the bottom
HOUR_VIBRATION - short vibration every hour between 8:00 and 22:00
*/

#define DISPLAY_SECONDS true
#define DISPLAY_DATE_ANALOG false
#define DISPLAY_DATE_DIGITAL false
#define DISPLAY_DATE_DIGITAL_DAY true
#define DISPLAY_LOGO false
#define HOUR_VIBRATION true
#define HOUR_VIBRATION_START 8
#define HOUR_VIBRATION_END 20

Window window;
BmpContainer background_image_container;

Layer minute_display_layer;
Layer hour_display_layer;
Layer center_display_layer;
Layer second_display_layer;
#if DISPLAY_DATE_ANALOG || DISPLAY_DATE_DIGITAL || DISPLAY_DATE_DIGITAL_DAY
TextLayer date_layer;
GFont date_font;
static char date_text[] = "Wed 13";
#endif

const GPathInfo MINUTE_HAND_PATH_POINTS = {
  4,
  (GPoint []) {
    {-4, 15},
    {4, 15},
    {4, -70},
    {-4,  -70},
  }
};


const GPathInfo HOUR_HAND_PATH_POINTS = {
  4,
  (GPoint []) {
    {-4, 15},
    {4, 15},
    {4, -50},
    {-4,  -50},
  }
};


GPath hour_hand_path;
GPath minute_hand_path;

#if DISPLAY_SECONDS
void second_display_layer_update_callback(Layer *me, GContext* ctx) {
  (void)me;

  PblTm t;
  get_time(&t);

  int32_t second_angle = t.tm_sec * (0xffff/60);
  int second_hand_length = 70;

  graphics_context_set_stroke_color(ctx, GColorWhite);

  GPoint center = grect_center_point(&me->frame);
  GPoint second = GPoint(center.x + second_hand_length * sin_lookup(second_angle)/0xffff,
				center.y + (-second_hand_length) * cos_lookup(second_angle)/0xffff);

  graphics_draw_line(ctx, center, second);
}
#endif
void center_display_layer_update_callback(Layer *me, GContext* ctx) {
  (void)me;

  GPoint center = grect_center_point(&me->frame);
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_circle(ctx, center, 4);
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_circle(ctx, center, 3);
}

void minute_display_layer_update_callback(Layer *me, GContext* ctx) {
  (void)me;

  PblTm t;

  get_time(&t);

  unsigned int angle = t.tm_min * 6 + t.tm_sec / 10;
  gpath_rotate_to(&minute_hand_path, (TRIG_MAX_ANGLE / 360) * angle);
  
  graphics_context_set_fill_color(ctx, GColorWhite);
  gpath_draw_filled(ctx, &minute_hand_path);
  graphics_context_set_stroke_color(ctx, GColorBlack);
  gpath_draw_outline(ctx, &minute_hand_path);
}

void hour_display_layer_update_callback(Layer *me, GContext* ctx) {
  (void)me;

  PblTm t;

  get_time(&t);

  unsigned int angle = t.tm_hour * 30 + t.tm_min / 2;
  gpath_rotate_to(&hour_hand_path, (TRIG_MAX_ANGLE / 360) * angle);

  graphics_context_set_fill_color(ctx, GColorWhite);
  gpath_draw_filled(ctx, &hour_hand_path);
  graphics_context_set_stroke_color(ctx, GColorBlack);
  gpath_draw_outline(ctx, &hour_hand_path);
}
#if DISPLAY_DATE_ANALOG
void draw_date(){
  PblTm t;
  get_time(&t);
  
  string_format_time(date_text, sizeof(date_text), "%d", &t);
  text_layer_set_text(&date_layer, date_text);
}
#elif DISPLAY_DATE_DIGITAL
void draw_date(){
  PblTm t;
  get_time(&t);
  
  string_format_time(date_text, sizeof(date_text), "%d-%m", &t);
  text_layer_set_text(&date_layer, date_text);
}
#elif DISPLAY_DATE_DIGITAL_DAY
void draw_date(){
  PblTm t;
  get_time(&t);
  
  string_format_time(date_text, sizeof(date_text), "%a %d", &t);
  text_layer_set_text(&date_layer, date_text);
}
#endif

void handle_init(AppContextRef ctx) {
  (void)ctx;

  window_init(&window, "Modern Watch");
  window_stack_push(&window, true /* Animated */);
  resource_init_current_app(&APP_RESOURCES);

#if DISPLAY_LOGO && DISPLAY_DATE_ANALOG
  bmp_init_container(RESOURCE_ID_IMAGE_BACKGROUND_LOGO_DATEBOX, &background_image_container);
#elif DISPLAY_LOGO
  bmp_init_container(RESOURCE_ID_IMAGE_BACKGROUND_LOGO, &background_image_container);
#elif DISPLAY_DATE_ANALOG
  bmp_init_container(RESOURCE_ID_IMAGE_BACKGROUND_DATEBOX, &background_image_container);
#else
  bmp_init_container(RESOURCE_ID_IMAGE_BACKGROUND, &background_image_container);
#endif
  layer_add_child(&window.layer, &background_image_container.layer.layer);

#if DISPLAY_DATE_ANALOG
  date_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ORBITRON_MEDIUM_12));
  text_layer_init(&date_layer, GRect(116, 77, 20, 20));
  text_layer_set_text_color(&date_layer, GColorBlack);
#elif DISPLAY_DATE_DIGITAL || DISPLAY_DATE_DIGITAL_DAY
  date_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_DIGITALDREAM_NARROW_12));
  text_layer_init(&date_layer, GRect(27, 40, 90, 30));
  text_layer_set_text_color(&date_layer, GColorWhite);
#endif
#if DISPLAY_DATE_ANALOG || DISPLAY_DATE_DIGITAL || DISPLAY_DATE_DIGITAL_DAY
  text_layer_set_text_alignment(&date_layer, GTextAlignmentCenter);
  text_layer_set_background_color(&date_layer, GColorClear);
  text_layer_set_font(&date_layer, date_font);
  layer_add_child(&window.layer, &date_layer.layer);

  draw_date();
#endif
  layer_init(&hour_display_layer, window.layer.frame);
  hour_display_layer.update_proc = &hour_display_layer_update_callback;
  layer_add_child(&window.layer, &hour_display_layer);

  gpath_init(&hour_hand_path, &HOUR_HAND_PATH_POINTS);
  gpath_move_to(&hour_hand_path, grect_center_point(&hour_display_layer.frame));

  layer_init(&minute_display_layer, window.layer.frame);
  minute_display_layer.update_proc = &minute_display_layer_update_callback;
  layer_add_child(&window.layer, &minute_display_layer);

  gpath_init(&minute_hand_path, &MINUTE_HAND_PATH_POINTS);
  gpath_move_to(&minute_hand_path, grect_center_point(&minute_display_layer.frame));

  layer_init(&center_display_layer, window.layer.frame);
  center_display_layer.update_proc = &center_display_layer_update_callback;
  layer_add_child(&window.layer, &center_display_layer);
#if DISPLAY_SECONDS
  layer_init(&second_display_layer, window.layer.frame);
  second_display_layer.update_proc = &second_display_layer_update_callback;
  layer_add_child(&window.layer, &second_display_layer);
#endif
}

void handle_deinit(AppContextRef ctx) {
  (void)ctx;

  bmp_deinit_container(&background_image_container);
#if DISPLAY_DATE_DIGITAL || DISPLAY_DATE_DIGITAL_DAY || DISPLAY_ANALOG
  fonts_unload_custom_font(date_font);
#endif
}

void handle_tick(AppContextRef ctx, PebbleTickEvent *t){
  (void)t;
  (void)ctx;
/*
#if DISPLAY_SECONDS
  if(t->tick_time->tm_sec!=0)
  {
     if(t->tick_time->tm_sec%10==0)
     {
        layer_mark_dirty(&minute_display_layer);
     }
     layer_mark_dirty(&second_display_layer);
  }
  else 
#endif
  if(t->tick_time->tm_min!=0&&t->tick_time->tm_hour!=0)
  {
     if(t->tick_time->tm_min%2==0)
     {
        layer_mark_dirty(&hour_display_layer);
     }
#if DISPLAY_SECONDS
     layer_mark_dirty(&second_display_layer);
#endif
     layer_mark_dirty(&minute_display_layer);
  }
  else
  {
     layer_mark_dirty(&hour_display_layer);
#if DISPLAY_SECONDS
     layer_mark_dirty(&second_display_layer);
#endif
     layer_mark_dirty(&minute_display_layer);
#if DISPLAY_DATE_ANALOG || DISPLAY_DATE_DIGITAL || DISPLAY_DATE_DIGITAL_DAY
     draw_date();
#endif
  }
*/


  if(t->tick_time->tm_sec%10==0)
  {
     layer_mark_dirty(&minute_display_layer);
     
     if(t->tick_time->tm_sec==0)
     {
        if(t->tick_time->tm_min%2==0)
        {
           layer_mark_dirty(&hour_display_layer);
#if DISPLAY_DATE_ANALOG || DISPLAY_DATE_DIGITAL || DISPLAY_DATE_DIGITAL_DAY
           if(t->tick_time->tm_min==0&&t->tick_time->tm_hour==0)
           {
              draw_date();
           }
#endif
#if HOUR_VIBRATION
           if(t->tick_time->tm_min==0
                 &&t->tick_time->tm_hour>=HOUR_VIBRATION_START
                    &&t->tick_time->tm_hour<=HOUR_VIBRATION_END)
           {
              vibes_double_pulse();
           }
#endif
        }
     }
  }

#if DISPLAY_SECONDS
  layer_mark_dirty(&second_display_layer);
#endif
}

void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
    .deinit_handler = &handle_deinit,
    .tick_info = {
			.tick_handler = &handle_tick,
#if DISPLAY_SECONDS
			.tick_units = SECOND_UNIT
#else 
			.tick_units = MINUTE_UNIT
#endif
		}
  };
  app_event_loop(params, &handlers);
}
