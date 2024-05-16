#include <stdio.h>
#include <stdlib.h>


typedef struct LogEntry
{
    int lineCode;
    int productID;
    int issueCode;
    int day;
    int hour;
    int minute;

} LogEntry;


typedef struct item
{
    int issueCode;
    int productID;
    struct item* next;

} item;


typedef struct pointerList
{
    item* slots[5000]; // mKINg an array to act as slots for my output table

} pointerList;

void initialiseList(pointerList* list); // function that initialises the list of pointers to null
void insertParts(pointerList* list, int productId, int lineCode, int issueCode); // function to put issue code into the linked lists
void printReport(pointerList* list); // function that prints the line report in task 2
void merge(LogEntry arr[], int leftIndex, int midIndex, int rightIndex); //another function to merge the 2 subarrays
void mergeSort(LogEntry arr[], int leftIndex, int rightIndex); // function to sort array by splitting it into 2 subarrays
int findFirstOccurrence(LogEntry logs[], int numLogs, int issueCode); //function to complete task 3 of finding earliest occurance of an issue code
void issueReport(LogEntry logs[], int numLogs); //function to make a report summary of the isssues counted on the product ID

int main()
{
    int logNum;
    int codeTarget;
    int firstIndex;
    int i;
    int j;

    pointerList list; //variable with the outputTable structure
    initialiseList(&list); // calls function to make the table and set all the slots to nulls


    //array of sample log data
    LogEntry logs[] =
            {{1, 12, 402, 15, 16, 30},
             {1, 14, 402, 9, 6, 15},
             {1, 15, 403, 16, 9, 45},
             {1, 12, 403, 21, 13, 30},
             {1, 13, 404, 17, 13, 45},
             {1, 13, 405, 19, 12, 30},
             {2, 21, 405, 12, 8, 30},
             {2, 23, 406, 13, 12, 45},
             {2, 22, 407, 17, 15, 45},
             {2, 22, 408, 15, 16, 0},
             {2, 23, 408, 16, 14, 30},
             {2, 24, 409, 14, 10, 15},
             {3, 34, 410, 22, 11, 15},
             {3, 35, 412, 20, 9, 30},
             {3, 32, 413, 21, 13, 45},
             {3, 31, 414, 23, 15, 0},
             {3, 34, 414, 25, 11, 45},
             {3, 33, 416, 24, 10, 30},
             {4, 41, 418, 26, 14, 45},
             {4, 43, 419, 28, 17, 0},
             {4, 42, 421, 27, 12, 15},
             {4, 42, 423, 25, 9, 30},
             {4, 44, 423, 31, 10, 45},
             {4, 41, 424, 29, 11, 30}
            };

    logNum = sizeof(logs) / sizeof(logs[0]); // getting the number of logs by getting the total size of the logs array and then dividing it by one of its elements

    /*
     *
     * Task 1
     *
     * */

    mergeSort(logs, 0, logNum - 1); // calling sorting function and passing logs array, and the indexes to that function

    // loop to print the sorted logs by line
    for (i = 1; i < 5; ++i)
    {//start for

        printf("Logs: Line %d\n", i);
        for (j = 0; j < logNum; ++j)
        {//start for

            if (logs[j].lineCode == i)
            {// start if

                printf("Product ID: %d, Issue Code: %d, Date and Time: %d:%02d:%02d\n", logs[j].productID, logs[j].issueCode, logs[j].day, logs[j].hour, logs[j].minute);

            }//end if

        }// end for
        printf("\n");

    }//end for

    /*
     *
     * task 2
     *
     * */

    //For loop to put the product IDs, line codes, and issue cades into the linked lists
    for (i = 0; i < logNum; ++i)
    {//start for
        insertParts(&list, logs[i].productID, logs[i].lineCode, logs[i].issueCode);
    }//end for


    printReport(&list); //calling function to print reprort for task 2


    /*
     *
     * Task 3
     *
     * */

    printf("Please enter the issue code that you would like to search for: ");//print statement to ask user to enter what issue code they are looking for
    scanf("%d", &codeTarget); // scans user input for what they are looking for into variable

    firstIndex = findFirstOccurrence(logs, logNum, codeTarget); //The return value of the function to find the earliest occurence of an issue code goes into the variable

    if (firstIndex != -1)
    {
        printf("Earliest occurrence of issue code %d found at index %d\n", codeTarget, firstIndex);
        printf("Product ID: %d, Issue Code: %d, Date and time: %d-%02d %02d\n", logs[firstIndex].productID, logs[firstIndex].issueCode, logs[firstIndex].day, logs[firstIndex].hour, logs[firstIndex].minute);
    }
    else
    {
        printf("Issue code %d not found\n", codeTarget);
    }

    /*
     *
     * task 4
     *
     * */


    issueReport(logs, logNum); //calling function to make a summary report of reported issues per product ID

    return 0;
}

