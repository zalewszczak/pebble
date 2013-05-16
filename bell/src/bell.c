#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID { 0xE7, 0x2D, 0x5A, 0x78, 0xCE, 0x57, 0x4D, 0xFE, 0x97, 0x1A, 0x6D, 0x09, 0xE0, 0x46, 0x06, 0x9C }
PBL_APP_INFO(MY_UUID,
             "Bell", "Zalew",
             1, 1, /* App version */
             RESOURCE_ID_IMAGE_MENU_ICON,
             APP_INFO_WATCH_FACE);

#include "build_config.h"
#define HOUR_VIBRATION_START 8
#define HOUR_VIBRATION_END 22

Window window;
BmpContainer background_image_container;

Layer minute_display_layer;
Layer hour_display_layer;
Layer center_display_layer;
Layer second_display_layer;
#if DISPLAY_DATE
TextLayer date_layer;
GFont date_font;
static char date_text[] = "ABCD. 12";
#endif

#include "lang.h"

const GPathInfo MINUTE_HAND_PATH_POINTS = {
  5,
  (GPoint []) {
    {-5, -16},
    {5, -16},
    {8,  -50},
    {0, -70},
    {-8,  -50},
  }
};

const GPathInfo HOUR_HAND_PATH_POINTS = {
  5,
  (GPoint []) {
    {-6, -16},
    {6, -16},
    {8,  -30},
    {0, -50},
    {-8,  -30},
  }
};

GPath hour_hand_path;
GPath minute_hand_path;

AppTimerHandle timer_handle;
#define COOKIE_MY_TIMER 1
#define ANIM_IDLE 0
#define ANIM_START 1
#define ANIM_HOURS 2
#define ANIM_MINUTES 3
#define ANIM_SECONDS 4
#define ANIM_DONE 5
int init_anim = ANIM_DONE;
int32_t second_angle_anim = 0;
int32_t counter_second_angle_anim = 0;
unsigned int minute_angle_anim = 0;
unsigned int hour_angle_anim = 0;

void handle_timer(AppContextRef ctx, AppTimerHandle handle, uint32_t cookie) {
  (void)ctx;
  (void)handle;

  if (cookie == COOKIE_MY_TIMER) {
    if(init_anim == ANIM_START)
    {
        init_anim = ANIM_HOURS;
        timer_handle = app_timer_send_event(ctx, 50 /* milliseconds */, COOKIE_MY_TIMER);
    }
    else if(init_anim==ANIM_HOURS)
    {
        layer_mark_dirty(&hour_display_layer);
        timer_handle = app_timer_send_event(ctx, 50 /* milliseconds */, COOKIE_MY_TIMER);
    }
    else if(init_anim==ANIM_MINUTES)
    {
        layer_mark_dirty(&minute_display_layer);
        timer_handle = app_timer_send_event(ctx, 50 /* milliseconds */, COOKIE_MY_TIMER);
    }
    else if(init_anim==ANIM_SECONDS)
    {
        layer_mark_dirty(&second_display_layer);
        timer_handle = app_timer_send_event(ctx, 50 /* milliseconds */, COOKIE_MY_TIMER);
    }
  }

}

void second_display_layer_update_callback(Layer *me, GContext* ctx) {
  (void)me;

  PblTm t;
  get_time(&t);

  int32_t second_angle = t.tm_sec * (0xffff/60);
  int32_t counter_second_angle = t.tm_sec * (0xffff/60);
  int second_hand_length = 70;
  int counter_second_hand_length = 17;
  int circle_radius = 7;
  GPoint center = grect_center_point(&me->frame);
  GPoint second = GPoint(center.x, center.y - second_hand_length);
  GPoint counter_second = GPoint(center.x, center.y + counter_second_hand_length);

  if(init_anim < ANIM_SECONDS)
  {
     second = GPoint(center.x, center.y - second_hand_length);
     counter_second = GPoint(center.x, center.y + counter_second_hand_length);
  }
  else if(init_anim==ANIM_SECONDS)
  {
     second_angle_anim += 0xffff/60;
     if(second_angle_anim<0xffff/2)
     {
        counter_second_angle_anim += 0xffff/2;
     }
     else
     {
        counter_second_angle_anim -= 0xffff/2;
     }
     if(second_angle_anim >= second_angle)
     {
        init_anim = ANIM_DONE;
        second = GPoint(center.x + second_hand_length * sin_lookup(second_angle)/0xffff,
				center.y + (-second_hand_length) * cos_lookup(second_angle)/0xffff);
        counter_second = GPoint(center.x + counter_second_hand_length * sin_lookup(counter_second_angle)/0xffff,
				center.y + (-counter_second_hand_length) * cos_lookup(counter_second_angle)/0xffff);
     }
     else
     {
        second = GPoint(center.x + second_hand_length * sin_lookup(second_angle_anim)/0xffff,
				center.y + (-second_hand_length) * cos_lookup(second_angle_anim)/0xffff);
        counter_second = GPoint(center.x + counter_second_hand_length * sin_lookup(counter_second_angle_anim)/0xffff,
				center.y + (-counter_second_hand_length) * cos_lookup(counter_second_angle_anim)/0xffff);
     }
  }
  else 
  {
     second = GPoint(center.x + second_hand_length * sin_lookup(second_angle)/0xffff,
			center.y + (-second_hand_length) * cos_lookup(second_angle)/0xffff);
     counter_second = GPoint(center.x + counter_second_hand_length * sin_lookup(counter_second_angle)/0xffff,
		        center.y + (-counter_second_hand_length) * cos_lookup(counter_second_angle)/0xffff);
  }

#if INVERTED
  graphics_context_set_stroke_color(ctx, GColorBlack);
#else
  graphics_context_set_stroke_color(ctx, GColorWhite);
#endif

  graphics_draw_line(ctx, counter_second, second);
}

