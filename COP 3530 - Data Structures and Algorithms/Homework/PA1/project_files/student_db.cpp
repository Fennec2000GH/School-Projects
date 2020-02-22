#include <cmath> 
#include <string>
#include <vector>
#include "student_db.h"

namespace cop3530 {

//CONSTRUCTORS
student_info::student_info() {}
student_info::student_info(std::string name, double gpa) : name(name), gpa(gpa) {}

//MEMBER FUNCTIONS
std::string student_info::get_name() const { return name; }

double student_info::get_gpa() const { return gpa; }

bool student_info::operator==(const student_info &other) const {
    return name == other.name && abs(gpa - other.gpa) < 0.000000001;
}

//CONSTRUCTORS
student_db::student_db() { student_bst = new bst<int, student_info>(); }

//DESTRUCTORS
student_db::~student_db() { delete student_bst; }

//MEMBER FUNCTIONS
void student_db::insert(const int student_id, const std::string &student_name, const double gpa) {
    student_bst -> insert(student_id, student_info(student_name, gpa));
}

void student_db::erase(const int student_id) { student_bst -> erase(student_id); }

student_info &student_db::lookup(const int student_id) { return student_bst -> at(student_id); }

bool student_db::empty() const { return student_bst -> empty(); }

size_t student_db::size() const { return student_bst -> size(); }

std::vector<std::pair<int, student_info>> student_db::get_all_students() { return student_bst -> inorder_contents(); }


} // namespace cop3530

//int main(){ return 0; } //needed for compiling student_db.cpp individually
