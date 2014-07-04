#ifndef _OBJECT_H_
#define _OBJECT_H_

#define NEW(type)                           ((type *) calloc (1, sizeof(type)))
#define ALLOC(times, type)                  ((type *) calloc ((times), sizeof (type)))
#define DEALLOC(obj)                         (free((obj)))

#define PRIVATE                             static
#define PUBLIC

#define OBJECT(o)                           ((o)->object)
#define OBJECT_GET_TYPE(o)                  (OBJECT((o)).type)
#define OBJECT_SET_TYPE(o,_type)            (OBJECT((o)).type = (_type))                 
#define OBJECT_GET_PRIVATE(type, obj)       (((type *)obj)->priv)


#define OBJECT_TYPE(type, name, MACRO)\
PUBLIC type * MACRO(void * obj) {\
    actual_##name = (type *)obj;\
    return (type *) obj;\
}\
\
PUBLIC type *name(type *obj) {\
    actual_##name = obj;\
    return obj;\
}


typedef enum    _objectType ObjectType;
enum _objectType {
    T_OBJECT = 0,
    T_SCANNER,
    T_STRING,
    T_OUT,
    
};

typedef struct  _object Object;
struct _object {
    ObjectType type;
    
};


#endif /* _OBJECT_H_ */
