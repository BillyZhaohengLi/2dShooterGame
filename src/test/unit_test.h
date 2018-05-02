#pragma once
#include <iostream>
using namespace std;
/*
spagetti unit test object created to test various functions in this openframeworks program since both Catch and Visual Studio
Unit Tests were not very cooperative.
this class and its class members were NOT named according to the C++ style guide to simulate a more realistic experience
with using an *actual* testing framework such as Catch.
*/
class UNIT_TEST {
private:
	/*
	total tests succeeded
	*/
	int tests_succeeded_;

	/*
	total tests run
	*/
	int tests_total_;

	/*
	name of the test block
	*/
	string test_name_;
public:
	/*
	creates a new unit test block.
	*/
	UNIT_TEST(string test_name) {
		tests_succeeded_ = 0;
		tests_total_ = 0;
		test_name_ = test_name;
		cout << "==================================================\n";
		cout << test_name << ":\n";
		cout << "==================================================\n";
	}

	/*
	destructor for unit test block; basically prints out the test results when the UNIT_TEST object goes out of scope
	(which is typically when all tests with a certain object is completed).
	*/
	~UNIT_TEST() {
		cout << "==================================================\n";
		cout << test_name_ << ": " << tests_succeeded_ << " out of " << tests_total_ << " passed.\n";
		cout << "==================================================\n";
	}

	/*
	assert two objects to be equal. Prints the outcome.
	*/
	template <class T>
	void ASSERT_EQUALS(string test_name, T a, T b) {
		if (a == b) {
			cout << test_name << ": passed\n";
			tests_succeeded_++;
		}
		else {
			cout << test_name << ": failed - " << a << " not equals " << b << "\n";
		}
		tests_total_++;
	}

	/*
	assert method specifically used for comparind doubles.
	determines whether two doubles are equal to within a certain range. Prints the outcome.
	*/
	void ASSERT_EQUALS(string test_name, double a, double b, double epsilon) {
		if (abs(a - b) < epsilon) {
			cout << test_name << ": passed\n";
			tests_succeeded_++;
		}
		else {
			cout << test_name << ": failed - " << a << " not equals " << b << "\n";
		}
		tests_total_++;
	}
};