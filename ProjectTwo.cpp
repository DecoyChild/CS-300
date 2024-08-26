//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Shayne
// Description : A data structure that holds Course information
//				as a vector. Files loaded from a csv file.
//============================================================================

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

/**
 * The struct for the Course object
 */
struct Course {
	string courseID;
	string courseTitle;
	vector<string> prereq;
	Course(){};
};

/**
 * Load the courses into a vector of Course objects
 * @PARAM String filepath where the csv file lives
 * @PARAM The vector used to load the Course structs
 */
void loadCourses(string filePath, vector<Course> *courses){
	// Create the input stream
	ifstream fin;

	// open the file using the stram
	fin.open(filePath,ios::in);

	// If the file open was a success
	if (fin.is_open()){
		vector<vector<string>> row;

		string line,temp;

		// while there is a line to get / there is still data to read
		while (getline(fin,line)){
			string word;

			// get the entire next line from file input and load to line
			stringstream s(line);

			vector<string> col;

			// separate the row into columns
			while (getline(s,word,',')){
				col.push_back(word);
			}
			row.push_back(col);

		}

		// store the values into the Course structure
		for (int i = 0; i < row.size(); i++ ){
			Course course;
			course.courseID = row[i][0];
			course.courseTitle = row[i][1];
			course.prereq.push_back(row[i][2]);
			course.prereq.push_back(row[i][3]);
			courses->push_back(course);
		}
	} else {
		cout << "File cannot be opened at this time...";
	}
}

/**
 * Prints the entire vector
 * @PARAM The vector of courses
 */
void printAll(vector<Course> *courses){

	// if there is anything loaded into the course vector
	if (courses->size() > 0){
		// Formatiting the output (Headers)
		cout << left << setw(12) << setfill(' ') << "Course ID";
		cout << left << setw(40) << "Title";
		cout << "Prereq" << endl;

		// looping though the courses to print
		for(int i = 0; i < courses->size(); i++){
			string prereqCourses;
			Course tempCourse = courses->at(i);
			cout << left << setw(12) << setfill('.') << tempCourse.courseID;
			cout << left << setw(40) << tempCourse.courseTitle;

			// concatinating a string of the prereques
			for(int j =0; j < tempCourse.prereq.size(); j++){
				prereqCourses = prereqCourses.append(" " + tempCourse.prereq.at(j));
			}
			cout << prereqCourses;
		}

	}else{
		cout << "There are no courses loaded to print...." << endl;
	}
}

/**
 * Search if a selected Course ID exists in the vector
 * @PARAM CourseID to search for
 * @PARAM vector of Courses
 * @RETURN The course if it exists, otherwise a null object
 */
Course search(string courseID, vector<Course> *courses){
	// if the vector is not empty, then
	for (int i = 0; i < courses->size(); i++){
		Course course = courses->at(i);
//		string tempCourseID = course.courseID;

		//Comparing the course ID in uppercase regardless of how the ID was  entered in
		transform(course.courseID.begin(), course.courseID.end(), course.courseID.begin(), ::toupper);

		if (courseID.compare(course.courseID) == 0){
			// if the course was found, return that course object
			return course;
		}
	}

	// create a null course in the case one was not found
	Course course;
	// returns a null course if nothing was found
	return course;
}


/**
 * Prints the info for the course entered
 * @PARAM Course struct
 */
void printCourse(Course course){
	cout << course.courseID << ": ";
	cout << course.courseTitle << endl;
	if (course.prereq.size() > 0 ){
		cout << "Prerequisites: " << endl;
		for (int i=0; i < course.prereq.size(); i++){
			cout << course.prereq.at(i) << endl;
		}
	}

}


int main() {
	// Prints out a border for the menu
	string menuBanner(25,'=');
	string filepath;
	string courseSearch;
	string newString;
	Course searchCourse;
	vector<Course> courses;

	int selection = 0;
	while (selection != 9) {
		cout << menuBanner << endl;
		cout << "ABCU Advising Course Menu" << endl;
		cout << menuBanner << endl;
		cout << "  Option 1: Load Data" << endl;
		cout << "  Option 2: Print All the Courses" << endl;
		cout << "  Option 3: Print a Course" << endl;
		cout << "  Option 9: Exit" << endl;
		cout <<  menuBanner << endl;
		cout << "  Enter selection..." << endl;

		cin >> selection;

		switch (selection) {
			case 1:
				cout << "Enter the name of the file..." << endl;
				cin >> filepath;
				loadCourses(filepath, &courses);
			break;
			case 2:
				printAll(&courses);
			break;
			case 3:

				cout << "Enter the course you are looking for..." << endl;
				cin >> courseSearch;
				transform(courseSearch.begin(), courseSearch.end(), courseSearch.begin(), ::toupper);

				searchCourse = search(courseSearch, &courses);
				if (!searchCourse.courseID.empty()){
					printCourse(searchCourse);
				} else {
					cout << "Sorry, the course you entered: " << courseSearch;
					cout << " was not found." << endl;
				}

			break;
			case 9:
				cout << "Thank you for using " << endl;
			break;
			default:
				cout << "Not a valid option...try again" << endl;
			break;
		}
	}

	cout << "Exiting program" << endl; // prints test
	return 0;
}
