#include "url.h"

#include <stdlib.h>
#include <string.h>

static inline void free_unless_null(void *);
static char *copy_string(const char *s, int len);
static int has_port(const char *s);
static const char *parse_protocol(struct url_t *self, const char *p);
static const char *parse_host(struct url_t *self, const char *p);
static const char *parse_port(struct url_t *self, const char *p);

/*** public functions ***/

struct url_t *url_new() {
  return (struct url_t *)calloc(1, sizeof(struct url_t));
}

struct url_t *url_parse(const char *url) {
  struct url_t *self = url_new();
  const char *p = url;

  if (!(p = parse_protocol(self, p))) {
    url_free(self);
    return NULL;
  }

  self->has_port = has_port(p);
  if (!(p = parse_host(self, p))) {
    url_free(self);
    return NULL;
  }

  if (!(p = parse_port(self, p))) {
    url_free(self);
    return NULL;
  }

  self->path = copy_string(p, strlen(p));
  return self;
}

void url_free(struct url_t *self) {
  free_unless_null(self->protocol);
  free_unless_null(self->host);
  free_unless_null(self->port);
  free_unless_null(self->path);
  free(self);
}

const char *url_get_filename(const struct url_t *url) {
  const char *res = strrchr(url->path, '/');
  return res ? res + 1 : NULL;
}

/*** private functions ***/

static inline void free_unless_null(void *p) {
  if (p) {
    free(p);
  }
}

static char *copy_string(const char *s, int len) {
  char *res = (char *) malloc(sizeof(char) * len + 1);
  strncpy(res, s, len);
  res[len] = '\0';
  return res;
}

static int has_port(const char *s) {
  const char *slash = strchr(s, '/');
  const char *colon = strchr(s, ':');
  if (!colon) {
    return 0;
  }
  return colon < slash;
}

static const char *parse_protocol(struct url_t *self, const char *p) {
  const char *q;

  if (q = strstr(p, "://")) {
    int len = q - p;
    self->protocol = copy_string(p, len);
    return q + 3;
  } else {
    return NULL;
  }
}

static const char *parse_host(struct url_t *self, const char *p) {
  const char *q;

  if (q = strchr(p, self->has_port ? ':' : '/')) {
    int len = q - p;
    self->host = copy_string(p, len);
    return q + 1;
  } else {
    return NULL;
  }
}

static const char *parse_port(struct url_t *self, const char *p) {
  const char *q;

  if (self->has_port) {
    if (q = strchr(p, '/')) {
      int len = q - p;
      self->port = copy_string(p, len);
      return q + 1;
    } else {
      return NULL;
    }
  } else {
    if (!strcmp(self->protocol, "http")) {
      self->port = strdup("80");
    } else if (!strcmp(self->protocol, "https")) {
      self->port = strdup("443");
    }
    return p;
  }
}
