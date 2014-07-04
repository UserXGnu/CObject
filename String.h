#ifndef _STRING_H_
#define _STRING_H_

#include <stdlib.h>
#include <string.h>


#include "abstraction/Object.h"

//#define STRING(o)               ((String *) (o))

typedef struct _string String;
typedef struct _stringPrivate StringPrivate;

struct _string {
    Object object;
    
    StringPrivate * priv;
    
    PUBLIC int (* length) (void);
    PUBLIC char * (* getContent) (void);
   // PUBLIC void (* cat) (String * str);
    PUBLIC void (* setContent) (char * content);  
    PUBLIC void (* dtor) (void);
};

String * new_string (void);

String * string (String * obj);
String * STRING (void * obj); 

#endif /* _STRING_H_ */
