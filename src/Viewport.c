#include "Viewport.h"
#include "Rect.h"
#include "Tone.h"
#include "Color.h"
#include "misc.h"

static void viewport_mark(struct Viewport *ptr);
static void viewport_free(struct Viewport *ptr);
static VALUE viewport_alloc(VALUE klass);

static VALUE rb_viewport_m_initialize(int argc, VALUE *argv, VALUE self);
static VALUE rb_viewport_m_initialize_copy(VALUE self, VALUE orig);
static VALUE rb_viewport_m_dispose(VALUE self);
static VALUE rb_viewport_m_disposed_p(VALUE self);
static VALUE rb_viewport_m_rect(VALUE self);
static VALUE rb_viewport_m_set_rect(VALUE self, VALUE newval);
static VALUE rb_viewport_m_visible(VALUE self);
static VALUE rb_viewport_m_set_visible(VALUE self, VALUE newval);
static VALUE rb_viewport_m_z(VALUE self);
static VALUE rb_viewport_m_set_z(VALUE self, VALUE newval);
static VALUE rb_viewport_m_ox(VALUE self);
static VALUE rb_viewport_m_set_ox(VALUE self, VALUE newval);
static VALUE rb_viewport_m_oy(VALUE self);
static VALUE rb_viewport_m_set_oy(VALUE self, VALUE newval);
static VALUE rb_viewport_m_color(VALUE self);
static VALUE rb_viewport_m_set_color(VALUE self, VALUE newval);
static VALUE rb_viewport_m_tone(VALUE self);
static VALUE rb_viewport_m_set_tone(VALUE self, VALUE newval);

VALUE rb_cViewport;

/*
 * A graphic object container.
 */
void Init_Viewport(void) {
  rb_cViewport = rb_define_class("Viewport", rb_cObject);
  rb_define_alloc_func(rb_cViewport, viewport_alloc);
  rb_define_private_method(rb_cViewport, "initialize",
      rb_viewport_m_initialize, -1);
  rb_define_private_method(rb_cViewport, "initialize_copy",
      rb_viewport_m_initialize_copy, 1);
  rb_define_method(rb_cViewport, "dispose", rb_viewport_m_dispose, 0);
  rb_define_method(rb_cViewport, "disposed?", rb_viewport_m_disposed_p, 0);
  rb_define_method(rb_cViewport, "rect", rb_viewport_m_rect, 0);
  rb_define_method(rb_cViewport, "rect=", rb_viewport_m_set_rect, 1);
  rb_define_method(rb_cViewport, "visible", rb_viewport_m_visible, 0);
  rb_define_method(rb_cViewport, "visible=", rb_viewport_m_set_visible, 1);
  rb_define_method(rb_cViewport, "z", rb_viewport_m_z, 0);
  rb_define_method(rb_cViewport, "z=", rb_viewport_m_set_z, 1);
  rb_define_method(rb_cViewport, "ox", rb_viewport_m_ox, 0);
  rb_define_method(rb_cViewport, "ox=", rb_viewport_m_set_ox, 1);
  rb_define_method(rb_cViewport, "oy", rb_viewport_m_oy, 0);
  rb_define_method(rb_cViewport, "oy=", rb_viewport_m_set_oy, 1);
  rb_define_method(rb_cViewport, "color", rb_viewport_m_color, 0);
  rb_define_method(rb_cViewport, "color=", rb_viewport_m_set_color, 1);
  rb_define_method(rb_cViewport, "tone", rb_viewport_m_tone, 0);
  rb_define_method(rb_cViewport, "tone=", rb_viewport_m_set_tone, 1);
  // TODO: implement Viewport#flash
  // TODO: implement Viewport#update
}

bool isViewport(VALUE obj) {
  if(TYPE(obj) != T_DATA) return false;
  return RDATA(obj)->dmark == (void(*)(void*))viewport_mark;
}

struct Viewport *convertViewport(VALUE obj) {
  Check_Type(obj, T_DATA);
  // Note: original RGSS doesn't check types.
  if(RDATA(obj)->dmark != (void(*)(void*))viewport_mark) {
    rb_raise(rb_eTypeError,
        "can't convert %s into Viewport",
        rb_class2name(rb_obj_class(obj)));
  }
  struct Viewport *ret;
  Data_Get_Struct(obj, struct Viewport, ret);
  return ret;
}

void rb_viewport_modify(VALUE obj) {
  // Note: original RGSS doesn't check frozen.
  if(OBJ_FROZEN(obj)) rb_error_frozen("Viewport");
}

static void viewport_mark(struct Viewport *ptr) {
  rb_gc_mark(ptr->rect);
  rb_gc_mark(ptr->color);
  rb_gc_mark(ptr->tone);
}

static void viewport_free(struct Viewport *ptr) {
  xfree(ptr);
}

static VALUE viewport_alloc(VALUE klass) {
  struct Viewport *ptr = ALLOC(struct Viewport);
  ptr->rect = rb_rect_new2();
  ptr->color = rb_color_new2();
  ptr->tone = rb_tone_new2();
  ptr->disposed = false;
  ptr->visible = true;
  ptr->ox = 0;
  ptr->oy = 0;
  ptr->z = 0;
  VALUE ret = Data_Wrap_Struct(klass, viewport_mark, viewport_free, ptr);
  return ret;
}

