# Cafeteria-Management-System


This project is a simple Cafeteria Menu Management System written in C. It allows users to view the menu, order items, and manage the menu by editing or removing items. The system also includes features to search for menu items, view total orders, and identify items with low stock. Admin authentication is required for sensitive operations like editing or removing menu items.

## Features

1. **Display Menu**: View all available items in the menu along with their details like ID, name, price, and stock availability.

2. **Order Item**: Users can select an item by its ID, specify the quantity, and the system will update the stock accordingly. It also tracks the total price for ordered items.

3. **Edit Menu Item**: Admins can edit the price and stock of an existing menu item after successful authentication.

4. **Remove Menu Item**: Admins can remove a menu item from the list after successful authentication.

5. **Search Menu Item by Name**: Users can search for menu items by entering a part or full name of the item. The system displays matching items along with their details.

6. **View Total Orders**: Display a summary of all items ordered, including the quantity and total revenue generated.

7. **View Low Stock Items**: Identify and display menu items that have stock below a user-defined threshold.

8. **Admin Authentication**: Certain operations, like editing or removing menu items, require admin authentication. The default admin password is `Pranay@123`.

## Example Usage
**Ordering an Item**: Select option 2, enter the item ID, and specify the quantity. The stock will be updated, and the total price will be calculated.


**Editing an Item**: Select option 3, enter the item ID, and input the new price and stock. Admin authentication is required.


**Viewing Low Stock Items**: Select option 7 and enter the stock threshold to see items with stock below that level.

## Admin Authentication
**Default Admin Password**: Pranay@123


**Authentication Process**: For operations that require admin privileges (e.g., editing or removing menu items), the system will prompt for the admin password. If the correct password is provided, the operation will proceed.

