#include <string.h>

#include <errno.h>
#include <stdarg.h>


#include "Stream.h"
#include "String.h"
#include "Scanner.h"
#include "Out.h"

struct _streamprivate {
    Scanner * s;
    Out * o;
    
    StreamType type;
    FILE * fp;
};


Stream * actual_stream;


OBJECT_TYPE (Stream, stream, STREAM);


PUBLIC int
StrmOpen (char * filename, char * mode) {
    StreamPrivate * priv = OBJECT_GET_PRIVATE (Stream, actual_stream);
    int i;
    priv->fp = fopen (filename, mode);
    if (priv->fp == NULL) {
        perror ("opening the file");
        return 0;
    }
    scanner (priv->s)->setFileDescriptor (priv->fp);
    
    i = 0;
    for (i = 0; i < strlen (mode); i++) {
        if (mode[i] == 'b') {
            printf ("\nUP\n");
            priv->type = T_BINARY;
            i = 0;
            break;
        }
    }
    if (i != 0) {
        priv->type = T_CHAR;
    }
    return 1;
}


PUBLIC void
StrmClose (void) {
    StreamPrivate * priv = OBJECT_GET_PRIVATE (Stream, actual_stream);
    
    if (priv->fp != NULL) {
    
        fflush (priv->fp);
        fclose (priv->fp);

    }
}


PUBLIC void 
StrmWrite (char * str) {
    StreamPrivate * priv = OBJECT_GET_PRIVATE (Stream, actual_stream);
    if (priv->type == T_BINARY) {
        out (priv->o)->Stdout ("Use WriteBinary stream method for binary stream mode [!!]\n");
        exit (1);
    }
    out (priv->o)->File (priv->fp, str);
}


PUBLIC void 
StrmWriteFmt (char * fmt, ...) {
    StreamPrivate * priv = OBJECT_GET_PRIVATE (Stream, actual_stream);
    if (priv->type == T_BINARY) {
        out (priv->o)->Stdout ("Use WriteBinary stream method for binary stream mode [!!]\n");
        exit (1);
    }
    
    va_list ap;
    
    va_start (ap, fmt);
    vfprintf (priv->fp, fmt, ap);
    
    va_end (ap);
    
}


PUBLIC int 
StrmWriteBinary (void * buf, size_t len) {
    StreamPrivate * priv = OBJECT_GET_PRIVATE (Stream, actual_stream);
    int written;
    
    if (priv->type != T_BINARY) {
        out (priv->o)->Stdout ("Use Write stream method for non-binary stream mode [!!]\n");
        exit (1);
    }
    written = fwrite (buf, len, 1, priv->fp);
    
    return written;
}


PUBLIC char *
StrmRead (unsigned int len) {
    StreamPrivate * priv = OBJECT_GET_PRIVATE (Stream, actual_stream);
    if (priv->type == T_BINARY) {
        out (priv->o)->Stdout ("Use ReadBinary stream method for binary stream mode [!!]\n");
        exit (1);
    }
    return scanner (priv->s)->getString (len);
}


PUBLIC int
StrmReadBinary (void * buf, size_t size) {
    StreamPrivate * priv = OBJECT_GET_PRIVATE (Stream, actual_stream);
    size_t read;
    
    if (priv->type != T_BINARY) {
        out (priv->o)->Stdout ("Use Read stream method for non-binary stream mode [!!]\n");
        exit (1);
    }
    read = fread (buf, size, 1, priv->fp);
    
    //((char *)buf)[size] = 0x00;
    
    if (read != size) {
        if (feof (priv->fp)) {
            out (priv->o)->Stdout ("Error reading the file: End of file found\n");
            return -1;
        }
    }
    return 1;
}


PUBLIC void
StrmReWind (void) {
    StreamPrivate * priv = OBJECT_GET_PRIVATE (Stream, actual_stream);
    
    rewind (priv->fp);
    
}


PUBLIC FILE *
StrmGetDescriptor (void) {
    StreamPrivate * priv = OBJECT_GET_PRIVATE (Stream, actual_stream);
    
    return priv->fp;
}


PUBLIC void
StrmSetDescriptor (FILE * fp) {
    StreamPrivate * priv = OBJECT_GET_PRIVATE (Stream, actual_stream);
    
    priv->fp = fp;
    if (fp != stdout) {
        scanner (priv->s)->setFileDescriptor (fp);
    }

}


PUBLIC void 
StrmDtor (void) {
    StreamPrivate * priv = OBJECT_GET_PRIVATE (Stream, actual_stream);
    
    scanner (priv->s)->dtor ();
    out (priv->o)->dtor ();


    if (priv->fp != NULL && priv->fp != stdout && priv->fp != stdin && priv->fp != stderr) {
    
        fflush (priv->fp);
        fclose (priv->fp);
        
    }

    DEALLOC (priv);
    DEALLOC (actual_stream);
    
    actual_stream = NULL;
    priv = NULL;

}


PUBLIC Stream *
new_stream (char * filename, char * mode) {
    Stream * strm = NEW (Stream);
    StreamPrivate * priv = NEW (StreamPrivate);
    
    priv->s = new_scanner (NULL);
    priv->o = new_out ();
    
    strm->priv = priv;
    strm->Open = StrmOpen;
    strm->Close = StrmClose;
    strm->Write = StrmWrite;
    strm->WriteFmt = StrmWriteFmt;
    strm->WriteBinary = StrmWriteBinary;
    strm->Read = StrmRead;
    strm->ReadBinary = StrmReadBinary;
    strm->ReWind = StrmReWind;
    strm->GetDescriptor = StrmGetDescriptor;
    strm->SetDescriptor = StrmSetDescriptor;

    strm->dtor = StrmDtor;
    if (filename != NULL && mode != NULL) {        
        if ((stream (strm)->Open (filename, mode)) == 0) {
            stream (strm)->dtor ();
            strm = NULL;
        }
    }

    return strm;
}

