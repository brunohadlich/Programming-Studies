///*
//48 bytes
struct data {
	char letter;
	int number;
	char leter2;
	long double number2;
	int number3;
	long number4; 
};
//*/
/*
//34 bytes
struct data {
	char letter;
	int number;
	char leter2;
	long double number2;
	int number3;
	long number4; 
} __attribute__((packed));
*/
/*
//48 bytes
struct data {
	long double number2;
	long number4; 
	int number3;
	int number;
	char letter;
	char leter2;
};
*/
long long soma_array(struct data *vetor, int size);
