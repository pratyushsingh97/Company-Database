/* 
 * EE312 Simple CRM Project
 *
 * Name: Pratyush Singh
 * Class: EE312 Spring 2016
 * 
 */

#include <stdio.h>
#include <assert.h>
#include "MyString.h"
#include "Invent.h"
//#include "MyString.cpp"

#define MAX_CUSTOMERS 1000
#define BOTTLES 1
#define DIAPERS 2
#define RATTLES 3
#define NEW_CUSTOMER -1
#define INVALID_PURCH 0
#define VALID_PURCH 1

//global variables
Customer Inventory;
Customer customers[MAX_CUSTOMERS];
int num_customers = 0;
int first_time = 1;
String name;
String prod;
//function declarations 
void sort(int size);
void swap(int min, int index);
void init();
int search(String* name);
int item(String* request);
int check(String* purchase, int amount);
int mostDiapers();
int mostBottles();
int mostRattles(); 
/* you'll probably need several more global variables */
/* and of course, you have a few functions to write */


/** reset(void)
 * Clears the Inventory and Customer database
 * [INPUT] none 
 * [OUTPUT] none
*/  
void reset(void) 
{
	/* your code here */
    //StringDestroy(&name);
    //StringDestroy(&prod);
    for(int x = 0; x < num_customers; x++)
    {
        StringDestroy(&(customers[x].name));
    }
    init();
    Inventory.bottles = 0;
    Inventory.rattles = 0;
    Inventory.diapers = 0;
    num_customers = 0;
    first_time = 1;
}

/** processSummarize
 * Prints the amount of Inventory left and the customers
 * that purchased the most of each product
 * [INPUT] none
 * [OUTPUT] prints the amount of inventory left and customer info
 */
void processSummarize() 
{
    //print out the number of items remaining in inventory
    printf("There are ");
    printf("%d Bottles, %d Diapers, and %d Rattles remaining in the inventory \n", Inventory.bottles, Inventory.diapers, Inventory.rattles);
    printf("We have had a total of %d different customers \n", num_customers);

    /*calls mostDiapers, mostRattles, and mostBottles to see the index 
     * of the customer who purchased the most of each product */
    int most_diapers = mostDiapers();
    int most_rattles = mostRattles();
    int most_bottles = mostBottles();

    //if mostDiapers return -1, then no customer has purchased the product
    if(most_bottles == -1) {
        printf("no one has purchased any Bottles\n");

    }

    //print the customer name who has purchased the most of that specific prodcut
    else {
        StringPrint(&(customers[most_bottles].name));
        printf(" has purchased the most bottles (%d)\n", customers[most_bottles].bottles);
   }

    if(most_diapers == -1) {
        printf("no one has purchased any Diapers\n");
    }

    else {
        StringPrint(&(customers[most_diapers].name));
        printf(" has purchased the most diapers (%d)\n", customers[most_diapers].diapers);
    }

    if(most_rattles == -1){
        printf("no one has purchased any Rattles\n");        
    }

    else{
        StringPrint(&(customers[most_rattles].name));
        printf(" has purchased the most rattles (%d)\n", customers[most_rattles].rattles);
    }


}

