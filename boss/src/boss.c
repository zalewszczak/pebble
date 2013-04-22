#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID { 0x7D, 0xBE, 0x9F, 0x98, 0xED, 0x6D, 0x45, 0xC7, 0x82, 0x4F, 0xED, 0x22, 0x26, 0x48, 0x61, 0xA7 }
PBL_APP_INFO(MY_UUID,
             "Boss", "Zalew",
             2, 0, /* App version */
             RESOURCE_ID_IMAGE_MENU_ICON,
             APP_INFO_WATCH_FACE);

#define DISPLAY_SECONDS false
#define DISPLAY_FILLED_HANDS true
#define DISPLAY_DATE true
#define DISPLAY_LOGO false

Window window;
BmpContainer background_image_container;
#if DISPLAY_SECONDS
Layer second_display_layer;
#endif
Layer time_display_layer;
#if DISPLAY_DATE
TextLayer date_layer;
GFont date_font;
static char date_text[] = "12";
#endif

#if DISPLAY_FILLED_HANDS
const GPathInfo HOUR_HAND_PATH_POINTS = {
  4,
  (GPoint []) {
    {0, 0},
    {4, -20},
    {0,  -40},
    {-4, -20},
  }
};

const GPathInfo MINUTE_HAND_PATH_POINTS = {
  4,
  (GPoint []) {
    {0, 0},
    {4, -20},
    {0,  -60},
    {-4, -20},
  }
};

GPath hour_hand_path;
GPath minute_hand_path;
#endif

#if DISPLAY_SECONDS
void second_display_layer_update_callback(Layer *me, GContext* ctx) {
  (void)me;

  PblTm t;
  get_time(&t);

  int32_t second_angle = t.tm_sec * (0xffff/60);
  int second_hand_length = 70;

  graphics_context_set_fill_color(ctx, GColorWhite);

  GPoint center = GPoint((144/2),(168/2));
  GPoint second = GPoint(center.x + second_hand_length * sin_lookup(second_angle)/0xffff,
				center.y + (-second_hand_length) * cos_lookup(second_angle)/0xffff);

  graphics_draw_line(ctx, center, second);
}
#endif

void time_display_layer_update_callback(Layer *me, GContext* ctx) {
  (void)me;
#if DISPLAY_FILLED_HANDS
  PblTm t;
  get_time(&t);

  unsigned int hour_angle = t.tm_hour * 30 + t.tm_min / 2;
  unsigned int minute_angle = t.tm_min * 6;
  gpath_rotate_to(&hour_hand_path, (TRIG_MAX_ANGLE / 360) * hour_angle);
  gpath_rotate_to(&minute_hand_path, (TRIG_MAX_ANGLE / 360) * minute_angle);
  
  graphics_context_set_fill_color(ctx, GColorWhite);
  gpath_draw_filled(ctx, &hour_hand_path);
  gpath_draw_filled(ctx, &minute_hand_path);
  gpath_draw_outline(ctx, &hour_hand_path);
  gpath_draw_outline(ctx, &minute_hand_path);
#else
  //Old hands drawing section, new above based on Segment Six watchface - allows to draw filled shapes
  PblTm t;
  get_time(&t);

  int32_t hour_angle = (t.tm_hour % 12) * (0xffff/12) + t.tm_min * (0xffff/720);
  int32_t hour_angle_offset1 = 0;
  int32_t hour_angle_offset2 = 0;
  int32_t minute_angle = t.tm_min * (0xffff/60);
  int32_t minute_angle_offset1 = 0;
  int32_t minute_angle_offset2 = 0;

  int hour_hand_length = 40;
  int minute_hand_length = 60;

  if(hour_angle<0xffff/36)
  {
     hour_angle_offset1 = hour_angle + (0xffff/36)*35;
     hour_angle_offset2 = hour_angle + 0xffff/36;
  }
  else if(hour_angle>(0xffff/36)*35)
  {
     hour_angle_offset1 = hour_angle - 0xffff/36;
     hour_angle_offset2 = hour_angle - (0xffff/36)*35;
  }
  else
  {
     hour_angle_offset1 = hour_angle - 0xffff/36;
     hour_angle_offset2 = hour_angle + 0xffff/36;
  }


  if(minute_angle<0xffff/36)
  {
     minute_angle_offset1 = minute_angle + (0xffff/36)*35;
     minute_angle_offset2 = minute_angle + 0xffff/36;
  }
  else if(hour_angle>(0xffff/36)*35)
  {
     minute_angle_offset1 = minute_angle - 0xffff/36;
     minute_angle_offset2 = minute_angle - (0xffff/36)*35;
  }
  else
  {
     minute_angle_offset1 = minute_angle - 0xffff/36;
     minute_angle_offset2 = minute_angle + 0xffff/36;
  }

  GPoint center = GPoint((144/2),(168/2));
  GPoint hour = GPoint(center.x + hour_hand_length * sin_lookup(hour_angle)/0xffff,
				center.y + (-hour_hand_length) * cos_lookup(hour_angle)/0xffff);
  GPoint hour_offset1 = GPoint(center.x + (hour_hand_length/2) * sin_lookup(hour_angle_offset1)/0xffff,
				center.y + (-(hour_hand_length/2)) * cos_lookup(hour_angle_offset1)/0xffff);
  GPoint hour_offset2 = GPoint(center.x + (hour_hand_length/2) * sin_lookup(hour_angle_offset2)/0xffff,
				center.y + (-(hour_hand_length/2)) * cos_lookup(hour_angle_offset2)/0xffff);
  GPoint minute = GPoint(center.x + minute_hand_length * sin_lookup(minute_angle)/0xffff,
				center.y + (-minute_hand_length) * cos_lookup(minute_angle)/0xffff);
  GPoint minute_offset1 = GPoint(center.x + (minute_hand_length/3) * sin_lookup(minute_angle_offset1)/0xffff,
				center.y + (-(minute_hand_length/3)) * cos_lookup(minute_angle_offset1)/0xffff);
  GPoint minute_offset2 = GPoint(center.x + (minute_hand_length/3) * sin_lookup(minute_angle_offset2)/0xffff,
				center.y + (-(minute_hand_length/3)) * cos_lookup(minute_angle_offset2)/0xffff);

  graphics_context_set_fill_color(ctx, GColorWhite);

  graphics_draw_line(ctx, center, hour_offset1);
  graphics_draw_line(ctx, hour_offset1, hour);
  graphics_draw_line(ctx, hour, hour_offset2);
  graphics_draw_line(ctx, hour_offset2, center);

  graphics_draw_line(ctx, center, minute_offset1);
  graphics_draw_line(ctx, minute_offset1, minute);
  graphics_draw_line(ctx, minute, minute_offset2);
  graphics_draw_line(ctx, minute_offset2, center);
#endif
}

