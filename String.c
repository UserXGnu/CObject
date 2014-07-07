#include "String.h"

//#include "abstraction/Object.h"

struct _stringPrivate {
    int len;
    char * ptr;
};

String * actual_string;

OBJECT_TYPE (String, string, STRING)

//#define STRING_GET_PRIVATE(o)           (STRING((o))->priv)


PUBLIC int 
strLength (void) {
    StringPrivate * priv = OBJECT_GET_PRIVATE (String, actual_string);
    
    return priv->len;    
}

PUBLIC char *
strGetContent (void) {
    StringPrivate * priv = OBJECT_GET_PRIVATE (String, actual_string);
    
    return priv->ptr;
}

PUBLIC void
strSetContent (char * content) {
    StringPrivate * priv = OBJECT_GET_PRIVATE (String, actual_string);
    //OBJECT_GET_PRIVATE (String, actual_string);
    
    priv->len = strlen (content);
    priv->ptr = ALLOC (priv->len, char);
    priv->ptr = strdup(content);
    
    DEALLOC (content);
    
}

PUBLIC void
strdtor (void) {
    StringPrivate * priv = OBJECT_GET_PRIVATE (String, actual_string);
    
    if (priv->ptr != NULL) {
        DEALLOC (priv->ptr);
    }
    DEALLOC (priv);
    DEALLOC (actual_string);
}

PUBLIC String * 
new_string (void) {
   
    String * s = NEW (String);//ALLOC(1, String);
    StringPrivate * priv= NEW (StringPrivate); //ALLOC (1, StringPrivate);
    
    s->priv = priv;
    
    OBJECT_SET_TYPE (s, T_STRING);
    
    s->Length = strLength;
    s->getContent = strGetContent;   
    s->setContent = strSetContent;
    
    s->dtor = strdtor;
    
    return s;
}
