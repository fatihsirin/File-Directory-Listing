//
// Created by n0pe on 10.06.2017.
//

#ifndef FILE_DIRECTORY_LISTING_LISTING_HPP
#define FILE_DIRECTORY_LISTING_LISTING_HPP


#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <linux/limits.h>
#include <dirent.h>

class listing {
public:
    listing();
    listing(char *p);
    char *GetCurrentDir();
    void ShowDirContent(char * p);

    int FileInfo(char *p);
    char *path;
    int print=0;
    /*****
     * print 0 ise sadece isimleri listele -< n
     * print 1 ise isim size               -< s
     * print 2 ise isim ve yetkileri       -< p
     * print 3 ise isim size ve yetkiler   -< d
     * print 4 ise zaman bilgileri         -< t
     * print 5 ise tüm bilgiler            -< a
     */
private:
    struct stat sb;
};


#endif //FILE_DIRECTORY_LISTING_LISTING_HPP
