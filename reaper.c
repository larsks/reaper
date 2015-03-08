#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int opt_quiet = 0;

void run_child(int argc, char **argv) {
	execvp(argv[0], argv);
}

void reap() {
	pid_t pid;
	int status;

	while (1) {
		if (-1 == (pid = wait(&status)))
			break;

		if (! opt_quiet)
			fprintf(stderr, "[reaper] pid %d exited with status == %d\n",
					pid, status);
	}
}

int start_reaper(int argc, char **argv) {
	int pid;
	int res = 0;

	pid = fork();
	switch(pid) {
		case 0: run_child(argc, argv);
			break;

		case -1: perror("fork");
			 res=1;
			 break;

		default: reap();
	}

	return res;
}

int main(int argc, char **argv) {
	int c;
	int res = 0;

	while ((c = getopt(argc, argv, "q")) != EOF) {
		switch (c) {
			case 'q': opt_quiet=1;
				  break;
		}
	}
	res = start_reaper(argc-optind, argv+optind);
	return res;
}

