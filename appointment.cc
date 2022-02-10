#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "appointment.h"
using namespace std;


//Add class functions here

//CONSTRUCTORS

Appointment::Appointment(){
    title = "N/A";
    year = 1;
    month = 1;
    day = 1;
    time = 0; //Military
    duration = 1;
}

Appointment::Appointment(string appData){
    title = "N/A";
    year = 1;
    month = 1;
    day = 1;
    time = 0; //Military
    duration = 1;
    
    int potYear;
    int potMonth;
    int potDay;
    int potDur;
    string potStandardTime;
    int potTime;
    size_t breakPos[5];

    string appDataClean = leadingAndTrailing(appData);

    //Find breaks
    for (size_t i = 0; i < 5; i++){
        if(i == 0){
            breakPos[i] = appDataClean.find("|", 0);
        } else{
            breakPos[i] = appDataClean.find("|", breakPos[i - 1] + 1);
        }
    }
    
    //TITLE
    if(appDataClean.substr(0, breakPos[0]) != ""){
        title = appDataClean.substr(0, breakPos[0]);
    }

    //YEAR
    potYear = stol(appDataClean.substr(breakPos[0]+1, (breakPos[1]-breakPos[0]-1)));
    if(potYear >= 0){
        year = potYear;
    }
    
    //MONTH
    potMonth = stol(appDataClean.substr(breakPos[1]+1, (breakPos[2]-breakPos[1]-1)));
    if(potMonth >= 1 && potMonth <= 12){
        month = potMonth;
    }

    //DAY
    potDay = stol(appDataClean.substr(breakPos[2]+1, (breakPos[3]-breakPos[2]-1)));
    if(potDay >= 1 && potDay <= 31){
        day = potDay;
    }

    //TIME
    potTime = standardToMilitary(appDataClean.substr(breakPos[3]+1, (breakPos[4]-breakPos[3]-1)));

    if(potTime >= 0 && potTime < 2400){
        if((potTime % 100) <= 59){
            time = potTime;
        }
    } else if(potTime == 2400){
        time = 0;
    }

    //DURATION
    potDur = stol(appDataClean.substr(breakPos[4]+1, (appDataClean.length()-breakPos[4]-1)));
    if(potDur >= 0){
        duration = potDur;
    }
}



//GETTERS

string Appointment::getTitle(){
    return title;
}

int Appointment::getYear(){
    return year;
}

int Appointment::getMonth(){
    return month;
}

int Appointment::getDay(){
    return day;
}

int Appointment::getTime(){
    return time;
} //Military

int Appointment::getDuration(){
    return duration;
}

string Appointment::getDate(){
    string extraZeroM = "";
    string extraZeroD = "";
    string date = to_string(year) + "-";
    if(month < 10){
        extraZeroM = "0";
    }
    date = date + extraZeroM + to_string(month) + "-";
    if(day < 10){
        extraZeroD = "0";
    }
    date = date + extraZeroD + to_string(day);
    return date;
} // Date in format 2021-11-23

string Appointment::getStandardTime(){
    return militaryToStandard(time);
}



//SETTERS

void Appointment::setTitle(string newTitle){
    if(newTitle != ""){
        title = newTitle;
    }
}

void Appointment::setYear(int newYear){
    if(newYear >= 0){
        year = newYear;
    }
}

void Appointment::setMonth(int newMonth){
    if(newMonth >= 1 && newMonth <= 12){
        month = newMonth;
    }
}

void Appointment::setDay(int newDay){
    if(newDay >= 1 && newDay <= 31){
        day = newDay;
    }
}

void Appointment::setTime(int newTime){
    if(newTime >= 0 && newTime < 2400){
        if((newTime % 100) <= 59){
            time = newTime;
        }
    } else if(newTime == 2400){
        time = 0;
    }
} //Military

void Appointment::setDuration(int newDuration){
    if(newDuration >= 0){
        duration = newDuration;
    }
}

