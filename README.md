# URL Parser Library in C

## Example

```c
#include <stdio.h>
#include <url.h>

int main() {
  struct url_t *url = url_parse("http://example.com/path/to/file.html");
  printf("PROTOCOL: %s\n", url->protocol);
  printf("HOST: %s\n", url->host);
  printf("PORT: %s\n", url->port);
  printf("PATH: %s\n", url->path);
  url_free(url);
  return 0;
}
```

```txt
PROTOCOL: http
HOST: example.com
PORT: 80
PATH: path/to/file.html
```

## Building liburl

```
$ mkdir build && cd build
$ cmake ..
$ make
```

## LICENSE

```txt
The MIT License (MIT)

Copyright (c) 2015 Hiroyuki Sano

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
```
