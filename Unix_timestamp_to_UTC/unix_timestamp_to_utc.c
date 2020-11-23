#include "unix_timestamp_to_utc.h"
/*********************************************************************
 * MACROS
 */
#define YearLength(year)			(IsLeapYear(year) ? 366 : 365)
#define	IsLeapYear(year)			(!((year) % 400) || (((year) % 100) && !((year) % 4)))

#define USE_CHINA_STD_TIME
#ifdef  USE_CHINA_STD_TIME
#define TIME_STAMP_DEFAULT 		(1546272000UL) 	//China standard time 2019-01-01 00:00:00
#else
#define TIME_STAMP_DEFAULT 		(1546300800UL) 	//GTM 2019-01-01 00:00:00
#endif

#define	BEGIN_YEAR	        	2019     // UTC started at 00:00:00 January 1, 2000

#define	DAY             		86400UL  // 24 hours * 60 minutes * 60 seconds

static SysTime_T System_time = {0};

/*********************************************************************
 * @fn      monthLength
 *
 * @param   lpyr - 1 for leap year, 0 if not
 *
 * @param   mon - 0 - 11 (jan - dec)
 *
 * @return  number of days in specified month
 */
static uint8_t monthLength( uint8_t lpyr, uint8_t mon)
{
	uint8_t days = 31;

	if ( mon == 1 ) // feb
	{
		days = ( 28 + lpyr );
	}
	else
	{
		if ( mon > 6 ) // aug-dec
		{
			mon--;
		}

		if ( mon & 1 )
		{
			days = 30;
		}
	}
	return ( days );
}


/*********************************************************************
 * @fn      ConvertUTCTime
 *
 * @brief   Converts UTCTime to system_time
 *
 * @param   secTime - number of seconds since 0 hrs, 0 minutes,
 *          0 seconds, on the 1st of January 2000 UTC
 *
 * @return  none
 */
void ConvertUTCTime(UTCtime secTime)
{ 
	System_time.utc_time = secTime;
	secTime -= TIME_STAMP_DEFAULT;
	// calculate the time less than a day - hours, minutes, seconds
	{
		uint32_t day = secTime % DAY;
		System_time.second 	= day % 60UL;
		System_time.minute 	= (day % 3600UL) / 60UL;
		System_time.hour 	= day / 3600UL;
	}
	
	// Fill in the calendar - day, month, year
	{
		uint16_t numDays = secTime / DAY;
		System_time.year = BEGIN_YEAR;
		while(numDays >= YearLength(System_time.year))
		{
			numDays -= YearLength(System_time.year);
			System_time.year++;
		}

		System_time.month = 0;
		while ( numDays >= monthLength( IsLeapYear(System_time.year), System_time.month))
		{
			numDays -= monthLength(IsLeapYear( System_time.year), System_time.month);
			System_time.month++;
		}
		System_time.month++;
		System_time.day = numDays + 1;
	}
	
	printf("Time %d-%d-%d %02d:%02d:%02d \r\n", System_time.year,
                                                System_time.month,
										        System_time.day,
										        System_time.hour,
										        System_time.minute,
										        System_time.second);
}