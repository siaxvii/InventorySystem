//Lasya Yakkala - IQY403
//Systems Programming CS 3424-0C1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assign4.h"

int main(int argc, char *argv[]) {
    
    //Initializing file pointer
    FILE* fileIn;
    
    //Initializing course file 
    char* input = "courses.dat";
    
    //Setting file pointer to open the file to read and write the binary file
    fileIn = fopen(input, "rb+");
    
    //Creates and writes to file if it doesn't already exist
    if(fileIn == NULL) {
        fileIn = fopen(input, "wb+");
    }

    //while loop condition
    int t = 1;
    
    //initializing user input (characters) character array
    char user[3];
    
    //Main loop that prompts user for selecting menu options
    while(t){
	//Prints menu options
        printf("Enter one of the following actions or press CTRL-D to exit.\n");
        printf("C - create a new item\n");
        printf("U - update an existing item\n");
        printf("R - read an existing item\n");
        printf("D - delete an existing item\n");
        
	//Prompts user for character
        fgets(user, 3, stdin);
        
	//Breaks if there is no more input
        if(feof(stdin)) break;
        
	//If user selects "c", jumps to create function
        if(user[0] == 'c' || user[0] == 'C'){
            create(fileIn);
	        //Clears the extra \n from stdin
        }
        
	//If user selects "u", jumps to update function
        else if(user[0] == 'u' || user[0] == 'U'){
            update(fileIn);
	    
        }
        
	//If user selects "r", jumps to read function
        else if(user[0] == 'r' || user[0] == 'R'){
            read(fileIn);
           
        }

        
	//If user selects "d", jumps to delete function
        else if(user[0] == 'd' || user[0] == 'D'){
            fdelete(fileIn);
	    
        }
	
	//Else, lets the user know that it was wrong input
        else {
            printf("invalid input\n");        
        }
        
    
    } 
    
    //closes the file pointer once finished using
    fclose(fileIn);
    
    return 0;
}    


void create(FILE* courseFile){
    int numCourse = 0;     //course number variable initialized
    
    //allocates memory for the course
    COURSE* read = (COURSE*)calloc(1, sizeof(COURSE));
    
    //Prompts user for course number
    printf("Enter a CS Course Number: ");
    scanf("%d", &numCourse);
    getc(stdin);
    printf("\n");
    
    //goes to the course in the binary file and reads it
    fseek(courseFile, numCourse*sizeof(COURSE), SEEK_SET);
    fread(read, sizeof(COURSE), 1, courseFile);
    
    //If the course exists, prints the error statement
    if(read->hours != 0){
        printf("ERROR: the course entered already exists.\n");
        return;
    }
    

    //Prompts for course credentials below
    printf("Enter a course name: ");
    scanf(" %[^\n]", read->name);

    printf("Enter a course schedule: ");
    scanf(" %s", read->schedule);
    
    printf("Enter number of course credit hours: ");
    scanf(" %u", &(read->hours));

    printf("Enter number of students enrolled in course: ");
    scanf(" %u", &(read->size));
    getc(stdin);

    //Goes back to the position of the course
    fseek(courseFile, numCourse*sizeof(COURSE), SEEK_SET);
    fwrite(read, sizeof(COURSE), 1, courseFile);
    
    free(read);
    
}


void update(FILE* courseFile){
    int numCourse = 0;
    
    //Allocates memory for the course
    COURSE* read = (COURSE*)calloc(1, sizeof(COURSE));
    
    //Initialize variables to hold user inputted values
    char userName[80];
    char userSched[4];
    unsigned userHours;
    unsigned userSize;

    //allocates memory for the user entered values into a buffer
    char* buf = malloc(sizeof(char)*80);
    
    printf("Enter a course number: \n");
    scanf("%d", &numCourse);
    getc(stdin);    //Clears newline left over in buffer

    //Seeks to the position of the course and reads it
    fseek(courseFile, numCourse*sizeof(COURSE), SEEK_SET);
    fread(read, sizeof(COURSE), 1, courseFile);


    //If the course doesn't exist, prints out an error statement
    if(read->hours == 0){
        printf("ERROR: Course does not exist.\n");
	free(read);
        return;
    }
    else{  //Otherwise, goes in to update each individual course attribute
            
        printf("Enter a course name: ");
        fgets(buf,80,stdin); //Prompts user for course name
	buf[strlen(buf)-1] = '\0'; //replaces newline with null
        if(strcmp(buf, "\n") != 0){  //Ensures that it isn't a newline
            strcpy(read->name, buf); //copies user input into course attribute 
        }
    
        printf("Enter a course schedule: ");
        fgets(buf, 4, stdin);
        if(strcmp(buf, "\n") != 0){
            strcpy(read->schedule, buf);
        }
        
        printf("Enter number of course credit hours: ");
        fgets(buf, 80, stdin);
        if(strcmp(buf, "\n") != 0){
            read->hours = atoi(buf);
        }
    
        printf("Enter number of students enrolled in course: ");
        fgets(buf, 80, stdin);
        if(strcmp(buf, "\n") != 0){
            read->size = atoi(buf);
        }
    }
    
    //Goes back to the position of the course
    fseek(courseFile, numCourse*sizeof(COURSE), SEEK_SET);
    fwrite(read, sizeof(COURSE), 1, courseFile);
    free(read);
    
}


//Reads attributes of an already existing course
void read(FILE* courseFile){
    int numCourse = 0;
    
    //allocating memory for the current course
    COURSE* read = (COURSE*)calloc(1, sizeof(COURSE));
    
    //Prompts user for course number
    printf("Enter a CS Course Number: ");
    scanf("%d", &numCourse);
    getc(stdin);    

    //Searches for the particular course in the binary file and reads it
    fseek(courseFile, numCourse*sizeof(COURSE), SEEK_SET);
    fread(read, sizeof(COURSE), 1, courseFile);
    
    //If course isn't there
    if(read->hours == 0){
        printf("ERROR! Could not find the course.\n");
        return;
    }
            
    //Prints all attributes of the course
    printf("   Course number: %d\n", numCourse);
    printf("   Course name: %s\n", read->name);
    printf("   Scheduled days: %s\n", read->schedule);
    printf("   Credit hours: %u\n", read->hours);
    printf("   Enrolled students: %u\n\n", read->size);
    
    free(read);
}

//delete function has the logic for deleting an item that already exists
//user can enter the course number for the course they wish to delete
void fdelete(FILE* courseFile){
    //Initializes variable for the course number
    int numCourse = 0;
    
    //allocates memory for the course
    COURSE* read = (COURSE*)calloc(1, sizeof(COURSE));

    //Prompts the user for the course number
    printf("Enter a course number: ");
    scanf("%d", &numCourse);
    getc(stdin);
    printf("\n");

    //seeks to the course in the binary file and reads it
    fseek(courseFile, numCourse*sizeof(COURSE), SEEK_SET);
    fread(read, sizeof(COURSE), 1, courseFile);
    
    //If the user inputted course number has zero hours
    //i.e., the course doesn't exist, it will print an error statement
    if(read->hours == 0){
        printf("ERROR: course not found.\n");
        return;
    }
    else{   //otherwise, it will set the number of hours of that course to 0
        read->hours = 0;
        printf("%d was successfully deleted.\n", numCourse);
    }
    
    //goes back to the course number position
    fseek(courseFile, numCourse*sizeof(COURSE), SEEK_SET);
    fwrite(read, sizeof(COURSE), 1, courseFile);
    free(read);
    
}
