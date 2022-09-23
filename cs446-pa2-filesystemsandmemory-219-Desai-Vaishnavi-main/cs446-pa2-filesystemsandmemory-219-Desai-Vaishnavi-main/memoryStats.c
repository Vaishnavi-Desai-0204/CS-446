//Vaishnavi Desai
//fileSystemInfo.c
//to implement modified version of free binary

#include <unistd.h>
#include <stdio.h>
#include <sys/statvfs.h>

int main(){
struct statvfs vfs;
statvfs("." , &vfs);
	long pages = sysconf(_SC_PHYS_PAGES);
	long page_size = sysconf(_SC_PAGE_SIZE);
	double page_size_kilo = page_size /1000 ;
	double memory = pages * page_size ;
	double mounted_file = (vfs.f_bfree * vfs.f_bsize);
	
	printf("====Mounted File System (HD) information====\n");
	printf("FREE BLOCKS: %li \n", vfs.f_bfree);
	printf("TOTAL FREE MOUNTED FILE SYSTEM MEM: %.2f\n", (mounted_file/10000000000));
	printf("GBFREE INODES: %li\n",vfs.f_ffree);
	
	printf("\n====System RAM information====\n");
	printf("There are %li pages available, each with %.2f kb\n", pages , page_size_kilo);
	printf("Total Available Memory: %.2f\n", memory / 10000000000);
	
	
}






