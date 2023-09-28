#include "google/protobuf/compiler/versions.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "absl/memory/memory.h"
#include "google/protobuf/test_textproto.h"

namespace google {
namespace protobuf {
namespace compiler {
namespace internal {
namespace {
TEST(GetProtobufVersionTest, EmptyVersionString) {
  EXPECT_DEATH({ ParseProtobufVersion(""); }, "version cannot be empty");
}

TEST(GetProtobufVersionTest, MissingVersionSegment) {
  EXPECT_DEATH({ ParseProtobufVersion("3.26-dev"); },
               "version string must provide major, minor and micro numbers.");
}

TEST(GetProtobufVersionTest, FullVersionWithRCSuffix) {
  auto version = absl::WrapUnique(ParseProtobufVersion("3.26.2-rc1"));
  EXPECT_THAT(*version,
              EqualsProto(R"pb(major: 3 minor: 26 patch: 2 suffix: "-rc1")pb"));
}

TEST(GetProtobufVersionTest, FullVersionWithoutSuffix) {
  auto version = absl::WrapUnique(ParseProtobufVersion("3.26.2"));
  EXPECT_THAT(*version, EqualsProto(R"pb(major: 3 minor: 26 patch: 2)pb"));
}

TEST(GetProtobufVersionTest, VersionWithDevSuffix) {
  auto version = absl::WrapUnique(ParseProtobufVersion("3.26.0-dev"));
  EXPECT_THAT(*version,
              EqualsProto(R"pb(major: 3 minor: 26 patch: 0 suffix: "-dev")pb"));
}
}  // namespace
}  // namespace internal
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
