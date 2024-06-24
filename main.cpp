#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
int andaze(string name) {
    ifstream file(name, ios::in | ios::binary);
    char c;
    int a = 0;
    while(file.read(&c, 1)) {
        a++;
    }
    return a;
}
class kharid {
public:
    char usrnmc[50];
    int pswrdc;
    char namep[50];
    long long int pricp;
    int nump;
};
class Date {
public:
    int day, month, year;
};
istream& operator>>(istream& is, Date& a) {
    is >> a.year;
    is >> a.month;
    is >> a.day;
    return is;
}
ostream& operator<<(ostream& x, Date& a) {
    x << " " << a.year;
    x << " " << a.month;
    x << " " << a.day;
    return x;
}
class product{
public:
    char name[50];
    int number;
    long long int price;
    Date dateOfManufacture, expirationDate;
};
istream& operator>>(istream& is, product& obj) {
    cout << "Enter the product's name:";
    is >> obj.name;
    cout << "Enter the product's number:";
    is >> obj.number;
    cout << "Enter the product's price:";
    is >> obj.price;
    cout << "Enter the product's manufacture date (yyyy mm dd):";
    is >> obj.dateOfManufacture.year
       >> obj.dateOfManufacture.month
       >> obj.dateOfManufacture.day;
    cout << "Enter the product's expiration date (yyyy mm dd):";
    is >> obj.expirationDate.year
       >> obj.expirationDate.month
       >> obj.expirationDate.day;
    cout << endl;
    return is;
}
ostream& operator<<(ostream& x, product& obj) {
    x << obj.name << " ";
    x << obj.number << " ";
    x << obj.price << " ";
    x << obj.dateOfManufacture.year << "/"
      << obj.dateOfManufacture.month << "/"
      << obj.dateOfManufacture.day << " ";
    x << obj.expirationDate.year << "/"
      << obj.expirationDate.month << "/"
      << obj.expirationDate.day << endl;
    return x;
}
class customer {
public:
    char username[50];
    int password;
    long long int balance;
    char name[50];
    char lastname[50];

    void showbalance(string usern, int pass) {
        customer cus;
        ifstream file("customer", ios::in | ios::out | ios::binary | ios::app);
        if (!file) {
            cerr << "Unable to open file";
        } else {
            while (file.read((char*)&cus, sizeof(customer))) {
                if (usern == cus.username && pass == cus.password) {
                    cout << cus.name << " " << cus.lastname << " " << cus.balance;
                    break;
                }
            }
            file.close();
        }
    }

    void inventoryAccountBalance(string usern, int pass) {
        customer cus;
        fstream file("customer", ios::in | ios::out | ios::binary);
        if (!file) {
            cerr << "Unable to open file";
        } else {
            while (file.read((char*)&cus, sizeof(customer))) {
                int pos = file.tellg();
                if (usern == cus.username && pass == cus.password) {
                    cout << "Enter the amount: " << endl;
                    long long int pool;
                    cin >> pool;
                    cus.balance += pool;
                    pos = pos - sizeof(cus);
                    file.seekg(pos);
                    file.write((char*)&cus, sizeof(customer));
                    cout << "Account balance update successfully!" << endl;
                    break;
                }
            }
            file.close();
        }
    }

    void buy(string usern, int pass) {
        customer cus;
        product pro;
        kharid kharid1;
        fstream file1("customer", ios::binary | ios::in | ios::out);
        fstream file2("product", ios::binary | ios::in | ios::out);
        fstream file3("kharid", ios::binary | ios::app);
        cout << "Enter product's name: " << endl;
        string namep;
        cin >> namep;
        if (!file1 || !file2) {
            cerr << "Unable to open file" << endl;
        } else if (file1.is_open() && file2.is_open()) {
            while (file1.read((char*)&cus, sizeof(customer))) {
                int pos1 = file1.tellg();
                if (usern == cus.username && pass == cus.password) {
                    while (file2.read((char*)&pro, sizeof(product))) {
                        int pos2 = file2.tellg();
                        if (namep == pro.name) {
                            cout << pro.name << " " << pro.price << endl;
                            cout << "How many do you want to buy? " << endl;
                            int n;
                            cin >> n;
                            long long int pric = n * pro.price;
                            if (pric <= cus.balance && n <= pro.number) {
                                cout << "**Thanks for your shoping**" << endl;
                                cus.balance -= pric;
                                pro.number -= n;
                                pos1 = pos1 - sizeof(cus);
                                pos2 = pos2 - sizeof(pro);
                                file1.seekg(pos1);
                                file2.seekg(pos2);
                                file1.write((char*)&cus, sizeof(customer));
                                file2.write((char*)&pro, sizeof(product));
                                strcpy(kharid1.usrnmc, cus.username);
                                kharid1.pswrdc = cus.password;
                                strcpy(kharid1.namep, pro.name);
                                kharid1.pricp = pro.price;
                                kharid1.nump = n;
                                file3.write((char *)&kharid1, sizeof(kharid));
                            } else if (pric > cus.balance) {
                                cout << "Your account balance is not enough!";
                            } else if (n > pro.number) {
                                cout << "You just can buy " << pro.number << " of this product!" << endl;
                            }
                            break;
                        }
                    }
                }
            }
            file1.close();
            file2.close();
            file3.close();
        }
    }

