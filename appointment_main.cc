/**
 *   @file: appointment_main.cc
 * @author: Jansen Craft
 *   @date: Nov 19, 2021
 *  @brief: This program manages a single day's agenda.
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <vector>
#include "appointment.h"
using namespace std;

/**
    *  Function:   inputData
    *              takes strings from the userfile and turns them into appointment objects
    *
    *  @param inFile - stream for taking in strings to make into objects
    *  @param meetings - vector of appointment class objects containing all day appointments
    *  @param inputStrings - vector of input strings from the user that contain valuable information to make the appointment objects
    */
void inputData(ifstream& inFile, vector <Appointment> &meetings, vector <string> &inputStrings);
/**
    *  Function:   outputData
    *              pushes corrected strings from the user back to the file
    *
    *  @param outFile - stream for sending strings to the output file
    *  @param meetings - vector of appointment class objects containing all day appointments
    *  @param inputStrings - vector of input strings from the user that contain valuable information to make the appointment objects
    */
void outputData(ofstream& outFile, vector <Appointment> meetings, vector <string> inputStrings);
/**
    *  Function:   delApptTime
    *              Deletes all appointments at the specified time
    *
    *  @param timeString - string containing the time in military format
    *  @param meetings - vector of appointment class objects containing all day appointments
    *  @param inputStrings - vector of input strings from the user that contain valuable information to make the appointment objects
    */
void delApptTime(string timeString,  vector <Appointment> meetings, vector <string> &inputStrings);
/**
    *  Function:   delApptTitle
    *              Deletes all appointments that match the specified title
    *
    *  @param timeString - string containing the time in military format
    *  @param meetings - vector of appointment class objects containing all day appointments
    *  @param inputStrings - vector of input strings from the user that contain valuable information to make the appointment objects
    */
void delApptTitle(string trashTitle,  vector <Appointment> meetings, vector <string> &inputStrings);
/**
    *  Function:   addAppointment
    *              Attempts to use user string to make an appointment object
    *
    *  @param appData - string for potential new appointment object
    *  @param inputStrings - vector of input strings from the user that contain valuable information to make the appointment objects
    */
void addAppointment(string appData, vector <string> &inputStrings);
/**
    *  Function:   commonTimes
    *              Prints out meetings that have the same time as passed
    *
    *  @param time - integer military time for checking against appointment times
    *  @param meetings - vector of appointment class objects containing all day appointments
    */
void commonTimes(vector <Appointment> &meetings, int time);
/**
    *  Function:   indexOfMin
    *              Sends back the index of teh smallest number in the vector
    *
    *  @param times - vector containing all meeting times
    *  @param start - integer showing index of where search should start
    *  @param end - integer showing index of where search should end
    *  @return - Index showing where the smallest number in the vector is
    */
int indexOfMin(vector <int> times, int start, int end);
/**
    *  Function:   sortMeetings
    *              sorts the order of the meetings from earliest to latest
    *
    *  @param meetings - vector of appointment class objects containing all day appointments
    */
void sortMeetings(vector <Appointment> &meetings);
/**
    *  Function:   cleanString
    *              removes tabs and extra spaces from the file for easier visibility
    *
    *  @param old - unprocessed string for changing
    */
string cleanString(string old);

