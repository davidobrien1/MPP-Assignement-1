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
	printf("%s Costs: %.2f", p.name, p.price);
	// printf("-------------\n");
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
	printf("-------------\n");
	printf("Below is the current status of the shop:\nCash in the shop is: %.2f in cash\nStock List:\n", s.cash);
	for (int i = 0; i < s.index; i++)
	{
		printProduct(s.stock[i].product);
		printf(" Quantity in Stock: %d\n", s.stock[i].quantity);
	}
}

double find(struct Shop s, char* name)
{
	for (int i = 0; i <s.index; i++)
	{
		if (strcmp(name, s.stock[i].product.name) == 0){
			return s.stock[i].product.price;
		}
	}
	return -1;
}

// double updateCustomerFile(char filename[],char customerName[],double newBudget){
// 	    FILE * fp;
//     char * line = NULL;
//     size_t len = 0;
//     ssize_t read;

//     fp = fopen(filename, "w"); 	// w to write
//     if (fp == NULL)					// if the file doesnt exist, exit the program (error handling)
//         exit(EXIT_FAILURE);
// 		fprintf(fp, "%s,%.2f\n",customerName,newBudget);
// }


struct Customer custOrders(char filename[], struct Shop s)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
	fp = fopen(filename, "r"); 	// r is to read the file, w to write
    if (fp == NULL)					// if the file doesnt exist, exit the program (error handling)
        exit(EXIT_FAILURE);

	getline(&line, &len, fp);
		char *n = strtok(line, ",");
		char *b = strtok(NULL, ",");
		char *custName = malloc(sizeof(char) * 50);
		double budget = atof(b);	// creates the variable budget from the first line in csv file
		strcpy(custName,n);
		struct Customer customer = { custName, budget };	
		printf("-------------\n");		
		printf("CUSTOMER NAME: %s\nCUSTOMER BUDGET: %.2f\n", n,budget);
		printf("-------------\n");
		
		double totalOrderAmount = 0;

		while ((read = getline(&line, &len, fp)) != -1) { 	// this says keep reading the line until we get to the end
			char *p = strtok(line,",");
			char *q = strtok(NULL, ",");
			int quantity = atoi(q);
			char *name = malloc(sizeof(char) * 50);
			strcpy(name, p);
			double price = find(s,name); 
			struct Product product = {name,price}; 
			struct ProductStock customerShoppingList = {product, quantity};
			customer.shoppingList[customer.index++] = customerShoppingList;
			double amount = quantity * price;  
			totalOrderAmount += amount;
			printf("%d %s purchased at €%.2f each TOTAL COST %.2f\n", quantity, p, product.price, amount); 
			} 
		if(totalOrderAmount >0 && totalOrderAmount < budget){
			printf("The total cost for this order is €%.2f\n", totalOrderAmount);
			// char customerName[25];
			// updateCustomerFile(filename,custName,200);			

		}
		if(totalOrderAmount > budget){
			printf("You do not have sufficent funds for this purchase\n");
		}		
		
		if(totalOrderAmount == 0){
			printf("Customer does not have a shopping list\n");
		}

}


void mainmenu(void)
{
	printf("***********************\n");	
	printf("Welcome to the Shop!\n");
	printf("***********************\n");
	printf("Choose option:\n");	
	printf("1. Purchase from a CSV file\n");
	printf("2. Live Purchase\n");
	printf("3. Exit\n");
	int choice;

		scanf("%d",&choice);
		if(choice==1)
		{	
			// char name[25];
			// updateCustomerFile("customer1.csv","Padraic",200);

			char filename[25];
			printf("Enter filename with extension:");
			scanf("%s",&filename);			
			struct Shop shop = createAndStockShop();
			printShop(shop);
			custOrders(filename, shop);
			mainmenu();
		}
		else if(choice==2)
		{
			int count;
			char prodName[25];
			struct Shop shop = createAndStockShop();
			char temp[100];
			printShop(shop);
			printf("How many products do you want to purchase?\n");
			scanf("%d",&count);

			while(count>0){
				printf("Enter product name you want to purchase:\n");
				scanf("%c", &temp);
				scanf("%[^\n]s", prodName); // this is used to allow for the space between words
				double price = find(shop,prodName); 
				printf("You want to purchase %d of %s at %.2f each\n", count, prodName,price);
				count--;
			}
			
			// char prodName;
			// printf("Enter product name you want to purchase:\n");
			// scanf("%s",&prodName);
			// int qty;
			// printf("Enter quantity you want to purchase:\n");
			// scanf("%d",&qty);
			// printf("%d",qty);	
			// printf("%d %s purchased\n", qty, prodName);		
		}
		else if(choice==3)
		{
			printf("***********************\n");
			printf("THANK YOU\n");
			printf("***********************\n");
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
