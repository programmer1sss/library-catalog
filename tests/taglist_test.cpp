#include <gtest/gtest.h>
#include <utility>
#include "TagList.h"

// 1. Глибока копія (Крок 3)
TEST(TagListTest, DeepCopy) {
    TagList a(4);
    a.add("x");
    a.add("y");

    TagList b = a;
    ASSERT_EQ(b.size(), 2u);
    EXPECT_EQ(b.at(0), "x");
    EXPECT_EQ(b.at(1), "y");
}

// 2. Незалежність копій
TEST(TagListTest, CopiesAreIndependent) {
    TagList a(4);
    a.add("x");
    TagList b = a;

    a.add("new");  // змінюємо оригінал

    EXPECT_EQ(a.size(), 2u);
    EXPECT_EQ(b.size(), 1u);  // копія не змінилася
    EXPECT_EQ(b.at(0), "x");
}

// 3. Присвоєння копіюванням
TEST(TagListTest, CopyAssignment) {
    TagList a(4);
    a.add("a1");

    TagList b(4);
    b.add("b1");
    b.add("b2");

    b = a;  // копіювання

    ASSERT_EQ(b.size(), 1u);
    EXPECT_EQ(b.at(0), "a1");
    EXPECT_EQ(a.size(), 1u);
}

// 4. Самоприсвоєння (через аліас, щоб уникнути попередження -Wself-assign)
TEST(TagListTest, SelfAssignment) {
    TagList a(4);
    a.add("x");
    a.add("y");
    a.add("z");

    TagList& alias = a;
    a = alias;

    EXPECT_EQ(a.size(), 3u);
    EXPECT_EQ(a.at(0), "x");
}

// 5. Переміщення з обнуленням джерела (Крок 5)
TEST(TagListTest, MoveConstructor) {
    TagList a(4);
    a.add("x");
    a.add("y");

    TagList b = std::move(a);

    EXPECT_EQ(b.size(), 2u);
    EXPECT_EQ(b.at(0), "x");
    EXPECT_EQ(a.size(), 0u);  // джерело спорожнене
}

// 6. Присвоєння переміщенням
TEST(TagListTest, MoveAssignment) {
    TagList a(4);
    a.add("x");
    a.add("y");

    TagList b(4);
    b.add("old");

    b = std::move(a);

    EXPECT_EQ(b.size(), 2u);
    EXPECT_EQ(b.at(0), "x");
    EXPECT_EQ(a.size(), 0u);
}