/** processPurchase
* creates a new entry in database if new customer, updates existing
* customer purchases, updates Inventory on valid purchases
* [INPUT] none
* [OUTPUT] prints if invalid purchase, updates Inventory and customers
* database for valid purchases
*/
void processPurchase() 
{
    /*if customers array is being accessed for the first time the intialize
     * with values 0*/
	if(first_time) {
		init();
		first_time = 0;
	}

    //get name of customer
	//String name;
	readString(&name);
    
    //get product that the customer has bought
	//String prod;
	readString(&prod); 
    
    //get the amount of product the customer wants to buy
	int amount;
	readNum(&amount);

	/*check if valid purchase, if invalid then print error message depending on
    *which product they bought*/
	int valid = check(&prod, amount);
	if(valid == INVALID_PURCH || amount == 0) {

        switch(item(&prod)){
                case BOTTLES:
                printf("Sorry ");
                StringPrint(&name);
                printf(", We only have %d ", Inventory.bottles);
                StringPrint(&prod);
                printf("left\n");
                StringDestroy(&name);
                StringDestroy(&prod);
                break;

                case DIAPERS:
                printf("Sorry ");
                StringPrint(&name);
                printf(", We only have %d ", Inventory.diapers);
                StringPrint(&prod);
                printf("left\n");
                StringDestroy(&name);
                StringDestroy(&prod);
                break;

                case RATTLES:
                printf("Sorry ");
                StringPrint(&name);
                printf(", We only have %d ", Inventory.rattles);
                StringPrint(&prod);
                printf("left\n");
                StringDestroy(&name);
                StringDestroy(&prod);
                break;

                default:
                puts("Invalid input");
            }
        //StringDestroy(&name);
        //StringDestroy(&prod);
		return;
	}
    //if first customer to database, then add customer to database
	if(num_customers == 0) {
            //fix this 
             customers[0].name = StringDup(&name);
            //copyChars(customers[0].name.ptr, name.ptr, name.len);

			//StringReAssign(&(customers[0].name), &name);

            switch(item(&prod)){
            	case BOTTLES:
            	customers[0].bottles = amount;
            	Inventory.bottles = Inventory.bottles - amount;
                break;

            	case DIAPERS:
            	customers[0].diapers = amount;
            	Inventory.diapers = Inventory.diapers - amount;
                break;

            	case RATTLES:
            	customers[0].rattles = amount;
            	Inventory.rattles = Inventory.rattles - amount;
                break;

            	default:
            	puts("Invalid input");
            }

            //new customer added now increment the number of customers
            num_customers++;

            //destroy variables stored on heap
            StringDestroy(&name);
            StringDestroy(&prod);
            return;
		}
       
    /* if not first customer to database, then search and sort to see 
     * if customer is a new customer or an existing customer */ 
	sort(num_customers);
	int index = search(&name);

    //if new customer then add new customer to the customer database
    if(index == NEW_CUSTOMER) {
        customers[num_customers].name = StringDup(&name); 

    	//StringReAssign(&(customers[num_customers].name), &name);

    	switch(item(&prod)) {
            	case BOTTLES:
            	customers[num_customers].bottles = amount;
            	Inventory.bottles = Inventory.bottles - amount;
                break;

            	case DIAPERS:
            	customers[num_customers].diapers = amount;
            	Inventory.diapers = Inventory.diapers - amount;
                break;

            	case RATTLES:
            	customers[num_customers].rattles = amount;
            	Inventory.rattles = Inventory.rattles - amount;
                break;

            	default:
            	puts("Invalid input");
            }

      num_customers++;  

      //re-sort customers database to take into account new customer
      sort(num_customers);

      //destroy variables created on heap
      StringDestroy(&name);
      StringDestroy(&prod);
      return;

    }

    //if a existing custoemr then update existing customer record
    else {
        switch(item(&prod)) {
                case BOTTLES:
                customers[index].bottles = customers[index].bottles + amount;
                Inventory.bottles = Inventory.bottles - amount;
                break;

                case DIAPERS:
                customers[index].diapers = customers[index].diapers + amount;
                Inventory.diapers = Inventory.diapers - amount;
                break;

                case RATTLES:
                customers[index].rattles = customers[index].rattles + amount;
                Inventory.rattles = Inventory.rattles - amount;
                break;

                default:
                puts("Invalid input");
            }

    }

   StringDestroy(&name);
   StringDestroy(&prod);

 }   

/* processInventory
 * process new shipment of items and updates inventory 
 * [INPUT] none
 * [OUTPUT] none
 */
void processInventory() 
{
	//get item name 
    String command;
    readString(&command);

    //get shipment amount 
    int shipment;

    //if first shipment to Inventory database, then make sure everything is 0
    static int first_shipment = 0;
    if(first_shipment == 0) {
    	Inventory.bottles = 0;
    	Inventory.rattles = 0;
    	Inventory.diapers = 0;
    	first_shipment++;
    }

    //switch case adds the appropriate item into the inventory
	switch(item(&command)) {

		case BOTTLES:
			readNum(&shipment);
			Inventory.bottles = Inventory.bottles + shipment;
			break;

		case DIAPERS:
			readNum(&shipment);
			Inventory.diapers = Inventory.diapers + shipment;
			break;

		case RATTLES:
			readNum(&shipment);
			Inventory.rattles = Inventory.rattles + shipment;
			break;

		default:
			printf("%s\n","Invalid input");
	}   

	StringDestroy(&command);

}