/*
 *
 * Task 1
 *
 * */

// Recursive function that sorts an array by dividing the array into smaller sub arrays then merging them by calling the merge function
void mergeSort(LogEntry array[], int leftIndex, int rightIndex)
{
    int midIndex;
    if (leftIndex < rightIndex)
    {
        midIndex = leftIndex + (rightIndex - leftIndex) / 2;
        mergeSort(array, leftIndex, midIndex);
        mergeSort(array, midIndex + 1, rightIndex);
        merge(array, leftIndex, midIndex, rightIndex);
    }
}


// Function that merges 2 sub arrays that have been sorted. It goes through the arrays, compares the elements and adds the elements into a single array that is sorted
// left sub array is array[leftSubIndex -> midSubIndex]. right sub array is array[midSubIndex + 1 -> rightSubIndex]
void merge(LogEntry array[], int leftIndex, int midIndex, int rightIndex)
{

    int leftSubNum = midIndex - leftIndex + 1;
    int rightSubNum = rightIndex - midIndex;
    int i = 0;
    int j = 0;
    int k = leftIndex;

    LogEntry leftSubArray[leftSubNum]; //creating left sub array
    LogEntry rightSubArray[rightSubNum]; //creating right sub array

    // Loop to copy data into the left temporary array
    for (int i = 0; i < leftSubNum; i++)
    {//start for

        leftSubArray[i] = array[leftIndex + i];

    }//end for

    //Loop to copy data into the right temporary array
    for (int j = 0; j < rightSubNum; j++)
    {//start for

        rightSubArray[j] = array[midIndex + 1 + j];
    }//end for

    //Loop to merge 2 subarrays into 1 sorted array
    while (i < leftSubNum && j < rightSubNum)
    {//start while
        if (leftSubArray[i].productID <= rightSubArray[j].productID)//
        {//start if
            array[k] = leftSubArray[i];
            i++;
        }//end if
        else
        {//start if
            array[k] = rightSubArray[j];
            j++;
        }//end if
        k++;

    }//end while

    // Loop to copy any remaining elements of the left sub array
    while (i < leftSubNum)
    {//start while
        array[k] = leftSubArray[i];
        i++;
        k++;
    }//end while

    // Loop to copy any elements that might remain from the right sub array
    while (j < rightSubNum)
    {//start while
        array[k] = rightSubArray[j];
        j++;
        k++;
    }//end while
}



/*
 *
 * task 2
 * */


// A funtion to set all the slots in the list of pointers to nulls so we can put stuff in there
void initialiseList(pointerList * list) //fuction takes pointer to structure
{
    //loop to put each slot to null
    for (int i = 0; i < 5000; ++i)
    {//start for

        list->slots[i] = NULL; //each place in the slots array is assigned to null

    }//end for
}



