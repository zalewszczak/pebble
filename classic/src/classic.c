#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID { 0xAD, 0x80, 0x11, 0xA9, 0x02, 0xB5, 0x4C, 0x88, 0x99, 0xF8, 0x88, 0xF4, 0x38, 0xAE, 0x8B, 0xC2 }
PBL_APP_INFO(MY_UUID,
             "Classic", "Zalew",
             2, 1, /* App version */
             RESOURCE_ID_IMAGE_MENU_ICON,
             APP_INFO_WATCH_FACE);

#define DISPLAY_SECONDS true
#define DISPLAY_TIME true
#define HOUR_VIBRATION true

Window window;

BmpContainer background_image_container;

Layer minute_display_layer;
Layer hour_display_layer;
Layer center_display_layer;
GFont roboto;
TextLayer date_layer;
static char date_text[] = "12";

#if DISPLAY_SECONDS
Layer second_display_layer;
#endif

#if DISPLAY_TIME
TextLayer time_layer;
static char time_text[] = "12:34";
#endif

const GPathInfo MINUTE_HAND_PATH_POINTS = {
  4,
  (GPoint []) {
    {-4, 10},
    {4, 10},
    {4, -55},
    {-4,  -55},
  }
};

const GPathInfo MINUTE_HAND_OUTLINE_PATH_POINTS = {
  4,
  (GPoint []) {
    {-5, 11},
    {5, 11},
    {5, -56},
    {-5,  -56},
  }
};

const GPathInfo MINUTE_HAND_LINE_PATH_POINTS = {
  4,
  (GPoint []) {
    {-2, -10},
    {2, -10},
    {2, -52},
    {-2,  -52},
  }
};

const GPathInfo HOUR_HAND_PATH_POINTS = {
  4,
  (GPoint []) {
    {-4, 10},
    {4, 10},
    {4, -40},
    {-4,  -40},
  }
};

const GPathInfo HOUR_HAND_OUTLINE_PATH_POINTS = {
  4,
  (GPoint []) {
    {-5, 11},
    {5, 11},
    {5, -41},
    {-5,  -41},
  }
};

const GPathInfo HOUR_HAND_LINE_PATH_POINTS = {
  4,
  (GPoint []) {
    {-2, -10},
    {2, -10},
    {2, -38},
    {-2,  -38},
  }
};

GPath hour_hand_path;
GPath hour_hand_outline_path;
GPath hour_hand_line_path;
GPath minute_hand_path;
GPath minute_hand_outline_path;
GPath minute_hand_line_path;

#if DISPLAY_SECONDS
void second_display_layer_update_callback(Layer *me, GContext* ctx) {
  (void)me;

  PblTm t;
  get_time(&t);

  int32_t second_angle = t.tm_sec * (0xffff/60);
  int second_hand_length = 70;

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
  gpath_rotate_to(&minute_hand_line_path, (TRIG_MAX_ANGLE / 360) * angle);
  
  graphics_context_set_fill_color(ctx, GColorBlack);
  gpath_draw_filled(ctx, &minute_hand_outline_path);
  graphics_context_set_fill_color(ctx, GColorWhite);
  gpath_draw_filled(ctx, &minute_hand_path);
  graphics_context_set_fill_color(ctx, GColorBlack);
  gpath_draw_filled(ctx, &minute_hand_line_path);
}

void hour_display_layer_update_callback(Layer *me, GContext* ctx) {
  (void)me;

  PblTm t;

  get_time(&t);

  unsigned int angle = t.tm_hour * 30 + t.tm_min / 2;
  gpath_rotate_to(&hour_hand_path, (TRIG_MAX_ANGLE / 360) * angle);
  gpath_rotate_to(&hour_hand_outline_path, (TRIG_MAX_ANGLE / 360) * angle);
  gpath_rotate_to(&hour_hand_line_path, (TRIG_MAX_ANGLE / 360) * angle);

  graphics_context_set_fill_color(ctx, GColorBlack);
  gpath_draw_filled(ctx, &hour_hand_outline_path);
  graphics_context_set_fill_color(ctx, GColorWhite);
  gpath_draw_filled(ctx, &hour_hand_path);
  graphics_context_set_fill_color(ctx, GColorBlack);
  gpath_draw_filled(ctx, &hour_hand_line_path);
}

void draw_date(){
  PblTm t;
  get_time(&t);
  
  string_format_time(date_text, sizeof(date_text), "%d", &t);
  text_layer_set_text(&date_layer, date_text);
}

