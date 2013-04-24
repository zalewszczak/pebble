#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID { 0x18, 0x49, 0x4A, 0x8C, 0x43, 0x61, 0x4B, 0x38, 0x8D, 0xC0, 0x08, 0x64, 0x9C, 0x64, 0x67, 0xE5 }
PBL_APP_INFO(MY_UUID,
             "Maurice", "Zalew",
             2, 1, /* App version */
             RESOURCE_ID_IMAGE_MENU_ICON,
             APP_INFO_WATCH_FACE);

#define DISPLAY_SECONDS true
#define DISPLAY_LOGO true
#define DISPLAY_DATE true
#define HOUR_VIBRATION true
#define HOUR_VIBRATION_START 8
#define HOUR_VIBRATION_END 20

Window window;
BmpContainer background_image_container;

Layer minute_display_layer;
Layer hour_display_layer;
Layer center_display_layer;

#if DISPLAY_LOGO
Layer second_display_layer;
#endif

#if DISPLAY_DATE
TextLayer date_layer;
GFont date_font;
static char date_text[] = "WED 13";
#endif

const GPathInfo MINUTE_HAND_PATH_POINTS = {
  4,
  (GPoint []) {
    {0, 15},
    {6, 0},
    {0, -68},
    {-6, 0},
  }
};

const GPathInfo MINUTE_HAND_OUTLINE_PATH_POINTS = {
  4,
  (GPoint []) {
    {0, 16},
    {7, 0},
    {0, -72},
    {-7,  0},
  }
};

const GPathInfo HOUR_HAND_PATH_POINTS = {
  4,
  (GPoint []) {
    {0, 15},
    {7, 0},
    {0, -50},
    {-7, 0},
  }
};

const GPathInfo HOUR_HAND_OUTLINE_PATH_POINTS = {
  4,
  (GPoint []) {
    {0, 16},
    {8, 0},
    {0, -52},
    {-8,  0},
  }
};

GPath hour_hand_path;
GPath hour_hand_outline_path;
GPath minute_hand_path;
GPath minute_hand_outline_path;

#if DISPLAY_SECONDS
void second_display_layer_update_callback(Layer *me, GContext* ctx) {
  (void)me;

  PblTm t;
  get_time(&t);

  int32_t second_angle = t.tm_sec * (0xffff/60);
  int second_hand_length = 72;

  graphics_context_set_fill_color(ctx, GColorWhite);

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
  graphics_fill_circle(ctx, center, 2);
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_circle(ctx, center, 1);
}

void minute_display_layer_update_callback(Layer *me, GContext* ctx) {
  (void)me;

  PblTm t;

  get_time(&t);

  unsigned int angle = t.tm_min * 6 + t.tm_sec / 10;
  gpath_rotate_to(&minute_hand_path, (TRIG_MAX_ANGLE / 360) * angle);
  gpath_rotate_to(&minute_hand_outline_path, (TRIG_MAX_ANGLE / 360) * angle);
  
  graphics_context_set_fill_color(ctx, GColorBlack);
  gpath_draw_filled(ctx, &minute_hand_outline_path);
  graphics_context_set_fill_color(ctx, GColorWhite);
  gpath_draw_filled(ctx, &minute_hand_path);
}

void hour_display_layer_update_callback(Layer *me, GContext* ctx) {
  (void)me;

  PblTm t;

  get_time(&t);

  unsigned int angle = t.tm_hour * 30 + t.tm_min / 2;
  gpath_rotate_to(&hour_hand_path, (TRIG_MAX_ANGLE / 360) * angle);
  gpath_rotate_to(&hour_hand_outline_path, (TRIG_MAX_ANGLE / 360) * angle);

  graphics_context_set_fill_color(ctx, GColorBlack);
  gpath_draw_filled(ctx, &hour_hand_outline_path);
  graphics_context_set_fill_color(ctx, GColorWhite);
  gpath_draw_filled(ctx, &hour_hand_path);
}

#if DISPLAY_DATE
void draw_date(){
  PblTm t;
  get_time(&t);
  
  string_format_time(date_text, sizeof(date_text), "%a %d", &t);
  text_layer_set_text(&date_layer, date_text);
}
#endif

void handle_init(AppContextRef ctx) {
  (void)ctx;

  window_init(&window, "Maurice Watch");
  window_stack_push(&window, true /* Animated */);

  resource_init_current_app(&APP_RESOURCES);
#if DISPLAY_LOGO
  bmp_init_container(RESOURCE_ID_IMAGE_BACKGROUND_LOGO, &background_image_container);
#else
  bmp_init_container(RESOURCE_ID_IMAGE_BACKGROUND, &background_image_container);
#endif
  layer_add_child(&window.layer, &background_image_container.layer.layer);
#if DISPLAY_DATE
  date_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_RADIOLAND_15));
  text_layer_init(&date_layer, GRect(27, 110, 90, 30));
  text_layer_set_text_alignment(&date_layer, GTextAlignmentCenter);
  text_layer_set_text_color(&date_layer, GColorWhite);
  text_layer_set_background_color(&date_layer, GColorClear);
  text_layer_set_font(&date_layer, date_font);
  layer_add_child(&window.layer, &date_layer.layer);

  draw_date();
#endif

  layer_init(&hour_display_layer, window.layer.frame);
  hour_display_layer.update_proc = &hour_display_layer_update_callback;
  layer_add_child(&window.layer, &hour_display_layer);

  gpath_init(&hour_hand_outline_path, &HOUR_HAND_OUTLINE_PATH_POINTS);
  gpath_move_to(&hour_hand_outline_path, grect_center_point(&hour_display_layer.frame));
  gpath_init(&hour_hand_path, &HOUR_HAND_PATH_POINTS);
  gpath_move_to(&hour_hand_path, grect_center_point(&hour_display_layer.frame));

  layer_init(&minute_display_layer, window.layer.frame);
  minute_display_layer.update_proc = &minute_display_layer_update_callback;
  layer_add_child(&window.layer, &minute_display_layer);

  gpath_init(&minute_hand_outline_path, &MINUTE_HAND_OUTLINE_PATH_POINTS);
  gpath_move_to(&minute_hand_outline_path, grect_center_point(&minute_display_layer.frame));
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
#if DISPLAY_DATE
  fonts_unload_custom_font(date_font);
#endif
}

void handle_second_tick(AppContextRef ctx, PebbleTickEvent *t){
  (void)t;
  (void)ctx;
/*
  if(t->tick_time->tm_sec!=0)
  {
     if(t->tick_time->tm_sec%10==0)
     {
        layer_mark_dirty(&minute_display_layer);
     }
     layer_mark_dirty(&second_display_layer);
  }
  else if(t->tick_time->tm_min!=0&&t->tick_time->tm_hour!=0)
  {
     if(t->tick_time->tm_min%2==0)
     {
        layer_mark_dirty(&hour_display_layer);
     }
     layer_mark_dirty(&second_display_layer);
     layer_mark_dirty(&minute_display_layer);
  }
  else
  {
     layer_mark_dirty(&hour_display_layer);
     layer_mark_dirty(&second_display_layer);
     layer_mark_dirty(&minute_display_layer);
     draw_date();
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
#if DISPLAY_DATE
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
			.tick_handler = &handle_second_tick,
#if DISPLAY_SECONDS
			.tick_units = SECOND_UNIT
#else 
			.tick_units = MINUTE_UNIT
#endif
		}
  };
  app_event_loop(params, &handlers);
}