int main(int argc, char const *argv[]) {
    vector <string> inputStrings;
    vector <Appointment> meetings;
    ifstream inFile;
    ofstream outFile;
    string secondArgv;
    string thirdArgv;

    if(argc == 2 || argc == 3){
        secondArgv = argv[1];
        if(argc == 2){
            if(secondArgv == "-ps"){
                //Input Data
                inputData(inFile, meetings, inputStrings);
                if(meetings.size() != 0){
                    cout << "Valid" << endl;
                    //Option Function
                    sortMeetings(meetings);
                } else {
                    cout << "Error: File is empty" << endl;
                }

                //Print my daily schedule in order by starting time using standard time format
                //The Appointments must be displayed in a table format with proper labels
            } else{
                cout << "Error: Invalid Option" << endl;
            }
        } else if(argc == 3){
            thirdArgv = argv[2];
            if(secondArgv == "-p"){
                //Input Data
                inputData(inFile, meetings, inputStrings);
                if(meetings.size() != 0){
                    //Option Function
                    commonTimes(meetings, stol(thirdArgv));
                } else {
                    cout << "Error: File is empty" << endl;
                }
                /* "time" print all appointments at specified military time
                */
            } else if(secondArgv == "-a"){
                //Input Data
                inputData(inFile, meetings, inputStrings);
                if(meetings.size() != 0){
                    //Option Function
                    addAppointment(thirdArgv, inputStrings);
                    //Output Data
                    outputData(outFile, meetings, inputStrings);    
                } else {
                    cout << "Error: File is empty" << endl;
                }
                /* "appointment data"
                Time is given in standard time and duration is given in minutes
                leading and Trailing spaces must be removed.
                */
            } else if(secondArgv == "-dt"){
                //Input Data
                inputData(inFile, meetings, inputStrings);
                if(meetings.size() != 0){
                    //Option Function
                    delApptTitle(thirdArgv, meetings, inputStrings);
                    //Output Data
                    outputData(outFile, meetings, inputStrings); 
                } else {
                    cout << "Error: File is empty" << endl;
                }
                /* "title"
                delete all appointments that match the title exactly. It Should
                work for both upper and lowercase characters with leading and trailing
                */
            } else if(secondArgv == "-dm"){
                //TODO
                //Input Data
                inputData(inFile, meetings, inputStrings);
                if(meetings.size() != 0){
                    //Option Function
                    delApptTime(thirdArgv, meetings, inputStrings);
                    //Output Data
                    outputData(outFile, meetings, inputStrings);
                } else {
                    cout << "Error: File is empty" << endl;
                }
                /* "time"
                Delete all appointments that match the starting military time exactly
                */
            } else {
                cout << "Error: Invalid Option" << endl;
            }
        }
    } else{
        cout << "Error: invalid number of arguments" << endl;
    }

    return 0;
}// main

void inputData(ifstream& inFile, vector <Appointment> &meetings, vector <string> &inputStrings){
    string curLine;
    bool isBar = 0;
    inFile.open("agenda.txt");
    while(getline(inFile, curLine)){
        isBar = 0;
        for (size_t i = 0; i < curLine.length(); i++){
            if(curLine.at(i) == '|'){
                isBar = 1;
            }
        }
        if(isBar == 1){
            curLine = cleanString(curLine);
            inputStrings.push_back(curLine);
            Appointment newApt(curLine);
            meetings.push_back(newApt);
        }
    }
    inFile.close();
    return;
}

void outputData(ofstream& outFile, vector <Appointment> meetings, vector <string> inputStrings){
    outFile.open("agenda.txt");
    for (size_t i = 0; i < inputStrings.size(); i++){
        outFile << inputStrings.at(i);
        outFile << endl;
    }
    outFile.close();
}

void delApptTime(string timeString,  vector <Appointment> meetings, vector <string> &inputStrings){
    int targetTime = stol(timeString);
    int numDeleted = 0;
    for (size_t i = 0; i < meetings.size(); i++){
        if(meetings.at(i).getTime() == targetTime){
            inputStrings.erase(inputStrings.begin()+i-numDeleted); //TODO ERROR HERE 
            numDeleted++;
        }
    }
}

void delApptTitle(string trashTitle,  vector <Appointment> meetings, vector <string> &inputStrings){
    int numDeleted = 0;
    string dummy = "";
    trashTitle = cleanString(trashTitle);
    for (size_t i = 0; i < trashTitle.length(); i++){
        if((trashTitle.at(i) >= 'A' && trashTitle.at(i) <= 'Z') || (trashTitle.at(i) >= 'a' && trashTitle.at(i) <= 'z')){
            trashTitle.at(i) = toupper(trashTitle.at(i));
        } 
    }
    for (size_t i = 0; i < meetings.size(); i++){
        for (size_t j = 0; j < meetings.at(i).getTitle().length(); j++){
            dummy += toupper(meetings.at(i).getTitle().at(j));
        }
        if(dummy == trashTitle){
            inputStrings.erase(inputStrings.begin() + i - numDeleted);
            numDeleted++;
        }
        dummy = "";
    }
}

