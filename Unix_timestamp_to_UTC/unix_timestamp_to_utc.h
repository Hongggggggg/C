#ifndef __TO_UTC_H
#define __TO_UTC_H

#include <stdint.h>
/*********************************************************************
 * TYPEDEFS
 */
typedef uint32_t UTCtime;

typedef struct
{
	uint8_t second;     // 0-59
	uint8_t minute;     // 0-59
	uint8_t hour;       // 0-23
	uint8_t day;        // 0-30
	uint8_t month;      // 0-11
	uint16_t year;      // 2019+
	UTCtime utc_time;
}SysTime_T;


/*********************************************************************
 * FUNCTION FOR EXTREN
 */
extern void ConvertUTCTime(UTCtime secTime);

#endif 