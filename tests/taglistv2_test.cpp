#include <gtest/gtest.h>
#include <string>
#include <utility>
#include <vector>
#include "taglistv2.h"

// Ті самі шість тестів, що й для TagList, але для TagListV2.

TEST(TagListV2Test, DeepCopy) {
    TagListV2 a;
    a.add("x");
    a.add("y");
    TagListV2 b = a;
    ASSERT_EQ(b.size(), 2u);
    EXPECT_EQ(b.at(0), "x");
    EXPECT_EQ(b.at(1), "y");
}

TEST(TagListV2Test, CopiesAreIndependent) {
    TagListV2 a;
    a.add("x");
    TagListV2 b = a;
    a.add("new");
    EXPECT_EQ(a.size(), 2u);
    EXPECT_EQ(b.size(), 1u);
}

TEST(TagListV2Test, CopyAssignment) {
    TagListV2 a;
    a.add("a1");
    TagListV2 b;
    b.add("b1");
    b.add("b2");
    b = a;
    ASSERT_EQ(b.size(), 1u);
    EXPECT_EQ(b.at(0), "a1");
}

TEST(TagListV2Test, SelfAssignment) {
    TagListV2 a;
    a.add("x");
    a.add("y");
    TagListV2& alias = a;
    a = alias;
    EXPECT_EQ(a.size(), 2u);
}

TEST(TagListV2Test, MoveConstructor) {
    TagListV2 a;
    a.add("x");
    a.add("y");
    TagListV2 b = std::move(a);
    EXPECT_EQ(b.size(), 2u);
    EXPECT_EQ(a.size(), 0u);  // std::vector залишає джерело порожнім
}

TEST(TagListV2Test, MoveAssignment) {
    TagListV2 a;
    a.add("x");
    a.add("y");
    TagListV2 b;
    b.add("old");
    b = std::move(a);
    EXPECT_EQ(b.size(), 2u);
    EXPECT_EQ(a.size(), 0u);
}
