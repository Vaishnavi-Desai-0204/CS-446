//Vaishnavi Desai
//fileSystemInfo.c
//to implement modified ls code

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

int ls_sim(struct dirent *d){  
	printf("%s \n", d->d_name);
	return 0;
}

int ls_sim_verbose(struct dirent *d){
  struct stat statbuf; 
    char fp[PATH_MAX];
    sprintf(fp, "%s",  d->d_name);
    if(stat(fp, &statbuf) == -1) {
        perror("stat");
        return 1;   
    }
    //file name 
    printf("%-25s", d->d_name); 
    
    //permission data/nlink 
    printf((S_ISDIR(statbuf.st_mode)) ? "d" : "-"); 
    printf((statbuf.st_mode & S_IRUSR) ? "r" : "-");
    printf((statbuf.st_mode & S_IWUSR) ? "w" : "-");
    printf((statbuf.st_mode & S_IXUSR) ? "x" : "-");
    printf((statbuf.st_mode & S_IRGRP) ? "r" : "-");
    printf((statbuf.st_mode & S_IWGRP) ? "w" : "-");
    printf((statbuf.st_mode & S_IXGRP) ? "x" : "-");
    printf((statbuf.st_mode & S_IROTH) ? "r" : "-");
    printf((statbuf.st_mode & S_IWOTH) ? "w" : "-");
    printf((statbuf.st_mode & S_IXOTH) ? "x " : "- ");
    
    printf("%10ld ", statbuf.st_ino); //inode
       
    //file size
    printf("%10ld ", statbuf.st_size);
    
    printf("%5li \n", statbuf.st_nlink); //links
    
    return 0;
   
}

int main(int argc , char* argv[]){
	int flag_long = 0;  // flag for -l option
	if (argv[1]){ //check if anything after filename has been entered
		if (strcmp(argv[1] , "ls") == 0){ //check for ls
			//get option 
    			int opt; 
	       		while((opt = getopt(argc, argv, "l")) != -1) { //check for -l option
				switch (opt) {
				case 'l':   
					flag_long = 1;  //set flag if -l is enters
				        break;
				default:
				        printf("fileSystemInfo: supports -l option\n"); 
				        return 1; 
        			}
        		}
        		if(flag_long == 0){ // if -l has not been entered
        			if(optind == argc-1 ) { // check if path is included
					struct dirent *d;
					DIR *dh = opendir(".");
					while ((d = readdir(dh)) != NULL){				
						ls_sim(d);
					}
					printf("\n");			     			
				}
				else{
					while(optind < argc-1) { //if path is inluded loop for all inlcuded paths
						char *arg = argv[optind+1]; 
				    		struct dirent *d;
				    		DIR *dh = opendir(arg);
				   		 if(dh == NULL) { //check for path
							printf("fileSystemInfo: cannot access '%s': No such file or directory\n", argv[optind+1]);
							return 1;
					    	}
				   		else{ //cal ls_sim() funtion if path exists
				    		    	while ((d = readdir(dh)) != NULL){	
								ls_sim(d);
							}	
						printf("\n");
				   		 }
					optind++ ;
			
					}
				
				}		
			}
			if (flag_long == 1){ // check if -l flag is set
				 if(optind == argc-1 ) { // if path is not included
					struct dirent *d;
					DIR *dh = opendir(".");
					printf("File Name                Mode           Inode     Size(B)     Links\n");
				    	printf("==============================================================================\n");
									    
					while ((d = readdir(dh)) != NULL){				
						ls_sim_verbose(d); 
					}
					printf("\n");
					
				}
				else{
					while(optind < argc-1) {
						char *arg = argv[optind+1]; 
				    		struct dirent *d;
				    		DIR *dh = opendir(arg);
				    
				    		if(dh == NULL) { //check for path
							printf("fileSystemInfo: cannot access '%s': No such file or directory\n", argv[optind+1]);
				    		}
				   		 else{
				    			printf("File Name                Mode           Inode     Size(B)     Links\n");
				    	printf("==============================================================================\n");
				    			while ((d = readdir(dh)) != NULL){				
								ls_sim_verbose(d);
							}	
							printf("\n");
				    		}
						optind++ ;		     			
					}
				}	
			}        		
        	}
        	else {
        		printf("Please enter ls \n"); 
        	}
	  } 		
	else{
		printf("An error has occured. Options are: \nls \nls -l \nls <path> \nls -l <path>\n");
		return 1; 
	}
	return 0;
}
	

