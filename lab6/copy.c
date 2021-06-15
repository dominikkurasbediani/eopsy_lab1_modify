#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h> // for warnings with memcpy

int main (int argc, char **argv){
	char a, use_mmap = 0, dsp_help = 0;
	int fd_from = 0, fd_to = 0;
	while((a = getopt (argc, argv, "mh")) != -1){
		switch (a){
			case 'm':
				use_mmap = 1;
				break;
			case 'h':
				dsp_help = 1;
				break;
			default:
				fprintf(stderr,"\nUnknown option character '%c'.\n",optopt);
		}
	}
	if (!dsp_help){
		if ((fd_from = open(argv[optind], O_RDONLY)) < 0){
			fprintf(stderr,"\nCan't open %s for reading!\n", argv[optind]);
			return 1;
		}
		if (use_mmap){
			printf("\nCopying '%s' into '%s' using mmap() and memcpy() functions.\n\n",argv[optind],argv[optind+1]);
		}
		else{
			printf("\nCopying '%s' into '%s' using read() and write() functions.\n\n",argv[optind],argv[optind+1]);
		}
		if (close(fd_from))
			fprintf(stderr,"\nCan't close %s!\n", argv[optind]);
		if (close(fd_to))
			fprintf(stderr,"\nCan't close %s!\n", argv[optind]);
	} else
		printf("The COPY program.\nUsage:\n\tcopy [-m] <file_name> <new_file_name>\n\tcopy [-h]\nWithout option -m, program uses read() and write() functions to copy file contents.\nIf the option -m is given, both files are mapped to memory regions with mmap() and are copied the file with memcpy() instead.\n\n");
	return 0;
}