    void kharidGozashte(string user, int pass) {
        kharid kh;
        fstream file("kharid", ios::binary | ios::in | ios::out | ios::app);
        if (!file) {
            cerr << "Unable to open file";
        } else {
            while (file.read((char*)&kh, sizeof(kharid))) {
                if (kh.usrnmc == user && kh.pswrdc == pass) {
                    cout << kh.namep << " " << kh.pricp << " " << kh.nump << endl;
                }
            }
            file.close();
        }
    }



    void showpro() {
        product pro;
        fstream file("product", ios::binary | ios::app | ios::in | ios::out);
        if (file.is_open()) {
            while (file.read((char*)&pro, sizeof(product))) {
                cout << "Product Name: " << pro.name << endl;
                cout << "Product Price: " << pro.price << endl;
                cout << "Product Quantity: " << pro.number << endl;
                cout << "Product exp: " << pro.expirationDate << endl;
                cout << "Product man: " << pro.dateOfManufacture << endl;
                cout << "******************************" << endl;
            }
            file.close();
        } else {
            cout << "Unable to open file" << endl;
        }
    }

    void editprofile(string user, int pass) {
        customer cus;
        fstream file("customer", ios::in | ios::out | ios::binary);
            while (file.read((char*)&cus, sizeof(customer))) {
                int pos = file.tellg();
                if (user == cus.username && pass == cus.password) {
                    cout << "Enter new name: " << endl;
                    cin >> cus.name;
                    cout << "Enter new lastname: " << endl;
                    cin >> cus.lastname;
                    cout << "Enter new username: " << endl;
                    cin >> cus.username;
                    cout << "Enter new password: " << endl;
                    cin >> cus.password;
                    cus.balance = cus.balance;
                    pos = pos - sizeof(cus);
                    file.seekg(pos);
                    file.write((char*)&cus, sizeof(customer));
                    file.close();
                }
            }
    }
};
istream& operator>>(istream& is, customer& obj) {
    cout << "Enter customer's username:";
    is >> obj.username;
    cout << "Enter customer's password:";
    is >> obj.password;
    cout << "Enter customer's balance:";
    is >> obj.balance;
    cout << "Enter customer's name:";
    is >> obj.name;
    cout << "Enter customer's lastname:";
    is >> obj.lastname;
    cout << endl;
    return is;
}
ostream& operator<<(ostream& x, customer& obj) {
    x << obj.username << " ";
    x << obj.password << " ";
    x << obj.balance << " ";
    x << obj.name << " ";
    x << obj.lastname << " ";
    x << endl;
    return x;
}
class manager {
public:
    char username[50];
    char password[50];
    char name[50];
    char lastname[50];

    void addNman (string user, char pass[50]) {
        manager manager1;
        ifstream file2("manager", ios::binary | ios::app);
        if (!file2) {
            cerr << "Unable to open file" << endl;
        } else {
            while (file2.read((char*)&manager1, sizeof(manager))) {
                if (user == manager1.username && strcmp(pass, manager1.password) == 0) {
                    cout << "Enter manager's details" << endl;
                    cin >> manager1;
                    ofstream file("manager", ios::app | ios::binary);
                    if (file.is_open()) {
                        file.write((char*)&manager1, sizeof(manager));
                        cout << "Manager details added successfully!" << endl;
                    } else {
                        cout << "Unable to open file" << endl;
                    }
                    file.close();
                }
            }
        }
        file2.close();
    }

