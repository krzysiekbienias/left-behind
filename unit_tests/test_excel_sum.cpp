#include <excel_sum.hpp>

#include <gtest/gtest.h>

// --- konstruktor ---

TEST(ExcelConstructorTest, InitializesAllCellsToZero) {
    Excel excel(3, 'C');

    EXPECT_EQ(excel.get(1, 'A'), 0);
    EXPECT_EQ(excel.get(1, 'B'), 0);
    EXPECT_EQ(excel.get(1, 'C'), 0);
    EXPECT_EQ(excel.get(2, 'A'), 0);
    EXPECT_EQ(excel.get(3, 'C'), 0);
}

TEST(ExcelConstructorTest, SupportsDifferentSheetSizes) {
    Excel excel(5, 'E');

    excel.set(5, 'E', 42);
    EXPECT_EQ(excel.get(5, 'E'), 42);
    EXPECT_EQ(excel.get(1, 'A'), 0);
}

// --- set / get (wartosci proste) ---

TEST(ExcelSetTest, StoresValueInCell) {
    Excel excel(3, 'C');

    excel.set(1, 'A', 2);

    EXPECT_EQ(excel.get(1, 'A'), 2);
}

TEST(ExcelSetTest, OverwritesPreviousValue) {
    Excel excel(3, 'C');

    excel.set(2, 'B', 5);
    excel.set(2, 'B', 9);

    EXPECT_EQ(excel.get(2, 'B'), 9);
}

TEST(ExcelSetTest, CellsAreIndependent) {
    Excel excel(3, 'C');

    excel.set(1, 'A', 2);
    excel.set(2, 'B', 7);

    EXPECT_EQ(excel.get(1, 'A'), 2);
    EXPECT_EQ(excel.get(2, 'B'), 7);
    EXPECT_EQ(excel.get(1, 'B'), 0);
    EXPECT_EQ(excel.get(2, 'A'), 0);
}

TEST(ExcelSetTest, AllowsZeroAndNegativeValues) {
    Excel excel(3, 'C');

    excel.set(1, 'A', 0);
    excel.set(1, 'B', -15);

    EXPECT_EQ(excel.get(1, 'A'), 0);
    EXPECT_EQ(excel.get(1, 'B'), -15);
}

TEST(ExcelSetTest, ClearsFormulaWhenOverwritten) {
    Excel excel(3, 'C');

    excel.set(1, 'A', 10);
    excel.sum(3, 'C', {"A1"});
    EXPECT_EQ(excel.get(3, 'C'), 10);

    excel.set(3, 'C', 99);
    EXPECT_EQ(excel.get(3, 'C'), 99);
}

// --- sum: pojedyncza komorka ---

TEST(ExcelSumTest, SingleCellReference) {
    Excel excel(3, 'C');

    excel.set(1, 'A', 7);
    EXPECT_EQ(excel.sum(2, 'B', {"A1"}), 7);
    EXPECT_EQ(excel.get(2, 'B'), 7);
}

// --- sum: zakres prostokatny ---

TEST(ExcelSumTest, RectangularRange) {
    Excel excel(3, 'C');

    excel.set(1, 'A', 1);
    excel.set(1, 'B', 2);
    excel.set(2, 'A', 3);
    excel.set(2, 'B', 4);

    EXPECT_EQ(excel.sum(3, 'C', {"A1:B2"}), 10);
    EXPECT_EQ(excel.get(3, 'C'), 10);
}

TEST(ExcelSumTest, MultipleTokens) {
    Excel excel(3, 'C');

    excel.set(1, 'A', 2);
    excel.set(2, 'B', 5);

    // A1 + B2
    EXPECT_EQ(excel.sum(3, 'C', {"A1", "B2"}), 7);
}

// --- przyklad z tresci zadania ---

TEST(ExcelExampleTest, FullSequenceFromProblemStatement) {
    Excel excel(3, 'C');

    excel.set(1, 'A', 2);
    EXPECT_EQ(excel.sum(3, 'C', {"A1", "A1:B2"}), 4);

    excel.set(2, 'B', 2);
    EXPECT_EQ(excel.get(3, 'C'), 6);
}

// --- lazy evaluation: zmiana zrodla aktualizuje formule ---