#if DISPLAY_DATE
void draw_date(){
  PblTm t;
  get_time(&t);
  
  string_format_time(date_text, sizeof(date_text), "%d", &t);
  text_layer_set_text(&date_layer, date_text);
}
#endif

void handle_init(AppContextRef ctx) {
  (void)ctx;

  window_init(&window, "Boss");
  window_stack_push(&window, true /* Animated */);

  resource_init_current_app(&APP_RESOURCES);
#if DISPLAY_DATE && DISPLAY_LOGO
  bmp_init_container(RESOURCE_ID_IMAGE_BACKGROUND_DATE_LOGO, &background_image_container);
#elif DISPLAY_DATE
  bmp_init_container(RESOURCE_ID_IMAGE_BACKGROUND_DATE, &background_image_container);
#elif DISPLAY_LOGO
  bmp_init_container(RESOURCE_ID_IMAGE_BACKGROUND_LOGO, &background_image_container);
#else
  bmp_init_container(RESOURCE_ID_IMAGE_BACKGROUND, &background_image_container);
#endif
  layer_add_child(&window.layer, &background_image_container.layer.layer);

#if DISPLAY_DATE
  GFont date_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_JOSEFINSLAB_BOLDITALIC_15));
  text_layer_init(&date_layer, GRect(60, 120, 22, 19));
  text_layer_set_text_alignment(&date_layer, GTextAlignmentCenter);
  text_layer_set_text_color(&date_layer, GColorBlack);
  text_layer_set_background_color(&date_layer, GColorClear);
  text_layer_set_font(&date_layer, date_font);
  layer_add_child(&window.layer, &date_layer.layer);

  draw_date();
#endif

  layer_init(&time_display_layer, window.layer.frame);
  time_display_layer.update_proc = &time_display_layer_update_callback;
  layer_add_child(&window.layer, &time_display_layer);
#if DISPLAY_FILLED_HANDS
  gpath_init(&minute_hand_path, &MINUTE_HAND_PATH_POINTS);
  gpath_move_to(&minute_hand_path, grect_center_point(&time_display_layer.frame));
  gpath_init(&hour_hand_path, &HOUR_HAND_PATH_POINTS);
  gpath_move_to(&hour_hand_path, grect_center_point(&time_display_layer.frame));
#endif

#if DISPLAY_SECONDS
  layer_init(&second_display_layer, window.layer.frame);
  second_display_layer.update_proc = &second_display_layer_update_callback;
  layer_add_child(&window.layer, &second_display_layer);
#endif
}

void handle_second_tick(AppContextRef ctx, PebbleTickEvent *t){
  (void)t;
  (void)ctx;

  layer_mark_dirty(&time_display_layer);

#if DISPLAY_SECONDS
  layer_mark_dirty(&second_display_layer);
#endif
#if DISPLAY_DATE
  if(t->tick_time->tm_min==0&&t->tick_time->tm_hour==0)
  {
     draw_date();
  }
#endif
}

void handle_deinit(AppContextRef ctx) {
  (void)ctx;

  bmp_deinit_container(&background_image_container);
#if DISPLAY_DATE
  fonts_unload_custom_font(date_font);
#endif
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
