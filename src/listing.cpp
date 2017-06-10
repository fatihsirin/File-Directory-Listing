//
// Created by n0pe on 10.06.2017.
//

#include "listing.hpp"
#include "debug.h"


listing::listing() {
    path=GetCurrentDir();
}

listing::listing(char *p) {
    path = (char *)malloc(sizeof(p));
    memset(path,0,sizeof(path));
    //memcpy(path,p,sizeof(path));
    strcpy(path,p);
    std::cout<<path;
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
        DEBUG_ERROR("verilen string path değil dosyadır.");


        if(FileInfo(p)){
            DEBUG_INFO("başarılı olarak yazılmıştır.");
        }


    }
    else{
        char *fullpath = (char *)malloc(PATH_MAX);
        if (fullpath == NULL) {
            /* deal with error and exit */
            DEBUG_ERROR("fullpath malloc error");
            exit(1);
        }
        struct dirent *dir;
        while ((dir = readdir(d)) != NULL) {
            std::cout<<dir->d_name<<std::endl;

            sprintf(fullpath, "%s/%s", path, dir->d_name);
            std::cout<<fullpath<<std::endl;
            FileInfo(fullpath);
            memset( fullpath, '\0', sizeof(path)+sizeof(dir->d_name)+2);
        }
        free(fullpath);
        closedir(d);
    }

}

int listing::FileInfo(char *p){
    if((stat(p, &sb)) == -1) {
        perror("fstat");
        return -1;
    }

    return 1;
};