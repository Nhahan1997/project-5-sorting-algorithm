// Data Structures - Spring 2021
// Project 5
// project4_sampleCode.cpp

#include<iostream>
#include<cstdlib> // used for random number generation
#include<math.h> // used for math functions 
#include<unordered_set> // used for generating unique elements

using namespace std;

// bubble sort algorithm with D number of comparisons allowed
int* bubbleSort(int* arr, int numElements, int D)
{
    int numComp = 0; // used to count the number of comparisons and to check with D

    int* arrCopy = new int[numElements]; // making a copy of arr as this is an inplace sorting algorithm
                                        // we want to retain the ordering of arr for shell sort 
    for(int i = 0; i < numElements; i++)
        arrCopy[i] = arr[i];

    // bubble sort starts
    for (int i = 0; i < numElements; i++)
    {
        for (int j = 0; j < numElements - 1; j++)
        {
            numComp++; // incrementing the number of comparisons done right before 
                        // the if condition where the comparison happens each time
            if(numComp >= D) // checking for number of comparisons
                return arrCopy; // return the not necessarily sorted array = approximately sorted array

            if (arrCopy[j] > arrCopy[j + 1])
            {
                // swap
                int temp = arrCopy[j];
                arrCopy[j] = arrCopy[j + 1];
                arrCopy[j + 1] = temp;
            }
        }
    }
    // return the completely sorted array
    return arrCopy;
}

// shell sort algorithm with D number of comparisons allowed
int* shellSort(int* arr, int numElements, int D)
{
	int j;
    int numComp = 0;

    // need not make a copy of the arr array since shell sort is performed later/last
	
    // Start with a largest increment, then reduce by factors of 3 
    for (int inc = numElements / 3; inc > 1; inc /= 3)
    {
        // Insertion sort for the increment length
        for (int i = inc; i < numElements; ++i) 
        {
            int temp = arr[i];
            j = i - inc;

            while ((j >= 0) && (arr[j] > temp))
            {
            	numComp++; // incrementing the number of comparisons done right before
					// the if condition where the comparison happens each time
				if(numComp >= D) // checking for number of comparisons
					return arr; // return the not necessarily sorted array = approximately sorted array

                arr[j + inc] = arr[j];
                j = j - inc;
            }
            arr[j + inc] = temp;
        }
    }
    // Insertion sort for the increment length = 1; force length 1 in case of inc/3 == 0
    for (int i = 1; i < numElements; ++i)
    {
        int temp = arr[i];
        j = i - 1;

        while ((j >= 0) && (arr[j] > temp))
        {
        	numComp++; // incrementing the number of comparisons done right before
				// the if condition where the comparison happens each time
			if(numComp >= D) // checking for number of comparisons
				return arr; // return the not necessarily sorted array = approximately sorted array

            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = temp;
    }
	return arr;
}

//method print the array's element
void printArray(int* arr, int n){
	for (int i = 0; i < n; i++){
		cout << arr[i] << " ";
	}
}

//method calculate the number of inversion
int inversion(int* arr, int n){
	int num = 0;  //inversion number
	for (int i = 0; i < n; i++){	//loop the array, index start at 0
		for (int j = i + 1; j < n; j++){  //loop again, index start at next index i
			if (arr[i] > arr[j])	//if there any element behind index i is smaller
				num++;				//increase inversion number by one
		}
	}
	return num;	//return
}

//main function
int main()
{   
	int n;
	cin >> n; // read the number of elements
	cout << "Number of elements: " << n << endl;

	int s, l, u, D;
	cin >> s >> l >> u; // read the seed, lower range, upper range and the number of comparisons

	cin >> D;
    cout << "Number of comparisons allowed: " << D << endl;
    cout << endl;

	// generate n random elements with the seed s, within the lower and upper range 
    // store the randomly generated UNIQUE set of elements in an array 'A'
    
    // you may use the unordered set to help generate unique elements

    srand(s);	//generate n random elements with the seed s
    unordered_set <int> str;	//create unordered_set str to get the unique elements
    for (int i = 0; i < n; i++){
    	int num = (rand()% (u -l +1)) + l;		//get random number is range of lower and upper
    	str.insert(num);	//insert that number to str
    }

    int* A = new int[n];	//create an array to pass all element in str to array A
    int k = 0;
    unordered_set<int> :: iterator itr;		//create an iterator to get each value in set str
	for (itr = str.begin(); itr != str.end(); itr++){	//using begin() to get first index, then loop utill last index by using end
		A[k++] = (*itr);
	}

	cout << "Randomly generated elements: ~~~~~~~~~~" << endl;
	// display the array A
	printArray(A, n);	//print array A
	cout << endl;
	cout << endl;

    // use one of the sorting algorithms with the third argument for D as n*n (for bubble sort) and store the fully sorted result 

	cout << "Completely sorted elements: ~~~~~~~~~~" << endl;
	// display the completely sorted array 
	int* A1 = bubbleSort(A, n, n*n);	//A1 is sorted array of A
	printArray(A1, n);	//print A1
	cout << endl;
	cout << endl;

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // sort the array A with only given D comparions using the Bubble Sort algorithm and store the output array as bubResult in an array
    // calculate and display the two quality measures for bubResult
    cout << "Bubble Sort Result: ~~~~~~~~~~" << endl;

    // display bubResult
    int* A2 = bubbleSort(A, n, D);	//A2 is sorted array of A bu using bubble sort
    printArray(A2, n);	//print array
	cout << endl;
	cout << endl;

    // find both the quality metrics for bubResult
	int numInver1 = inversion(A2, n);	//get number of inversion and print output
	cout << "Number of inversions in bubResult: " << numInver1 << endl;

	//start to get the cheby distance value
	int cheby1 = 0;
	for (int i = 0; i < n; i++){		//loop the array A1
		int num = 0;
		for (int j = 0; j < n; j++){ 	//loop array A2
			if (A1[i] == A2[j])			//if the element at index i in A1 equal element at index j in A2
				num = abs(i - j);		//calculate the distance with absolute value
		}
		if (num > cheby1)		//this code to find the max distance and return cheby1 value
			cheby1 = num;
	}
	cout << "Chebyshev distance in bubResult: " << cheby1 << endl;
	cout << endl;

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // sort the array A with only given D comparions using the Shell Sort algorithm and store the output array as shellResult in an array
    // calculate and display the two quality measures for shellResult
    cout << "Shell Sort Result: ~~~~~~~~~~" << endl;

    // display shellResult
    int* A3 = shellSort(A, n, D);		//A3 is sorted array of A using shell sort
    printArray(A3, n);		//print array
    cout << endl;
    cout << endl;

    // find both the quality metrics for shellResult
    int numInver2 = inversion(A3, n);	//get number  of inversion of array A3
    cout << "Number of inversions in shellResult: " << numInver2 << endl;

    //second cheby for shell sort, algorithms same as above
    int cheby2 = 0;
	for (int i = 0; i < n; i++){
		int num = 0;
		for (int j = 0; j < n; j++){
			if (A1[i] == A3[j])
				num = abs(i - j);
		}
		if (num > cheby2)
			cheby2 = num;
	}
	cout << "Chebyshev distance in shellResult: " << cheby2 << endl;
	cout << endl;

	delete A;
    return 0;
}