void addAppointment(string appData, vector <string> &inputStrings){
    appData = cleanString(appData);
        if(appData.length() != 0){
            inputStrings.push_back(appData);
        }
}

void commonTimes(vector <Appointment> &meetings, int time){
    int numMeetings = 0;
    cout << "--------------------------------------------------------------------------------"<< endl;
    cout << setw(47)<< "Meetings at "<< time << endl;
    cout << "--------------------------------------------------------------------------------"<< endl;
    cout << setw(35) << left << "Title" << setw(10) << "Year";
    cout << setw(10) << "Month" << setw(10) << "Day";
    cout << setw(10) << "Time" << setw(10) << "Duration(Mins)" << endl;
    cout << "--------------------------------------------------------------------------------"<< endl;
    
    for (size_t i = 0; i < meetings.size(); i++){
        if(meetings.at(i).getTime() == time){
            numMeetings++;
            cout << setw(35) << left << meetings.at(i).getTitle() << setw(10) << meetings.at(i).getYear();
            cout << setw(10) << meetings.at(i).getMonth() << setw(10) << meetings.at(i).getDay();
            cout << setw(10) << meetings.at(i).getStandardTime() << setw(10) << meetings.at(i).getDuration() << endl;
        }
    }
    if(numMeetings == 0){
        cout << "Error: There are no meetings at the specified time" << endl;
    }
}

string cleanString(string old){
    string cleanString = "";

    for (size_t i = 0; i < old.length(); i++){
        if(old.at(i) != '\t'){
            if(i == 0 || i == (old.length() - 1)){
            if(old.at(i) != ' '){
                cleanString = cleanString + old.at(i);
            }
        } else {
            if(old.at(i) == ' '){
                if((old.at(i - 1) != ' ') && (old.at(i + 1) != ' ') && (old.at(i - 1) != '|') && (old.at(i + 1) != '|')){
                    cleanString = cleanString + old.at(i);
                }
            }else{
                cleanString = cleanString + old.at(i);
            }
        }
        }        
    }
    return cleanString;
}

void sortMeetings(vector <Appointment> &meetings){
    vector <int> times;
    //load time vector
    for (size_t i = 0; i < meetings.size(); i++){
        times.push_back(meetings.at(i).getTime());
    }
    int minIndex;
    for (size_t i = 0; i < times.size() - 1; i++){
        minIndex = indexOfMin(times, i, times.size());
        swap(meetings.at(i), meetings.at(minIndex));
        swap(times.at(i), times.at(minIndex));
    }
    cout << "--------------------------------------------------------------------------------"<< endl;
    cout << setw(47)<< "Daily Schedule"<< endl;
    cout << "--------------------------------------------------------------------------------"<< endl;
    cout << setw(35) << left << "Title" << setw(10) << "Year";
    cout << setw(10) << "Month" << setw(10) << "Day";
    cout << setw(10) << "Time" << setw(10) << "Duration(Mins)" << endl;
    cout << "--------------------------------------------------------------------------------"<< endl;
    
    for (size_t i = 0; i < meetings.size(); i++){
        cout << setw(35) << left << meetings.at(i).getTitle() << setw(10) << meetings.at(i).getYear();
        cout << setw(10) << meetings.at(i).getMonth() << setw(10) << meetings.at(i).getDay();
        cout << setw(10) << meetings.at(i).getStandardTime() << setw(10) << meetings.at(i).getDuration() << endl;
    }
}

int indexOfMin(vector <int> times, int start, int end){
    int min = times.at(start);
    int minIndex = start;
    for (int i = start; i < end; i++){
        if (times.at(i) < min){
            min = times.at(i);
            minIndex = i;
        }
    }
    return minIndex;
}

//mingw32-make