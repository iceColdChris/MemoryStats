/*
 * Chris Fahlin
 * TCSS 422
 * Homework 7
 * 3/14/15
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    //Variables for the memory statistics
	unsigned long long totalMemory = 0;
	unsigned long averageMemory;
	unsigned long largestMemory = 0;
	unsigned long smallestMemory = ULONG_MAX;
	unsigned long totalProcesses = 0;
    
    //Hardcoded proc and filename
	char* directory = "/proc";
	char* fileName = "/psinfo";

    //dirent stuffs
	struct dirent* dent;
	DIR* srcdir = opendir(directory);
	
    //Create input file pointer
    FILE *ifp;

	if (srcdir == NULL)
	{
		perror("opendir");
		return -1;
	}

	while((dent = readdir(srcdir)) != NULL)
	{
        //Ignore the . and .. directories
		if(strcmp(dent->d_name, ".") == 0 || strcmp(dent->d_name, "..") == 0)
			continue;

        //Find the current path
		char* currentPath = malloc(strlen(directory) + strlen("/") + strlen(dent->d_name) + 1);
		strcpy(currentPath, directory);
		strcat(currentPath, "/");
		strcat(currentPath, dent->d_name);

        //Find the full path to the psinfo
		char* fullPath = malloc(strlen(currentPath) + strlen(fileName) + 1);
		strcpy(fullPath,currentPath);
		strcat(fullPath, fileName);

        //Open the full path
		ifp = fopen(fullPath, "r");

		if (ifp == NULL) {
			//Do Nothing
            //Because its not a real
            //directory
		}else{
			
            /*All your variables are belong to us*/
            int line1_1;  /* information version */
			char line1_2; /* process type */
			int line1_3;  /* process endpoint */
			char line1_4; /* process name */
			char line1_5; /* process state letter */
			int line1_6;  /* endpt blocked on, or NONE */
			int line1_7; /* process priority */
			unsigned long line1_8;  /* user time */
			unsigned long line1_9;  /* system time */
			unsigned long line1_10; /* execution cycles */
			unsigned long line1_11; /* execution cycles */
			unsigned long line1_12; /* total memory */
			unsigned long line1_13; /* common memory */
			unsigned long line1_14; /* shared memory */
			char line1_15; /* sleep state */
			int line1_16; /* parent PID */
			unsigned int line1_17; /* real UID */
			unsigned int line1_18; /* effective UID */
			unsigned int line1_19; /* process group */
			int line1_20;  /* nice value */
			char line1_21; /* VFS block state */
			int line1_22;  /* block proc */
			unsigned int line1_23; /* controlling tty */
            /*Whew you survived the wall of variables*/

			fscanf(ifp,"%d %c %d %s %c %d %d %lu %lu %lu %lu %lu %lu %lu %c %d %u %u %u %d %c %d %u"
					,&line1_1, &line1_2, &line1_3, &line1_4, &line1_5, &line1_6, &line1_7, &line1_8,
					&line1_9, &line1_10, &line1_11, &line1_12, &line1_13, &line1_14, &line1_15, &line1_16,
					&line1_17, &line1_18, &line1_19, &line1_20, &line1_21, &line1_22, &line1_23);

            if(line1_12 != 0)
            {
                
                totalProcesses++;
                totalMemory += line1_12;
                //Finds the smallest process
                if(smallestMemory > line1_12) smallestMemory = line1_12;
                //Finds the largest memory usage
                if(largestMemory < line1_12) largestMemory = line1_12;
            }
		}
        //Gotta free those mallocs :D
		free(currentPath);
		free(fullPath);
	}

	closedir(srcdir);


	averageMemory = totalMemory/totalProcesses;

	printf("\nTotal Memory: %llu \nAverageMemory: %lu \nBiggest Process: %lu \nSmallest Process: %lu\n"
			,totalMemory, averageMemory, largestMemory, smallestMemory);
	return 0;

}
