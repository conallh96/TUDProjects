//Conall Hunt C17344203
#define _CRT_SECURE_NO_WARNINGS
#define bool int
#define false 0
#define true (!false)


//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>



//Book Structure
struct Book {
	char id[15];
	char name[30];
	char author[30];
	int year;
	bool avail;
	char custId[100];
	int pop;
};

//Stucture for LinearNode
struct LinearNode {
	struct Book *element;
	struct LinearNode *next;
};


// Function prototypes
void menu(); //Main menue for program 
void addBooks();  //adding books to end of the list
void viewBooks();//display all books
void deleteBooks(char anID[15] ); // delete a specific book
void searchBooks(char aName[100]); //search for a particular book
void borrowBooks();// borrow a book if available
void returnBooks();// return a book
void popBooks();// display most and least polular books
bool isEmpty();// check if library is empty 
void saveToFile(FILE *);//save nodes of books to file
void getFromFile(FILE *);//load books from file
void learnMore();//online database of books




// Global Variables
struct LinearNode *front = NULL;
struct LinearNode *last = NULL;
int menuSelect;// menu selection
int length;

FILE *fp;


/**************MAIN FUNCTION*******************/
int main() {
	

	if ((fp = fopen("Z:library.dat", "rb")) == NULL) {

		//file doesn't exist so get user to input books
		printf("Welcome, please enter details of the first library book.");
		addBooks();
		menu();//run menu as normal
	}
	else {
		getFromFile(fp);//load books 
		menu();
		
	}

}


/**********ADD THREE NODES TO THE LIST******************/
// Each new node is added to the end of the list

void addBooks() {




	struct LinearNode *aNode, *current;// initialise nodes
	struct Book *anElement;
	bool notFound = true;
	
	anElement = (struct Book *)malloc(sizeof(struct Book));

	if (anElement == NULL)
		printf("Error - no space for the new element\n");
	else
	{

		

		fflush(stdin);
		getchar();
		do {


			printf("\nEnter an id for Book: ");
			fgets(anElement->id, 15, stdin);
			length = strlen(anElement->id);


			current = front;

			while (notFound && current != NULL) {
			if (strcmp(anElement->id, current->element->id) == 0)
				notFound = false;
			current = current->next;
		}
			
			 if (notFound == false) {
				 printf("Book ID must be unique!\n");
			 }
				if ( isdigit(anElement->id[0]) == 0 || isdigit(anElement->id[1]) == 0 || isdigit(anElement->id[2]) == 0 || isdigit(anElement->id[3]) == 0 || isdigit(anElement->id[5]) == 0 || isdigit(anElement->id[6]) == 0 || isdigit(anElement->id[7]) == 0 || isdigit(anElement->id[8]) == 0 || anElement->id[4] != '-')
					printf("Book ID must be a number in the format XXXX-XXXX");
	
			} while (notFound == false || isdigit(anElement->id[0]) == 0 || isdigit(anElement->id[1]) == 0 || isdigit(anElement->id[2]) == 0 || isdigit(anElement->id[3]) == 0 || isdigit(anElement->id[5]) == 0 || isdigit(anElement->id[6]) == 0 || isdigit(anElement->id[7]) == 0 || isdigit(anElement->id[8]) == 0 || anElement->id[4] != '-' );



			printf("Enter a name for Book: ");
			fgets(anElement->name, 30, stdin);




			printf("Enter an author for Book: ");
			fgets(anElement->author, 30, stdin);



			do {
				printf("Enter a year of publication for Book: ");
				scanf("%d", &anElement->year);
				if (anElement->year < 2008) {
					printf("You can not add a book older than 2008\n");
				}
			} while (anElement->year < 2008);


			anElement->avail = true;
			anElement->pop = 0;







			// create space for new node that will contain data
			aNode = (struct LinearNode *)malloc(sizeof(struct LinearNode));

			if (aNode == NULL)
				printf("Error - no space for the new Book!\n");
			else { // add book to the node
				aNode->element = anElement;
				aNode->next = NULL;

				//add book to end of the list
				if (isEmpty())
				{
					front = aNode;
					last = aNode;
				}
				else {
					if (aNode->element < front->element) {
						aNode->next = front;
						front = aNode;
					}

					else {
						last->next = aNode;
						last = aNode;
					}
				}
			}
		}



	}

void viewBooks() {

	struct LinearNode *current;// initialise nodes

	printf("\n");
	if (isEmpty())
		printf("Error - there are no books in the library!\n");
	else {
		current = front;
		while (current != NULL) {//display details for current book node
			printf("Book ID: %s", current->element->id);
			printf("Name: %s", current->element->name);
			printf("Author:  %s", current->element->author);
			printf("Year: %d\n", current->element->year);
			if (current->element->avail == true) {
				printf("Availabilty: Book Avaialble\n");
			}
			else if (current->element->avail == false) {
				printf("Availabilty: Book Unavaialble\n");
				("Customer id: %s\n", current->element->custId);
			}
			if (current->element->pop == 0) {
				printf("Times Borrowed: 0\n");
			}
			else {
				printf("Times Borrowed: %d\n", current->element->pop);
			}
			printf("\n");
			current = current->next;
		}
	}
}


