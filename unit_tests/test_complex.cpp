#include <gtest/gtest.h>
#include <stdexcept>
#include <string>

#include "complex_numbers.hpp"

void expectComplexEq(const Complex& c, int ra, int ib) {
    EXPECT_EQ(c.a, ra);
    EXPECT_EQ(c.b, ib);
}

// ----------------------------
// Constructor tests
// ----------------------------

TEST(ComplexCtor, DefaultCtorIsZeroZero) {
    Complex c;
    expectComplexEq(c, 0, 0);
}

TEST(ComplexCtor, TwoArgCtorSetsFields) {
    Complex c(3, -5);
    expectComplexEq(c, 3, -5);
}

TEST(ComplexCtor, OneArgCtorSetsRealAndZeroImag) {
    Complex c(7);
    expectComplexEq(c, 7, 0);
}

// ----------------------------
// operator+ tests
// ----------------------------

TEST(ComplexPlus, SimpleAdd) {
    Complex c1(3, 4);
    Complex c2(2, 5);
    Complex res = c1 + c2;
    expectComplexEq(res, 5, 9);
}

TEST(ComplexPlus, AddWithNegatives) {
    Complex c1(3, -4);
    Complex c2(-2, 5);
    Complex res = c1 + c2;
    expectComplexEq(res, 1, 1);
}

TEST(ComplexPlus, AddWithZeros) {
    Complex c1;
    Complex c2(7, -8);
    Complex res = c1 + c2;
    expectComplexEq(res, 7, -8);
}

TEST(ComplexPlus, DoesNotMutateOperands) {
    Complex c1(3, 4);
    Complex c2(2, 5);

    Complex res = c1 + c2;

    // result ok
    expectComplexEq(res, 5, 9);

    // operands unchanged
    expectComplexEq(c1, 3, 4);
    expectComplexEq(c2, 2, 5);
}

// ----------------------------
// conjugate() tests
// ----------------------------

TEST(ComplexConjugate, FlipsImaginarySign) {
    Complex z(3, 5);
    Complex c = z.conjugate();
    EXPECT_EQ(c.a, 3);
    EXPECT_EQ(c.b, -5);
}

TEST(ComplexConjugate, WorksForNegativeImaginary) {
    Complex z(3, -5);
    Complex c = z.conjugate();
    EXPECT_EQ(c.a, 3);
    EXPECT_EQ(c.b, 5);
}

TEST(ComplexConjugate, ZeroImaginaryStaysZero) {
    Complex z(7, 0);
    Complex c = z.conjugate();
    EXPECT_EQ(c.a, 7);
    EXPECT_EQ(c.b, 0);
}

TEST(ComplexConjugate, ZeroZeroStaysZeroZero) {
    Complex z(0, 0);
    Complex c = z.conjugate();
    EXPECT_EQ(c.a, 0);
    EXPECT_EQ(c.b, 0);
}

TEST(ComplexConjugate, DoesNotMutateOriginal) {
    Complex z(3, 5);
    Complex c = z.conjugate();

    // original unchanged
    EXPECT_EQ(z.a, 3);
    EXPECT_EQ(z.b, 5);

    // conjugate correct
    EXPECT_EQ(c.a, 3);
    EXPECT_EQ(c.b, -5);
}

// Optional "property-like" test: conjugate twice gives original
TEST(ComplexConjugate, DoubleConjugateGivesOriginal) {
    Complex z(-12, 34);
    Complex back = z.conjugate().conjugate();
    EXPECT_EQ(back.a, z.a);
    EXPECT_EQ(back.b, z.b);
}

