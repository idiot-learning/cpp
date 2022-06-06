#ifndef __STUDENT_HPP__
#define __STUDENT_HPP__
#include <string>
#include <iostream>

struct Student {
    std::string name;
    float score;

    bool operator<(const Student& rhs) {
        return this->score < rhs.score;
    }
    friend std::ostream& operator<<(std::ostream& os, const Student& student) {
        os << "Student: " << student.name << " " << student.score << std::endl;
        return os;
    }
};

#endif