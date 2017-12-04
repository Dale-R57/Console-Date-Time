// crt_localtime_s.cpp  
/* This program uses _time64 to get the current time
* and then uses _localtime64_s() to convert this time to a structure
* representing the local time. The program converts the result
* from a 24-hour clock to a 12-hour clock and determines the
* proper extension (AM or PM).
*/

#include <iostream>
#include <time.h>  
using namespace std;


int main(void)
{
	struct tm newtime;
	char am_pm[] = "AM";
	__time64_t long_time;
	char timebuf[26];
	errno_t err;

	char wkday [7][6] = { "Sun ", "Mon ", "Tue ", "Wed ", "Thur ", "Fri ", "Sat " };
	char mths [12][6] = { "Jan ", "Feb ", "Mar ", "Apr ", "May ", "June ", "July ",
							"Aug ", "Sept ", "Oct ", "Nov ", "Dec " };
	int wkdaynum, mthsnum;

	// Get time as 64-bit integer.  
	_time64(&long_time);
	// Convert to local time.  
	err = _localtime64_s(&newtime, &long_time);
	if (err)
	{
		cout << "Invalid argument to _localtime64_s.";
		exit(1);
	}
	if (newtime.tm_hour > 12)        // Set up extension.   
		strcpy_s(am_pm, sizeof(am_pm), "PM");
	if (newtime.tm_hour > 12)        // Convert from 24-hour   
		newtime.tm_hour -= 12;       // to 12-hour clock.   
	if (newtime.tm_hour == 0)        // Set hour to 12 if midnight.  
		newtime.tm_hour = 12;

	wkdaynum = newtime.tm_wday;
	mthsnum = newtime.tm_mon;

	// Print out date & time.
	cout << "Date: " << wkday[wkdaynum] << mths[mthsnum] << newtime.tm_mday
		<< " " << newtime.tm_year + 1900 << "\n\n";

	cout << "Time: " << newtime.tm_hour << ":" << newtime.tm_min << ":" << newtime.tm_sec 
		<< " " << am_pm << "\n\n";

	system("pause");
}