    void addNpro(string user, char pass[50]) {
        manager manager1;
        product product1;
        ifstream file2("manager", ios::binary | ios::app);
        if (!file2) {
            cerr << "Unable to open file" << endl;
        } else {
            while (file2.read((char*)&manager1, sizeof(manager))) {
                if (user == manager1.username && strcmp(pass, manager1.password) == 0) {
                    cout << "Enter product's details" << endl;
                    cin >> product1;
                    ofstream file("product", ios::app | ios::binary);
                    if (file.is_open()) {
                        file.write((char*)&product1, sizeof(product));
                        cout << "Product details added successfully!" << endl;
                    } else {
                        cout << "Unable to open file" << endl;
                    }
                    file.close();
                }
            }
        }
        file2.close();
    }

    void addNcus(string user, char pass[50]) {
        manager manager1;
        customer customer1;
        ifstream file2("manager", ios::binary | ios::app);
        if (!file2) {
            cerr << "Unable to open file" << endl;
        } else {
            while (file2.read((char*)&manager1, sizeof(manager))) {
                if (user == manager1.username && strcmp(pass, manager1.password) == 0) {
                    cout << "Enter customer's details" << endl;
                    cin >> customer1;
                    ofstream file("customer", ios::app | ios::binary);
                    if (file.is_open()) {
                        file.write((char*)&customer1, sizeof(customer));
                        cout << "Customer details added successfully!" << endl;
                    } else {
                        cout << "Unable to open file" << endl;
                    }
                    file.close();
                }
            }
        }
        file2.close();
    }

    void showman(string user, char pass[50]) {
        manager manager1;
        ifstream file2("manager", ios::binary | ios::app);
        if (!file2) {
            cerr << "Unable to open file" << endl;
        } else {
            while (file2.read((char*)&manager1, sizeof(manager))) {
                if (user == manager1.username && strcmp(pass, manager1.password) == 0) {
                    manager man;
                    fstream file("manager", ios::binary | ios::app | ios::in | ios::out);
                    if (file.is_open()) {
                        while (file.read((char*)&man, sizeof(manager))) {
                            cout << "Manager Name: " << man.name << endl;
                            cout << "Manager Lastname: " << man.lastname << endl;
                            cout << "Manager username: " << man.username << endl;
                            cout << "Manager Password: " << man.password << endl;
                            cout << "******************************" << endl;
                        }
                        file.close();
                    } else {
                        cout << "Unable to open file" << endl;
                    }
                }
            }
        }
        file2.close();
    }

    void showpro(string user, char pass[50]) {
        manager manager1;
        ifstream file2("manager", ios::binary | ios::app);
        if (!file2) {
            cerr << "Unable to open file" << endl;
        } else {
            while (file2.read((char*)&manager1, sizeof(manager))) {
                if (user == manager1.username && strcmp(pass, manager1.password) == 0) {
                    product pro;
                    fstream file("product", ios::binary | ios::app | ios::in | ios::out);
                    if (file.is_open()) {
                        while (file.read((char*)&pro, sizeof(product))) {
                            cout << "Product Name: " << pro.name << endl;
                            cout << "Product Price: " << pro.price << endl;
                            cout << "Product Quantity: " << pro.number << endl;
                            cout << "Product man: " << pro.dateOfManufacture << endl;
                            cout << "Product exp: " << pro.expirationDate << endl;
                            cout << "******************************" << endl;
                        }
                        file.close();
                    } else {
                        cout << "Unable to open file" << endl;
                    }
                }
            }
        }
        file2.close();
    }

    void showCus(string user, char pass[50]) {
        manager manager1;
        ifstream file2("manager", ios::binary | ios::app);
        if (!file2) {
            cerr << "Unable to open file" << endl;
        } else {
            while (file2.read((char*)&manager1, sizeof(manager))) {
                if (user == manager1.username && strcmp(pass, manager1.password) == 0) {
                    customer cus;
                    fstream file("customer", ios::binary | ios::in | ios::out | ios::app);
                    if (file.is_open()) {
                        while (file.read((char *) &cus, sizeof(customer))) {
                            cout << "Customer username: " << cus.username << endl;
                            cout << "Customer password: " << cus.password << endl;
                            cout << "Customer balance: " << cus.balance << endl;
                            cout << "Customer name: " << cus.name << endl;
                            cout << "Customer lastname: " << cus.lastname << endl;
                            cout << "******************************" << endl;
                        }
                        file.close();
                    } else {
                        cout << "Unable to open file" << endl;
                    }
                }
            }
        }
        file2.close();
    }

