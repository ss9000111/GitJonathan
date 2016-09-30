/*
 ============================================================================
 Name        : Lab4.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Signals
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>

double avg(int a[], int quantity, int max) {
	int total = 0, i = 0;		//initialize variables
	double average;
	while (i < quantity) {		//Sum up all the numbers in the array
		total += a[i];
		i++;
	}
	average = (double) total / quantity;	//Find the average of the sum
	return average;			//return average
}

int max(int a[], int length) {
	int Max = 0;				//initialize variables
	int i = 0;
	while (i < length) {		//Find the max in the array
		if (a[i] > Max)
			Max = a[i];
		i++;
	}
	return Max;					//Return the Max
}

void filewrite(double a[], int num, int quantity, double change) {
	int i = 0;										//initialize 'i'
	if (num == 1) {
		FILE *file = fopen("Offset_data_nn.txt", "w"); //Open file and write data to file
		fprintf(file, "%d %.04f\n", quantity, change);
		while (i < quantity) {
			fprintf(file, "%.04f\n", a[i]);
			i++;
		}
		if (file == NULL) {				//Check if file opens
			printf("Error! File couldn't be open!");
			exit(0);
		}
		fclose(file);			//Close file
	}
	if (num == 2) {
		FILE *file = fopen("Scaled_data_nn.txt", "w");//Open file and write data to file
		fprintf(file, "%d %.04f\n", quantity, change);
		while (i < quantity) {
			fprintf(file, "%.04f\n", a[i++]);
		}
		if (file == NULL) {				//Check if file opens
			printf("Error! File couldn't be open!");
			exit(0);
		}
		fclose(file);			//Close file
	}
}

void scale(int a[], int length) {
	double scaler, b[length];			//initialize variables
	int i = 0;
	printf("What would you like the scaler to be?: ");//Receive user input for scaler
	fflush(stdout);
	scanf("%lf", &scaler);
	while (i < length) {				//Assign scale of array a to array b
		b[i] = a[i] * scaler;
		i++;
	}
	filewrite(b, 2, length, scaler);	//Write array b to file
}

void offset(int a[], int quantity) {
	double oFFset, b[quantity];			//initialize variables
	int i = 0;
	fflush(stdin);
	printf("how much do you want to offset the signal?");//Receive user input for offset
	fflush(stdout);
	scanf("%lf", &oFFset);
	while (i < quantity) {				//Assign offset of array a to array b
		b[i] = a[i] + oFFset;
		i++;
	}
	filewrite(b, 1, quantity, oFFset);		//Write array b to file
}

void normal(int array[], int quantity, int max) {
	int i = 0;				//initialize variables
	float array2[quantity];
	while (i < quantity) {
		array2[i] = array[i];	//assign array to array2
		i++;
	}
	i = 0;
	while (i < quantity) {			//Normalize arrary2
		array2[i] = array2[i] / max;
		i++;
	}
	i = 0;
	FILE *File = fopen("Normalized_data_nn.txt", "w");//write information to file
	if (File == NULL) {				//Check if file opens
		printf("Error! File couldn't be open!");
		exit(0);
	}
	fprintf(File, "%d %d\n", quantity, max);		//Print information to file
	while (i < quantity) {
		fprintf(File, "%.04f\n", array2[i]);
		i++;
	}
}

void center(int array[], int quantity, int max) {
	int i = 0;				//initialize variables
	double aveg;
	float array2[quantity];
	aveg = avg(array, quantity, max);		//find average of array
	while (i < quantity) {					//Center the array
		array2[i] = array[i] - aveg;
		i++;
	}
	i = 0;
	FILE *File = fopen("Centered_data_nn.txt", "w");		//Create file
	if (File == NULL) {				//Check if file opens
		printf("Error! File couldn't be open!");
		exit(0);
	}
	fprintf(File, "%d %.04f\n", quantity, aveg);		//Write data to file
	while (i < quantity) {
		fprintf(File, "%.04f\n", array2[i]);
		i++;
	}
}

int main(int argc, char** argv) {
	int choice, quantity, Max, num, i=0;				//initialize variables
	int array1[quantity], array2[quantity], array3[quantity], array4[quantity];
	char fIle[20] = { 0 };
	puts("Choose a number between 0 and 12:");	//Prompt user for input and flushing output
	fflush(stdout);
	scanf("%d", &choice);						//Receive input from user
	sprintf(fIle, "Raw_data_%d.txt", choice);
	FILE *filE = fopen(fIle, "r");				//Open chosen file
	if (filE == NULL) {				//Check if file opens
		printf("Error! File couldn't be open!");
		exit(0);
	}
	fscanf(filE, "%d %d", &quantity, &Max);		//read the chosen file

	while (!feof(filE)) {						//assign numbers from file to arrays
		fscanf(filE, "%d\n", &num);
		array1[i] = num;
		array2[i] = num;
		array3[i] = num;
		array4[i] = num;
		i++;
	}

	fclose(filE);					//close file
	center(array1, quantity, Max);		//call function center on array1
	normal(array2, quantity, Max);		//call function center on array2
	FILE *File = fopen("Statistics_data_nn.txt", "w");	//Open writable file for average and max
	if (File == NULL) {				//Check if file opens
		printf("Error! File couldn't be open!");
		exit(0);
	}
	fprintf(File, "%.04f %d", avg(array3, quantity, Max),
			max(array4, quantity));			//write the average and max to file
	fclose(File);			//close file
	int choice2;
	fflush(stdin);
	printf(
			"Enter 1 to offset the chosen file or enter 2 to scale the chosen file:");		//Prompt user for input and receives input
	fflush(stdout);
	scanf("%d", &choice2);
	switch (choice2) {				//Use case statement to handle both choices
	case 1:
		offset(array4, quantity);	//Call offset function while passing array4 and quantity
		break;
	case 2:
		scale(array4, quantity);	//Call offset function while passing array4 and quantity
		break;
	default:						//Use to test user input
		printf("Error, invalid input");
		break;
	}

	return EXIT_SUCCESS;
}
