#ifndef __YOTTA_BUILD_INFO_H__
#define __YOTTA_BUILD_INFO_H__
// yotta build info, #include YOTTA_BUILD_INFO_HEADER to access
#define YOTTA_BUILD_YEAR 2018 // UTC year
#define YOTTA_BUILD_MONTH 1 // UTC month 1-12
#define YOTTA_BUILD_DAY 31 // UTC day 1-31
#define YOTTA_BUILD_HOUR 23 // UTC hour 0-24
#define YOTTA_BUILD_MINUTE 5 // UTC minute 0-59
#define YOTTA_BUILD_SECOND 18 // UTC second 0-61
#define YOTTA_BUILD_UUID 999a1dd9-7ab1-4ed2-8adb-787cec313760 // unique random UUID for each build
#define YOTTA_BUILD_VCS_ID d15457e179236e477b19c457be4a5539c51702a7 // git or mercurial hash
#define YOTTA_BUILD_VCS_CLEAN 0 // evaluates true if the version control system was clean, otherwise false
#define YOTTA_BUILD_VCS_DESCRIPTION d15457e // git describe or mercurial equivalent
#endif // ndef __YOTTA_BUILD_INFO_H__
