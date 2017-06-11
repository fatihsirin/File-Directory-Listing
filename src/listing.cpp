//
// Created by n0pe on 10.06.2017.
//

#include "listing.hpp"
#include "debug.h"


#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <stdio.h>
#include <stdint.h>




char *
permOfFile(mode_t mode)
{
    int i;
    char *p;
    static char perms[10];

    p = perms;
    strcpy(perms, "---------");

    /*
     * The permission bits are three sets of three
     * bits: user read/write/exec, group read/write/exec,
     * other read/write/exec.  We deal with each set
     * of three bits in one pass through the loop.
     */
    for (i=0; i < 3; i++) {
        if (mode & (S_IREAD >> i*3))
            *p = 'r';
        p++;

        if (mode & (S_IWRITE >> i*3))
            *p = 'w';
        p++;

        if (mode & (S_IEXEC >> i*3))
            *p = 'x';
        p++;
    }

    /*
     * Put special codes in for set-user-id, set-group-id,
     * and the sticky bit.  (This part is incomplete; "ls"
     * uses some other letters as well for cases such as
     * set-user-id bit without execute bit, and so forth.)
     */
    if ((mode & S_ISUID) != 0)
        perms[2] = 's';

    if ((mode & S_ISGID) != 0)
        perms[5] = 's';

    if ((mode & S_ISVTX) != 0)
        perms[8] = 't';

    return(perms);
}


listing::listing() {
    path=GetCurrentDir();
}

listing::listing(char *p) {

    try{
        path = new char[strlen(p)];
        strncpy(path,p,strlen(p));
    }catch (std::bad_alloc& ba) {
        std::cerr<<"bad_alloc caught: "<< ba.what() << std::endl;
    }
}

listing::~listing() {
    delete path;
}

char *listing::GetCurrentDir(){
    char *cwd= new char[PATH_MAX];
    FILE* output = popen("/bin/pwd", "r");
    fgets(cwd, PATH_MAX, output);
    cwd = strtok(cwd, "\n");
    return cwd;
}

void listing::ShowDirContent(char *p){

    DIR *d = opendir(p);
    if (d==NULL) {
        //verilen string path değil. Dosya testini yap
        DEBUG_ERROR("verilen string path değil dosyadır.\n");

        if(FileInfo(p,basename(p))){
            DEBUG_INFO("başarılı olarak yazılmıştır.\n");
        }

    }
    else{
        char *fullpath;
        try{
            fullpath = new char[PATH_MAX];
        }catch (std::bad_alloc& ba) {
            std::cerr<<"bad_alloc caught: "<< ba.what() << std::endl;
        }
        struct dirent *dir;
        while ((dir = readdir(d)) != NULL) {
            sprintf(fullpath, "%s/%s", path, dir->d_name);
            FileInfo(fullpath,dir->d_name);
            memset( fullpath, '\0', sizeof(path)+sizeof(dir->d_name)+2);
        }
        delete []fullpath;
        closedir(d);
    }

}

