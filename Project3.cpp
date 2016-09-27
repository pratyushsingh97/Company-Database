/* 
 * EE312 Simple CRM Project
 *
 * YOUR INFO HERE!
 */

#include <stdio.h>
#include <assert.h>
#include "MyString.h"
#include "Invent.h"

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


/* clear the inventory and reset the customer database to empty */
void reset(void) {
	/* your code here */
    init();
    Inventory.bottles = 0;
    Inventory.rattles = 0;
    Inventory.diapers = 0;
    num_customers = 0;
    first_time = 1;
}

void processSummarize() {
    //print out the number of items remaining in inventory
    printf("There are ");
    printf("%d Bottles, %d Diapers, and %d Rattles remaining in the inventory \n", Inventory.bottles, Inventory.diapers, Inventory.rattles);
    printf("We have had a total of %d different customers \n", num_customers);

    int most_diapers = mostDiapers();
    int most_rattles = mostRattles();
    int most_bottles = mostBottles();

    if(most_bottles == -1)
    {
        printf("no one has purchased any Bottles\n");

    }
    else {
        StringPrint(&(customers[most_bottles].name));
        printf(" has purchased the most bottles (%d)\n", customers[most_bottles].bottles);
   }

    if(most_diapers == -1)
    {
        printf("no one has purchased any Diapers\n");
    }
    else {
        StringPrint(&(customers[most_diapers].name));
        printf(" has purchased the most diapers (%d)\n", customers[most_diapers].diapers);
    }

    if(most_rattles == -1)
    {
        printf("no one has purchased any Rattles\n");        
    }
    else{
        StringPrint(&(customers[most_rattles].name));
        printf(" has purchased the most rattles (%d)\n", customers[most_rattles].rattles);
    }


}

void processPurchase() {
	if(first_time)
	{
		init();
		first_time = 0;
	}

	String name;
	readString(&name);
    

	String purchase;
	readString(&purchase); 
    

	int amount;
	readNum(&amount);

	//check if valid purchase 
	int valid = check(&purchase, amount);
	if(valid == INVALID_PURCH)
	{
        switch(item(&purchase)){
                case BOTTLES:
                printf("Sorry ");
                StringPrint(&name);
                printf(", We only have %d ", Inventory.bottles);
                StringPrint(&purchase);
                printf("left\n");
                StringDestroy(&name);
                StringDestroy(&purchase);
                break;

                case DIAPERS:
                printf("Sorry ");
                StringPrint(&name);
                printf(", We only have %d ", Inventory.diapers);
                StringPrint(&purchase);
                printf("left\n");
                StringDestroy(&name);
                StringDestroy(&purchase);
                break;

                case RATTLES:
                printf("Sorry ");
                StringPrint(&name);
                printf(", We only have %d ", Inventory.rattles);
                StringPrint(&purchase);
                printf("left\n");
                StringDestroy(&name);
                StringDestroy(&purchase);
                break;

                default:
                puts("Invalid input");
            }
        //fix invalid purchase with name
       /* printf("Sorry ");
        StringPrint(&name);
        printf(", We only have %d ", amount);
        StringPrint(&purchase);
        printf("\n");
        StringDestroy(&name);
        StringDestroy(&purchase);*/
		return;
	}

	if(num_customers == 0)
	{
            //fix this 
			StringReAssign(&(customers[0].name), &name);

            switch(item(&purchase)){
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

            num_customers++;
            //StringDestroy(&name);
            StringDestroy(&purchase);
            return;
		}
       

	sort(num_customers);
	int index = search(&name);

    if(index == NEW_CUSTOMER)
    {
        //fix this 
    	StringReAssign(&(customers[num_customers].name), &name);

    	switch(item(&purchase)){
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
      sort(num_customers);
      //StringDestroy(&name);
      StringDestroy(&purchase);
      return;

    }
    else 
    {
        switch(item(&purchase)){
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
    StringDestroy(&purchase);

 }   



void processInventory() {
	//get item name 
    String command;
    readString(&command);

    //get shipment amount 
    int shipment;

   static int first_shipment = 0;
    if(first_shipment == 0){
    	Inventory.bottles = 0;
    	Inventory.rattles = 0;
    	Inventory.diapers = 0;
    	first_shipment++;
    }

    //switch case adds the appropriate item into the inventory
	switch(item(&command)){
		case BOTTLES:
			readNum(&shipment);
			/*printf("Number of bottles: %d\n", shipment);
			printf("Current inventory of bottles %d\n", Inventory.bottles);*/
			Inventory.bottles = Inventory.bottles + shipment;
			//printf("Updated inventory of bottles %d\n", Inventory.bottles);
			break;
		case DIAPERS:
			readNum(&shipment);
			//printf("Number of diapers: %d\n", shipment);
			Inventory.diapers = Inventory.diapers + shipment;
			break;
		case RATTLES:
			readNum(&shipment);
			//printf("Number of rattles: %d\n", shipment);
			Inventory.rattles = Inventory.rattles + shipment;
			break;
		default:
			printf("%s\n","Invalid input");
	}   

	StringDestroy(&command);

}

//remember to destroy request
int item(String* request)
{
	//create constants
    String bottles = StringCreate("Bottles");
	String diapers = StringCreate("Diapers");
	String rattles = StringCreate("Rattles");

	if(StringIsEqualTo(request, &bottles)){
		StringDestroy(&bottles);
		return BOTTLES;
	}
	else if(StringIsEqualTo(request, &diapers)){
		StringDestroy(&diapers);
		return DIAPERS;
	}
	else
	{
		StringDestroy(&rattles);
		return RATTLES;
	}

	return 0;
}

void sort(int size)
{
  int i, j, min_index;

  for(i = 0; i < size - 1; i++)
  {
  	min_index = i;
  	for(j = i + 1; j < size; j++)
  	{
  		if(StringIsLessThan(&(customers[j].name), &(customers[min_index].name)))
  		{
  			min_index = j;
  		}
  	}
  	if(min_index != i)
  	{
  		swap(min_index, i);
  	}
  	
  }
  
}

void swap(int min, int index)
{
	Customer temp = customers[min];
	customers[min] = customers[index];
	customers[index] = temp;
}

//remember to destroy name
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