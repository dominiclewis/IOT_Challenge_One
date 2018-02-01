#ifndef __YOTTA_BUILD_INFO_H__
#define __YOTTA_BUILD_INFO_H__
// yotta build info, #include YOTTA_BUILD_INFO_HEADER to access
#define YOTTA_BUILD_YEAR 2018 // UTC year
#define YOTTA_BUILD_MONTH 2 // UTC month 1-12
#define YOTTA_BUILD_DAY 1 // UTC day 1-31
#define YOTTA_BUILD_HOUR 12 // UTC hour 0-24
#define YOTTA_BUILD_MINUTE 57 // UTC minute 0-59
#define YOTTA_BUILD_SECOND 0 // UTC second 0-61
#define YOTTA_BUILD_UUID 921a6376-a4f8-49ca-8a16-9819b9accf49 // unique random UUID for each build
#define YOTTA_BUILD_VCS_ID e6b925a6422bc947194784edd61a941fcfe0e6fb // git or mercurial hash
#define YOTTA_BUILD_VCS_CLEAN 0 // evaluates true if the version control system was clean, otherwise false
#define YOTTA_BUILD_VCS_DESCRIPTION e6b925a // git describe or mercurial equivalent
#endif // ndef __YOTTA_BUILD_INFO_H__
