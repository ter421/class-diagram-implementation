#include <iostream>
#include <string>
using namespace std;

class Item 
{
private:
    int id;
    string itemName;
    double itemPrice;

public:
    Item() : id(0), itemName(""), itemPrice(0.0) {}
    Item(int itemId, string name, double price) : id(itemId), itemName(name), itemPrice(price) {}

    int getId() const { return id; }
    string getName() const { return itemName; }
    double getPrice() const { return itemPrice; }

    void showItem() const 
    {
        cout << id << "\t" << itemName << "\t" << itemPrice << endl;
    }
};

class Purchase 
{
private:
    int purchaseId;
    struct PurchaseDetail 
    {
        Item item;
        int amount;
    };
    
    PurchaseDetail details[100]; 
    int totalItems;
    double totalCost;

public:
    Purchase(int id) : purchaseId(id), totalItems(0), totalCost(0.0) {}

    void addItem(Item item, int amount) 
    {
        details[totalItems].item = item;
        details[totalItems].amount = amount;
        totalCost += item.getPrice() * amount;
        totalItems++;
    }

    double calculateTotal() const 
    {
        return totalCost;
    }

    void showPurchase() const 
    {
        cout << "Purchase ID: " << purchaseId << endl;
        cout << "Total Cost: " << totalCost << endl;
        cout << "Purchase Details:\n\nItem ID\tName\tPrice\tAmount" << endl;
        for (int i = 0; i < totalItems; ++i) 
        {
            cout << details[i].item.getId() << "\t\t"
                 << details[i].item.getName() << "\t"
                 << details[i].item.getPrice() << "\t"
                 << details[i].amount << endl;
        }
    }
};

class Cart 
{
private:
    int cartId;
    struct CartEntry 
    {
        Item item;
        int amount;
    };
    CartEntry entries[100];  
    int numberOfItems;

public:
    Cart(int id) : cartId(id), numberOfItems(0) {}

    void addEntry(Item item, int amount) 
    {
        for (int i = 0; i < numberOfItems; ++i) 
        {
            if (entries[i].item.getId() == item.getId()) 
            {
                entries[i].amount += amount;
                return;
            }
        }
        entries[numberOfItems].item = item;
        entries[numberOfItems].amount = amount;
        numberOfItems++;
    }

    void removeEntry(Item item) 
    {
        for (int i = 0; i < numberOfItems; ++i) 
        {
            if (entries[i].item.getId() == item.getId()) 
            {
                for (int j = i; j < numberOfItems - 1; ++j) 
                {
                    entries[j] = entries[j + 1];
                }
                numberOfItems--;
                break;
            }
        }
    }

    void showCart() const 
    {
        if (numberOfItems == 0) 
        {
            cout << endl;
            cout << "\nCart is empty!" << endl;
            return;
        }

        cout << "Cart ID: " << cartId << endl;
        cout << endl;
        cout << "ID\tName\tPrice\tAmount" << endl;

        for (int i = 0; i < numberOfItems; ++i) 
        {
            cout << entries[i].item.getId() << "\t"
                 << entries[i].item.getName() << "\t"
                 << entries[i].item.getPrice() << "\t"
                 << entries[i].amount << endl;
        }
    }

    void finalizePurchase() 
    {
        showCart();
        numberOfItems = 0; 
    }

    CartEntry* getEntries() { return entries; }
    int getNumberOfItems() const { return numberOfItems; }
};

class Client 
{
private:
    int clientId;
    string clientName;
    string clientEmail;
    int orderCounter;

public:
    Client(int id, string name, string email) : clientId(id), clientName(name), clientEmail(email), orderCounter(1) {}

    Purchase createPurchase(Cart& cart) 
    {
        Purchase newPurchase(orderCounter++);

        for (int i = 0; i < cart.getNumberOfItems(); ++i) 
        {
            newPurchase.addItem(cart.getEntries()[i].item, cart.getEntries()[i].amount);
        }

        return newPurchase;
    }

    void showClientInfo() const 
    {
        cout << "Client ID: " << clientId << "\nName: " << clientName << "\nEmail: " << clientEmail << endl;
    }
};

int main() 
{
    Item items[100];  
    int itemCount = 0;   

    Client client(1, "Michelangelo", "mikey@example.com");
    Cart cart(101);

    int option = 0;
    bool running = true;
    while (running) 
    {
        cout << "\n1. Add Item to System\n"
             << "2. View Items\n"
             << "3. View Cart\n"
             << "4. Add Item to Cart\n"
             << "5. Remove Item from Cart\n"
             << "6. Checkout\n"
             << "7. Exit\n";
        
        cout << endl;
        cout << "Enter your choice: ";
        cin >> option;
        cout << endl;

        if (option == 1) 
        {
            int id;
            string name;
            double price;

            cout << "Enter item ID: ";
            cin >> id;
            cout << "Enter item name: ";
            cin.ignore(); 
            getline(cin, name);
            cout << "Enter item price: ";
            cin >> price;

            cout << endl;

            items[itemCount] = Item(id, name, price);
            itemCount++;
            cout << "Item added successfully!" << endl;

        } 
        
        else if (option == 2) 
        {
            if (itemCount == 0) 
            {
                cout << "No items available." << endl;
            } 
            
            else 
            {
                cout << "ID\tName\tPrice" << endl;
                for (int i = 0; i < itemCount; ++i) 
                {
                    items[i].showItem();
                }
            }
        } 
        
        else if (option == 3) 
        {
            cart.showCart();
        } 
        
        else if (option == 4) 
        {
            if (itemCount == 0) 
            {
                cout << "No items available to add to cart!" << endl;
            } 
            
            else 
            {
                int id, quantity;
                cout << "Enter item ID: ";
                cin >> id;
                cout << "Enter quantity: ";
                cin >> quantity;
                bool found = false;
                for (int i = 0; i < itemCount; ++i) 
                {
                    if (items[i].getId() == id) 
                    {
                        cart.addEntry(items[i], quantity);
                        cout << "\nItem added to cart!" << endl;
                        found = true;
                        break;
                    }
                }
                
                if (!found) 
                {
                    cout << "\nInvalid item ID!" << endl;
                }
            }
        } 
        
        else if (option == 5) 
        {
            int id;
            cout << "Enter item ID to remove from cart: ";
            cin >> id;
            cout << endl;
            bool found = false;
            for (int i = 0; i < itemCount; ++i) 
            {
                if (items[i].getId() == id) 
                {
                    cart.removeEntry(items[i]);
                    cout << "Item removed from cart!" << endl;
                    found = true;
                    break;
                }
            }
            
            if (!found) 
            {
                cout << "\nInvalid item ID!" << endl;
            }
        } 
        
        else if (option == 6) 
        {
            cout << "Purchase Details:" << endl;
            cout << endl;
            Purchase newPurchase = client.createPurchase(cart);
            newPurchase.showPurchase();  
            cout << endl;
        } 
        
        else if (option == 7) 
        {
            running = false;
            cout << "Exiting..." << endl;
        } 
        
        else 
        {
            cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