void borrowBooks() {
	struct LinearNode *current, *previous;// initialise nodes
	bool notFound = true;

	char custName[100];
	char idSearch[15];

	printf("\n");
	if (isEmpty())
		printf("Error - there are no books in the library\n");
	else {
		fflush(stdin);
		getchar();

		printf("\nPlease enter the ID of the Book you would like to borrow: ");
		fgets(idSearch, 15, stdin);


		current = previous = front;

		while (notFound && current != NULL) {
			if (strcmp(idSearch, current->element->id) == 0)
				notFound = false;
			else {
				previous = current;
				current = current->next;
			}//end else
		} //end while

		if (notFound) {
		printf("There is no such Book with the ID %s\n", idSearch);
		printf("We may however have the book you are looking for in our online database, available from the main menu.\n");
	}
		else if (notFound == false && current->element->avail == false) {

			printf("We do stock this book but another member has borrowed it.\n", current->element->name);
		}
		else {
			printf("\n The book is available, please enter your name:");
			fgets(current->element->custId, 100, stdin);
			current->element->avail = false;//set book to unavailable and incriment times borrowed
			current->element->pop = current->element->pop + 1;
			printf("\nThe book has been successfully borrowed!\n");
			
		}

	}
}

void returnBooks() {

	struct LinearNode *current, *previous;// initialise nodes
	bool notFound = true;

	char custName[100];
	char idSearch[15];

	printf("\n");
	if (isEmpty())
		printf("Error - there are no books in the library\n");
	else {
		fflush(stdin);
		getchar();
	
		printf("\nPlease enter the ID of the Book you would like to return: ");
		fgets(idSearch, 15, stdin);


		current = previous = front;

		current = previous = front;

		while (notFound && current != NULL) {
			if (strcmp(idSearch, current->element->id) == 0)
				notFound = false;
			else {
				previous = current;
				current = current->next;
			}//end else
		} //end while

		if (notFound)
			printf("There is no such Book with the ID %s\n", idSearch);
		else if (notFound == false && current->element->avail == false) {
			printf("\Please enter your name:");
			fgets(custName, 100, stdin);
			if (strcmp(custName, current->element->custId) == 0) {//set book to available
				current->element->avail = true;
				memset(current->element->custId, 0, strlen(current->element->custId));
				printf("The book has been returned, thank you!");

			}
			else {
				printf("You did not borrow this book.");
			}
			
		}
		else {
			printf("This book has not been borrowed and is available to be booked!.");

		}

	}

}


void deleteBooks(char anID[]) {
	struct LinearNode *current, *previous;// initialise nodes
	bool notFound = true;

	printf("\n");
	if (isEmpty())
		printf("Error - there are no books in the library\n");
	else {
		current = previous = front;

		while (notFound && current != NULL) {
			if (strcmp(anID,current->element->id) ==0)
				notFound = false;
			else {
				previous = current;
				current = current->next;
			}//end else
		} //end while

		if (notFound)
			printf("Error - there is no such Book with the ID %s\n", anID);
		else if (notFound == false && current->element->year >= 2010) {

			printf("You may only delete books from the library older than 2010\n");
		}
		else if (notFound == false && current->element->year<2010){
			if (current == front) { //delete front node
				front = front->next;
				free(current);
			} //end else
			else if (current == last) {//delete last node
				free(current);
				previous->next = NULL;
				last = previous;
			}
			else {//delete node in middle of list
				previous->next = current->next;
				free(current);
			} //end else
			printf("The Book has been deleted\n");
		}//end else
	}//end else
}

void popBooks() {

		struct LinearNode *current, *most, *least;// initialise nodes
		
		printf("\n");
		if (isEmpty())
			printf("Error - there are no Books in the library\n");
		else {

			current = front;
			most = current;
			least = current;

			while (current != NULL) {
			if (current->element->pop < least->element->pop) {
				least->element = current->element;
			}
				if (current->element->pop > most->element->pop) {
				most->element = current->element;
				}
				current = current->next;
			} //end while
			printf("The details of the most popular books are as follows.\n");
			printf("Book ID: %s", most->element->id);
			printf("Name: %s", most->element->name);
			printf("Author:  %s", most->element->author);
			printf("Year: %d\n", most->element->year);
			if (most->element->avail == true) {
				printf("Availabilty: Book Avaialble\n");
			}
			else if (most->element->avail == false) {
				printf("Availabilty: Book Unavaialble\n");
				("Customer Name: %s\n", most->element->custId);
			}
			if (most->element->pop == 0) {
				printf("Times Borrowed: 0\n");
			}
			else {
				printf("Times Borrowed: %d\n", most->element->pop);
			}
			printf("\n");

			printf("The details of the least popular books are as follows.\n");
			printf("Book ID: %s", least->element->id);
			printf("Name: %s", least->element->name);
			printf("Author:  %s", least->element->author);
			printf("Year: %d\n", least->element->year);
			if (least->element->avail == true) {
				printf("Availabilty: Book Avaialble\n");
			}
			else if (least->element->avail == false) {
				printf("Availabilty: Book Unavaialble\n");
				("Customer Name: %s\n", least->element->custId);
			}
			if (least->element->pop == 0) {
				printf("Times Borrowed: 0\n");
			}
			else {
				printf("Times Borrowed: %d\n", least->element->pop);
			}
			printf("\n");
		}//end else

}

