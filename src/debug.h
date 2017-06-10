//
// Created by n0pe on 10.06.2017.
//

#ifndef FILE_DIRECTORY_LISTING_DEBUG_H
#define FILE_DIRECTORY_LISTING_DEBUG_H

#define red     "\033[1;31m"
#define green   "\033[1;32m"
#define yellow  "\033[1;33m"
#define blue    "\033[1;34m"
#define magenta "\033[1;35m"
#define cyan    "\033[1;36m"
#define none    "\033[0m"

/**
 * @brief Program çalışırken bilgi almak için kullanılır.
 *
*/

#define DEBUG_INFO(format, args...)  \
        setbuf(stdout, NULL), \
        fprintf(stdout, "%12s: %3d: %s ", __FILE__, __LINE__, green), \
        fprintf(stdout, format, ##args)

#define DEBUG_ERROR(format, args...)  \
        setbuf(stdout, NULL), \
        fprintf(stdout, "%12s: %3d: %s ", __FILE__, __LINE__, red), \
        fprintf(stdout, format, ##args)





#endif //FILE_DIRECTORY_LISTING_DEBUG_H