#if DISPLAY_TIME
void draw_time(){
  PblTm t;
  get_time(&t);

  // section based on Simplicity by Pebble Team begins
  char *time_format;
  if (clock_is_24h_style()) {
     time_format = "%R";
  } else {
     time_format = "%I:%M";
  }
  string_format_time(time_text, sizeof(time_text), time_format, &t);
  // section ends

  text_layer_set_text(&time_layer, time_text);
}
#endif

void handle_init(AppContextRef ctx) {
  (void)ctx;

  window_init(&window, "Classic Watch");
  window_stack_push(&window, true /* Animated */);

  resource_init_current_app(&APP_RESOURCES);
#if DISPLAY_TIME
  bmp_init_container(RESOURCE_ID_IMAGE_BACKGROUND, &background_image_container);
#else
  bmp_init_container(RESOURCE_ID_IMAGE_BACKGROUND_LOGO, &background_image_container);
#endif
  layer_add_child(&window.layer, &background_image_container.layer.layer);

  roboto = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ROBOTO_THIN_11));

#if DISPLAY_TIME
  text_layer_init(&time_layer, GRect(58, 42, 29, 14));
  text_layer_set_text_alignment(&time_layer, GTextAlignmentCenter);
  text_layer_set_text_color(&time_layer, GColorWhite);
  text_layer_set_background_color(&time_layer, GColorClear);
  text_layer_set_font(&time_layer, roboto);
  layer_add_child(&window.layer, &time_layer.layer);

  draw_time();
#endif

  text_layer_init(&date_layer, GRect(64, 109, 16, 14));
  text_layer_set_text_alignment(&date_layer, GTextAlignmentCenter);
  text_layer_set_text_color(&date_layer, GColorWhite);
  text_layer_set_background_color(&date_layer, GColorClear);
  text_layer_set_font(&date_layer, roboto);
  layer_add_child(&window.layer, &date_layer.layer);

  draw_date();

  layer_init(&hour_display_layer, window.layer.frame);
  hour_display_layer.update_proc = &hour_display_layer_update_callback;
  layer_add_child(&window.layer, &hour_display_layer);

  gpath_init(&hour_hand_outline_path, &HOUR_HAND_OUTLINE_PATH_POINTS);
  gpath_move_to(&hour_hand_outline_path, grect_center_point(&hour_display_layer.frame));
  gpath_init(&hour_hand_path, &HOUR_HAND_PATH_POINTS);
  gpath_move_to(&hour_hand_path, grect_center_point(&hour_display_layer.frame));
  gpath_init(&hour_hand_line_path, &HOUR_HAND_LINE_PATH_POINTS);
  gpath_move_to(&hour_hand_line_path, grect_center_point(&hour_display_layer.frame));

  layer_init(&minute_display_layer, window.layer.frame);
  minute_display_layer.update_proc = &minute_display_layer_update_callback;
  layer_add_child(&window.layer, &minute_display_layer);

  gpath_init(&minute_hand_outline_path, &MINUTE_HAND_OUTLINE_PATH_POINTS);
  gpath_move_to(&minute_hand_outline_path, grect_center_point(&minute_display_layer.frame));
  gpath_init(&minute_hand_path, &MINUTE_HAND_PATH_POINTS);
  gpath_move_to(&minute_hand_path, grect_center_point(&minute_display_layer.frame));
  gpath_init(&minute_hand_line_path, &MINUTE_HAND_LINE_PATH_POINTS);
  gpath_move_to(&minute_hand_line_path, grect_center_point(&minute_display_layer.frame));

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
  fonts_unload_custom_font(roboto);
}

void handle_tick(AppContextRef ctx, PebbleTickEvent *t){
  (void)t;
  (void)ctx;

  if(t->tick_time->tm_sec%10==0)
  {
     layer_mark_dirty(&minute_display_layer);
     
     if(t->tick_time->tm_sec==0)
     {
        if(t->tick_time->tm_min%2==0)
        {
           layer_mark_dirty(&hour_display_layer);
           if(t->tick_time->tm_min==0&&t->tick_time->tm_hour==0)
           {
              draw_date();
           }
        }
#if DISPLAY_TIME
        draw_time();
#endif
#if HOUR_VIBRATION
        if(t->tick_time->tm_min==0)
        {
           vibes_short_pulse();
        }
#endif
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
