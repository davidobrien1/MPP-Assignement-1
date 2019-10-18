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
	struct Shop shop = { 200 };
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("stock.csv", "r"); 	// r is to read the file, w to write
    if (fp == NULL)					// if the file doesnt exist, exit the program (error handling)
        exit(EXIT_FAILURE);

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
	
	struct Shop shop = createAndStockShop();
	printShop(shop);
	
// printf("The shop has %d of the product %s\n", cokeStock.quantity, cokeStock.product.name);
	
    return 0;
}