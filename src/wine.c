#include "pebble.h"

Window *window;
TextLayer *text_wine_layer;
TextLayer *text_oclock_layer;
Layer *line_layer;

void line_layer_update_callback(Layer *layer, GContext* ctx) {
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_rect(ctx, layer_get_bounds(layer), 0, GCornerNone);
}

void handle_deinit(void) {
}

void handle_init(void) {
  static char wine_text[] = "Wine";
  static char oclock_text[] = "O'Clock";

  window = window_create();
  window_stack_push(window, true /* Animated */);
  window_set_background_color(window, GColorBlack);

  Layer *window_layer = window_get_root_layer(window);

  text_wine_layer = text_layer_create(GRect(8, 52, 144-8, 168-52));
  text_layer_set_text_color(text_wine_layer, GColorWhite);
  text_layer_set_background_color(text_wine_layer, GColorClear);
  text_layer_set_font(text_wine_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ROBOTO_BOLD_SUBSET_36)));
  layer_add_child(window_layer, text_layer_get_layer(text_wine_layer));

  text_oclock_layer = text_layer_create(GRect(8, 97, 144-8, 168-97));
  text_layer_set_text_color(text_oclock_layer, GColorWhite);
  text_layer_set_background_color(text_oclock_layer, GColorClear);
  text_layer_set_font(text_oclock_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ROBOTO_BOLD_SUBSET_36)));
  layer_add_child(window_layer, text_layer_get_layer(text_oclock_layer));

  GRect line_frame = GRect(8, 97, 139, 2);
  line_layer = layer_create(line_frame);
  layer_set_update_proc(line_layer, line_layer_update_callback);
  layer_add_child(window_layer, line_layer);

  text_layer_set_text(text_oclock_layer, oclock_text);
  text_layer_set_text(text_wine_layer, wine_text);
}


int main(void) {
  handle_init();

  app_event_loop();
  
  handle_deinit();
}
