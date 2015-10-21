// Author: Evan Glazer

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LENGTH 96
// Structs for Boggle Data
struct boggleDataNode {
    char data[3];
    struct boggleDataNode *nextData;
};

struct boggleDieSideNode {
    char dieSideData[3];
    struct boggleDieSideNode *nextSide;
};

// Function Prototypes
struct boggleDieSideNode *curr1Ref = NULL;
void readData(struct boggleDataNode **,struct boggleDataNode **);
void addEntry(struct boggleDataNode **,struct boggleDataNode **, char *);
void display(struct boggleDataNode *);
void displayDie(struct boggleDieSideNode *);
void sideData(struct boggleDataNode *, struct boggleDieSideNode **, int location);

// Main Function
int main() {

            int i,j;
            // Instance of struct
            struct boggleDataNode * head = NULL;
            struct boggleDataNode * curr = NULL;
            struct boggleDieSideNode *head1[16];
            readData(&head,&curr);
            display(head);

            curr=head;
            // Loop through the 16 dice of the Boggle board
            for (i=0; i<16; i++)
            {
                 //a.Reset each reference of the linked list containing the six sides of the data to create a new instance
                 head1[i]= NULL;

                 //Loop through the 6 sides of the die
                for(j=0; j<6; j++)
                {
                //i.Call the function to add a node to the
                // linked list of six sides of a die; arguments should include the linked
                // list reference of struct boggleDieSideNode, the linked list
                // reference of struct boggleDataNode, and the counter variable
                    sideData(curr,&head1[i],j);
                    curr=curr->nextData;
                //ii.Increase the counter variable

                }
                //c.Call function to display the data on the six sides of the die
                displayDie(head1[i]);
        }

        return 0;
}

void readData(struct boggleDataNode **headRef, struct boggleDataNode **currRef){
    //initializing variables including
    //opening the input file
    int counter = 96;
    int i = 0;
    char dataLine[LENGTH];
    char *data;
    char *fileName = "BoggleData.txt";
    FILE *filePointer;

   // printf("Trying to open file %s\n", fileName);
    filePointer = fopen(fileName, "r"); //read mode
    //printf("Successfully opened file %s\n", fileName);

    if (filePointer == NULL){
        perror("Error while opening file. \n");
        exit(0);
    }
char *tok;
    //loop until find end of file
    while ( fgets(dataLine, LENGTH, filePointer) != NULL){
        for (tok = strtok(dataLine, " "); tok; tok = strtok(NULL, " "))//for (char *tok = strtok(dataLine, " "); tok; tok = strtok(NULL, " "))
    {
        addEntry(headRef,currRef, tok);

    }

    }
    fclose(filePointer);

}

void addEntry(struct boggleDataNode **headRef,struct boggleDataNode **currRef, char *data){

    //allocate node
    struct boggleDataNode* temp = (struct boggleDataNode*) malloc(sizeof(struct boggleDataNode));

    //put in data
    strcpy(temp->data, data);

    // link the old list off the new node
  //  temp->nextData = (*headRef);

//Correction

if(*headRef==NULL)
{
    (*headRef) = temp;
    (*currRef)= temp;
    temp->nextData=NULL;
}
    // move the curr to point to the new node
    else {
        (*currRef)->nextData= temp;
        (*currRef)=temp;
    }

}

void display(struct boggleDataNode *headRef){

    struct boggleDataNode *helper = headRef;
    // if head is null then nothing
    if (helper == NULL){
        return;
    }
    // else display
    else{
        printf(" **** Displaying Boggle Data **** \n");

        int counter = 0;

        while (helper != NULL){
            printf("Data value %d :  %s", counter++, helper->data);
            printf("\n");
            helper = helper->nextData;

        }
    }
    //system("pause");
}

void sideData(struct boggleDataNode *temp, struct boggleDieSideNode **head1, int location)
{
    //allocate node
    struct boggleDieSideNode* tempo = (struct boggleDieSideNode*) malloc(sizeof(struct boggleDieSideNode));

    //put in data

    strcpy(tempo->dieSideData,temp->data);

if((*head1)==NULL && location==0)
    {
        (*head1) = tempo;
        curr1Ref=tempo;

        }
    else
    {
        curr1Ref->nextSide=tempo;
        curr1Ref=tempo;

    }

    // link the old list off the new node
//    tempo->nextSide = (*head1);

    // move the head to point to the new node
  //  (*head1) = tempo;
}


void displayDie(struct boggleDieSideNode *head1)
{
    // Traverse the linked list and display the data portion of each node to the screeen
    struct boggleDieSideNode *helper1 = head1;

    if (helper1 == NULL){
        return;
    }
    else{
        printf(" **** Displaying Die Side Data **** \n");

        int counter = 0;

        while (helper1 != NULL){
            printf("Side value %d :  %s", counter++, helper1->dieSideData);
            printf("\n");
            helper1 = helper1->nextSide;

        }
    }
    system("pause");
}
