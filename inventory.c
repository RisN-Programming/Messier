#define MAX_INVENTORY_SIZE 100
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "inventory.h"


int main()
{
	char choice;
	InventoryItemType inventoryItems [MAX_INVENTORY_SIZE];
	int size=0;
	int location;

	printf("Opening file\n");
	OpenFile(inventoryItems, &size);

	do{
		MenuPrint();
		choice= Menu();

		if(choice=='\n'){
			scanf("%c",&choice);
		}
		switch(choice){
		case 'a':
			{
				//display inventory
				DisplayInv(inventoryItems, size);
				break;
			}

		case 'b':
			{
				//display sales
				DisplaySales(inventoryItems, size);
				break;
			}

		case 'c':
			{

				//add items
				AddItem(inventoryItems, &size);
				break;
			}

		case 'd':
			{
				//Delete
				DisplaySales(inventoryItems, size);
				location = FindLocation(inventoryItems,size);
				Delete(inventoryItems, &size, location);
				break;
			}

		case 'e':
			{
				//update stock (enter shipment)
				DisplayInv(inventoryItems, size);
				location = FindLocation(inventoryItems, size);
				enterShipment(inventoryItems,location);
				break;
			}

		case 'f':
			{
				//update sales
				DisplaySales(inventoryItems, size);
				location = FindLocation(inventoryItems, size);
				updateSales(inventoryItems, location);
				break;
			}

		case 'g':
			{
				//sort
				sort(inventoryItems,size);
				DisplayInv(inventoryItems, size);
				break;
			}

		case 'h':
			{
				printf("Saving\n");
				SaveInventory(inventoryItems, &size);
				printf("Good Bye\n");
				break;
			}

		default:
			{ // if any other input
				printf("Error: choose a letter from the list\n\n");
			}

		}
	}while(choice!='h');
	return 0;
}



void OpenFile(InventoryItemType br[], int *size)
{
	FILE * inp;

	if((inp = fopen("inventory.dat","r"))==0)
	{
		printf("File cannot be opened\n");
		return;
	}

	inp = fopen("inventory.dat","r");

	fscanf(inp,"%d",size);
	fread(br, sizeof(InventoryItemType),*size,inp);
	fclose(inp);
}

void MenuPrint(void)
{
	printf("\nWelcome to the Inventory Management Program\n Please select an option\n\n");
	printf("a) Display Inventory\n");
	printf("b) Display Sales\n");
	printf("c) Add Item\n");
	printf("d) Remove Item\n");
	printf("e) Enter Shipment\n");
	printf("f) Update Sales\n");
	printf("g) Sort\n");
	printf("h) Quit\n");
}

char Menu(void)
{
	char selection;
	printf("\nEnter selection: ");
	scanf("%c", &selection);

	return selection;
}

void DisplayInv(InventoryItemType entry[], int size)
{
	int i=0; 
	float value;

	printf("Item Number\t");
	printf("Item Name\t");
	printf("# of Units\t");
	printf("Unit Cost\t");
	printf("Value\n");
	for(i=0; i<size; i++)
	{
		value =(entry[i].Stock) * (entry[i].Price);
		printf("%3s %12s %13d %23f %16f\n", entry[i].itemNum, entry[i].itemName, entry[i].Stock, entry[i].Price, value);

	}
}

void DisplaySales(InventoryItemType entry[], int size)
{
	int i=0;
	float total=0;
	printf("Item Number\t");
	printf("Item Name\t");
	printf("# Sold\t");
	printf("Selling Price\t");
	printf("Profit\n");
	for(i=0; i<size; i++)
	{
		(entry[i].Profit)=(entry[i].Sold) * (entry[i].Price) * 1.5;
		printf("%3s %12s %13d %15f %16f\n", entry[i].itemNum, entry[i].itemName, entry[i].Sold, entry[i].Price, entry[i].Profit);
	}
	for(i=1; i<size; i++){
	total= total + (entry[i].Profit);
	}
		printf("total profit: %f\n\n",total);
}

