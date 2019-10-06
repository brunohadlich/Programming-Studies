/*
 * =====================================================================================
 *
 *       Filename:  segmentation_fault.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/24/2019 01:14:04 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>

int main() {
	*(int *)0 = 5;
}
