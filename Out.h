#ifndef _OUT_H_
#define _OUT_H_

#include <stdio.h>

#include "abstraction/Object.h"


typedef struct _out Out;
typedef struct _outprivate OutPrivate;

struct _out {
    Object object;
    
    OutPrivate * priv;
    
    PUBLIC void (* Stdout) (char * fmt, ...);
    PUBLIC void (* File) (FILE * fp, char * buff);
    
    PUBLIC void (*dtor) (void);
};

Out * new_out (void);

Out * out (Out * obj);
Out * OUT (void * obj);

#endif /* _OUT_H_ */
