#pragma once

#include <string>
#include <vector>

/**
 * @brief Represents a student with a name and grade.
 *
 * Stores all instances in a static list for aggregate operations
 * such as finding the best student or calculating average grade.
 */
class Student {
private:
    std::string name;
    int grade;

    static std::vector<Student*> all_students; ///< Tracks all instantiated students

public:
    /**
         * @brief Constructs a new Student object and registers it.
         * @param name The name of the student.
         * @param grade The initial grade of the student (0 - 100).
    */
    Student(const std::string& name, int grade);
    /**
         * @brief Constructs a new Student object and registers it.
         * @param name The name of the student.
         * @param grade The initial grade of the student (0 - 100).
    */
    const std::string& get_name() const;
    /**
         * @brief Retrieves the student's name.
         * @return A constant reference to the student's name.
    */
    int get_grade() const;
    
    /**
       * @brief Sets a new grade for the student.
       * @param new_grade The new grade to assign.
       * @throws std::out_of_range if the grade is not between 0 and 100.
    */
    void set_grade(int new_grade);

    static double calculate_average(const std::vector<Student*>& students);
    /**
         * @brief Finds the best-performing student.
         * @return A pointer to the student with the highest grade, or nullptr if none exist.
    */
    static Student* get_best_student();
    /**
         * @brief Clears the internal list of all students.
         *
         * Useful for isolating test runs or resetting application state.
    */
    static void reset_all_students();
};
