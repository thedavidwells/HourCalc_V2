// HourCalc_v2.cpp : Defines the entry point for the console application.
//
// Copyright 2013 NorthWest Engineering
// Code by David Wells


#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctime>
#include <ctype.h>
#include <sstream>
#include <iomanip>
#include <ctype.h>
#include <exception>

using namespace std;

const char delim = ':';
const int hoursPerDay = 24;
const int minutesPerHour = 60;

//  FUNCTION DECLARATIONS
//  ******************************************************
	string floatFix(float);
	void start_app();
	void enter_timeCard(int &, int &, int &, int &);
	int calculate_hours(int , int);
	float calculate_min(int , int, int &);
	void getTime(int &, int &);
	bool isValidTime(int, int);
	float tookLunch();
	void printResults(int , float );
	void calculate_time();
//  ******************************************************



// GLOBAL VARIABLES (DANGER!)
//  ******************************************************



//  ******************************************************



//  MAIN FUNCTION
//  ******************************************************
int _tmain(int argc, _TCHAR* argv[])
{
	char c = 'y';

	start_app();

	do{
		calculate_time();
		
		// cout << "Calculate another? (y or n)";
		// cin >> c;

		cout << endl << endl;
	} while(c != 'n' );

	return 0;
	// system("PAUSE");
}
//  ******************************************************



//  FUNCTION DEFINITIONS
//  ******************************************************



void calculate_time(){

	// Time variables
	int start_hours, start_minutes, end_hours, end_minutes;
	bool stay_in_loop = true;

	enter_timeCard(start_hours, start_minutes, end_hours, end_minutes);

	
	int total_hours = calculate_hours(start_hours, end_hours);
	float total_minutes = calculate_min(start_minutes, end_minutes, total_hours );


	printResults(total_hours, total_minutes);


}


void start_app(){

	cout << endl;
	cout << "HourCalc 2013" << endl;
	cout << "_____________" << endl << endl;

	cout << "This app will calculate the actual hours an employee has worked." << endl;
	cout << "You will be prompted to enter in the start time and end time as well as whether or not the employee took a lunch break." << endl;
	cout << endl << endl;
	

    cout << "Time format: <HH>:<MM>" << endl;
	
    cout << " HH = hours, 0 .. 12" << endl;
    cout << " MM = minutes, 0 .. 59" << endl << endl;

	cout << "Start time is assumed to be AM (morning) " << endl;
	cout << "and End time is assumed to be PM unless after 7, " << endl;
	cout << "then we assume it is AM." << endl << endl;
}




void printResults(int total_hours, float min){
	float total_minutes = min;

	

	// cout << "TOTAL MINUTES (FINAL STAGE) " << total_minutes << endl;

	if(total_minutes < 0){
		total_hours--;
		total_minutes = 1 - abs(total_minutes);
	}
	else if(total_minutes >= 1){
		total_hours++;
		total_minutes = abs(total_minutes) - 1;
	};

	string minutes = floatFix(total_minutes);

	float temp = ::atof(minutes.c_str());

	cout << endl << endl;
	cout << "--------------------------------------------------" << endl;
	cout << "TOTAL TIME WORKED: ";
	if(temp > 0.00){
		cout << setw(2) << setfill('0') << total_hours << setw(2) << minutes << " Hours." << endl;
	}
	else{
		cout << setw(2) << setfill('0') << total_hours << " Hours." << endl;
	}
	cout << "--------------------------------------------------" << endl << endl;
}

string floatFix(float f) {
	stringstream oss;
	oss << f;
	string str = oss.str();
	if(str.length() > 2)
		if(str.substr(0, 2) == (string) "0.")
			str = str.substr(1, str.length() - 1);
	return str;
}








void enter_timeCard(int &start_hours, int &start_minutes, int &end_hours, int &end_minutes){
	cout << "Start Time - ";
    getTime(start_hours, start_minutes);

    cout << setw(2) << setfill('0') << start_hours << ':' << setw(2) << setfill('0') << start_minutes << endl << endl;


	cout << "End Time - ";
	getTime(end_hours, end_minutes);

	if(end_hours <= 7){
		end_hours = end_hours + 12;
	};
	

	cout << setw(2) << setfill('0') << end_hours << ':' << setw(2) << setfill('0') << end_minutes << endl << endl;
}




