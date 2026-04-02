#include <stdlib.h>
#include <string.h>
#include "session.h"

session_t *session_create(const char *id, unsigned int uid,
                           const unsigned char *data, size_t data_len)
{
    session_t *s;

    s = (session_t *)malloc(sizeof(*s));
    if (!s)
        return NULL;

    /* Bug 1 fix : on copie id, la session en est propriétaire */
    s->id = (char *)malloc(strlen(id) + 1);
    if (!s->id) {
        free(s);          /* Bug 2 fix : on libère s avant de retourner NULL */
        return NULL;
    }
    strcpy(s->id, id);

    s->uid = uid;

    if (data_len > 0) {
        s->data = (unsigned char *)malloc(data_len);
        if (!s->data) {
            free(s->id);  /* Bug 2 fix : on libère ce qui a déjà été alloué */
            free(s);
            return NULL;
        }
        memcpy(s->data, data, data_len);
        s->data_len = data_len;
    } else {
        s->data = NULL;
        s->data_len = 0;
    }

    return s;
}

int session_set_data(session_t *s, const unsigned char *data, size_t data_len)
{
    unsigned char *tmp;

    if (!s)
        return 0;

    if (data_len == 0) {
        free(s->data);
        s->data = NULL;
        s->data_len = 0;
        return 1;
    }

    /* Bug 3 fix : on garde l'ancien pointeur au cas où realloc échoue */
    tmp = (unsigned char *)realloc(s->data, data_len);
    if (!tmp) {
        /* s->data pointe toujours vers l'ancien bloc, pas de fuite */
        s->data_len = 0;
        return 0;
    }

    s->data = tmp;
    memcpy(s->data, data, data_len);
    s->data_len = data_len;
    return 1;
}

void session_destroy(session_t *s)
{
    if (!s)
        return;

    free(s->id);    /* OK : maintenant id est bien alloué par la session */
    free(s->data);
    free(s);
}
