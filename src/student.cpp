#include "student.hpp"
#include <stdexcept>
#include <limits>

std::vector<Student*> Student::all_students;

Student::Student(const std::string& name, int grade)
    : name(name), grade(grade) {
    all_students.push_back(this);
}

const std::string& Student::get_name() const {
    return name;
}

int Student::get_grade() const {
    return grade;
}

void Student::set_grade(int new_grade) {
    if (new_grade < 0 || new_grade > 100) {
        throw std::out_of_range("New grade not in accepted range of [0-100]");
    }
    grade = new_grade;
}

double Student::calculate_average(const std::vector<Student*>& students) {
    if (students.empty()) return -1.0;

    double sum = 0.0;
    for (const auto* student : students) {
        sum += student->get_grade();
    }
    return sum / students.size();
}

Student* Student::get_best_student() {
    Student* best = nullptr;
    int highest_grade = std::numeric_limits<int>::min();

    for (Student* s : all_students) {
        if (s && s->get_grade() > highest_grade) {
            highest_grade = s->get_grade();
            best = s;
        }
    }
    return best;
}

void Student::reset_all_students() {
    all_students.clear();
}
