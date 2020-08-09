/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/29/2020 10:44:24 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t lock;

int main(int argc, char *argv[]) {
	pthread_mutex_init(&lock, NULL);
	pthread_mutex_lock(&lock);
}
