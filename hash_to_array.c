#include <ruby/ruby.h>
#include <ruby/st.h>

static VALUE rb_cHashToArray;

static void 
hash_to_array_mark(void *f) {
}

static void 
hash_to_array_free(void *f) { 
}

static VALUE 
hash_to_array_init(VALUE obj) {
  return Qnil; 
}

static VALUE
hash_to_array_alloc(VALUE klass) { 
  return Data_Wrap_Struct(klass, hash_to_array_mark, hash_to_array_free, NULL); 
}

static int
convert_keys_to_a(VALUE key, VALUE value, VALUE ary) {
  if (key == Qundef) return ST_CONTINUE;

  if (TYPE(value) == T_HASH) {
    rb_hash_foreach(value, convert_keys_to_a, ary);
  }

  return rb_ary_push(ary, key);
}

static VALUE
hash_to_array_all_keys(VALUE obj, VALUE hash) {

  VALUE ary;

  ary = rb_ary_new();

  rb_hash_foreach(hash, convert_keys_to_a, ary);

  return ary;
}

static int
convert_values_to_a(VALUE key, VALUE value, VALUE ary) {
  if (key == Qundef) return ST_CONTINUE;

  if (TYPE(value) == T_HASH) {
    rb_hash_foreach(value, convert_values_to_a, ary);
    return ST_CONTINUE;
  } else { 
    return rb_ary_push(ary, value);
  }
}

static VALUE
hash_to_array_all_values(VALUE obj, VALUE hash) {

  VALUE ary;

  ary = rb_ary_new();

  rb_hash_foreach(hash, convert_values_to_a, ary);

  return ary;
}


void
Init_hash_to_array()
{
  rb_cHashToArray = rb_define_class("HashToArray", rb_cObject);
  rb_define_alloc_func(rb_cHashToArray, hash_to_array_alloc);
  rb_define_method(rb_cHashToArray, "initialize", hash_to_array_init, 0);
  rb_define_method(rb_cHashToArray, "all_keys", hash_to_array_all_keys, 1);
  rb_define_method(rb_cHashToArray, "all_values", hash_to_array_all_values, 1);
}
