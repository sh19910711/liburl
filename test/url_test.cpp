#include <gtest/gtest.h>

extern "C" {
  #include "url.h"
}

class UrlTest : public ::testing::Test {
protected:
  struct url_t *self;

  virtual void TearDown() {
    url_free(self);
  }
};

class UrlExampleCom : public UrlTest {
protected:
  virtual void SetUp() {
    self = url_parse("http://example.com/path/to/file.tar.gz");
  }
};

TEST_F(UrlExampleCom, Protocol) {
  ASSERT_TRUE(self->protocol);
  ASSERT_STREQ("http", self->protocol);
}

TEST_F(UrlExampleCom, Host) {
  ASSERT_TRUE(self->host);
  ASSERT_STREQ("example.com", self->host);
}

TEST_F(UrlExampleCom, Port) {
  ASSERT_TRUE(self->port);
  ASSERT_STREQ("80", self->port);
}

TEST_F(UrlExampleCom, Path) {
  ASSERT_TRUE(self->path);
  ASSERT_STREQ("path/to/file.tar.gz", self->path);
}

TEST_F(UrlExampleCom, GetFileName) {
  ASSERT_STREQ("file.tar.gz", url_get_filename(self));
}
