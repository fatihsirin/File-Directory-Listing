####File-Directory-Listing

File listing in a directory and show information about files.

## Help Page
```
-Display options
     if -n 1print just names 					
     if -s print names and sizes                 
     if -p print names and permissions       	
     if -d print names, sizes, permissions   	
     if -t print time information        		
     if -a print all information           

-i path parameter
-h help page
```

##Example
```
$ ./File_Directory_Listing -a -i /home/n0pe/Desktop/
-> test
	Device: 2055
	Inode: 3152956
	Permissions: 33204
	Number of hard links: 1
	User ID of owner: 1000->n0pe
	Group ID of owner: 1000->n0pe
	Device type (if inode device): 0
	total size, in bytes: 136
	blocksize for filesystem I/O 4096
	number of blocks allocated 8
	time of last access: 1496688739:Mon Jun  5 20:52:19 2017
	time of last modification: 1496688734:Mon Jun  5 20:52:14 2017
	time of last change: 1496688734:Mon Jun  5 20:52:14 2017
		regular file
	Permission Bits:    rw-rw-r-- (0664)

-> asdasdasdasd.cpp
	Device: 2055
	Inode: 3155725
	Permissions: 33204
	Number of hard links: 1
	User ID of owner: 1000->n0pe
	Group ID of owner: 1000->n0pe
	Device type (if inode device): 0
	total size, in bytes: 1686
	blocksize for filesystem I/O 4096
	number of blocks allocated 8
	time of last access: 1497137866:Sun Jun 11 01:37:46 2017
	time of last modification: 1497113197:Sat Jun 10 18:46:37 2017
	time of last change: 1497113197:Sat Jun 10 18:46:37 2017
		regular file
	Permission Bits:    rw-rw-r-- (0664)

```