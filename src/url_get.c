#include "url.h"

#include <string.h>

const char *url_get_filename(const struct url_t *url) {
  const char *res = strrchr(url->path, '/');
  return res ? res + 1 : NULL;
}
