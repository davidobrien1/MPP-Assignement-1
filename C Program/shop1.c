#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Product {  
	char* name;
	double price;
};

struct ProductStock {
	struct Product product; 	// Struct that contains a struc
	int quantity;				// quantity of stock
};

struct Shop {						//
	double cash;
	struct ProductStock stock[20];	// this is our stock in our shop
	int index;
};

struct Customer { 	// a type of data that we define ourselves and can be made up of one or more data types
	char* name;		// we want the customer to have a name, and we dont know how long it will be so we will make it a pointer so it can expand in memory
	double budget;	// double means it can be a decimal number
	struct ProductStock shoppingList[10];
	int index; // this is created to keep track of value
};

void printProduct(struct Product p)	// void doesnt return anything, only prints.  This prints the product info
{
	printf("PRODUCT NAME: %s \nPRODUCT PRICE: %.2f\n", p.name, p.price);
	printf("-------------\n");
}

void printCustomer(struct Customer c) // This prints the customer into
{
	printf("CUSTOMER NAME: %s \nCUSTOMER BUDGET: %.2f\n", c.name, c.budget);
	printf("-------------\n");
	for(int i = 0; i < c.index; i++) //c.index is customer index
	{
		printProduct(c.shoppingList[i].product);
		printf("%s ORDERS %d OF ABOVE PRODUCT\n", c.name, c.shoppingList[i].quantity);
		double cost = c.shoppingList[i].quantity * c.shoppingList[i].product.price; 
		printf("The cost to %s will be €%.2f\n", c.name, cost);
	}
}

struct Shop createAndStockShop()
{

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("stock.csv", "r"); 	// r is to read the file, w to write
    if (fp == NULL)					// if the file doesnt exist, exit the program (error handling)
        exit(EXIT_FAILURE);

	getline(&line, &len, fp);
	double cashInShop = atof(line);		// creates the variable cashInShop from the first line in csv file
	struct Shop shop = { cashInShop };	// declares the initial value of the cashInShop

    while ((read = getline(&line, &len, fp)) != -1) { 	// this says keep reading the line until we get to the end
        // printf("Retrieved line of length %zu:\n", read);
        // printf("%s IS A LINE", line);
		char *n = strtok(line, ","); //parse the line at the comment
		char *p = strtok(NULL, ","); // Null means we're not passing any information, continues from where it last stop
		char *q = strtok(NULL, ",");
		int quantity = atoi(q); //converts to an integer
		double price = atof(p); //converts to floating point
		char *name = malloc(sizeof(char) * 50); //malloc allocates memory assumes name is less than 50 characters. allocates memory to each name
		strcpy(name, n); //takes from the source which is n, makes a copy of the data and puts it into the new memory location represented in malloc
		struct Product product = { name, price }; 
		struct ProductStock stockItem = { product, quantity }; 
		shop.stock[shop.index++] = stockItem; // this adds the item to the shop
		// printf("NAME OF PRODUCT %s PRICE %.2f QUANTITY %d\n", name, price, quantity);
    }
	
	return shop;
}


void printShop(struct Shop s)
{
	printf("Shop has %.2f in cash\n", s.cash);
	for (int i = 0; i < s.index; i++)
	{
		printProduct(s.stock[i].product);
		printf("The shop has %d of the above\n", s.stock[i].quantity);
	}
}

void orders()
{

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("david.csv", "r"); 	// r is to read the file, w to write
    if (fp == NULL)					// if the file doesnt exist, exit the program (error handling)
        exit(EXIT_FAILURE);

	getline(&line, &len, fp);
		char *n = strtok(line, ",");
		char *b = strtok(NULL, ",");
		double budget = atof(b);	// creates the variable budget from the first line in csv file
		struct Customer name = { n };	
	// printf("CUSTOMER NAME: %s\nCUSTOMER BUDGET: %.2f\n", n,budget);
	// printf("-------------\n");
		struct ProductStock.shoppingList array[] = {i}; 
		while ((read = getline(&line, &len, fp)) != -1) { 	// this says keep reading the line until we get to the end
		struct Product p = array[i].product
		printf("Product is %s", p.name*******)


    
}

void mainmenu(void)
{
	printf("                                 **************************************************************************\n");
	printf("                                                     WELCOME TO OUR SHOP\n");
	printf("                                 **************************************************************************\n\n\n");
	printf("          1. STOCK SHOP AND SHOW CURRENT STOCK--> \n\n          2. ORDERS--> \n\n          3. Exit--> \n\n\n             Enter Your Choice --->");
	int choice;
		scanf("%d",&choice);
		if(choice==1)
		{
			struct Shop shop = createAndStockShop();
			printShop(shop);
			mainmenu();
		}
		else if(choice==2)
		{
			orders();
			mainmenu();
		}
		else if(choice==3)
		{
			
			printf("\n\n\n");
			printf("*******************************THANK YOU**************************************\n");
			exit(0);
		}
		else
		{
			printf("Incorrect Selection. PLease Select 1,2 or 3");
			mainmenu();
		}	
}


int main(void) 
{
	// struct Customer dominic = { "Dominic", 100.0 };  this creates the customer dominic
	//
	// struct Product coke = { "Can Coke", 1.10 };
	// struct Product bread = { "Bread", 0.7 };
	// // printProduct(coke);
	//
	// struct ProductStock cokeStock = { coke, 20 };
	// struct ProductStock breadStock = { bread, 2 };
	//
	// dominic.shoppingList[dominic.index++] = cokeStock; // this code is used to return to value at index, and increment it by one so that the next time its accessed it is one
	// dominic.shoppingList[dominic.index++] = breadStock;
	//
	// printCustomer(dominic);
	
//	struct Shop shop = createAndStockShop();
//	printShop(shop);

//	orders();
	

// printf("The shop has %d of the product %s\n", cokeStock.quantity, cokeStock.product.name);
	mainmenu();
    return 0;
}
