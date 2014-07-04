#include "Scanner.h"
#include "Out.h"

int
main (int argc, char ** argv) {

    Scanner * in = new_scanner (stdin);
    Out * o = new_out ();
    
    int a;
    a = scanner (in)->getInt ();
    
    out(o)->Stdout ("%d", a);
    
    
    scanner (in)->dtor ();
    out(o)->dtor ();
    return 0;
}
