#ifndef URL_H
#define URL_H

struct url_t {
  char *protocol;
  char *host;
  char *port;
  char *path;

  int has_port;
};

extern struct url_t *url_new();
extern struct url_t *url_parse(const char *);
extern void url_free(struct url_t *);
extern const char *url_get_filename(const struct url_t *url);

#endif