void Appointment::setDate(int newYear, int newMonth, int newDay){
    setYear(newYear);
    setMonth(newMonth);
    setDay(newDay);
}



//HELPER FUNCTIONS

string Appointment::militaryToStandard(int time){
    string stdTime = "";
    string hrs;
    string extraZero = "";
    int hrz;
    string mins;
    int minz;
    string amOrPm;
    if(time < 1200){
        hrz = time / 100;
        if(hrz == 0){
            hrz = 12;
        }
        hrs = to_string(hrz);
        minz = time % 100;
        if(minz >= 0 && minz <= 9){
            extraZero = "0";
        }
        mins = to_string(minz);
        amOrPm = "AM";
        
    } else if(time >= 1200){
        hrz = (time / 100) - 12;
        if(hrz == 0){
            hrz = 12;
        }
        hrs = to_string(hrz);
        minz = time % 100;
        if(minz >= 0 && minz <= 9){
            extraZero = "0";
        }
        mins = to_string(minz);
        amOrPm = "PM";
    }
    stdTime = hrs + ":" + extraZero + mins + amOrPm;
    return stdTime;
} //Converts time from military(1830) to standard time ("6:30PM")

int Appointment::standardToMilitary(string time){
    int newTime = -1;
    string noSTime = "";
    int numTime;
    char ch;
    bool isAM = 1;
    
    int len = time.length();

    //search for am or pm
    if(len >= 6){
        if(time.at(len - 2) == 'a' || time.at(len - 2) == 'A'){
            isAM = 1;
        } else if(time.at(len - 2) == 'p' || time.at(len - 2) == 'P'){
            isAM = 0;
        }
        //Keeps Only numbers
        for (int i = 0; i < len; i++){
            ch = time.at(i);
            if(ch >= '0' && ch <= '9'){
                noSTime += ch;
            }
        }
        numTime = stol(noSTime);
        //Valid or no?
        if(numTime >= 0 && numTime < 1300){
            if(isAM){
                //if 12 make 0
                if((numTime / 100) == 12){
                    numTime -= 1200;
                }
                newTime = numTime;
            } else{
                if((numTime / 100) == 12){
                    numTime -= 1200;
                }
                newTime = numTime + 1200;
            }
        }
    }
    return newTime;
} //Converts standard time ("8:30PM") to military time(2030) handles upper and lowercase

void Appointment::output(){
    cout << left << setw(11) << "Title " << title << endl;
    cout << left << setw(11) << "Year " << year << endl;
    cout << left << setw(11) << "Month " << month << endl;
    cout << left << setw(11) << "Day " << day << endl;
    cout << left << setw(11) << "Time " << time << endl;
    cout << left << setw(11) << "Duration " << duration << endl;
    return;
}

string Appointment::leadingAndTrailing(string old){
    string noSpaces = "";

    for (size_t i = 0; i < old.length(); i++){
        if(old.at(i) != '\t'){
            if(i == 0 || i == (old.length() - 1)){
            if(old.at(i) != ' '){
                noSpaces = noSpaces + old.at(i);
            }
        } else {
            if(old.at(i) == ' '){
                if((old.at(i - 1) != ' ') && (old.at(i + 1) != ' ') && (old.at(i - 1) != '|') && (old.at(i + 1) != '|')){
                    noSpaces = noSpaces + old.at(i);
                }
            }else{
                noSpaces = noSpaces + old.at(i);
            }
        }
        }        
    }
    return noSpaces;
}

bool operator==(const Appointment &first, const Appointment &second){
    bool isEqual = 0;
    int numEqual = 0;
    if(first.title == second.title){
        numEqual++;
    }
    if(first.year == second.year){
        numEqual++;
    }
    if(first.month == second.month){
        numEqual++;
    }
    if(first.day == second.day){
        numEqual++;
    }
    if(first.time == second.time){
        numEqual++;
    }
    if(first.duration == second.duration){
        numEqual++;
    }
    if(numEqual == 6){
        isEqual = 1;
    }
    return isEqual;
}