#include "Scanner.h"
#include "Out.h"

int
main (int argc, char ** argv) {
    int a;
    
    Scanner * in = new_scanner (stdin);
    Out * o = new_out ();
    
    a = scanner (in)->getInt ();law
    
//    printf ("%d", a);  
    out(o)->Stdout ("%d", a);
   
    scanner (in)->dtor ();
    return 0;
}
