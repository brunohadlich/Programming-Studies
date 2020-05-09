/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/28/20 12:00:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <stdio.h>

#include "time_measurement.h"

/* Estimate the clock rate by measuring the cycles that elapse */
/* while sleeping for sleeptime seconds */
double mhz(int verbose, int sleeptime) {
	double rate;

	start_counter();
	sleep(sleeptime);
	rate = get_counter() / (1e6*sleeptime);
	if (verbose)
		printf("Processor clock rate ˜= %.1f MHz\n", rate);
	return rate;
}

int main(int argc, char *argv[]) {
	mhz(1, 7);
	return 0;
}