int listing::FileInfo(char *p, char *fname){
    if((stat(p, &sb)) == -1) {
        perror("stat");
        return -1;
    }
    struct passwd  *pwd;
    struct group   *grp;
    char *pw_name;
    char *gr_name;

    /* Print out owner's name if it is found using getpwuid(). */
    if ((pwd = getpwuid(sb.st_uid)) != NULL)
        pw_name=pwd->pw_name;
    else
        pw_name =NULL;

    /* Print out group name if it is found using getgrgid(). */
    if ((grp = getgrgid(sb.st_gid)) != NULL)
        gr_name= grp->gr_name;
    else
        gr_name=NULL;

    if (print == 0) {
        std::cout << "*****" << std::endl;
        std::cout << "-> " << fname << std::endl;
    }
    else if (print == 1){
        std::cout << "*****" << std::endl;
        std::cout << "-> " << fname << std::endl;
        std::cout << "\tSize: "<< sb.st_size << std::endl;
        std::cout << "\tOwner's name: " << pw_name <<std::endl;
        std::cout << "\tGroup's name: " << gr_name <<std::endl;
    }
    else if (print == 2){
        std::cout << "*****" << std::endl;
        std::cout << "-> " << fname << std::endl;
        std::cout << "\tSize: "<< sb.st_size << std::endl;
        std::cout << "\tUser ID of owner: " << sb.st_uid << "->" << pw_name << std::endl;
        std::cout << "\tGroup ID of owner: " << sb.st_gid << "->" <<gr_name << std::endl;
    }
    else if (print == 3){
        std::cout << "*****" << std::endl;
        std::cout << "-> " << fname << std::endl;
        std::cout << "\tSize: "<< sb.st_size << std::endl;
        std::cout << "\tPermissions: "<< (sb.st_mode & 07777) << std::endl;
        std::cout << "\tUser ID of owner: " << sb.st_uid << "->" << pw_name << std::endl;
        std::cout << "\tGroup ID of owner: " << sb.st_gid << "->" <<gr_name << std::endl;
    }
    else if (print == 4){
        std::cout << "*****" << std::endl;
        std::cout << "-> " << fname << std::endl;
        std::cout << "\ttime of last access: "<< sb.st_atime <<":"<< ctime(&sb.st_atime);
        std::cout << "\ttime of last modification: "<< sb.st_mtime <<":"<< ctime(&sb.st_mtime);
        std::cout << "\ttime of last change: "<< sb.st_ctime <<":"<< ctime(&sb.st_ctime);
    }
    else if (print == 5){
        std::cout << "-> " << fname << std::endl;
        std::cout << "\tDevice: " << sb.st_dev << std::endl;
        std::cout << "\tInode: " << sb.st_ino << std::endl;
        std::cout << "\tPermissions: " << sb.st_mode  << std::endl;
        std::cout << "\tNumber of hard links: "<< sb.st_nlink << std::endl;
        std::cout << "\tUser ID of owner: " << sb.st_uid << "->" << pw_name << std::endl;
        std::cout << "\tGroup ID of owner: " << sb.st_gid << "->" <<gr_name << std::endl;
        std::cout << "\tDevice type (if inode device): " << sb.st_rdev << std::endl;
        std::cout << "\ttotal size, in bytes: " << sb.st_size << std::endl;
        std::cout << "\tblocksize for filesystem I/O " << sb.st_blksize << std::endl;
        std::cout << "\tnumber of blocks allocated " << sb.st_blocks << std::endl;
        std::cout << "\ttime of last access: " << sb.st_atime <<":"<< ctime(&sb.st_atime);
        std::cout << "\ttime of last modification: " << sb.st_mtime <<":"<< ctime(&sb.st_mtime);
        std::cout << "\ttime of last change: " << sb.st_ctime <<":"<< ctime(&sb.st_ctime);

        switch (sb.st_mode & S_IFMT) {
            case S_IFBLK:  std::cout<<"\t\tblock device"<< std::endl;   		break;
            case S_IFCHR:  std::cout<<"\t\tcharacter device"<< std::endl;       break;
            case S_IFDIR:  std::cout<<"\t\tdirectory"<< std::endl;              break;
            case S_IFIFO:  std::cout<<"\t\tFIFO/pipe"<< std::endl;              break;
            case S_IFLNK:  std::cout<<"\t\tsymlink"<< std::endl;                break;
            case S_IFREG:  std::cout<<"\t\tregular file"<< std::endl;           break;
            case S_IFSOCK: std::cout<<"\t\tsocket"<< std::endl;                 break;
            default:       std::cout<<"\t\tunknown?"<< std::endl;               break;
        }
        printf("\tPermission Bits:    %s (%04o)\n", permOfFile(sb.st_mode),
               sb.st_mode & 07777);

    }


    return 1;
};

/*****
     * print 0 ise sadece isimleri listele -< n
     * print 1 ise isim size               -< s
     * print 2 ise isim ve yetkileri       -< p
     * print 3 ise isim size ve yetkiler   -< d
     * print 4 ise zaman bilgileri         -< t
     * print 5 ise tüm bilgiler            -< a
     */