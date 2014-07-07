#ifndef _SCANNER_H_
#define _SCANNER_H_

#include <stdio.h>

#include "abstraction/Object.h"
#include "String.h"


//#define SCANNER(obj)            ((Scanner *) (obj))
               

typedef struct _scanner Scanner;
typedef struct _scannerprivate ScannerPrivate;

struct _scanner {
    
    PUBLIC Object object;
    
    ScannerPrivate * priv;
    
    PUBLIC char * (* getString) (unsigned int);
    PUBLIC int (* getChar) (void);
    PUBLIC unsigned int (* getUint) (void);
    PUBLIC int (* getInt) (void);
    
    PUBLIC FILE * (* getFileDescriptor) (void);
    
    PUBLIC void (* setFileDescriptor) (FILE * fp);
    
    PUBLIC void (* dtor) (void);
};

PUBLIC Scanner * new_scanner (FILE * fp);

Scanner * scanner (Scanner * obj);
Scanner * SCANNER (void * obj);

#endif /* _SCANNER_H_ */

