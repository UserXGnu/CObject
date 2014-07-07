#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "Scanner.h"
#include "String.h"

//#define SCANNER_GET_PRIVATE(obj)            (((Scanner *)(obj))->priv)

struct _scannerprivate {
//    void * ptr;
    FILE * fp;    
};


Scanner * actual_scanner;

OBJECT_TYPE(Scanner, scanner, SCANNER);

PRIVATE void
strformat (char * c) {
    c[strlen(c) - 1] = 0x00;
}

PRIVATE void 
dump_io (void) {
    int c;
    ScannerPrivate * priv = OBJECT_GET_PRIVATE (Scanner, actual_scanner);
    
    while ((c = fgetc (priv->fp)) != 0x0a && c != 0x00 && c != 0x0d);
}

PUBLIC char *
scnGetString (unsigned int len) {
    char str[len];
    
    ScannerPrivate * priv = OBJECT_GET_PRIVATE (Scanner, actual_scanner);
    
    fgets (str, len, priv->fp);
    if (priv->fp != stdin) {
        str[len] = 0x00;
    } else {
        strformat (str);
    }
    // priv->ptr = strdup(str);

    
    return strdup (str);
}

PUBLIC int 
scnGetChar (void) {
    ScannerPrivate * priv = OBJECT_GET_PRIVATE (Scanner, actual_scanner);
    
    return fgetc (priv->fp);
}


PUBLIC unsigned int
scnGetUInt (void) {
    unsigned int u;
    ScannerPrivate * priv = OBJECT_GET_PRIVATE (Scanner, actual_scanner);
    
    fscanf (priv->fp, "%u", &u);
    
    dump_io ();
    
    return u;
}

PUBLIC int
scnGetInt (void) {
    int i;
    ScannerPrivate * priv = OBJECT_GET_PRIVATE (Scanner, actual_scanner);
    
    fscanf (priv->fp , "%d", &i);
    dump_io ();
    return i;
}

PUBLIC FILE *
scnGetFileDescriptor (void) {

    ScannerPrivate * priv = OBJECT_GET_PRIVATE (Scanner, actual_scanner);
    return priv->fp;
}

PUBLIC void
scnSetFileDescriptor (FILE * fp) {
    ScannerPrivate * priv = OBJECT_GET_PRIVATE (Scanner, actual_scanner);
    
    priv->fp = fp;
}


PUBLIC void
scndtor (void) {
    ScannerPrivate * priv = OBJECT_GET_PRIVATE (Scanner, actual_scanner);

    DEALLOC (priv);
    DEALLOC (actual_scanner);
}


// constructor ::S
PUBLIC Scanner *
new_scanner (FILE * fp) {
    if (fp == stdout || fp == stderr) {
        printf ("Scanner can only be used with input streams [!!]\n");
        exit(1);
    }
        

    Scanner * s = NEW (Scanner);
    ScannerPrivate * priv = NEW (ScannerPrivate);
    s->priv = priv;
    
    OBJECT_SET_TYPE (s, T_SCANNER);
    
    s->getString = scnGetString;
    s->getChar = scnGetChar;
    s->getUint = scnGetUInt;
    s->getInt = scnGetInt;
    
    s->getFileDescriptor = scnGetFileDescriptor;
    s->setFileDescriptor = scnSetFileDescriptor;
    
    
    s->dtor = scndtor;
    

    priv->fp = fp;

    
    return s;
}

