


#include <stdlib.h>
#include <stdio.h>
#include<string.h>

struct Node {
    //In order to have multiple linked lists, each node will have a Head and Tail that is Binary.
    //A Head node will have its head point to itself and so will a Tail node. Otherwise the Node Head
    //or Tail will point to NULL  
 
    char age[25];
    char fname[25];
    char lname[25];
    char birthDate[11];
	struct Node *next;
    struct Node* Head;
    struct Node* Tail;
};



//This function is meant to be private.
struct Node* _CreateNode(char fname[25], char lname[25], char age[25], char dob[11]){

    struct Node *curNode=(struct Node*) malloc (sizeof(struct Node));
    strcpy(curNode->fname, fname);
    strcpy(curNode->lname, lname);
    strcpy(curNode->birthDate, dob);
    strcpy(curNode->age,age);
    curNode->next=NULL;
    curNode->Head=NULL;
    curNode->Tail=NULL;
    return curNode;
    
}

//Since this adds a tail it needs a previous node to work, be it an different tail or node
struct Node* AddTail(struct Node* oldTail,char fname[], char lname[],char age[] ,char dob[])
{
	if (oldTail == NULL)
	{
		printf("A previous node is required");
		exit(0);
	}
	
    struct Node* newNode;
    
    newNode=_CreateNode(fname, lname,age, dob);
    
    if(oldTail->Tail!=NULL)
        {
            oldTail->next=newNode;
            oldTail->Tail=NULL;
            newNode->Tail=newNode;
            return newNode;
        }
	else if(oldTail->Tail = NULL)
	{
		oldTail->next = newNode;
		newNode->Tail = newNode;
		return newNode;
	}
            
           
        
    
}

//New Head either creates a new Head on its one or adds one to a different head. 
struct Node* NewHead(struct Node* oldhead , char fname[25], char lname[25], char age[2], char dob[11])
{
    
    struct Node* newNode;
    newNode=_CreateNode(fname, lname,age, dob);
	if (oldhead == NULL)
	{
		newNode->Head = newNode;
		newNode->Tail = newNode;
		return newNode;
	}
    
    if (oldhead->Head!=NULL)
        {
            newNode->next=oldhead;
            oldhead->Head=NULL;
            newNode->Head=newNode;
            return newNode;

        }
	
}


//This function could be used to create a new head for a linked list or extend an existing one.
//by adding the new node to any point of a linked list.
//It provides a wide user error margin by creating Head Nodes and Tail Nodes where needed. 
struct Node* AddNode(struct Node* prevNode, char fname[25], char lname[25],char age[2], char dob[11]){
   
    if(prevNode==NULL)
        {
		struct Node* new_node = NewHead(NULL, fname, lname,age, dob);
			return new_node;
       
        }
    else{
            if(prevNode->Tail!=NULL)
            {
				struct Node* new_node = AddTail(prevNode,fname, lname,age, dob);
                return new_node;
            }
            
            if(prevNode->Tail==NULL)
            {
				struct Node* new_node = _CreateNode(fname, lname,age, dob);
                new_node->next=prevNode->next;
                prevNode->next=new_node;
                return new_node;
            }
        
            
        }
       
}



//In order to delete a non-Head node, the previous node is required so this function provides it.
struct Node* _FindNodeBefore(struct Node* curNode,char fname[], char lname[],char age[], char dob[])
{   

    if(curNode->Head!=NULL) 
    {
      
        while (curNode->next!=NULL)
        { 

            if (strcmp(curNode->next->fname,fname)==0)
            {
        
                 if (strcmp(curNode->next->lname,lname)==0)
                     {
                         if (strcmp(curNode->next->birthDate,dob)==0)
                             {
                                 return curNode;
                             }
                         else 
                             {
                                 curNode=curNode->next;
                              }
           
                     }
                 else 
                        {
                            curNode=curNode->next;
                        }           
            }
            
            else 
                {
                    curNode=curNode->next;
                }
             
           
        } 
        
    }    
}


//This provides a 0 as 'True' and 1 as 'False' due in lie of Boolean values.
int SearchNode(struct Node* current,char fname[], char lname[],char age[], char dob[])
{
    if(current->Head!=NULL) 
    {    
        while (current!=NULL)
        { 
            if (strcmp(current->fname,fname)==0)
            {      
                 if (strcmp(current->lname,lname)==0)
                     {
                         if (strcmp(current->birthDate,dob)==0)
                             {
                                 return 0;
                             }
                         else 
                      
       {
                                 current=current->next;
                              }
           
                     }
                 else 
                        {
                            current=current->next;
                        }           
            }
            
            else 
                {
                    current=current->next;
                }
             
           
        } 
        return 1;        
    }  
	printf("Need to put in a head node");
	exit(0);
}
        
void PrintList(struct Node* head){
    
    if(head->Head!=NULL)
    {
         struct Node* curNode = head;

        while (curNode!= NULL) {
        printf("First Name= %s, Last name= %s, Date of Birth = %s\n",curNode->fname,
        curNode->lname,
        curNode->birthDate);
        curNode=curNode->next;
                                }
   
    
    }


}

//This function is used in case the node being deleted is a Head Node.
void _pDeleteNodeAfter(struct Node* previous)
{
    struct Node* curNode=previous->next;


	if (curNode->Tail!=NULL)
	{
		previous->Tail = previous;
		curNode->Tail = NULL;
		free(previous->next);
		previous->next=NULL;
		curNode=NULL;
		
	}

	else
	{
		struct Node* temp = curNode->next;
		curNode->next = NULL;
		free(previous->next);
		previous->next=temp;
		temp=NULL;
		curNode=NULL;
		

	}


}
//This function is available to a user and will delete any Node.
void DeleteNode(struct Node* head, char fname[], char lname[], char age[],char birthDate[])
{

	if (SearchNode(head, fname, lname,age, birthDate) == 0)
	{
	    if(head->next!=NULL)
	    {
	   
		struct Node* previous =_FindNodeBefore(head, fname, lname,age, birthDate);
	
		_pDeleteNodeAfter(previous);
	    }
	    
	    else
	    {
	       
	       head->Tail=NULL;
	       head->Head=NULL;
	     
	       free(head);
	    
	       head=NULL;
	 
	      
	    }
	}
}



void main() {
    
     
     struct Node* x= AddNode(NULL,"Bob", "Kelso","12", "12/01/1998");
 
     struct Node* z= NewHead(x,"JKS","agjAY","1","12/01/1998");
     
     struct Node* y=AddNode(x,"Charles","Dickens","22","12/01/1998");
     
    
     
     struct Node* as=AddTail(y,"Bowsette","Smash","21","12/01/1998");
     PrintList(z);
    

    
	 DeleteNode(z,"Charles","Dickens","22","12/01/1998");
	 DeleteNode(z,"Bob", "Kelso","12","12/01/1998");
	 DeleteNode(z,"Bowsette","Smash","21","12/01/1998");


	 DeleteNode(z,"JKS","agjAY","1","12/01/1998");
	 
	 PrintList(z);
	 free(x);
	 free(z);
	 free(y);
	 free(as);
	 x=NULL;
	 z=NULL;
	 y=NULL;
	 as=NULL; 

   
    

     
    
  
    
    

