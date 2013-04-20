#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID { 0x4F, 0x4E, 0xEE, 0xFA, 0x16, 0xB0, 0x46, 0xFE, 0x82, 0x1E, 0xDC, 0xCF, 0xB5, 0xD2, 0x27, 0x19 }
PBL_APP_INFO(MY_UUID,
             "Brown", "Zalew",
             1, 0, /* App version */
             RESOURCE_ID_IMAGE_MENU_ICON,
             APP_INFO_WATCH_FACE);

Window window;
BmpContainer background_image_container;

Layer minute_display_layer;
Layer hour_display_layer;
Layer center_display_layer;
Layer second_display_layer;
TextLayer date_layer;

static char date_text[] = "Sat 13";

const GPathInfo MINUTE_HAND_PATH_POINTS = {
  4,
  (GPoint []) {
    {-3, 0},
    {3, 0},
    {3, -60},
    {-3,  -60},
  }
};

const GPathInfo MINUTE_HAND_OUTLINE_PATH_POINTS = {
  4,
  (GPoint []) {
    {-4, 0},
    {4, 0},
    {4, -61},
    {-4,  -61},
  }
};

const GPathInfo HOUR_HAND_PATH_POINTS = {
  4,
  (GPoint []) {
    {-3, 0},
    {3, 0},
    {3, -40},
    {-3,  -40},
  }
};

const GPathInfo HOUR_HAND_OUTLINE_PATH_POINTS = {
  4,
  (GPoint []) {
    {-4, 16},
    {4, 16},
    {4, -41},
    {-4,  -41},
  }
};

GPath hour_hand_path;
GPath hour_hand_outline_path;
GPath minute_hand_path;
GPath minute_hand_outline_path;

void second_display_layer_update_callback(Layer *me, GContext* ctx) {
  (void)me;

  PblTm t;
  get_time(&t);

  int32_t second_angle = t.tm_sec * (0xffff/60);
  int32_t counter_second_angle = t.tm_sec * (0xffff/60);
  if(t.tm_sec<30)
  {
     counter_second_angle += 0xffff/2;
  }
  else
  {
     counter_second_angle -= 0xffff/2;
  }
  int second_hand_length = 70;
  int counter_second_hand_length = 15;

  graphics_context_set_fill_color(ctx, GColorWhite);

  GPoint center = grect_center_point(&me->frame);
  GPoint counter_second = GPoint(center.x + counter_second_hand_length * sin_lookup(counter_second_angle)/0xffff,
				center.y + (-counter_second_hand_length) * cos_lookup(counter_second_angle)/0xffff);
  GPoint second = GPoint(center.x + second_hand_length * sin_lookup(second_angle)/0xffff,
				center.y + (-second_hand_length) * cos_lookup(second_angle)/0xffff);

  graphics_draw_line(ctx, counter_second, second);
}

void center_display_layer_update_callback(Layer *me, GContext* ctx) {
  (void)me;

  GPoint center = grect_center_point(&me->frame);
  //graphics_context_set_fill_color(ctx, GColorBlack);
  //graphics_fill_circle(ctx, center, 5);
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_circle(ctx, center, 4);
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

void draw_date(){
  PblTm t;
  get_time(&t);
  
  string_format_time(date_text, sizeof(date_text), "%a %d", &t);
  text_layer_set_text(&date_layer, date_text);
}

void handle_init(AppContextRef ctx) {
  (void)ctx;

  window_init(&window, "Brown Watch");
  window_stack_push(&window, true /* Animated */);
  //window_set_background_color(&window, GColorBlack);

  resource_init_current_app(&APP_RESOURCES);
  bmp_init_container(RESOURCE_ID_IMAGE_BACKGROUND, &background_image_container);
  layer_add_child(&window.layer, &background_image_container.layer.layer);

  GFont sans = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_OPENSANS_REGULAR_14));
  text_layer_init(&date_layer, GRect(27, 110, 90, 30));
  text_layer_set_text_alignment(&date_layer, GTextAlignmentCenter);
  text_layer_set_text_color(&date_layer, GColorWhite);
  text_layer_set_background_color(&date_layer, GColorClear);
  text_layer_set_font(&date_layer, sans);
  layer_add_child(&window.layer, &date_layer.layer);

  draw_date();

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

  layer_init(&second_display_layer, window.layer.frame);
  second_display_layer.update_proc = &second_display_layer_update_callback;
  layer_add_child(&window.layer, &second_display_layer);
}

void handle_deinit(AppContextRef ctx) {
  (void)ctx;

  bmp_deinit_container(&background_image_container);
}

void handle_second_tick(AppContextRef ctx, PebbleTickEvent *t){
  (void)t;
  (void)ctx;

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
