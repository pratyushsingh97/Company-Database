# Database for a Business
Managing a database for a business that sells 3 products: diapers, rattles, and baby bottles.

This program tracks changes to the Inventory of bottles, diapers, and rattles such as updating the Inventory after a 
new shipment of products or after a customer makes a valid purchase of a certain product.

Additionally, this program updates the customer database after a customer makes a valid purchase, 
and keeps track of which customer has bought the most of each product. 

#Technical Description 

This program was coded in C.

This program also uses the **heap** to allocate space for the Inventory and Customer databases. 

Memory leaks were identified and taken care of using **Valgrind**.

The Inventory database is a struct, while the Customer database is an **array of structs**.

#Modules 

##**Format of Instructions**

In order to use the database, the commands *must follow* a specific format.

###**Changing the Inventory**

In order to access the inventory to update the amount of a certain product, the instruction must be in the following format:

__Inventory \<type> #__

ex. _Inventory Diapers 100_

  This command will add 100 diapers to the Inventory 
  
###**Updating the Customer database**

In order to update the customer database after a valid purchase has been processed, the instruction must be in the following format:

__Purchase \<name> <type> #__

ex. _Purchase Paul Diapers 10_

This command will create a new customer record under Paul and record that Paul has bought 10 diapers. Additionally this function will also update the amount of product left in the Inventory. 

In this example, the amount of diapers in the inventory will automatically be reduced by 10.

###**Getting Summary of Inventory and Customers**

This command will automatically return the amount of product left in the Inventory and which customers have purchased the most of each item.

To use this command simply type _Summarize_

__Summarize__

###Resetting Inventory and Customer databse

In the case you wish to clear the inventory and customer database, simply type _Quit_, and this will clear the customer database as well as the inventory.

__Quit__


##Error Handling

If a customer tries purchases more than there is available in the inventory, the transaction will be denied, and neither the  customer nor the inventory will updated.

_Purchase Craig Diapers 0_

This is not a valid purchase, since essentially Craig has not purchased anything, so a new entry will not be created. 


  





