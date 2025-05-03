// test_student.cpp
#include "student.hpp"
#include <gtest/gtest.h>

TEST(StudentTest, GradeSetterValidRange) {
    Student s("Alice", 80);
    s.set_grade(90);
    EXPECT_EQ(s.get_grade(), 90);
}

TEST(StudentTest, GradeSetterOutOfRangeThrows) {
    Student s("Bob", 75);
    EXPECT_THROW(s.set_grade(150), std::out_of_range);
    EXPECT_THROW(s.set_grade(-10), std::out_of_range);
}

TEST(StudentTest, CalculatesAverage) {
    Student s1("Alice", 90);
    Student s2("Bob", 80);
    Student s3("Charlie", 70);

    std::vector<Student*> group = {&s1, &s2, &s3};
    double average = Student::calculate_average(group);

    EXPECT_DOUBLE_EQ(average, 80.0);
}

TEST(StudentTest, BestStudentReturned) {
    // Clear the static all_students vector for isolated test (optional but good for isolation)
    Student::reset_all_students();
    
    Student s1("Alice", 85);
    Student s2("Bob", 92);
    Student s3("Charlie", 78);
    
    Student* best = Student::get_best_student();
    ASSERT_NE(best, nullptr);
    EXPECT_EQ(best->get_name(), "Bob");
    EXPECT_EQ(best->get_grade(), 92);
}
