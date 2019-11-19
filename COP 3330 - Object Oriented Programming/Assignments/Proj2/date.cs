using System.Linq;
using System;

class Date{
    //CONSTANTS
    public static readonly int[] shortMonth = {4, 6, 9, 11};
    public static readonly int[] longMonth = {1, 3, 5, 7, 8, 10, 12};

    //VARIABLES
    private int month;
    private int day;
    private int year;
    public Date(int m = 1, int d = 1, int y = 2019){
        bool valid = ValidDate(m, d, y);
        if(valid != false){
            month = m;
            day = d;
            year = y;
        } else{
            month = 1;
            day = 1;
            year = 2019;
        }
    }

    public bool ValidDate(int m, int d, int y){
        bool valid = true;
        if(year < 1900)
            valid = false;
        if(month < 1 || month > 12)
            valid = false;
        if(day < 1)
            valid = false;
        if(month == 2 && day > 29)
            valid = false;
        if(month == 2 && year % 4 != 0 && day > 28)
            valid = false;
        foreach(int item in shortMonth)
            if(month == m && day > 30)
                valid = false;
        foreach(int item in longMonth)
            if(month == m && day > 31)
                valid = false;
        return valid;
    }

    public void Input(){
        Console.Write("Input date in month/day/year format: ");
        string input = Console.ReadLine();
        string[] date = input.Split('/');
        while(date.Length != 3 || ValidDate(Convert.ToInt32(date[0]), Convert.ToInt32(date[1]), Convert.ToInt32(date[2])) == false){
            Console.Write("Invalid date. Try again:");
            input = Console.ReadLine();
            date = input.Split('/');
        }
        month = Convert.ToInt32(date[0]);
        day = Convert.ToInt32(date[1]);
        year = Convert.ToInt32(date[2]);
        return;
    }

    //ACCESSORS
    public int GetMonth(){
        return month;
    }

    public int GetDay(){
        return day;
    }

    public int GetYear(){
        return year;
    }

    bool Set(int m, int d, int y){
        int m1 = month;
        int d1 = day;
        int y1 = year;
        if(ValidDate(m, d, y) != false){
            month = m;
            day = d;
            year = y;
            return true;
        }

        return false;
    }

    public void Increment(){
        bool short_month = false;
        foreach(int m in shortMonth)
            if(month == m){
                short_month = true;
                break;
            }
        if((month == 2 && day == 29) || (month == 2 && year % 4 != 0 && day == 28)){
            month = 3;
            day = 1;
        } else if(day == 31){
            if(month == 12){
                month = 1;
                day = 1;
                ++year;
            } else {
                ++month;
                day = 1;
            }
        } else if(short_month != false && day == 30){
            ++month;
            day = 1;
        } else {
            ++month;
            ++day;
        }

        return;
    }

    public int Compare(ref Date d){
        int num = 0;
        if(year < d.GetYear())
            num = -1;
        else if(year > d.GetYear())
            num = 1;
        else if(year == d.GetYear()){
            if(month < d.GetMonth())
                num = -1;
            else if(month > d.GetMonth())
                num = 1;
            else if(month == d.GetMonth()){
                if(day < d.GetDay())
                    num = -1;
                else if(day > d.GetDay())
                    num = 1;
                else if(day == d.GetDay())
                    num = 0;
            }
        }
        return num;
    }

    public int DayofWeek(){
        int[] t = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
        int m = month;
        int d = day;
        int y = year;
        y -= Convert.ToInt16(m < 3);
        return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
    }

    public int DayofWeek(int m1, int d1, int y1){
        int[] t = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
        int m = m1;
        int d = d1;
        int y = y1;
        y -= Convert.ToInt16(m < 3);
        return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
    }

    public void ShowByDay(){
        int dow = DayofWeek();
        string dowStr = "";
        switch(dow){
            case 0: {dowStr = "Sunday"; break;}
            case 1: {dowStr = "Monday"; break;}
            case 2: {dowStr = "Tuesday"; break;}
            case 3: {dowStr = "Wednesday"; break;}
            case 4: {dowStr = "Thursday"; break;}
            case 5: {dowStr = "Friday"; break;}
            case 6: {dowStr = "Saturday"; break;}
        }
        Console.WriteLine("{0} {1}/{2}/{3}", dowStr, month, day, year);
        return;
    }

    public void ShowByMonth(){
        int numDays = 0;
        bool short_month = false;
        foreach(int m in shortMonth)
            if(month == m){
                short_month = true;
                break;
            }
        if(month == 2 && year % 4 == 0)
            numDays = 29;
        else if(month == 2)
            numDays = 28;
        else if(short_month != false)
            numDays = 30;
        else
            numDays = 31;
        Console.WriteLine("Su Mo Tu We Th Fr Sa");
        for(int i = 1; i <= DayofWeek(month, 1, year); i++)
            Console.Write("    ");
        for(int i = 1; i <= numDays; i++){
            if(i < 10)
                Console.Write("0{0}  ", i);
            else
                Console.Write("{0}  ", i);
            if(DayofWeek(month, i, year) == 6)
                Console.WriteLine("");
        }

        return;
    }

    public static void Main(string[] args){
        Date d1 = new Date(3, 9, 2000);
        d1.Input();
        d1.ShowByMonth(); 
        Console.ReadKey();
    }
}
