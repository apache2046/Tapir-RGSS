#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <stdbool.h>
#include <ruby.h>

extern VALUE rb_cViewport;
void Init_Viewport(void);

struct Viewport {
  VALUE rect, color, tone;
  bool disposed, visible;
  int ox, oy, z;
};

bool isViewport(VALUE obj);
struct Viewport *convertViewport(VALUE obj);
void rb_viewport_modify(VALUE obj);

#endif /* VIEWPORT_H */