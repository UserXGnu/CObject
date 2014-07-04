#include "Out.h"

#include <stdarg.h>
#include <stdlib.h>

//#include <syslog.h>

struct _outprivate {
    
};

Out * actual_out;

OBJECT_TYPE (Out, out, OUT);

PUBLIC void 
oStdOut (char * fmt, ...) {
    va_list ap;
    
    va_start (ap, fmt);
    vprintf (fmt, ap);
    va_end (ap);
}

PUBLIC void
oFile (FILE * fp, char * buff) {

    fprintf (fp, "%s", buff);
    
}

PUBLIC void
odtor (void) {
    OutPrivate * priv = OBJECT_GET_PRIVATE (Out, actual_out);
    DEALLOC (priv);
    DEALLOC (actual_out);
}

PUBLIC Out *
new_out (void) {
    Out * o = NEW (Out);
    OutPrivate * priv = NEW (OutPrivate);
    o->priv = priv;
    
    OBJECT_SET_TYPE (o, T_OUT);
    
    o->File = oFile;
    o->Stdout = oStdOut;
    
    o->dtor = odtor;
    
    return o;
}
