#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

struct node{
    int data;
    struct node *next;
    struct node *prev;
    
};

struct node *head = NULL;


void insertAtBeginning(int data){
    struct node *newNode;
    newNode = malloc(sizeof(struct node));
    newNode -> data = data;
    newNode ->next = head;
    newNode ->prev = NULL;
    head = newNode;
}


void insertAtEnd(int data){

    struct node *newNode;
    newNode = malloc(sizeof(struct node));
    newNode ->data = data;
    newNode ->next = NULL;

    struct node *temp = head;

    while(temp ->next != NULL){
        temp = temp ->next;
    }
    temp ->next = newNode;
}


void insertAfter(int data, int previous){
    struct node *newNode;
    newNode = malloc(sizeof(struct node));
    newNode ->data = data;

    struct node *currentNode = head;
    while(currentNode != NULL && currentNode->data != previous){
        currentNode = currentNode ->next;
    }

    if(currentNode != NULL){
        newNode ->next = currentNode->next;
        currentNode ->next ->prev = newNode;
        currentNode ->next = newNode;
        newNode ->prev = currentNode;
    }

}

void deleteByValue(int data){
    struct node *currentNode = head;
    struct node *prevNode = NULL;

    if(currentNode->data == data){
        head = head ->next;
        head ->prev = NULL; 
        return;
    }

    while(currentNode != NULL){
        if(currentNode->data == data){
            prevNode ->next = currentNode->next;
            currentNode->next->prev = prevNode;
            break;
        }

        prevNode = currentNode;
        currentNode = currentNode -> next;
    }
}



void printList(){
    
    struct node *temp = head;
    printf("printing the list\n");

    while(temp!= NULL){
        printf("%d ", temp->data);
        temp = temp -> next;
        
    }
    

}



int main(){
    
    char c[47];
    char d[47],a[47];
    int j=0, size=0 ,*arr, press= 11, value, prev;

    arr = (int*)malloc(3*sizeof(int));
    FILE *fptr1 = fopen("source.txt","r+");
    FILE *fptr2 = fopen("source.txt","r+");
    int fd1 = open("source.txt", O_RDONLY);
    int fd2 = open("source.txt", O_RDONLY);

    while(fgetc(fptr1)!= EOF){
        read(fd2,d,1);
        fscanf(fptr2,"%d",&arr[j]);
        j++;
        size++;
    }
    

    for(int i=0;i<4;i++){
        if(head == NULL){
            insertAtBeginning(arr[i]);
        }else{
            insertAtEnd(arr[i]);
        }
        
        
        
    }
    
    while(press !=0){
    printList();
    printf("\npress 1 for insurt a new node");
    printf("\npress 2 for insert a new node between two nodes");
    printf("\npress 3 for delete node");
    printf("\npress 0 for exit\n");

    scanf("%i",&press);
    if(press ==1){
        printf("Insert your node data");
        scanf("%i",&value);
        insertAtEnd(value);

        printf("\n");
        printList();
    }
    else if(press == 2){
        printf("Insert your new node data ");
        scanf("%i",&value);
        printf("Insert your previous data ");
        scanf("%i",&prev);
        insertAfter(value,prev);

        printf("\n");
        printList();
        
    }
    else if(press == 3){
        printf("Insert the node number you want to delete ");
        scanf("%i",&value);
        deleteByValue(value);

        printf("\n");
        printList();

    }
    }
    
    close(fd1);
    close(fd2);
    fclose(fptr1);
    

    return 0;
}