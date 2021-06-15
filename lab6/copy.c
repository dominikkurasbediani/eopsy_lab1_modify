// REFERENCES:
// https://man7.org/linux/man-pages/man3/getopt.3.html
// https://man7.org/linux/man-pages/man2/open.2.html
// https://stackoverflow.com/questions/15798450/open-with-o-creat-was-it-opened-or-created
// https://man7.org/linux/man-pages/man2/read.2.html
// https://man7.org/linux/man-pages/man2/write.2.html
// https://stackoverflow.com/questions/9219079/copying-contents-of-a-file-to-another-using-read-write-open


#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h> // for warnings with memcpy

int copy_read_write(int fd_from, int fd_to);


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
		// O_WRONLY mode is not sufficient when mmaping.
		if ((fd_to = open(argv[optind+1], O_RDWR | O_CREAT | O_TRUNC, 0666)) < 0){
			fprintf(stderr,"\nCan't open %s for writing!\n", argv[optind+1]);
			return 1;
		}
		if (use_mmap){
			printf("\nCopying '%s' into '%s' using mmap() and memcpy() functions.\n\n",argv[optind],argv[optind+1]);
		}
		else{
			printf("\nCopying '%s' into '%s' using read() and write() functions.\n\n",argv[optind],argv[optind+1]);
			copy_read_write(fd_from, fd_to);
		}
		if (close(fd_from))
			fprintf(stderr,"\nCan't close %s!\n", argv[optind]);
		if (close(fd_to))
			fprintf(stderr,"\nCan't close %s!\n", argv[optind]);
	} else
		printf("The COPY program.\nUsage:\n\tcopy [-m] <file_name> <new_file_name>\n\tcopy [-h]\nWithout option -m, program uses read() and write() functions to copy file contents.\nIf the option -m is given, both files are mapped to memory regions with mmap() and are copied the file with memcpy() instead.\n\n");
	return 0;
}

int copy_read_write(int fd_from,int fd_to){
	size_t copied_bytes;
	char buf[256]; // 256B buffer
	size_t nbyte = sizeof(buf);
	while ((copied_bytes = read(fd_from, &buf, nbyte)) > 0)
		if (write(fd_to, &buf, copied_bytes) < 0)
			fprintf(stderr,"\nError writing into output file!\n");
	if (copied_bytes < 0)
		fprintf(stderr,"\nError reading input file!\n");
}