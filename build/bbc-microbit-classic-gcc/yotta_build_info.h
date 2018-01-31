#ifndef __YOTTA_BUILD_INFO_H__
#define __YOTTA_BUILD_INFO_H__
// yotta build info, #include YOTTA_BUILD_INFO_HEADER to access
#define YOTTA_BUILD_YEAR 2018 // UTC year
#define YOTTA_BUILD_MONTH 1 // UTC month 1-12
#define YOTTA_BUILD_DAY 31 // UTC day 1-31
#define YOTTA_BUILD_HOUR 23 // UTC hour 0-24
#define YOTTA_BUILD_MINUTE 36 // UTC minute 0-59
#define YOTTA_BUILD_SECOND 1 // UTC second 0-61
#define YOTTA_BUILD_UUID fc56291e-ffe6-4fbc-9918-d8f039c094fa // unique random UUID for each build
#define YOTTA_BUILD_VCS_ID a8861a48d7acf8b76e6fc872e9fc24a68130e20d // git or mercurial hash
#define YOTTA_BUILD_VCS_CLEAN 0 // evaluates true if the version control system was clean, otherwise false
#define YOTTA_BUILD_VCS_DESCRIPTION a8861a4 // git describe or mercurial equivalent
#endif // ndef __YOTTA_BUILD_INFO_H__
