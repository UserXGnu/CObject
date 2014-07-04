#ifndef _STREAM_H_
#define _STREAM_H_

#include <stdio.h>

#include "abstraction/Object.h"
#include "String.h"
#include "Scanner.h"
#include "Out.h"


typedef struct _stream Stream;
typedef struct _streamprivate StreamPrivate;

struct _stream {
    Object object;
    
    StreamPrivate * priv;
    
    PUBLIC int (* Open) (char * filename, char * mode);
    PUBLIC void (* Close) ();
    PUBLIC void (* Write) (char * str);
    PUBLIC void (* WriteFmt) (char * fmt, ...);
    PUBLIC int (* WriteBinary) (void * buf, size_t len);
    
    PUBLIC char * (* Read) (unsigned int len);
    PUBLIC int (* ReadBinary) (void * buff, size_t size);
    PUBLIC void (* ReWind) (void);
    
    PUBLIC FILE * (* GetDescriptor) (void);
    PUBLIC void (* SetDescriptor) (FILE * fp);
    
    PUBLIC void (*dtor) (void);
};

PUBLIC Stream * new_stream (char * filename, char * mode);

PUBLIC Stream * stream (Stream * obj);
PUBLIC Stream * STREAM (void * obj);

#endif /* _STREAM_H_ */
