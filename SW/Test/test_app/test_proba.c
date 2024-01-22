
#include <stdint.h> // uint16_t and family
#include <stdio.h> // printf and family
#include <unistd.h> // file ops
#include <fcntl.h> // open() flags
#include <string.h> // strerror()
#include <errno.h> // errno

#include "motor_ctrl.h"


void usage(FILE* f){
	fprintf(f,
"\nUsage: "\
"\n	test_servos -h|--help"\
"\n		print this help i.e."\
"\n	test_servos w servo_idx duty"\
"\n		write angle at servo_idx servo motor"
"\n	test_servos r servo_idx"\
"\n		read feedback angle of servo_idx servo motor"\
"\n	servo_idx = [0, 6)"\
"\n	duty = [0, 1000]"\
"\n"
	);
}

static inline int c_str_eq(const char* a, const char* b) {
	return !strcmp(a, b);
}


int main(int argc, char** argv){
	int servo_idx = 0;
	int duty = 500;

	uint16_t duties[MOTOR_CLTR__N_SERVO] = {0};
	
	int fd;
	fd = open(DEV_FN, O_RDWR);
	if(fd < 0){
		fprintf(stderr, "ERROR: \"%s\" not opened!\n", DEV_FN);
		fprintf(stderr, "fd = %d %s\n", fd, strerror(-fd));
		return 4;
	}
	
	
	
		printf("duty = %d\n", duty);
		duties[servo_idx] = duty; // [permilles]
		
		for(int i = 0; i < MOTOR_CLTR__N_SERVO; i++){
			printf("duties[%d] = %d\n", i, duties[i]);
		}
		
		r = write(fd, (char*)&duties, sizeof(duties));
		if(r != sizeof(duties)){
			fprintf(stderr, "ERROR: write went wrong!\n");
			return 4;
		}
	
		r = read(fd, (char*)&duties, sizeof(duties));
		if(r != sizeof(duties)){
			fprintf(stderr, "ERROR: read went wrong!\n");
			return 4;
		}
		for(int i = 0; i < MOTOR_CLTR__N_SERVO; i++){
			printf("duties[%d] = %d\n", i, duties[i]);
		}
		
		duty = duties[servo_idx]; // [permilles]
		printf("duty = %d\n", duty);
	

	close(fd);

	printf("End.\n");

	return 0;
}

