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

#include <cmath>

// ----------------------------
// modulus() tests
// ----------------------------

TEST(ComplexModulus, ZeroIsZero) {
    Complex z(0, 0);
    EXPECT_DOUBLE_EQ(z.modulus(), 0.0);
}

TEST(ComplexModulus, PureReal) {
    Complex z(5, 0);
    EXPECT_DOUBLE_EQ(z.modulus(), 5.0);
}

TEST(ComplexModulus, PureImag) {
    Complex z(0, -7);
    EXPECT_DOUBLE_EQ(z.modulus(), 7.0);
}

TEST(ComplexModulus, ThreeFourFive) {
    Complex z(3, 4);
    EXPECT_DOUBLE_EQ(z.modulus(), 5.0);
}

TEST(ComplexModulus, SymmetricForSigns) {
    Complex z1(3, 4);
    Complex z2(-3, 4);
    Complex z3(3, -4);
    Complex z4(-3, -4);

    EXPECT_DOUBLE_EQ(z1.modulus(), z2.modulus());
    EXPECT_DOUBLE_EQ(z1.modulus(), z3.modulus());
    EXPECT_DOUBLE_EQ(z1.modulus(), z4.modulus());
}


// ----------------------------
// modulus() tests with epsilon
// ----------------------------

TEST(ComplexModulus, WorksWithNonTrivialValues) {
    Complex z(1, 1);
    double expected = std::sqrt(2.0);
    EXPECT_NEAR(z.modulus(), expected, 1e-9);
}

TEST(ComplexModulus, LargerValuesEpsilonCheck) {
    Complex z(123, 456);
    double expected = std::sqrt(123.0 * 123.0 + 456.0 * 456.0);
    EXPECT_NEAR(z.modulus(), expected, 1e-9);
}

TEST(ComplexModulus, ModulusEqualsConjugateModulus) {
    Complex z(3, -7);
    EXPECT_NEAR(z.modulus(), z.conjugate().modulus(), 1e-9);
}