    void showKharid(string user, char pass[50]) {
        manager manager1;
        ifstream file2("manager", ios::binary | ios::app);
        if (!file2) {
            cerr << "Unable to open file" << endl;
        } else {
            while (file2.read((char *) &manager1, sizeof(manager))) {
                if (user == manager1.username && strcmp(pass, manager1.password) == 0) {
                    kharid kh;
                    fstream file("kharid", ios::in);
                    if (file.is_open()) {
                        while (file.read((char *) &kh, sizeof(kharid))) {
                            cout << "Customer username: " << kh.usrnmc << endl;
                            cout << "Customer password: " << kh.pswrdc << endl;
                            cout << "Product name: " << kh.namep << endl;
                            cout << "Product price: " << kh.pricp << endl;
                            cout << "Product number: " << kh.nump << endl;
                            cout << "******************************" << endl;
                        }
                        file.close();
                    } else {
                        cout << "Unable to open file" << endl;
                    }
                }
            }
        }
        file2.close();
    }

    void increaseProNum(string user, char pass[50]) {
        manager manager1;
        ifstream file2("manager", ios::binary | ios::app);
        if (!file2) {
            cerr << "Unable to open file" << endl;
        } else {
            while (file2.read((char *) &manager1, sizeof(manager))) {
                if (user == manager1.username && strcmp(pass, manager1.password) == 0) {
                    cout << "Enter the name of product you want to increase: " << endl;
                    string nam;
                    cin >> nam;
                    product pro;
                    fstream file("product", ios::in | ios::out | ios::binary);
                    if (!file) {
                        cerr << "Unable to open file" << endl;
                    } else {
                        while (file.read((char *) &pro, sizeof(product))) {
                            int pos = file.tellg();
                            if (nam == pro.name) {
                                cout << "Enter the new inventory: " << endl;
                                int n;
                                cin >> n;
                                pro.number += n;
                                pos = pos - sizeof(pro);
                                file.seekg(pos);
                                file.write((char *) &pro, sizeof(product));
                                cout << "Update successfully!" << endl;
                            }
                        }
                    }
                }
            }
        }
    }

    void mojodiStor(string user, char pass[50]) {
        manager manager1;
        ifstream file2("manager", ios::binary | ios::app);
        if (!file2) {
            cerr << "Unable to open file" << endl;
        } else {
            while (file2.read((char *) &manager1, sizeof(manager))) {
                if (user == manager1.username && strcmp(pass, manager1.password) == 0) {
                    kharid kh;
                    unsigned long int mojodi = 0;
                    fstream file("kharid", ios::binary | ios::in | ios::out | ios::app);
                    cout << "All transactions" << endl;
                    cout << "username " << "password " << "name " << "price " << "number" << endl;
                    while (file.read((char *) &kh, sizeof(kharid))) {
                        cout << kh.usrnmc << " " << kh.pswrdc << " " << kh.namep
                             << " " << kh.pricp << " " << kh.nump << endl;
                        mojodi = (kh.nump * kh.pricp) + mojodi;
                    }
                    cout << "Total sales: " << mojodi << endl << "/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*" << "endl";
                    file.close();
                }
            }
        }
    }

    void editPro (string user, char pass[50]) {
        manager man;
        ifstream file2("manager", ios::binary | ios::app);
        if (!file2) {
            cerr << "Unable to open file" << endl;
        } else {
            while (file2.read((char *) &man, sizeof(manager))) {
                if (user == man.username && strcmp(pass, man.password) == 0) {
                    man.showpro(user, pass);
                    string nam;
                    cout << "Enter the name of product you want to edit: " << endl;
                    cin >> nam;
                    fstream file("product", ios::in | ios::out | ios::binary);
                    product pro;
                    while (file.read((char*)&pro, sizeof(product))) {
                        int pos = file.tellg();
                        if (pro.name == nam) {
                            cout << "Enter new name:" << endl;
                            cin >> pro.name;
                            cout << "Enter new price:" << endl;
                            cin >> pro.price;
                            cout << "Enter new number" << endl;
                            cin >> pro.number;
                            cout << "Enter new man date:" << endl;
                            cin >> pro.dateOfManufacture;
                            cout << "Enter new exp date:" << endl;
                            cin >> pro.expirationDate;
                            pos = pos - sizeof(pro);
                            file.seekg(pos);
                            file.write((char*)&pro, sizeof(product));
                            file.close();
                            break;
                        }
                    }
                    break;
                }
            }
        }
        file2.close();
    }

