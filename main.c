 // o mesmo que import do java
#include "Scanner.h" // Scanner é uma classe similar à Scanner do java!
#include "String.h"  // String é um tipo abstrato de dados, é similar à String do java!
#include "Out.h"     // Out é uma classe que trata saida de dados, seja saida padrão, de erro ou stream de arquivo.
#include "Stream.h"

//#include <stdlib.h>

int
main (int argc, char ** argv) {

    int main_class (int argc, char ** argv) {
        int i;
        
        // instanciando as classes Scanner e String ::
        Scanner * s = new_scanner (stdin);
        String * str = new_string ();
        String * a = new_string ();
        Out * o = new_out ();
        Stream * strm = new_stream ("teste", "ab+"); // contructor may return NULL if file couldn't be openned ::
        char b[10];
        
        // chamando metodo de leitura de um inteiro ::
        i = scanner(s)->getInt();

        out(o)->Stdout ("i: %d\n", i);
    
        string (str)->setContent (scanner (s)->getString (10));
//        printf ("String: %s | Len: %d\n", string (str)->getContent (), string (str)->length ());
        out (o)->Stdout ("String: %s | Len: %d\n", string (str)->getContent (), string (str)->Length ());
        
        stream (strm)->WriteBinary (s, sizeof (s));
        
        stream (strm)->ReWind ();

        stream (strm)->ReadBinary (a, sizeof (s));
        out (o)->Stdout ("File: %s\n", string (a)->getContent());

        
        // destrutors ::
        stream (strm)->dtor ();
        out (o)->dtor ();
        string (str)->dtor ();
        string (a)->dtor ();
        scanner (s)->dtor ();

        return 0;
    }
    
    return main_class (argc, argv);

}

