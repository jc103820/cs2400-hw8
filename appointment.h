
using namespace std;
class Appointment{
public:
    //Constructors
    /**
    *  Function:   Appointment
    *              Default constructor setting the default values of 
    title = "N/A";
    year = 1;
    month = 1;
    day = 1;
    time = 0; //Military
    duration = 1;    
    */
    Appointment();
    /**
    *  Function:   Appointment
    *              Constructor that uses user data to setup an appointment object  
    * @param appData - user string for setting up an appointment
    */
    Appointment(string appData);

    //Getters
    string getTitle();
    /**
    *  Function:   getYear
    *              returns the year of the meeting
    *  @return - the year of the meeting
    */
    int getYear();
    /**
    *  Function:   getMonth
    *              returns the month of the meeting
    *  @return - the month of the meeting
    */
    int getMonth();
    /**
    *  Function:   getDay
    *              returns the day of the meeting
    *  @return - the day of the meeting
    */
    int getDay();
    /**
    *  Function:   getTime
    *              returns the time of the meeting in military format
    *  @return - the time of the meeting in military format
    */
    int getTime();
    /**
    *  Function:   getDuration
    *              returns the duration of the meeting
    *  @return - the duration of the meeting
    */
    int getDuration();
    /**
    *  Function:   getDate
    *              returns the date in format 2021-11-23
    *  @return - date in format 2021-11-23
    */
    string getDate();
    /**
    *  Function:   getStandardTime
    *              returns the time in standard format
    *  @return - time in standard format
    */
    string getStandardTime();

    //Setters
    /**
    *  Function:   setTitle
    *              Attempts to set the title of the object to the passed value
    *  @param newTitle - potential new title value
    */
    void setTitle(string newTitle);
    /**
    *  Function:   setYear
    *              Attempts to set the year of the object to the passed value
    *  @param newYear - potential new year value
    */
    void setYear(int newYear);
    /**
    *  Function:   setMonth
    *              Attempts to set the month of the object to the passed value
    *  @param newMonth - potential new month value
    */
    void setMonth(int newMonth);
    /**
    *  Function:   setDay
    *              Attempts to set the Day of the object to the passed value
    *  @param newDay - potential new day value
    */
    void setDay(int newDay);
    /**
    *  Function:   setTime
    *              Attempts to set the time of the object to the passed value
    *  @param newTime - potential new time value
    */
    void setTime(int newTime); //Military
    /**
    *  Function:   setDuration
    *              Attempts to set the duration of the object to the passed value
    *  @param newDuration - potential new duration value
    */
    void setDuration(int newDuration);
    /**
    *  Function:   setDate
    *              Attempts to set the day month and year of the object to  the passed values
    *  @param newYear - potential new year value
    *  @param newMonth - potential new Month value
    *  @param newDay - potential new day value
    */
    void setDate(int newYear, int newMonth, int newDay);

    //Helper Functions
    /**
    *  Function:   militaryToStandard
    *              Converts time from military(1830) to standard time ("6:30PM")
    *  @param time - integer time in military format
    *  @return - string time in standard format
    */
    string militaryToStandard(int time);
    /**
    *  Function:   standardToMilitary
    *              Converts standard time ("8:30PM") to military time(2030) handles upper and lowercase
    *
    *  @param time - string time in standard format
    *  @return - integer time in military format
    */
    int standardToMilitary(string time);
     /**
    *  Function:   output
    *              Prints out the values stored in the class
    */
    void output();
    /**
    *  Function:   leadingAndTrailing
    *              gets rid of all leading and trailing spaces in a string
    *
    *  @param old - string containign leading and trailing spaces
    *  @return - string with no leading or trailing spaces
    */
    string leadingAndTrailing(string old);
    /**
    *  Function:   operator==
    *              == operator overload that compares the data between two objects of the appointment class
    *
    *  @param first - first appointment class object to be compared
    *  @param second - second appointment class object to be compared
    *  @return - true if all values are equal and false if not
    */
    friend bool operator==(const Appointment &first, const Appointment &second);

private:
    //Member Variables
    string title;
    int year;
    int month;
    int day;
    int time; //Military
    int duration;

};