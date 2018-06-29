#ifndef JULIA_INTERNAL_H
#define JULIA_INTERNAL_H 1
#define JL_DATA_TYPE

#ifdef __cplusplus
extern "C" {
#if 0
} /* satisfy cc-mode */
#endif
#endif

#include <ruby.h>

#if SIZEOF_LONG == SIZEOF_VOIDP
# define PTR2NUM(x)   (LONG2NUM((long)(x)))
# define NUM2PTR(x)   ((void*)(NUM2ULONG(x)))
#elif SIZEOF_LONG_LONG == SIZEOF_VOIDP
# define PTR2NUM(x)   (LL2NUM((LONG_LONG)(x)))
# define NUM2PTR(x)   ((void*)(NUM2ULL(x)))
#else
# error ---->> ruby requires sizeof(void*) == sizeof(long) or sizeof(LONG_LONG) to be compiled. <<----
#endif

typedef struct _jl_value_t jl_value_t;
typedef struct _jl_taggedvalue_t jl_taggedvalue_t;

typedef struct _jl_sym_t {
    JL_DATA_TYPE
    struct _jl_sym_t *left;
    struct _jl_sym_t *right;
    uintptr_t hash;
} jl_sym_t;

typedef struct {
    JL_DATA_TYPE
    size_t length;
} jl_svec_t;

typedef struct {
    uint32_t nfields;
    uint32_t alignment : 9;
    uint32_t haspadding : 1;
    uint32_t npointers : 20;
    uint32_t fielddesc_type : 2;
} jl_datatype_layout_t;

typedef struct {
    JL_DATA_TYPE
    jl_sym_t *name;
    jl_value_t *lb;
    jl_value_t *ub;
} jl_tvar_t;

typedef struct {
    JL_DATA_TYPE
    jl_tvar_t *var;
    jl_value_t *body;
} jl_unionall_t;

typedef struct {
    JL_DATA_TYPE
    jl_sym_t *name;
    struct _jl_module_t *module;
    jl_svec_t *names;
    jl_value_t *wrapper;
    jl_svec_t *cache;
    jl_svec_t *linearcache;
    intptr_t hash;
    struct _jl_methtable_t *mt;
} jl_typename_t;

typedef struct _jl_datatype_t {
    JL_DATA_TYPE
    jl_typename_t *name;
    struct _jl_datatype_t *super;
    jl_svec_t *parameters;
    jl_svec_t *types;
    jl_svec_t *names;
    jl_value_t *instance;
    const jl_datatype_layout_t *layout;
    int32_t size;
    int32_t ninitialized;
    uint32_t uid;
    uint8_t abstract;
    uint8_t mutabl;
    uint8_t hasfreetypevars;
    uint8_t isconcretetype;
    uint8_t isdispatchtuple;
    uint8_t isbitstype;
    uint8_t zeroinit;
    uint8_t isinlinealloc;
    void *struct_decl;
    void *ditype;
} jl_datatype_t;

struct julia_api_table {
  int (* jl_is_initialized)(void);
  void (* jl_init)(void);
  jl_datatype_t *jl_bool_type;
  jl_datatype_t *jl_char_type;
  jl_datatype_t *jl_string_type;
  jl_datatype_t *jl_int8_type;
  jl_datatype_t *jl_uint8_type;
  jl_datatype_t *jl_int16_type;
  jl_datatype_t *jl_uint16_type;
  jl_datatype_t *jl_int32_type;
  jl_datatype_t *jl_uint32_type;
  jl_datatype_t *jl_int64_type;
  jl_datatype_t *jl_uint64_type;
  jl_datatype_t *jl_float16_type;
  jl_datatype_t *jl_float32_type;
  jl_datatype_t *jl_float64_type;
  jl_datatype_t *jl_datatype_type;
  jl_typename_t *jl_array_typename;
  jl_value_t * (* jl_eval_string)(const char *str);
  jl_datatype_t * (* jl_typeof)(jl_value_t *v);
  const char * (* jl_typeof_str)(jl_value_t *v);
  const char * (* jl_string_ptr)(jl_value_t *s);
  int8_t (* jl_unbox_bool)(jl_value_t *v);
  int8_t (* jl_unbox_int8)(jl_value_t *v);
  uint8_t (* jl_unbox_uint8)(jl_value_t *v);
  int16_t (* jl_unbox_int16)(jl_value_t *v);
  uint16_t (* jl_unbox_uint16)(jl_value_t *v);
  int32_t (* jl_unbox_int32)(jl_value_t *v);
  uint32_t (* jl_unbox_uint32)(jl_value_t *v);
  int64_t (* jl_unbox_int64)(jl_value_t *v);
  uint64_t (* jl_unbox_uint64)(jl_value_t *v);
  float (* jl_unbox_float32)(jl_value_t *v);
  double (* jl_unbox_float64)(jl_value_t *v);
};

struct julia_api_table *julia_get_api_table(void);
#define JULIA_API(name) (julia_get_api_table()->name)

void julia_init_libjulia(void);

extern VALUE julia_mJulia;
extern VALUE julia_mLibJulia;
#endif /* JULIA_INTERNAL_H */