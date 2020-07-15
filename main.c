//Listing 15.7 A program the reads lines of text from the keyboard, sorts them alphabetically,
// and displays the sorted text; page 377

//NOTE: THIS METHOD OF SORTING IS VERY INEFFICIENT!

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 25

int get_lines(char *lines[]); //array of pointers
void sort(char *p[], int n);  //passes in an array of pointers and an integer
void print_strings(char *p[], int n);  //passes in an array of pointers and an integer

char *lines[MAXLINES]; //declares an array of 25 pointers and is GLOBAL

int counter = 0; //for testing purposes

int main(void)
{
    int number_of_lines;
    //read from keyboard
    number_of_lines = get_lines(lines);

    if (number_of_lines<0)
    {
        puts("\n** Memory allocation error **");
        exit(-1);
    }

    printf("\n**********************************************");
    printf("\n********   For testing purposes     **********");
    printf("\n********   (Before sorting data)    **********");
    printf("\n**********************************************");

    for(counter=0; (counter<MAXLINES && lines[counter]!='\0'); counter++)  //for testing purposes
        printf("\n%s",lines[counter]);                                    // to see how stored in array
                                                                          //before sort

    sort(lines,number_of_lines);
    printf("\n\n**********************************************");
    printf("\n********   (After sorting data)     **********");
    printf("\n**********************************************\n");
    print_strings(lines,number_of_lines);
    printf("\n");
    return 0;

}

int get_lines(char *lines[])
{
    int n = 0;
    char buffer[80];  // temporary storage for each line

    puts("\nEnter one line at a time; enter a blank when done.");

        //Execute loop while max number of lines NOT input, execute the gets()
        // function to read the input data, verify that eof or other file error
        // has not occurred, and also verify that the first line of input is not
        // the null character which would indicate that a blank line was entered
    while((n<MAXLINES) && (gets(buffer)!= 0) && (buffer[0]!='\0'))
    {
        //dynamically allocates space by calling malloc() function to store the
        // string that was just input. If malloc returns NULL, the if loop
        // returns execution to the calling pgm with a return value of -1. Otherwise the
        // pointer that malloc returns (malloc always returns a pointer to the space
        // allocated) is assigned to the array of pointers (lines[])... so you know where
        // the first line was stored...
        //
        //see page 377,378,379 pink for more info...
        //    1.Call malloc() to allocate space for string just read... using length of buffer+1
        //       for allow for terminating null character on end of each string...
        //    2.(char *) is a typecase that specifies the type of the pointer to be returned by
        //     malloc() - in this case char...
        //    3.The part of the statement lines[n]=(char *)malloc(strlen(buffer+1) assigns
        //       the pointer returned from malloc() to lines[n]
        //    4.THEN, it checks to see if malloc() returned a NULL and if it did, the loop exits
        //       with a return value of -1
        //    NOTES: ALWAYS PAY ATTENTION TO PARENTHESIS BECAUSE THAT'S HOW THE ORDER
        //      OF EXECUTION FROM ABOVE WORKS HERE -- EVERYTHING ON "LEFT" IS DONE FIRST
        //      AND ***THEN*** IT'S CHECKED TO SEE IF IT'S NULL!!!!
        //
        if((lines[n] = (char *)malloc(strlen(buffer)+1)) == NULL)
            return -1;
        strcpy(lines[n++],buffer);
    }
    return n; //returns the number of lines entered
} //end of get_lines

void sort(char *p[], int n)
{
    int a, b;
    char *temp;

    // not sure about a<n test here
    for(a=1; a<n; a++)
    {
        //step through array of pointers
        for(b=0; b<(n-1); b++)
        {
            //if first string > second string, switch the pointers around
            //in the array of pointers to effectively "sort" the strings of data..
            // **p[b] is the address of the first string; p[b+1] is the address of
            //   the second string; strcmp is comparing the strings of data
            //   stored at each of these addresses - ie. the "contents" at the addresses
            if(strcmp(p[b], p[b+1]) > 0)
            {
                //switch the pointers around
                temp = p[b];
                p[b] = p[b+1];
                p[b+1] = temp;
            }
        }
    }
}

void print_strings(char *p[], int n) //n is the number of strings input
{
    int count;

    for(count=0; count<n; count++)
    {
        printf("%s\n",p[count]);
    }
}