int calculate_hours(int start, int end){

	int total_hours = end - start;
 	return total_hours;
}



float calculate_min(int start, int end, int &hours){

	float total_minutes = 0.00;
	

	int start_min = start;
	int end_min = end;

	const float quarter = 0.25;
	const float half = 0.50;
	const float three_quarters = 0.75;

	float start_adjustment = 0;
	float end_adjustment = 0;

	
	// FIND DIFFERENCE FROM THE HOUR to we can get fractional hour adjustment value.
	start_min = 60 - start_min;


	//  Hour adjustment for START TIME
	//  As long as the start minutes are within the hour boundaries enter this loop
	if(start_min > 0 && start_min < 60){

		// Between 10 and 20 minutes give you 0.25 hours
		if(start_min >= 10 && start_min <=20){
			start_adjustment = quarter;
			hours--;
			}

		// Between 21 and 35 minutes give you 0.5 hours
		else if(start_min > 20 &&  start_min <=35){
			start_adjustment = half;
			hours--;
			}

		// Between 36 and 50 minutes give you 0.75 hours
		else if(start_min > 35 && start_min <=50){
			start_adjustment = three_quarters;
			hours--;
			}

		// Anything below 10 minutes from the hour gets you 0 hours
		else{
			start_adjustment = 0;
			if(start < 10){//do not decrement hours
				}
			else{
				hours--;
				}
			};
		}
	//  END Hour Adjustment for START TIME
	



	//  Hour adjustment for END TIME
	//  As long as the end minutes are within the hour boundaries enter this loop
	if(end_min > 0 && end_min < 60){

		// Between 10 and 20 minutes give you 0.25 hours
		if(end_min >= 10 && end_min <=20){
			end_adjustment = quarter;
			}

		// Between 21 and 35 minutes give you 0.5 hours
		else if(end_min > 20 &&  end_min <=35){
			end_adjustment = half;
			}

		// Between 36 and 50 minutes give you 0.75 hours
		else if(end_min > 35 && end_min <=50){
			end_adjustment = three_quarters;
			}

		// Anything below 10 minutes from the hour gets you 0 hours
		else if(end_min > 50){
			end_adjustment = 1;
			}
		else{
			end_adjustment = 0;
		}
	}
	//  END Hour Adjustment for END TIME

	

	// cout << "start adjustment: " << start_adjustment << endl;
	// cout << "end adjustment: " << end_adjustment << endl;


	// TOTAL HOUR ADJUSTMENT BASED ON ADJUSTMENT TABLE
	// Add START and END
	float hour_adjustment = 0.00;
	hour_adjustment = end_adjustment + start_adjustment;


	// cout << "total hours (pre-tooklunch): " << total_minutes << endl;


	// CHECK IF EMPLOYEE TOOK A LUNCH BREAK:
	float lunch = 0.00;
	lunch = tookLunch();
	
	total_minutes = hour_adjustment + lunch;

	// cout << "total minutes (post-tooklunch): " << total_minutes << endl;

	

	//  RETURNS TOTAL ADJUSTED MINUTES VALUE IN A FRACTION OF AN HOUR
	//  MINUS THE LUNCH BREAK IF TAKEN.
	return total_minutes;
}

float tookLunch(){
	
	char lunch;
	cout << "Did the employee take a lunch break? (y or n) ";
	cin >> lunch;
	float minutes = 0;

	// if employee took a lunch subtrack a half-hour from time.
	if(lunch == 'y' || lunch == 'Y'){
		minutes = minutes - .50;
		}

	// cout << "minutes post-lunch " << minutes << endl;

	return minutes;
}


void getTime(int &h, int &m) {



    string in;
    char c;
    stringstream ss;

    do {
        cout << "(HH:MM) : ";
        getline(cin,in);
		
        ss.clear(); ss.str(in);

    } while ( !(ss >> h >> c >> m) || ss.good() || (c != delim) || (isValidTime(h, m) == false) );


}





bool isValidTime(int h, int m) {
    return (h >= 0) && (h < hoursPerDay) && (m >= 0) && (m < minutesPerHour);
}

