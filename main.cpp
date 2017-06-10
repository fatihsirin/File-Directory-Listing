#include <iostream>
#include <unistd.h>
#include "src/listing.hpp"


int main(int argc, char **argv) {

    int c;
    int count=0;
    char *path=NULL;
    opterr = 0;
    listing *t = new listing((char *)"/home/n0pe/Desktop/");
    //t->FileInfo("asdasda");
    //t->ShowDirContent(t->path);
    //char *ta = t->GetCurrentDir();
/*
    //parametre ile çalışma
    if  (argc < 1){


    }
    //parametresiz çalışma
    else{
        FileTest *t = new FileTest();
    }
*/

    while ((c=getopt(argc,argv,"nspdtai:")) != -1) {
        switch (c) {
            case 'n':
                t->print = 0;
                count +=1;
                break;
            case 's':
                t->print = 1;
                count +=1;
                break;
            case 'p':
                t->print = 2;
                count +=1;
                break;
            case 'd':
                t->print = 3;
                count +=1;
                break;
            case 't':
                t->print = 4;
                count +=1;
                break;
            case 'a':
                t->print = 5;
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

    delete t;
    return 0;
}