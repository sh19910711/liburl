#include "url.h"

#include <stdlib.h>

static inline void free_unless_null(void *);

struct url_t *url_new() {
  return (struct url_t *)calloc(1, sizeof(struct url_t));
}

void url_free(struct url_t *self) {
  free_unless_null(self->protocol);
  free_unless_null(self->host);
  free_unless_null(self->port);
  free_unless_null(self->path);
  free(self);
}

/*** private functions ***/

static inline void free_unless_null(void *p) {
  if (p) {
    free(p);
  }
}