void searchBooks(char aName[]) {
	struct LinearNode *current;// initialise nodes
	bool notFound = true;

	
	if (isEmpty())
		printf("Error - there are no books in the library\n");
	else {
		current = front;

		while (notFound && current != NULL) {
			if (strcmp(aName, current->element->name) == 0) {
			notFound = false;

			
		}
			current = current->next;
		} //end while

		if (notFound==true) {
			printf("We do not have that book but be sure to check our Online Database for it!");
		}
		else if (notFound == false) {
			printf("We do stock this book, here are its details: \n");
			printf("Book ID: %s", current->element->id);
			printf("Name: %s", current->element->name);
			printf("Author:  %s", current->element->author);
			printf("Year: %d\n", current->element->year);
			if (current->element->avail == true) {
				printf("Availabilty: Book Avaialble\n");
			}
			else if (current->element->avail == false) {
				printf("Availabilty: Book Unavaialble\n");
				("Customer id: %s\n", current->element->custId);
			}
			if (current->element->pop == 0) {
				printf("Times Borrowed: 0\n");
			}
			else {
				printf("Times Borrowed: %d\n", current->element->pop);
			}
			
			printf("\n");
		}
	}

}



void learnMore() {
	printf("Loading our Online Databse....");
	system("START https://www.dit.ie/library/databases/");// launch browser to DIT library
}



bool isEmpty() {
	if (front == NULL)
		return true;
	else
		return false;
}

void saveToFile(FILE *fp) {

	struct LinearNode *current;

	fp = fopen("Z:library.dat", "wb");

	current = front;
	while (current != NULL) {
		fwrite(current->element, sizeof(struct Book), 1, fp);
		current = current->next;
	}

	fclose(fp);
}


void getFromFile(FILE *fp) {





	struct LinearNode *aNode;
	struct Book *newBook;

	// create space for new node that will contain books
	newBook = (struct Book *)malloc(sizeof(struct Book));
	aNode = (struct LinearNode *)malloc(sizeof(struct LinearNode));



	while (fread(newBook, sizeof(struct Book), 1, fp) != NULL)
	{

		if (aNode == NULL)
			printf("Error - no space for the new Book!\n");
		else { // add book to the node
			aNode->element = newBook;
			aNode->next = NULL;
		}
			//add book to end of the list
			if (isEmpty())
			{
				front = aNode;
				last = aNode;
			}
			else {


				last->next = aNode;
				last = aNode;
			}
		

			//recreate space in nodes for book
		newBook = (struct Book *)malloc(sizeof(struct Book));
		aNode = (struct LinearNode *)malloc(sizeof(struct LinearNode));


	}
		fclose(fp);
	}







void menu() {
	
	do {
		printf("\n-----MAIN MENU---------------------");
		printf("\n 1. Add A Book\n 2. Borrow A Book\n 3. Return A Book\n 4. Delete A Book\n 5. Search For A Book\n 6. View All Books\n 7. View Book Popularity\n 8. View Our Extensive Online Library\n 9. Exit Library\n");
		printf("-----------------------------------");
		printf("\n");
		printf(" Enter a number corresponding to your menu selection: ");
		scanf("%d", &menuSelect);

		if (menuSelect == 1) {
			addBooks();
		}

		else if (menuSelect == 2) {
			borrowBooks();
		}

		else if (menuSelect == 3) {
			returnBooks();
		}

		else if (menuSelect == 4) {
			
			fflush(stdin);
			char anID[15];
			getchar();
			printf("What book ID would you like to delete? ");
			
			fgets(anID, 15, stdin);
			deleteBooks(anID);
		}

		else if (menuSelect == 5) {
			fflush(stdin);
			char aName[100];
			getchar();
			printf("What is the name of the book would you like to search for? ");
			fgets(aName, 100, stdin);
			
			searchBooks(aName);
		}

		else if (menuSelect == 6) {
			viewBooks();
		}

		else if (menuSelect == 7) {
			popBooks();
		}

		else if (menuSelect == 8) {
			learnMore();
		}

		

		else if (menuSelect == 9) {

			saveToFile(fp);
			exit(0);
		}

		else if (menuSelect != 6 || menuSelect != 5 || menuSelect != 4 || menuSelect != 3 || menuSelect != 2 || menuSelect != 1 || menuSelect != 7 || menuSelect != 8){
			printf(" Please select valid option!\n");
		}

	} while (menuSelect != 9);


}