#ifndef __YOTTA_BUILD_INFO_H__
#define __YOTTA_BUILD_INFO_H__
// yotta build info, #include YOTTA_BUILD_INFO_HEADER to access
#define YOTTA_BUILD_YEAR 2018 // UTC year
#define YOTTA_BUILD_MONTH 2 // UTC month 1-12
#define YOTTA_BUILD_DAY 1 // UTC day 1-31
#define YOTTA_BUILD_HOUR 12 // UTC hour 0-24
#define YOTTA_BUILD_MINUTE 55 // UTC minute 0-59
#define YOTTA_BUILD_SECOND 12 // UTC second 0-61
#define YOTTA_BUILD_UUID 4d8e1289-da10-4e4f-8b2d-920f0f9f0709 // unique random UUID for each build
#define YOTTA_BUILD_VCS_ID 0fbee9a47aaa6403da7d5c14c3328fe753815bb1 // git or mercurial hash
#define YOTTA_BUILD_VCS_CLEAN 0 // evaluates true if the version control system was clean, otherwise false
#define YOTTA_BUILD_VCS_DESCRIPTION 0fbee9a // git describe or mercurial equivalent
#endif // ndef __YOTTA_BUILD_INFO_H__