//remember to destroy request
/** item(String* request)
 * helper function that returns 0, 1, 2 
 * depending on if the product is bottles, diapers, or rattles
 * [INPUT] String pointer to the request
 * [OUTPUT] returns an int that is symbolic of each product
 */
int item(String* request)
{
    int out = 0;
	//create constants to compare to request 
    String bottles = StringCreate("Bottles");
	String diapers = StringCreate("Diapers");
	String rattles = StringCreate("Rattles");

    //if request is a bottle, then return BOTTLE
	if(StringIsEqualTo(request, &bottles)) {
		
		out = BOTTLES;
	}

    //if request is a diaper, then return DIAPER    
	else if(StringIsEqualTo(request, &diapers)){
		
		out = DIAPERS;
	}

    //if not diaper or bottle then must be a rattle
	else {

		out = RATTLES;
    }

    StringDestroy(&bottles);
    StringDestroy(&diapers);
    StringDestroy(&rattles);
	return out;
}

/** sort(int size)
 * sorts the customers array in alphabetical order
 * [INPUT] size of customers array
 * [OUTPUT] none
 */
void sort(int size)
{
  int i, j, min_index;

  for(i = 0; i < size - 1; i++) {

  	min_index = i;

    //find the smallest element in customers array
  	for(j = i + 1; j < size; j++) {
  		if(StringIsLessThan(&(customers[j].name), &(customers[min_index].name))) {
  			min_index = j;
  		}
  	}

    //call helper function 'swap' to swap the smallest element with the element at current index
  	if(min_index != i) {
  		swap(min_index, i);
  	}
  	
  }
  
}

/** swap(int min, int index)
 * swaps the customer entry at index with min
 * [INPUT] input is min and index which are two indexes in the customer array
 * [OUTPUT] none
 */ 
void swap(int min, int index)
{
	Customer temp = customers[min];
	customers[min] = customers[index];
	customers[index] = temp;
}

//remember to destroy name
/** search(int min, int index)
 * a helper binary serach function that determines if customer is a new
 * customer or an existing one
 * [INPUT]
 */
int search(String* name)
{
	int low = 0;
	int mid = 0;
	int high = num_customers - 1;

	while(low <= high)
	{
		mid = (low + high)/2;
		if(StringIsLessThan(&(customers[mid].name), name))
		{
			low = mid + 1;
		}
		else if(StringIsEqualTo(&(customers[mid].name), name))
		{
			return mid;
		}
		else if(StringIsLessThan(name, &(customers[mid].name)))
		{
			high = mid - 1;
            if(high < 0)
                break;
		}
	}
	return NEW_CUSTOMER;
}

void init()
{
	for (int i = 0; i < MAX_CUSTOMERS; ++i)
	{
		customers[i].bottles = 0;
		customers[i].rattles = 0;
		customers[i].diapers = 0;
	}
}

//remember to destroy product
int check(String* product, int amount)
{
	switch(item(product)){
		case BOTTLES:
			if(amount > Inventory.bottles)
			{
				return INVALID_PURCH;
			}
			return VALID_PURCH;

		case DIAPERS:
			if(amount > Inventory.diapers)
			{
				return INVALID_PURCH;
			}
			return VALID_PURCH;

		case RATTLES:
			if(amount > Inventory.rattles)
			{
				return INVALID_PURCH;
			}

			return VALID_PURCH;
		default:
			printf("%s\n","Invalid input");
	}   	
}

int mostBottles(){
    int max = customers[0].bottles;
    int index = 0;
    for(int x = 0; x < num_customers; x++){
        if(customers[x].bottles > max)
        {
            max = customers[x].bottles;
            index = x;
        }
    }
  if(max == 0)
  {
    return -1;
  } 
  return index;
}

int mostDiapers(){
    int max = customers[0].diapers;
    int index = 0;
    for(int x = 0; x < num_customers; x++){
        if(customers[x].diapers > max)
        {
            max = customers[x].diapers;
            index = x;
        }
    }
    if(max == 0)
    {
        return -1;
    } 
  return index;
}

int mostRattles(){
    int max = customers[0].rattles;
    int index = 0;
    for(int x = 0; x < num_customers; x++){
        if(customers[x].rattles > max)
        {
            max = customers[x].rattles;
            index = x;
        }
    }
    if(max == 0)
    {
        return -1;
    } 
  return index;
}