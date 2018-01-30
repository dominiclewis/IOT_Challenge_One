#ifndef __YOTTA_BUILD_INFO_H__
#define __YOTTA_BUILD_INFO_H__
// yotta build info, #include YOTTA_BUILD_INFO_HEADER to access
#define YOTTA_BUILD_YEAR 2018 // UTC year
#define YOTTA_BUILD_MONTH 1 // UTC month 1-12
#define YOTTA_BUILD_DAY 30 // UTC day 1-31
#define YOTTA_BUILD_HOUR 22 // UTC hour 0-24
#define YOTTA_BUILD_MINUTE 4 // UTC minute 0-59
#define YOTTA_BUILD_SECOND 2 // UTC second 0-61
#define YOTTA_BUILD_UUID c1071e67-9e7b-49df-abbe-b523400ab64a // unique random UUID for each build
#define YOTTA_BUILD_VCS_ID b1ad284568455b786d66d0a220cc9ef07a59b868 // git or mercurial hash
#define YOTTA_BUILD_VCS_CLEAN 0 // evaluates true if the version control system was clean, otherwise false
#define YOTTA_BUILD_VCS_DESCRIPTION b1ad284 // git describe or mercurial equivalent
#endif // ndef __YOTTA_BUILD_INFO_H__