TEST(ExcelLazyEvalTest, FormulaReflectsUpdatedDependencies) {
    Excel excel(3, 'C');

    excel.set(1, 'A', 1);
    excel.sum(3, 'C', {"A1"});

    EXPECT_EQ(excel.get(3, 'C'), 1);

    excel.set(1, 'A', 100);
    EXPECT_EQ(excel.get(3, 'C'), 100);
}

TEST(ExcelLazyEvalTest, RangeSumUpdatesWhenCellInsideRangeChanges) {
    Excel excel(3, 'C');

    excel.set(1, 'A', 1);
    excel.set(2, 'B', 2);
    excel.sum(3, 'C', {"A1:B2"});

    EXPECT_EQ(excel.get(3, 'C'), 3);

    excel.set(2, 'B', 20);
    EXPECT_EQ(excel.get(3, 'C'), 21);
}

// --- sum nadpisuje poprzednia formule ---

TEST(ExcelSumTest, OverwritesPreviousFormula) {
    Excel excel(3, 'C');

    excel.set(1, 'A', 5);
    excel.set(2, 'B', 10);

    excel.sum(3, 'C', {"A1"});
    EXPECT_EQ(excel.get(3, 'C'), 5);

    excel.sum(3, 'C', {"B2"});
    EXPECT_EQ(excel.get(3, 'C'), 10);
}

// --- po nadpisaniu formuly stare zrodlo NIE wplywa juz na wynik ---

TEST(ExcelSumTest, OldDependencyStopsAffectingAfterReformula) {
    Excel excel(3, 'C');

    excel.set(1, 'A', 5);
    excel.set(2, 'B', 10);

    excel.sum(3, 'C', {"A1"});   // C3 zalezy od A1
    EXPECT_EQ(excel.get(3, 'C'), 5);

    excel.sum(3, 'C', {"B2"});   // C3 zalezy teraz od B2, NIE od A1
    EXPECT_EQ(excel.get(3, 'C'), 10);

    excel.set(1, 'A', 999);      // zmiana starego zrodla nie moze ruszyc C3
    EXPECT_EQ(excel.get(3, 'C'), 10);
}

// --- lancuch formul: zmiana korzenia propaguje sie przez cache ---

TEST(ExcelCacheTest, ChainInvalidatesThroughDependents) {
    Excel excel(4, 'A');

    excel.set(1, 'A', 1);
    excel.sum(2, 'A', {"A1"});   // A2 = A1
    excel.sum(3, 'A', {"A2"});   // A3 = A2
    excel.sum(4, 'A', {"A3"});   // A4 = A3

    EXPECT_EQ(excel.get(4, 'A'), 1);

    excel.set(1, 'A', 50);       // zmiana korzenia
    EXPECT_EQ(excel.get(4, 'A'), 50);
    EXPECT_EQ(excel.get(3, 'A'), 50);
    EXPECT_EQ(excel.get(2, 'A'), 50);
}

// --- test wydajnosci: "schodkowy" przypadek z LeetCode (dawny TLE) ---
// Kazdy wiersz k = suma 4 komorek wiersza k-1. Lazy bez cache = 4^depth (TLE).
// Z memoizacja kazda komorka liczona raz -> szybko.

TEST(ExcelPerformanceTest, StaircaseSumsDoNotBlowUp) {
    Excel excel(16, 'D');

    for (int row = 2; row <= 16; row++) {
        std::string range = "A" + std::to_string(row - 1) + ":D" + std::to_string(row - 1);
        for (char col = 'A'; col <= 'D'; col++) {
            excel.sum(row, col, {range});
        }
    }

    // wiersz 1 nigdy nie ustawiony -> wszystko zeruje sie do 0
    EXPECT_EQ(excel.get(16, 'D'), 0);

    // ustaw jedna komorke korzenia i sprawdz propagacje w gore
    excel.set(1, 'A', 1);
    // wiersz 2: kazda komorka = suma A1:D1 = 1
    EXPECT_EQ(excel.get(2, 'A'), 1);
    // wiersz 3: kazda komorka = suma A2:D2 = 4
    EXPECT_EQ(excel.get(3, 'A'), 4);
    // wiersz 4: suma A3:D3 = 4*4 = 16
    EXPECT_EQ(excel.get(4, 'A'), 16);
}