    friend ostream& operator<<(ostream& x, manager& a);
    friend istream& operator>>(istream& x, manager& a);
};
istream& operator>>(istream& is, manager& obj) {
    cout << "Enter manager's username:";
    is >> obj.username;
    cout << "Enter manager's password:";
    is >> obj.password;
    cout << "Enter manager's name:";
    is >> obj.name;
    cout << "Enter manager's lastname:";
    is >> obj.lastname;
    cout << endl;
    return is;
}
ostream& operator<<(ostream& x, manager& obj) {
    x << obj.username << " ";
    x << obj.password << " ";
    x << obj.name << " ";
    x << obj.lastname << " ";
    x << endl;
    return x;
}
int main() {
    cout << "=============================================" << endl;
    cout << "                  MOT SHOP" << endl;
    cout << "=============================================" << endl;
    cout << "1. Manager" << endl;
    cout << "2. Customer" << endl;
    cout << "Choose your role:";
    int n;
    cin >> n;
    if (n == 1) {
        string user;
        char pass[50];
        manager manager1;
        cout << "Enter your user name:" << endl;
        cin >> user;
        cout << "Enter your password:" << endl;
        cin >> pass;
        int ch = 10;
        while (ch != 0) {
            cout << endl << "1. View product's list" << endl;
            cout << "2. View customer's list" << endl;
            cout << "3. View purchases list" << endl;
            cout << "4. View manager's list" << endl;
            cout << "5. Add new product" << endl;
            cout << "6. Add new customer" << endl;
            cout << "7. Add new manager" << endl;
            cout << "8. Add inventory" << endl;
            cout << "9. View store account" << endl;
            //cout << "10. Edit product detaile" << endl;
            cout << "0. Exit." << endl;
            cout << "Enter your choise" << endl;
            cin >> ch;
            switch (ch) {
                case 1: {
                    manager1.showpro(user, pass);
                    break;
                } case 2: {
                    manager1.showCus(user, pass);
                    break;
                } case 3: {
                    manager1.showKharid(user, pass);
                    break;
                } case 4: {
                    manager1.showman(user, pass);
                    break;
                } case 5: {
                    product pro;
                    manager1.addNpro(user, pass);
                    break;
                } case 6: {
                    customer cus;
                    manager1.addNcus(user, pass);
                    break;
                } case 7: {
                    manager man;
                    manager1.addNman(user, pass);
                    break;
                } case 8: {
                    manager1.increaseProNum(user, pass);
                    break;
                } case 9: {
                    manager1.mojodiStor(user, pass);
                    break;
                } case 10: {
                    manager1.editPro(user, pass);
                } case 0: {
                    break;
                }
            }
        }
    }

    if (n == 2) {
        string user;
        int pass;
        customer customer1;
        cout << "Enter your user name:" << endl;
        cin >> user;
        cout << "Enter your password:" << endl;
        cin >> pass;
        int ch = 10;
        while (ch != 0) {
            cout << endl << "1. View product's list" << endl;
            cout << "2. View past purchases" << endl;
            cout << "3. Buy" << endl;
            cout << "4. Increase account balance" << endl;
            cout << "5. View inventory" << endl;
            cout << "6. Edit profile" << endl;
            cout << "0. Exit." << endl;
            cout << "Enter your choise" << endl;
            cin >> ch;
            switch (ch) {
                case 1: {
                    customer1.showpro();
                    break;
                } case 2: {
                    customer1.kharidGozashte(user, pass);
                    break;
                } case 3: {
                    customer1.buy(user, pass);
                    break;
                } case 4: {
                    customer1.inventoryAccountBalance(user, pass);
                    break;
                } case 5: {
                    customer1.showbalance(user, pass);
                    break;
                } case 6: {
                    customer1.editprofile(user, pass);
                    break;
                } case 0: {
                    break;
                }
            }
        }
    }
}