// Function to put issue code into table
void insertParts(pointerList * list, int productID, int lineCode, int issueCode)
{
    int index = (productID * 10) + lineCode; // Calculate the index based on product ID and assembly code to distribute the entries evenly and prevent overlapping
    item* newItem;
    item* temp;

    newItem = (item*)malloc(sizeof(item)); //the size of item is calculated, then malloc allocates the memory dynamically and the pointer returned by malloc is cast as the item structure and stored in newItem

    newItem->productID = productID; //productID variable of newItem structure is assigned value from productId parameter
    newItem->issueCode = issueCode; // issueCode varible of the newItem structure is assigned value from the issueCode function parameter
    newItem->next = NULL; // next member of the newItem structure is set to null

    //block to add items to linked list
    if (list->slots[index] == NULL) //this if statement checks if the slots array at the calculated index is a null
    {//start if
        list->slots[index] = newItem; // if the space is a null then the newItem structure and its contents will be added to the slots array at that index
    }//end if
    else // if the slots member of the table structure is not a null
    {//start if
        temp = list->slots[index]; //temp variable is assigned to that space of the linked list

        //loop to go through the linked list and move temp through the list until it finds a null
        while (temp->next != NULL) //loop keeps going until temp is null
        {//start while
            temp = temp->next; //temp goes through the list until it comes across a null
        }//end while


        temp->next = newItem; //value of newItem is put to where temp was when it came across a null
    }//end if
}

// Function to print the report for Task 2
void printReport(pointerList * list)
{
    int i;
    item* current;

    printf("\n\tReport: Issue Codes by Product ID and Line ID\n\n");

    //block to print the report
    for (i = 0; i < 5000; ++i) //for loop that goes through slots array that contains pointers
    {//start for
        current = list->slots[i]; //current is assigned the product id and issue code pointers in the slots array at index i
        while (current != NULL)//loop that keeps going until the current is a null which signifies the end of the linked list
        {//start while
            printf("Line Code: %d, Product ID: %d, Issue Code: %d\n", i % 10, current->productID, current->issueCode);
            current = current->next; //current is set to the next pointers for product id and issue code
        }//end while
    }//end for
}

/*
 *
 * Task 3
 *
 * */

// A function to find the earliest occurrence of an issue code using a binary search
int findFirstOccurrence(LogEntry logs[], int numLogs, int issueCode)
{
    int leftIndex = 0;
    int midIndex;
    int rightIndex = numLogs - 1;
    int earliestIndex = -1;

    while (leftIndex <= rightIndex)
    {//start while
        midIndex = leftIndex + (rightIndex - leftIndex) / 2; //calculating middle index. this way prevents overflow

        if (logs[midIndex].issueCode == issueCode)// if statement to check if the issuecode variable in the logs array at the middle index is equal to the issue code it is searching for
        {//start if
            earliestIndex = midIndex; //return value is set at as the middle index
            return earliestIndex; //earilest index is returned and the loop is broken
        }//end if
        else if (logs[midIndex].issueCode < issueCode)
        {//start else if
            leftIndex = midIndex + 1;
        }//end else if
        else
        {//start ele
            rightIndex = midIndex - 1;
        }//end else
    }//end while

    return earliestIndex;
}

/*
 *
 * Task 4
 *
 * */

// Function to generate a summary report of the number of issues reported for each product in task 4
void issueReport(LogEntry logs[], int numLogs)
{
    int productNums[1000] = {}; //making array for the report
    int i;

    printf("Report ; The amount of issues reported for each product\n");

    // Loop to count the number of issues for each product
    for (i = 0; i < numLogs; i++)
    {// start for
        productNums[logs[i].productID]++;//incrementing the count of issues that are reported for each product
    }//end for

    // Loop to print the report of number of issues per product
    for (i = 0; i < 1000; ++i)
    {//start for
        if (productNums[i] > 0)
        {//start if
            printf("Product ID: %d,, Number of Issues Reported: %d\n", i, productNums[i]);
        }//end if
    }//end for
}
