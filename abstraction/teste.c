#include <stdio.h>

#define bla(type, name)\
type * name (type * a, type * b) {\
    type c = *a;\
    *a = *b;\
    *b = c;\
    return a;\
}\

VARIAVEL(int, d);

typedef struct _teste Teste {
    char nome[16];
    int idade;
}
bla (int, muda);

int main (void) {
    d = 20;
    a = 10;
    int b = 11;
    
    muda (&a, &d);
    
    printf ("A: %d\tB: %d\n", a, b);
    
    return 0;
    
}
