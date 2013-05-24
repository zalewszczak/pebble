#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID { 0x24, 0x96, 0xB4, 0xA9, 0xED, 0x76, 0x48, 0xF9, 0xA8, 0xDB, 0x49, 0xB1, 0x7C, 0x8A, 0x71, 0xBA }
PBL_APP_INFO(MY_UUID,
             "Rounds", "Zalew",
             1, 0, /* App version */
             RESOURCE_ID_IMAGE_MENU_ICON,
             APP_INFO_WATCH_FACE);

Window window;

#define inverted false
#define dash_thickness 4
#define first_circle 11
#define second_circle 31
#define third_circle 51
#define fourth_circle 71

Layer second_display_layer;
Layer minute_display_layer;
Layer hour_display_layer;
TextLayer date_layer;
static char date_text[] = "12";

const GPathInfo SECOND_HAND_PATH_POINTS = {
  4,
  (GPoint []) {
    {-dash_thickness, -first_circle},
    {dash_thickness, -first_circle},
    {dash_thickness, -second_circle},
    {-dash_thickness,  -second_circle},
  }
};

const GPathInfo MINUTE_HAND_PATH_POINTS = {
  4,
  (GPoint []) {
    {-dash_thickness, -second_circle},
    {dash_thickness, -second_circle},
    {dash_thickness, -third_circle},
    {-dash_thickness,  -third_circle},
  }
};

const GPathInfo HOUR_HAND_PATH_POINTS = {
  4,
  (GPoint []) {
    {-dash_thickness, -third_circle},
    {dash_thickness, -third_circle},
    {dash_thickness, -fourth_circle},
    {-dash_thickness,  -fourth_circle},
  }
};

GPath hour_hand_path;
GPath minute_hand_path;
GPath second_hand_path;

void second_display_layer_update_callback(Layer *me, GContext* ctx) {
  (void)me;

  PblTm t;
  get_time(&t);

  unsigned int angle = t.tm_sec * 6;
  gpath_rotate_to(&second_hand_path, (TRIG_MAX_ANGLE / 360) * angle);
 
#if inverted
  graphics_context_set_fill_color(ctx, GColorBlack);
#else
  graphics_context_set_fill_color(ctx, GColorWhite);
#endif
  gpath_draw_filled(ctx, &second_hand_path);
}

void minute_display_layer_update_callback(Layer *me, GContext* ctx) {
  (void)me;

  PblTm t;
  get_time(&t);

  unsigned int angle = t.tm_min * 6 + t.tm_sec / 10;
  gpath_rotate_to(&minute_hand_path, (TRIG_MAX_ANGLE / 360) * angle);
  
#if inverted
  graphics_context_set_fill_color(ctx, GColorBlack);
#else
  graphics_context_set_fill_color(ctx, GColorWhite);
#endif
  gpath_draw_filled(ctx, &minute_hand_path);
}

void hour_display_layer_update_callback(Layer *me, GContext* ctx) {
  (void)me;

  PblTm t;
  get_time(&t);
  GPoint center = grect_center_point(&me->frame);

  unsigned int angle = t.tm_hour * 30 + t.tm_min / 2;
  gpath_rotate_to(&hour_hand_path, (TRIG_MAX_ANGLE / 360) * angle);

#if inverted
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_context_set_stroke_color(ctx, GColorBlack);
#else
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_context_set_stroke_color(ctx, GColorWhite);
#endif
  gpath_draw_filled(ctx, &hour_hand_path);

  graphics_draw_circle(ctx, center, first_circle);
  graphics_draw_circle(ctx, center, second_circle);
  graphics_draw_circle(ctx, center, third_circle);
  graphics_draw_circle(ctx, center, fourth_circle);
}

void draw_date(){
  PblTm t;
  get_time(&t);
  
  string_format_time(date_text, sizeof(date_text), "%d", &t);
  text_layer_set_text(&date_layer, date_text);
}

void handle_init(AppContextRef ctx) {
  (void)ctx;

  window_init(&window, "Rounds Watch");
  window_stack_push(&window, true /* Animated */);
#if inverted
  window_set_background_color(&window, GColorWhite);
#else
  window_set_background_color(&window, GColorBlack);
#endif

  resource_init_current_app(&APP_RESOURCES);

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

  layer_init(&second_display_layer, window.layer.frame);
  second_display_layer.update_proc = &second_display_layer_update_callback;
  layer_add_child(&window.layer, &second_display_layer);
  gpath_init(&second_hand_path, &SECOND_HAND_PATH_POINTS);
  gpath_move_to(&second_hand_path, grect_center_point(&second_display_layer.frame));

  text_layer_init(&date_layer, GRect(0, 72, 144, 30));
#if inverted
  text_layer_set_text_color(&date_layer, GColorBlack);
#else
  text_layer_set_text_color(&date_layer, GColorWhite);
#endif
  text_layer_set_background_color(&date_layer, GColorClear);
  text_layer_set_font(&date_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  text_layer_set_text_alignment(&date_layer, GTextAlignmentCenter);
  text_layer_set_text(&date_layer, date_text);
  layer_add_child(&window.layer, &date_layer.layer);

  draw_date();
}

void handle_second_tick(AppContextRef ctx, PebbleTickEvent *t){
  (void)t;
  (void)ctx;

  if(t->tick_time->tm_sec%10){
     if(t->tick_time->tm_min%2==0)
     {
        layer_mark_dirty(&hour_display_layer);
     }
     layer_mark_dirty(&minute_display_layer);
  }
  layer_mark_dirty(&second_display_layer);
}

void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
    .tick_info = {
			.tick_handler = &handle_second_tick,
			.tick_units = SECOND_UNIT
		}
  };
  app_event_loop(params, &handlers);
}
