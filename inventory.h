typedef struct {
	char itemNum[4]; //itemnum
	char itemName[20]; //company that sells the item
	unsigned int Stock; //how many of the item are instock
	unsigned int Sold; //last ship date of that item
	float Price; //cost to make the item
	float Profit; //price of the item
} InventoryItemType;

//load the inventory from the file that is being saved
void OpenFile(InventoryItemType br[], int *size);

//display the options to the user
void MenuPrint(void);

//prompts the user to get a selection
char Menu(void);

//display the current inventory to screen
void DisplayInv(InventoryItemType entry[], int size);

//display sales
void DisplaySales(InventoryItemType entry[], int size);

//function to add a new entry to the inventory
void AddItem(InventoryItemType entry[], int *size);

//function to delete a selected entry from inventory
void Delete(InventoryItemType entry[], int *size, int location);

//find location of entry that is going to be edited or deleted
int FindLocation(InventoryItemType entry[], int size);

//function to update shipment on a selected entry
void enterShipment(InventoryItemType entry[], int location);

//function to edit selected entry
void updateSales(InventoryItemType entry[], int location);

//sorts  the array of entries
void sort(InventoryItemType entry[],int size);

//save the current inventory to file
void SaveInventory(InventoryItemType br[], int *size);