void AddItem(InventoryItemType entry[], int *size)
{
	int temp=-1;
	printf("\nEnter Item Number:");
	scanf("%s", entry[*size].itemNum);


	printf("\nEnter Purchase Price:");
	scanf("%f", &entry[*size].Price);

	printf("\nEnter Item Name:");
	scanf("%s", entry[*size].itemName);

	entry[*size].Profit = (entry[*size].Price) * 1.5;
	do{
		printf("\nEnter The Amount In Stock:");
		scanf("%d", &temp);
		if (temp<0){
			printf("Error: Must be greater than 0\n");
		}
	}while(temp<0);
	(entry[*size].Stock=temp);
	entry[*size].Profit=entry[*size].Price * 1.5;
	entry[*size].Sold=0;

	*size = *size + 1;
}

void Delete(InventoryItemType entry[], int *size, int location)
{	if(location>=0){
	entry[location] = entry[*size - 1];
	*size = *size - 1;
}
}

int FindLocation(InventoryItemType entry[], int size) 
{
	int i;
	int j;
	int p;
	int length;
	char userItem[MAX_INVENTORY_SIZE];
	char item[MAX_INVENTORY_SIZE];

	printf("1) item number   2) item name: ");
	scanf("%d",&p);

	if(p==1){ 
		printf("Enter item: ");
		scanf("%s", userItem);
		length = strlen(userItem);

		for(i=0; i<length; i++)
		{
			item[i] = (userItem[i]);
		}
		for(j=0; j<size; j++)
		{
			if(strcmp(entry[j].itemNum,userItem)==0)
			{
				return j;
			}
		}
		return -1;
	}
	else if(p==2){
		printf("Enter item: ");
		scanf("%s", userItem);
		length = strlen(userItem);

		for(i=0; i<length; i++)
		{
			item[i] = (userItem[i]);
		}
		for(j=0; j<size; j++)
		{
			if(strcmp(entry[j].itemName,userItem)==0)
			{
				return j;
			}
		}
		return -1;
	}

}

void enterShipment(InventoryItemType entry[], int location)
{
	if(location>=0){
		int num=0;
		float price=0;
		printf("\nEnter the recieved amount: ");
		scanf("%d", &num);
		printf("\nEnter the purchase price:");
		scanf ("%f",&price);
		entry[location].Stock+=num;
		entry[location].Price=price;
		entry[location].Profit= entry[location].Price*entry[location].Stock*1.5;
	}
}

void updateSales(InventoryItemType entry[], int location)
{
	if(location>=0){
		unsigned int num=0;
		printf("\nEnter amount sold: ");
		scanf("%d", &num);
		if(num>entry[location].Stock){
			printf("Error: That amount is not in stock\n");
		}else{
			entry[location].Profit= entry[location].Price*num*1.5;
			entry[location].Stock=entry[location].Stock-num;
			entry[location].Sold+=num;
		}
	}
}

void sort(InventoryItemType entry[],int size)
{
	int choice=0;
	int i=0;
	int j=0;

	printf("\nEnter 1 to sort by item number or 2 to sort by item name:");
	scanf("%d",&choice);
	if(choice==1){
		for(i=0; i<size-1; i++){
			for(j=i+1; j<size-i-1;j++){
				if(strcmp(entry[j].itemNum,entry[j+1].itemNum)>0){
					InventoryItemType tmp;
					tmp=entry[j];
					entry[j]=entry[j+1];
					entry[j+1]=tmp;
				}
			}
		}
	}else{
		for(i=0; i<size-1; i++){
			for(j=0; j<size-i-1;j++){
				if(strcmp(entry[j].itemName,entry[j+1].itemName)>0){
					InventoryItemType tmp;
					tmp=entry[j];
					entry[j]=entry[j+1];
					entry[j+1]=tmp;
				}
			}
		}
	}
}

void SaveInventory(InventoryItemType br[], int *size)
{
	FILE *outp;

	if((outp = fopen("inventory.dat","w"))==0)
	{
		printf("Error cannot find file\n");
		return;
	}

	outp= fopen("inventory.dat","w");

	fprintf(outp,"%d", *size);
	fwrite(br, sizeof(InventoryItemType),*size,outp);
	fclose(outp);
}