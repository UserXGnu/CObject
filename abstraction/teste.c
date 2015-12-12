#include <stdio.h>

#define VARIAVEL(type, name)    type name
#define bla(type, name)\
type * name (type * a, type * b) {\
    type c = *a;\
    *a = *b;\
    *b = c;\
    return a;\
}\


typedef struct _teste {
    char nome[16];
    int idade;
} Teste;


int main (void) {
    VARIAVEL(int, d);
    VARIAVEL(int, a);

    d = 20;
    a = 10;
    bla (int, muda);

    
    int b = 11;
    
    muda (&a, &d);
    
    printf ("A: %d\tB: %d\n", a, b);
    
    return 0;
    
}
