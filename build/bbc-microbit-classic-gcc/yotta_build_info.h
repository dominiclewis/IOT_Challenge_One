#ifndef __YOTTA_BUILD_INFO_H__
#define __YOTTA_BUILD_INFO_H__
// yotta build info, #include YOTTA_BUILD_INFO_HEADER to access
#define YOTTA_BUILD_YEAR 2018 // UTC year
#define YOTTA_BUILD_MONTH 1 // UTC month 1-12
#define YOTTA_BUILD_DAY 31 // UTC day 1-31
#define YOTTA_BUILD_HOUR 13 // UTC hour 0-24
#define YOTTA_BUILD_MINUTE 30 // UTC minute 0-59
#define YOTTA_BUILD_SECOND 37 // UTC second 0-61
#define YOTTA_BUILD_UUID c4c55047-43ee-44e3-997d-4d7f196bb720 // unique random UUID for each build
#define YOTTA_BUILD_VCS_ID 5109bd9b366c07f3f149942b6b9d0d49cbab4e16 // git or mercurial hash
#define YOTTA_BUILD_VCS_CLEAN 0 // evaluates true if the version control system was clean, otherwise false
#define YOTTA_BUILD_VCS_DESCRIPTION 5109bd9 // git describe or mercurial equivalent
#endif // ndef __YOTTA_BUILD_INFO_H__