void center_display_layer_update_callback(Layer *me, GContext* ctx) {
  (void)me;

  GPoint center = grect_center_point(&me->frame);
#if INVERTED
  //graphics_context_set_fill_color(ctx, GColorWhite);
  //graphics_fill_circle(ctx, center, 16);
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_circle(ctx, center, 2);
#else
  //graphics_context_set_fill_color(ctx, GColorBlack);
  //graphics_fill_circle(ctx, center, 16);
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_circle(ctx, center, 2);
#endif
}

void minute_display_layer_update_callback(Layer *me, GContext* ctx) {
  (void)me;

  PblTm t;

  get_time(&t);

  unsigned int angle = t.tm_min * 6 + t.tm_sec / 10;

  if(init_anim < ANIM_MINUTES)
  {
     angle = 0;
  }
  else if(init_anim==ANIM_MINUTES)
  {
     minute_angle_anim += 6;
     if(minute_angle_anim >= angle)
     {
        init_anim = ANIM_SECONDS;
     }
     else
     {
        angle = minute_angle_anim;
     }
  }

  gpath_rotate_to(&minute_hand_path, (TRIG_MAX_ANGLE / 360) * angle);


#if INVERTED
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_context_set_stroke_color(ctx, GColorWhite);
#else
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_context_set_stroke_color(ctx, GColorBlack);
#endif

  gpath_draw_filled(ctx, &minute_hand_path);
  gpath_draw_outline(ctx, &minute_hand_path);
}

void hour_display_layer_update_callback(Layer *me, GContext* ctx) {
  (void)me;

  PblTm t;

  get_time(&t);

  unsigned int angle = t.tm_hour * 30 + t.tm_min / 2;

  if(init_anim < ANIM_HOURS)
  {
     angle = 0;
  }
  else if(init_anim==ANIM_HOURS)
  {
     if(hour_angle_anim==0&&t.tm_hour>=12)
     {
        hour_angle_anim = 360;
     }
     hour_angle_anim += 6;
     if(hour_angle_anim >= angle)
     {
        init_anim = ANIM_MINUTES;
     }
     else
     {
        angle = hour_angle_anim;
     }
  }

  gpath_rotate_to(&hour_hand_path, (TRIG_MAX_ANGLE / 360) * angle);

#if INVERTED
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_context_set_stroke_color(ctx, GColorWhite);
#else
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_context_set_stroke_color(ctx, GColorBlack);
#endif

  gpath_draw_filled(ctx, &hour_hand_path);
  gpath_draw_outline(ctx, &hour_hand_path);
}
#if DISPLAY_DATE
void draw_date(){
  PblTm t;
  get_time(&t);
  
  char day[] = "14";
  string_format_time(day, sizeof(day), "%d", &t);
  
  size_t size = sizeof(date_text);
  memset(date_text, 0, size);
  
  strncat(date_text, DAYS[t.tm_wday], size);
  size -= strlen(DAYS[t.tm_wday]);
  strncat(date_text, " ", size);
  size -= strlen(" ");
  strncat(date_text, day, size);
  text_layer_set_text(&date_layer, date_text);
}
#endif
void handle_init(AppContextRef ctx) {
  (void)ctx;

  window_init(&window, "Bell Watch");
  window_stack_push(&window, true /* Animated */);
  resource_init_current_app(&APP_RESOURCES);

#if INVERTED
  bmp_init_container(RESOURCE_ID_IMAGE_BACKGROUND_INVERTED, &background_image_container);
#else
  bmp_init_container(RESOURCE_ID_IMAGE_BACKGROUND, &background_image_container);
#endif
  layer_add_child(&window.layer, &background_image_container.layer.layer);

#if DISPLAY_DATE
  date_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ORBITRON_HEAVY_18));
  text_layer_init(&date_layer, GRect(17, 116, 110, 30));
#endif
#if DISPLAY_DATE && INVERTED
  text_layer_set_text_color(&date_layer, GColorBlack);
#elif DISPLAY_DATE
  text_layer_set_text_color(&date_layer, GColorWhite);
#endif
#if DISPLAY_DATE
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

  layer_init(&second_display_layer, window.layer.frame);
  second_display_layer.update_proc = &second_display_layer_update_callback;
  layer_add_child(&window.layer, &second_display_layer);
}

void handle_deinit(AppContextRef ctx) {
  (void)ctx;

  bmp_deinit_container(&background_image_container);
#if DISPLAY_DATE
  fonts_unload_custom_font(date_font);
#endif
}

void handle_tick(AppContextRef ctx, PebbleTickEvent *t){
  (void)t;
  (void)ctx;

  if(init_anim == ANIM_IDLE)
  {
     init_anim = ANIM_START;
     timer_handle = app_timer_send_event(ctx, 50 /* milliseconds */, COOKIE_MY_TIMER);
  }
  else if(init_anim == ANIM_DONE)
  {
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
  layer_mark_dirty(&second_display_layer);
  }
}

void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
    .deinit_handler = &handle_deinit,
    .timer_handler = &handle_timer,
    .tick_info = {
			.tick_handler = &handle_tick,
			.tick_units = SECOND_UNIT
		}
  };
  app_event_loop(params, &handlers);
}