/*
 * call-seq:
 *   Viewport.new(x, y, width, height)
 *   Viewport.new(rect)
 *   Viewport.new
 *
 * Creates a new viewport.
 */
static VALUE rb_viewport_m_initialize(int argc, VALUE *argv, VALUE self) {
  struct Viewport *ptr = convertViewport(self);
  switch(argc) {
    case 1:
      rb_rect_set2(ptr->rect, argv[0]);
      break;
    case 4:
      rb_rect_set(ptr->rect,
          NUM2INT(argv[0]), NUM2INT(argv[1]),
          NUM2INT(argv[2]), NUM2INT(argv[3]));
      break;
#if RGSS == 3
    case 0:
      break;
#endif
    default:
#if RGSS == 3
      rb_raise(rb_eArgError,
          "wrong number of arguments (%d for 0..1 or 4)", argc);
#else
      rb_raise(rb_eArgError,
          "wrong number of arguments (%d for 1 or 4)", argc);
#endif
      break;
  }
  return Qnil;
}

static VALUE rb_viewport_m_initialize_copy(VALUE self, VALUE orig) {
  struct Viewport *ptr = convertViewport(self);
  struct Viewport *orig_ptr = convertViewport(orig);
  rb_rect_set2(ptr->rect, orig_ptr->rect);
  rb_color_set2(ptr->color, orig_ptr->color);
  rb_tone_set2(ptr->tone, orig_ptr->tone);
  ptr->disposed = orig_ptr->disposed;
  ptr->visible = orig_ptr->visible;
  ptr->ox = orig_ptr->ox;
  ptr->oy = orig_ptr->oy;
  ptr->z = orig_ptr->z;
  return Qnil;
}

static VALUE rb_viewport_m_dispose(VALUE self) {
  struct Viewport *ptr = convertViewport(self);
  ptr->disposed = true;
  return Qnil;
}

static VALUE rb_viewport_m_disposed_p(VALUE self) {
  struct Viewport *ptr = convertViewport(self);
  return ptr->disposed ? Qtrue : Qfalse;
}

static VALUE rb_viewport_m_rect(VALUE self) {
  struct Viewport *ptr = convertViewport(self);
  return ptr->rect;
}

static VALUE rb_viewport_m_set_rect(VALUE self, VALUE newval) {
  struct Viewport *ptr = convertViewport(self);
  rb_viewport_modify(self);
  rb_rect_set2(ptr->rect, newval);
  return newval;
}

static VALUE rb_viewport_m_visible(VALUE self) {
  struct Viewport *ptr = convertViewport(self);
  return ptr->visible ? Qtrue : Qfalse;
}

static VALUE rb_viewport_m_set_visible(VALUE self, VALUE newval) {
  struct Viewport *ptr = convertViewport(self);
  rb_viewport_modify(self);
  ptr->visible = RTEST(newval);
  return newval;
}

static VALUE rb_viewport_m_z(VALUE self) {
  struct Viewport *ptr = convertViewport(self);
  return INT2NUM(ptr->z);
}

static VALUE rb_viewport_m_set_z(VALUE self, VALUE newval) {
  struct Viewport *ptr = convertViewport(self);
  rb_viewport_modify(self);
  ptr->z = NUM2INT(newval);
  return newval;
}

static VALUE rb_viewport_m_ox(VALUE self) {
  struct Viewport *ptr = convertViewport(self);
  return INT2NUM(ptr->ox);
}

static VALUE rb_viewport_m_set_ox(VALUE self, VALUE newval) {
  struct Viewport *ptr = convertViewport(self);
  rb_viewport_modify(self);
  ptr->ox = NUM2INT(newval);
  return newval;
}

static VALUE rb_viewport_m_oy(VALUE self) {
  struct Viewport *ptr = convertViewport(self);
  return INT2NUM(ptr->oy);
}

static VALUE rb_viewport_m_set_oy(VALUE self, VALUE newval) {
  struct Viewport *ptr = convertViewport(self);
  rb_viewport_modify(self);
  ptr->oy = NUM2INT(newval);
  return newval;
}

static VALUE rb_viewport_m_color(VALUE self) {
  struct Viewport *ptr = convertViewport(self);
  return ptr->color;
}

static VALUE rb_viewport_m_set_color(VALUE self, VALUE newval) {
  struct Viewport *ptr = convertViewport(self);
  rb_viewport_modify(self);
  rb_rect_set2(ptr->color, newval);
  return newval;
}

static VALUE rb_viewport_m_tone(VALUE self) {
  struct Viewport *ptr = convertViewport(self);
  return ptr->tone;
}

static VALUE rb_viewport_m_set_tone(VALUE self, VALUE newval) {
  struct Viewport *ptr = convertViewport(self);
  rb_viewport_modify(self);
  rb_rect_set2(ptr->tone, newval);
  return newval;
}