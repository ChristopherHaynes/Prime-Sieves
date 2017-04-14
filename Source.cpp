//prime number calculator
#include <iostream>
#include <conio.h>
#include <windows.h>

int RUNS;                 //integer for multiple run throughs allowing me to calculate mean average running times
int i, j, c = 0, p;       //integers for test number "i", divisor "j", prime counter "c", current prime number "p"
const int MAX = 100000;   //constant integer used to set the size of the PRIMES array
char PRIMES[MAX];		  //array to hold the prime numbers
char z[50000];            //array representing just the odd numbers between 0 and 100,000

void main(void)
{
	//################################################################################################## Brute Force Method

	for (i = 4; i < 100000; i += 2) { PRIMES[i] = 1; }   //initilisation of array, setting all even array positions above 2 to a value of 1 

	DWORD starttime, endtime;
	float totaltime, totaltime1, totaltime2;
	starttime = GetTickCount();     //get start time

	for (i = 3; i < 100000; i += 2) //numbers to check if prime, counting up in increments of 2
	{
		for (j = 3; j < i; j += 2)  //divisor values increasing from 3 up to the current value being checked
		{
			if (i % j == 0) { PRIMES[i] = 1; break; }  //if "i" divided by "j" returns no remainder then "i" can not be a prime
		}                                              //set the current "i" position to 1 in the primes array
	}
	endtime = GetTickCount();       //get finish time

	for (i = 1; i < 100000; i++)    //count the number of primes in the array
	{
		if (PRIMES[i] == 0) { c++; }
	}
	std::cout << "Total Primes: " << c << "\n";

	totaltime = ((float)endtime - (float)starttime) / 1000.0;  //calculate total time in secs
	std::cout << "Totaltime=" << totaltime << " sec\n\n";

	//################################################################################################## Memset Timer 1

	starttime = GetTickCount();            //get start time
	for (RUNS = 0; RUNS < 100000; RUNS++)
	{
		memset(PRIMES, 0, 100000);
	}
	endtime = GetTickCount();             //get finish time


	totaltime1 = (((float)endtime - (float)starttime) / (1000 * RUNS));//calculate total time in secs
																	  
	printf("total time for memset=%.12f secs\n\n", totaltime1);

	//################################################################################################## Sieve of Eratosthenes V1
	 
	starttime = GetTickCount();           //get start time
	for (RUNS = 0; RUNS < 10000; RUNS++)  //as each run is faster than a millisecond, this loop runs it 10,000 times and records the mean runtime
	{
		memset(PRIMES, 0, 100000);         //memset command is needed to reset the array after each run
		PRIMES[0] = 1;					   //The 0 and 1 position in the array are set to 1
		PRIMES[1] = 1;                  
		p = 2;                             //the initial prime number value is set to 2
		do 
		{
			for (i = p + p; i <= MAX; i = i + p)        //starting at "2*p" and increasing in increments of "p", as long as the value remains under 100,000
			{
				if (PRIMES[i] == 0) { PRIMES[i] = 1; }  //if the value has already been marked as not prime, ignore it, otherwise mark it as a non-prime
			}

			for (i = p + 1; i <= 317; i++)              //change the value of "p" to the next un marked number 
			{
				if (PRIMES[i] == 0) { p = i; break; }   //once "p" is set; break out the loop and test the new value of "p"
			}
		} while (p <= 316);                //316 is the square root of 100,000 meaning I only need check values less than this

	}
	endtime = GetTickCount();     //get finish time
	c = 0;                        //reset the primes counter

	for (i = 0; i <= MAX; i++)    //count the amount of 0s in the array to give the amount of primes
	{
		if (PRIMES[i] == 0) c++;
	}
	std::cout << (c) << " Primes\n";
	totaltime = (((float)endtime - (float)starttime) / 1000) / RUNS;//calculate total time in secs
																	
	printf("total time=%.12f secs\n\n", totaltime - totaltime1);

	//################################################################################################## Sieve of Eratosthenes V2

	starttime = GetTickCount();            //get start time
	for (RUNS = 0; RUNS < 10000; RUNS++)   //as each run is faster than a millisecond, this loop runs it 10,000 times and records the mean runtime
	{
		memset(PRIMES, 0, 100000);         //memset command is needed to reset the array after each run
		PRIMES[0] = 1;					   //The 0 and 1 position in the array are set to 1
		PRIMES[1] = 1;
		p = 2;                             //the initial prime number value is set to 2
		do
		{
			if (PRIMES[p] == 0)            //check if the current value of "p" is marked, if it isn't increase "p" by 1 and check again
			{
				for (i = p * p; i < MAX; i = i + p)    // starting at "p^2" and increasing by an increment of "p" as long as the value remains under 100,000
				{
					PRIMES[i] = 1;         //mark each visited position in the array as a non-prime
				}
			}
			p++;
		} while (p <= 316);                //316 is the square root of 100,000 meaning I only need check values less than this

	} 
	endtime = GetTickCount();     //get finish time
	c = 0;                        //reset the primes counter

	for (i = 0; i <= MAX; i++)    //count the amount of 0s in the array to give the amount of primes
	{
		if (PRIMES[i] == 0) c++;
	}
	std::cout << (c) << " Primes\n";
	totaltime = (((float)endtime - (float)starttime) / 1000) / RUNS;//calculate total time in secs

	printf("total time=%.12f secs\n\n", totaltime - totaltime1);

	//################################################################################################## Memset Timer 2

	starttime = GetTickCount();            //get start time
	for (RUNS = 0; RUNS < 100000; RUNS++)
	{
		memset(z, 0, 50000);
	}
	endtime = GetTickCount();             //get finish time


	totaltime2 = (((float)endtime - (float)starttime) / (1000 * RUNS));//calculate total time in secs
																	   
	printf("total time for memset=%.12f secs\n\n", totaltime2);
	
	//################################################################################################## Sieve of Eratosthenes V3

	starttime = GetTickCount();             //get start time
	for (RUNS = 0; RUNS < 10000; RUNS++)    //as each run is faster than a millisecond, this loop runs it 10,000 times and records the mean runtime
	{
		memset(z, 0, 50000);                //memset command is needed to reset the array after each run
		p = 0;

		do
		{
			if (z[p] == 0)                  //check if the current value of "p" is marked, if it is increase "p" by 1 and check again
			{ 
				for (i =2 * p*p + 6 * p + 3; i < MAX / 2; i += (p << 1) + 3) //counts up from "p^2" in increments of "p", whilst translating those values to the array which is only representing odd numbers
				{
					z[i] = 1;              //mark each visited position in the array as a non-prime
				}
			}
			p++;
		} while (p <= 224);               //224 is the square root of 50,000 meaning I only need check values less than this

	}
	endtime = GetTickCount();             //get finish time
	c = 0;                                //reset the primes counter

	for (i = 0; i <= MAX / 2; i++)        //count the amount of 0s in the array to give the amount of primes
	{
		if (z[i] == 0) c++;
	}
	std::cout << (c) << " Primes\n";
	totaltime = (((float)endtime - (float)starttime) / (1000 * RUNS));//calculate total time in secs
																	 
	printf("total time =%.12f secs\n", totaltime - totaltime2);

	_getch();
}
