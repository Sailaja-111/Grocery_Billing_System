#include<stdio.h>
#include<string.h>

// Structs
struct Item
{
  int id;
  char name[30];
  float price;
  float discount;
  int quantity;
  float cost;
};

struct Bill
{
  char customer_name[500];
  int num_items;
  struct Item items[100];
};



//Bill header
void billhead(char ch[50])
{
  printf("\n\n");
  printf("\t\t\t               Grocery Bill");
  printf("\n\t\t\t            -----------------");
  printf("\n\t\tInvoice To:%s", ch);
  printf("\n");
  printf("\t\t-----------------------------------------------------------------\n");
  printf("\t\t  ID\t");
  printf("\t\t  Name\t");
  printf("\t\t  Quantity\t");
  printf("\t\t  Discount\t\n");
  printf("\t\t  Cost\t\n");
  printf("\n\t\t------------------------------------------------------------------");
  printf("\n\n");
}
// Bill body
void billbody(struct Item item)
{
  printf("\t\t%d\t\t\t %s\t\t\t %d\t\t\t %.3f\t\t\t %.3f\t\n", item.id, item.name, item.quantity, item.discount, item.cost);
}
// Bill footer
void billfoot(float total)
{
  printf("\n");

  printf("\n\t\t----------------------------------------------------------");
  printf("\n\t\tGrand Total\t\t\t\t        %.3f", total);
  printf("\n\t\t----------------------------------------------------------\n");
}
// Displaying the items
void print_items(struct Item items[100], int size)
{
  int j;
  printf("Items in the catalogue :\n");
  printf("\t\t  ID\t");
  printf("\t\t  Name\t");
  printf("\t\t  Price\t");
  printf("\t\t  Discount\t\n");
  for (j = 0; j < size; j++)
  {
    printf("\t\t%d\t\t\t %s\t\t\t %.3f\t\t\t %.3f\t\n", items[j].id, items[j].name, items[j].price, items[j].discount);
  }
}

void main()
{


  struct Item items[100];
  int choice, password, i, j, option, start, k, position,size= 16;
  char temp, temp1, str[16][20] = {"Tomatoes", "Onions", "Potatoes", "Carrots", "Milk", "Curd", "Ice Cream", "Cheese", "Flour", "Pepper", "Sugar", "Salt", "Apples", "Bananas", "Grapes", "Berries"};
  int price[16] = {120, 100, 90, 90, 100, 50, 150, 120, 80, 90, 80, 20, 60, 70, 80, 70};
  int discount[16] = {10, 25, 20, 15, 12, 30, 0, 10, 20, 34, 12, 15, 20, 0, 12, 16};


  for (i = 0; i < size; i++)
  {

    items[i].id = rand() % 10000;
    strcpy(items[i].name, str[i]);
    items[i].price = price[i];
    items[i].discount = discount[i];
  }

start:
  printf("***WELCOME TO GROCERY STORE*****\n");
  printf("Choose the action to be performed :\n\t enter 1 :Change in inventory \n\t enter 2 :Billing\n");
  scanf("%d", &choice);

  if (choice == 1)
  {
    for (i = 1; i <= 3; i++)
    {
      printf("================================Enter the password===============================\n");
      scanf("%d", &password);

      if (password == 260204)
      {
        printf("Choose the options from list of actions:\n\t enter 1 :Add an item\n\t enter 2 : Remove an item \n");
        scanf("%d", &option);
        break;
      }
      else
      {
        printf("**|| Password is incorrect. %d attempts left ||***\n", 3 - i);
      }
    }
    if (i == 4)
    {
      printf("Sorry.. 3 wrong attempts!\n");
      goto start;
    }
    if (option == 1)
    {
      if (size== 100)
      {
        printf("Catalogue maximum size reached. Please remove some items.");
        goto start;
      }
      struct Item item;
      printf("Input the id for item to be added\n");
      scanf("%d", &item.id);

      printf("Enter the name of the item\n");
      scanf("%s", &item.name);

      printf("Enter the price of the item\n");
      scanf("%f", &item.price);

      printf("Enter the discount on the item\n");
      scanf("%f", &item.discount);

      items[size++] = item;

      printf("%d\t%s\t%.3f\t%.3f\nThe item is successfully added\n", item.id, item.name, item.price, item.discount);
      print_items(items,size);
      goto start;
    }
    else if (option == 2)
    {
      print_items(items, size);
      printf("Enter the ID to be removed\n");
      scanf("%d", &position);
      int index = -1;
      for (k = 0; k < size; k++)
      {
        if (items[k].id == position)
        {
          index = k;
          break;
        }
      }
      if (index == -1)
      {
        printf("Item not found!");
        goto start;
      }
      else
      {
        for (k = index; k < size - 1; k++)
        {
          struct Item temp;
          temp = items[k];
          items[k] = items[k + 1];
          items[k + 1] = temp;
        }
        size--;
      }
      print_items(items, size);
      goto start;
    }
    else
    {
      printf("Invalid input!\n");
    }
  }
  else if (choice == 2)
  {
    int id;
    float total = 0;
    struct Bill bill;
    print_items(items, size);
    printf("\nEnter the Name Of The Customer :");
    scanf("%s", bill.customer_name);
    printf("\nPlease Enter the Number of Items (max 100):");
    scanf("%d", &bill.num_items);
    if (bill.num_items > 100)
    {
      printf("Maximum items is 100.\n");
      goto start;
    }
    for (i = 0; i < bill.num_items; i++)
    {
      printf("\n\n");
      printf("Please Enter the ID of Item %d:\n", i + 1);
      scanf("%d", &id);
      int index = -1;
      for (k = 0; k < size; k++)
      {
        if (items[k].id == id)
        {
          index = k;
          break;
        }
      }
      if (index == -1)
      {
        printf("Item not found");
        i--;
        continue;
      }
      bill.items[i] = items[index];
      printf("Please Enter the Quantity of %s:\n", bill.items[i].name);
      scanf("%d", &bill.items[i].quantity);
      bill.items[i].cost = (100 - bill.items[i].discount) * bill.items[i].price * bill.items[i].quantity / 100;
      total += bill.items[i].cost;
    }
    billhead(bill.customer_name);
    for (i = 0; i < bill.num_items; i++)
    {
      billbody(bill.items[i]);
    }
    billfoot(total);
  }else{
    printf("Invalid Input!\n");
  }
}
