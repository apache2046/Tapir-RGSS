#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>
#include <ruby.h>

#include "sdl_misc.h"

extern VALUE rb_cWindow;
void Init_Window(void);

struct Window {
  struct Renderable renderable;
  VALUE windowskin;
  int x, y, width, height;
};

bool isWindow(VALUE obj);
struct Window *convertWindow(VALUE obj);
void rb_window_modify(VALUE obj);

void initWindowSDL(void);
void deinitWindowSDL(void);

#endif /* WINDOW_H */
