#include <iostream>
#include <unistd.h>
#include "src/listing.hpp"


int main(int argc, char **argv) {

    int c;
    int count=0;
    char *path=NULL;
    int p=0;
    opterr = 0;
    listing *t =NULL;

    while ((c=getopt(argc,argv,"nspdtai:")) != -1) {
        switch (c) {
            case 'n':
                p = 0;
                count +=1;
                break;
            case 's':
                p = 1;
                count +=1;
                break;
            case 'p':
                p = 2;
                count +=1;
                break;
            case 'd':
                p = 3;
                count +=1;
                break;
            case 't':
                p = 4;
                count +=1;
                break;
            case 'a':
                p = 5;
                count +=1;
                break;
            case 'i':
                path=optarg;
                break;
            default:
                abort();
        }
    }

    if (count!=1){
        fprintf (stderr, "Birden fazla option girildi ya da geçerli parametre girilmedi.\n");
    }

    if (path == NULL){
        t=new listing();
    }
    else{
        t=new listing(path);
    }

    //t->print=p;
    t->print=5;
    t->path="/home/n0pe/Desktop/apue.pdf";
    t->ShowDirContent(t->path);



    delete t;
    return 0;
}