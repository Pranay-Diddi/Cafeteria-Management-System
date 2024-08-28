#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct MenuItem {
    int id;
    char name[50];
    double price;
    int stock; 
    int quantityOrdered; 
    struct MenuItem* next;
};
typedef struct MenuItem MenuItem;

const char adminPassword[] = "Pranay@123"; 

MenuItem* createMenuItem(int id, char* name, double price, int stock) {
    MenuItem* newItem = (MenuItem*)malloc(sizeof(MenuItem));
    newItem->id = id;
    strcpy(newItem->name, name);
    newItem->price = price;
    newItem->stock = stock;
    newItem->quantityOrdered = 0;
    newItem->next = NULL;
    return newItem;
}

void addMenuItem(MenuItem** head, int id, char* name, double price, int stock) {
    MenuItem* newItem = createMenuItem(id, name, price, stock);
    if (*head == NULL) {
        *head = newItem;
    } else {
        MenuItem* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newItem;
    }
}

void displayMenu(MenuItem* head) {
    printf("--------- Cafeteria Menu ---------\n");
    MenuItem* temp = head;
    while (temp != NULL) {
        printf("ID: %d\t", temp->id);
        printf("Name: %s\t", temp->name);
        printf("Price: $%.2lf\t", temp->price);
        printf("Stock: %d\n", temp->stock);
        temp = temp->next;
    }
}

MenuItem* selectItemFromMenu(MenuItem* head, int id) {
    MenuItem* temp = head;
    while (temp != NULL) {
        if (temp->id == id && temp->stock > 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

int authenticateAdmin() {
    char inputPassword[50];
    printf("Enter admin password: ");
    scanf("%s", inputPassword);

    if (strcmp(inputPassword, adminPassword) == 0) {
        return 1; 
    } else {
        printf("Incorrect password. Access denied.\n");
        return 0; 
    }
}

void editMenuItem(MenuItem* head, int id) {
    if (!authenticateAdmin()) return; 
    
    MenuItem* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            printf("Editing item: %s\n", temp->name);
            printf("Enter new price: ");
            scanf("%lf", &(temp->price));
            printf("Enter new stock: ");
            scanf("%d", &(temp->stock));
            printf("Item updated successfully!\n");
            return;
        }
        temp = temp->next;
    }
    printf("Item with ID %d not found.\n", id);
}

void removeMenuItem(MenuItem** head, int id) {
    if (!authenticateAdmin()) return; 
    
    MenuItem* temp = *head;
    MenuItem* prev = NULL;

    while (temp != NULL) {
        if (temp->id == id) {
            if (prev == NULL) {
                *head = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            printf("Item with ID %d removed successfully.\n", id);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Item with ID %d not found.\n", id);
}

void searchMenuItemByName(MenuItem* head, char* name) {
    MenuItem* temp = head;
    int found = 0;
    printf("Search results for \"%s\":\n", name);
    while (temp != NULL) {
        if (strstr(temp->name, name) != NULL) {
            printf("ID: %d\t", temp->id);
            printf("Name: %s\t", temp->name);
            printf("Price: $%.2lf\t", temp->price);
            printf("Stock: %d\n", temp->stock);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found) {
        printf("No items found with name containing \"%s\".\n", name);
    }
}

void viewTotalOrders(MenuItem* head) {
    double totalRevenue = 0.0;
    MenuItem* temp = head;
    printf("Order Summary:\n");
    printf("-------------------------\n");
    while (temp != NULL) {
        if (temp->quantityOrdered > 0) {
            printf("%s (Quantity: %d) - $%.2lf\n", temp->name, temp->quantityOrdered, (temp->price * temp->quantityOrdered));
            totalRevenue += (temp->price * temp->quantityOrdered);
        }
        temp = temp->next;
    }
    printf("-------------------------\n");
    printf("Total Revenue: $%.2lf\n", totalRevenue);
}

void viewLowStockItems(MenuItem* head, int threshold) {
    MenuItem* temp = head;
    printf("Items with stock below %d:\n", threshold);
    printf("-------------------------\n");
    while (temp != NULL) {
        if (temp->stock < threshold) {
            printf("ID: %d\t", temp->id);
            printf("Name: %s\t", temp->name);
            printf("Stock: %d\n", temp->stock);
        }
        temp = temp->next;
    }
}

int main() {
    MenuItem* head = NULL;
    double totalPrice = 0.0;

    // Add menu items
    addMenuItem(&head, 1, "Burger", 6.49, 30);
    addMenuItem(&head, 2, "Pizza", 7.49, 50);
    addMenuItem(&head, 3, "Salad", 3.99, 30);
    addMenuItem(&head, 4, "Chicken Sandwich", 5.49, 35);
    addMenuItem(&head, 5, "French Fries", 2.99, 35);
    addMenuItem(&head, 6, "Grilled Cheese", 3.99, 20);
    addMenuItem(&head, 7, "Iced Coffee", 3.49, 30);
    addMenuItem(&head, 8, "Chocolate Chip Cookie", 2.49, 35);
    addMenuItem(&head, 9, "Caesar Salad", 5.99, 20);
    addMenuItem(&head, 10, "Chicken Shawarma", 4.99, 40);

    
    int choice;
    do {
        printf("\n1. Display Menu\n2. Order Item\n3. Edit Menu Item\n4. Remove Menu Item\n5. Search Menu Item by Name\n6. View Total Orders\n7. View Low Stock Items\n8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");
        switch (choice) {
            case 1:
                displayMenu(head);
                break;
            case 2: {
                int selectedItemId, quantity;
                printf("Enter the ID of the item you want to select: ");
                scanf("%d", &selectedItemId);

                MenuItem* selectedMenuItem = selectItemFromMenu(head, selectedItemId);
                if (selectedMenuItem != NULL) {
                    printf("You selected: %s\n", selectedMenuItem->name);
                    printf("Price: $%.2lf\n", selectedMenuItem->price);
                    printf("Stock available: %d\n", selectedMenuItem->stock);

                    printf("Enter quantity: ");
                    scanf("%d", &quantity);
                    if (quantity > selectedMenuItem->stock) {
                        printf("\nQuantity exceeded, please reconsider the quantity\n");
                    } else {
                        if (quantity > 0) {
                            selectedMenuItem->stock -= quantity; 
                            selectedMenuItem->quantityOrdered += quantity; 
                            totalPrice += (selectedMenuItem->price * quantity); 
                        } else {
                            printf("Quantity must be greater than 0.\n");
                        }
                    }
                } else {
                    printf("Item not available or out of stock.\n");
                }
                break;
            }
            case 3: {
                int editItemId;
                printf("Enter the ID of the item to edit: ");
                scanf("%d", &editItemId);
                editMenuItem(head, editItemId);
                break;
            }
            case 4: {
                int removeItemId;
                printf("Enter the ID of the item to remove: ");
                scanf("%d", &removeItemId);
                removeMenuItem(&head, removeItemId);
                break;
            }
            case 5: {
                char searchName[50];
                printf("Enter the name of the item to search: ");
                scanf("%s", searchName);
                searchMenuItemByName(head, searchName);
                break;
            }
            case 6:
                viewTotalOrders(head);
                break;
            case 7: {
                int threshold;
                printf("Enter the stock threshold: ");
                scanf("%d", &threshold);
                viewLowStockItems(head, threshold);
                break;
            }
            case 8:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice, please try again.\n");
                break;
        }
    } while (choice != 8);

    return 0;
}
