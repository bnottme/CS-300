#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <sstream>
#include <set>

/*
* Developer: Brett Nottmeier
* Course: SNHU CS 300
* Teacher: Charles Griffith 
*/

using namespace std;

// Course class 
class Course {

public:

    string number; // Course Number
    string title;  //Course Title
    string prerequisite; // Course Prerequisites

    
    Course(string num = "", string tit = "", string prereq = "") : number(num), title(tit), prerequisite(prereq) {}
};


// Load data from file into data structure
bool loadDataStructure(unordered_map<string, Course>& courses, const string& filename) {

    ifstream file(filename);

    // If file does not open return error
    if (!file.is_open()) {
        return false;
    }

    
    set<string> courseNumbers;

    string line;

    // Read file line by line
    while (getline(file, line)) {
        
        stringstream ss(line);
        string courseNumber, courseTitle, prerequisites;

        // Get course information from line
        getline(ss, courseNumber, ',');
        getline(ss, courseTitle, ',');
        getline(ss, prerequisites);


        courseNumbers.insert(courseNumber); // Add Course number

        // Create Course object to store in unordered map
        Course course(courseNumber, courseTitle, prerequisites); 
        courses[courseNumber] = course;
    }

    file.close();
    return true;
}

// Print the list of courses in alphanumeric order
void printCourseList(const unordered_map<string, Course>& courses) {
    
    vector<pair<string, string>> sortedCourses;

    
    for (const auto& pair : courses) {

        sortedCourses.push_back({ pair.second.number, pair.second.title });
    }

   // Sort courses 
    sort(sortedCourses.begin(), sortedCourses.end());

    // Print course list
    cout << "Course List:" << endl;
    for (const auto& pair : sortedCourses) {
        cout << pair.first << " - " << pair.second << endl;
    }
}

// Print information about a specific course
void printCourseInfo(const unordered_map<string, Course>& courses, const string& courseNumber) {

    // Check course number exists
    if (courses.find(courseNumber) == courses.end()) {
        cout << "Course " << courseNumber << " not found." << endl;
        return;
    }

    // Get course info from map
    const Course& course = courses.at(courseNumber);

    // Print course number and title
    cout << course.number << ", " << course.title << endl;

    // Print course Prerequisites if they exist
    if (course.prerequisite.empty()) {
        cout << "No prerequisites" << endl;
    }
    else {
        cout << "Prerequisites: " << course.prerequisite << endl;
    }
}

int main() {

    // Hash table for storing courses
    unordered_map<string, Course> courses; 

    int choice = 0;

    while (choice != 9) {
        cout << "1. Load data structure" << endl;
        cout << "2. Print Course List" << endl;
        cout << "3. Print Course" << endl;
        cout << "9. Exit program" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string filename;
            cout << "Enter the filename: ";
            cin >> filename;
            if (!loadDataStructure(courses, filename)) {
                cout << "Failed to load file." << endl;
            }
            break;
        }
        case 2:
            if (courses.empty()) {
                cout << "No course data loaded please choose a file in option 1." << endl;
            }
            else {
                printCourseList(courses);
            }
            break;
        case 3: {
            if (courses.empty()) {
                cout << "No course data loaded please choose a file in option 1." << endl;
            }
            else {
                string courseNumber;
                cout << "Enter the course number: ";
                cin >> courseNumber;
                printCourseInfo(courses, courseNumber);
            }
            break;
        }
        case 9:
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << choice << " is not a valid option." << endl;
        }
    }

    return 0;
}
