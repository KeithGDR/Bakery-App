// Bakery-App.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Bakery-App.h"

#define DEBUG

using namespace std;

//Predefining functions above for easy backwards selection.
void openMain();
void openSection(int section);
void openItem(int section, int selection);

//Define the specific sections to index values.
#define SECTION_CLIENTS 1
#define SECTION_REPRESENTATIVES 2
#define SECTION_PRODUCTS 3
#define SECTION_SALES 4

std::string ReplaceString(std::string subject, const std::string& search, const std::string& replace) {
    size_t pos = 0;

    while ((pos = subject.find(search, pos)) != std::string::npos) {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }

    return subject;
}

std::string FinToStr(std::fstream& in) {
    std::ostringstream sstr;
    sstr << in.rdbuf();
    return sstr.str();
}

namespace Clients {
    fstream parse(bool update = false, ios_base::openmode mode = ios::out | ios::in | ios::app) {
        fstream fin;
        fin.open(update ? "clients2.csv" : "clients.csv", mode);
        return fin;
    }

    void list() {
        fstream fin = Clients::parse();

        if (!fin.is_open()) {
            cout << "Unable to open file.\n---\nPlease input any value to continue: ";
            int selection;
            cin >> selection;
            return;
        }

        cout << " :: Name, Address, Sales\n";

        string line; bool found = false;
        while (getline(fin, line))
        {
            cout << line << '\n';
            found = true;
        }

        fin.close();

        if (!found) {
            cout << "No Clients Found";
        }

        cout << "\n---\nPlease input any value to continue: ";
        int selection;
        cin >> selection;

        openSection(SECTION_CLIENTS);
    }

    void specific() {
        cout << "\n---\nPlease input a name to search for: ";
        string input;
        getline(cin >> ws, input);

        fstream fin = Clients::parse();

        if (!fin.is_open()) {
            cout << "Unable to open file.\n---\nPlease input any value to continue: ";
            int selection;
            cin >> selection;
            return;
        }

        cout << " :: Name, Address, Sales\n";
        
        string line;
        while (getline(fin, line)) {
            if (line.find(input) != string::npos) {
                cout << line << "\n";
            }
        }

        fin.close();

        cout << "\n---\nPlease input any value to continue: ";
        int selection;
        cin >> selection;

        openSection(SECTION_CLIENTS);
    }

    void add() {
        cout << " :: Name, Address, Sales\n";
        cout << "\n---\nPlease input a new client: ";
        string input;
        getline(cin >> ws, input);

        fstream fin = Clients::parse();

        if (!fin.is_open()) {
            cout << "Unable to open file.\n---\nPlease input any value to continue: ";
            int selection;
            cin >> selection;
            return;
        }

        fin << input;
        cout << "Client has been added: " << input;

        fin.close();

        cout << "\n---\nPlease input any value to continue: ";
        int selection;
        cin >> selection;

        openSection(SECTION_CLIENTS);
    }

    void update() {
        cout << "\n---\nPlease input a name to search for: ";

        string search;
        getline(cin >> ws, search);

        fstream fin = Clients::parse();

        if (!fin.is_open()) {
            cout << "Unable to open file.\n---\nPlease input any value to continue: ";
            int selection;
            cin >> selection;
            return;
        }

        string line; bool found = false;
        while (getline(fin, line))
        {
            if (line.find(search) != string::npos) {
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Unable to find client.\n---\nPlease input any value to continue: ";
            int selection;
            cin >> selection;
            return;
        }

        fin.close();
        fin = Clients::parse();
        string clients = FinToStr(fin);
        fin.close();

        fstream fin2 = Clients::parse(true);

        if (!fin2.is_open()) {
            cout << "Unable to open temporary file.\n---\nPlease input any value to continue: ";
            int selection;
            cin >> selection;
            return;
        }

        cout << "Client found: " << line << endl;
        cout << "\n---\nPlease input the updates: " << endl;
        cout << " :: Example: Name,Address,Sales\n";
        cout << "Update to: ";

        string update;
        getline(cin >> ws, update);

        clients = ReplaceString(clients, line, update);

        fin2 << clients;
        fin2.close();

        cout << "\n---\nClient has been updated: " << update << "\n";

        if (remove("clients.csv")) {
            perror("Unknown error while deleting file 'clients.csv': ");
        }
        if (rename("clients2.csv", "clients.csv")) {
            perror("Unknown error while renaming file 'clients2.csv': ");
        }

        cout << "\n---\nPlease input any value to continue: ";
        int selection;
        cin >> selection;

        openSection(SECTION_CLIENTS);
    }
}

namespace Representatives {
    fstream parse(bool update = false, ios_base::openmode mode = ios::out | ios::in | ios::app) {
        fstream fin;
        fin.open(update ? "representatives2.csv" : "representatives.csv", mode);
        return fin;
    }

    void list() {
        fstream fin = Representatives::parse();

        if (!fin.is_open()) {
            cout << "Unable to open file.\n---\nPlease input any value to continue: ";
            int selection;
            cin >> selection;
            return;
        }

        cout << " :: Name, Address, Sales\n";

        string line; bool found = false;
        while (getline(fin, line))
        {
            cout << line << '\n';
            found = true;
        }

        fin.close();

        if (!found) {
            cout << "No Representatives Found";
        }

        cout << "\n---\nPlease input any value to continue: ";
        int selection;
        cin >> selection;

        openSection(SECTION_REPRESENTATIVES);
    }

    void specific() {
        cout << "\n---\nPlease input a name to search for: ";
        string input;
        getline(cin >> ws, input);

        fstream fin = Representatives::parse();

        if (!fin.is_open()) {
            cout << "Unable to open file.\n---\nPlease input any value to continue: ";
            int selection;
            cin >> selection;
            return;
        }

        cout << " :: Name, Address, Sales\n";

        string line;
        while (getline(fin, line)) {
            if (line.find(input) != string::npos) {
                cout << line << "\n";
            }
        }

        fin.close();

        cout << "\n---\nPlease input any value to continue: ";
        int selection;
        cin >> selection;

        openSection(SECTION_REPRESENTATIVES);
    }

    void add() {
        cout << " :: Name, Address, Sales\n";
        cout << "\n---\nPlease input a new representative: ";
        string input;
        getline(cin >> ws, input);

        fstream fin = Representatives::parse();

        if (!fin.is_open()) {
            cout << "Unable to open file.\n---\nPlease input any value to continue: ";
            int selection;
            cin >> selection;
            return;
        }

        fin << input;
        cout << "Representative has been added: " << input;

        fin.close();

        cout << "\n---\nPlease input any value to continue: ";
        int selection;
        cin >> selection;

        openSection(SECTION_REPRESENTATIVES);
    }

    void update() {
        cout << "\n---\nPlease input a name to search for: ";

        string search;
        getline(cin >> ws, search);

        fstream fin = Representatives::parse();

        if (!fin.is_open()) {
            cout << "Unable to open file.\n---\nPlease input any value to continue: ";
            int selection;
            cin >> selection;
            return;
        }

        string line; bool found = false;
        while (getline(fin, line))
        {
            if (line.find(search) != string::npos) {
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Unable to find client.\n---\nPlease input any value to continue: ";
            int selection;
            cin >> selection;
            return;
        }

        fin.close();
        fin = Representatives::parse();
        string representatives = FinToStr(fin);
        fin.close();

        fstream fin2 = Representatives::parse(true);

        if (!fin2.is_open()) {
            cout << "Unable to open temporary file.\n---\nPlease input any value to continue: ";
            int selection;
            cin >> selection;
            return;
        }

        cout << "Representative found: " << line << endl;
        cout << "\n---\nPlease input the updates: " << endl;
        cout << " :: Example: Name,Address,Sales\n";
        cout << "Update to: ";

        string update;
        getline(cin >> ws, update);

        representatives = ReplaceString(representatives, line, update);

        fin2 << representatives;
        fin2.close();

        cout << "\n---\nRepresentative has been updated: " << update << "\n";

        if (remove("representatives.csv")) {
            perror("Unknown error while deleting file 'representatives.csv': ");
        }
        if (rename("representatives2.csv", "representatives.csv")) {
            perror("Unknown error while renaming file 'representatives2.csv': ");
        }

        cout << "\n---\nPlease input any value to continue: ";
        int selection;
        cin >> selection;

        openSection(SECTION_REPRESENTATIVES);
    }

    void report() {

    }
}

namespace Products {
    fstream parse(bool update = false, ios_base::openmode mode = ios::out | ios::in | ios::app) {
        fstream fin;
        fin.open(update ? "products2.csv" : "products.csv", mode);
        return fin;
    }

    void list() {
        fstream fin = Products::parse();

        if (!fin.is_open()) {
            cout << "Unable to open file.\n---\nPlease input any value to continue: ";
            int selection;
            cin >> selection;
            return;
        }

        cout << " :: Name, Type, Price\n";

        string line; bool found = false;
        while (getline(fin, line))
        {
            cout << line << '\n';
            found = true;
        }

        fin.close();

        if (!found) {
            cout << "No Products Found";
        }

        cout << "\n---\nPlease input any value to continue: ";
        int selection;
        cin >> selection;

        openSection(SECTION_PRODUCTS);
    }

    void specific() {
        cout << "\n---\nPlease input a name to search for: ";
        string input;
        getline(cin >> ws, input);

        fstream fin = Products::parse();

        if (!fin.is_open()) {
            cout << "Unable to open file.\n---\nPlease input any value to continue: ";
            int selection;
            cin >> selection;
            return;
        }

        cout << " :: Name, Type, Price\n";

        string line;
        while (getline(fin, line)) {
            if (line.find(input) != string::npos) {
                cout << line << "\n";
            }
        }

        fin.close();

        cout << "\n---\nPlease input any value to continue: ";
        int selection;
        cin >> selection;

        openSection(SECTION_PRODUCTS);
    }

    void add() {
        cout << " :: Name, Type, Price\n";
        cout << "\n---\nPlease input a new product: ";
        string input;
        getline(cin >> ws, input);

        fstream fin = Products::parse();

        if (!fin.is_open()) {
            cout << "Unable to open file.\n---\nPlease input any value to continue: ";
            int selection;
            cin >> selection;
            return;
        }

        fin << input;
        cout << "Product has been added: " << input;

        fin.close();

        cout << "\n---\nPlease input any value to continue: ";
        int selection;
        cin >> selection;

        openSection(SECTION_PRODUCTS);
    }

    void update() {
        cout << "\n---\nPlease input a name to search for: ";

        string search;
        getline(cin >> ws, search);

        fstream fin = Products::parse();

        if (!fin.is_open()) {
            cout << "Unable to open file.\n---\nPlease input any value to continue: ";
            int selection;
            cin >> selection;
            return;
        }

        string line; bool found = false;
        while (getline(fin, line))
        {
            if (line.find(search) != string::npos) {
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Unable to find client.\n---\nPlease input any value to continue: ";
            int selection;
            cin >> selection;
            return;
        }

        fin.close();
        fin = Products::parse();
        string products = FinToStr(fin);
        fin.close();

        fstream fin2 = Products::parse(true);

        if (!fin2.is_open()) {
            cout << "Unable to open temporary file.\n---\nPlease input any value to continue: ";
            int selection;
            cin >> selection;
            return;
        }

        cout << "Product found: " << line << endl;
        cout << "\n---\nPlease input the updates: " << endl;
        cout << " :: Example: Name,Type,Price\n";
        cout << "Update to: ";

        string update;
        getline(cin >> ws, update);

        products = ReplaceString(products, line, update);

        fin2 << products;
        fin2.close();

        cout << "\n---\nProduct has been updated: " << update << "\n";

        if (remove("products.csv")) {
            perror("Unknown error while deleting file 'products.csv': ");
        }
        if (rename("products2.csv", "products.csv")) {
            perror("Unknown error while renaming file 'products2.csv': ");
        }

        cout << "\n---\nPlease input any value to continue: ";
        int selection;
        cin >> selection;

        openSection(SECTION_PRODUCTS);
    }

    void report() {

    }
}

namespace Sales {
    fstream parse(bool update = false, ios_base::openmode mode = ios::out | ios::in | ios::app) {
        fstream fin;
        fin.open(update ? "sales2.csv" : "sales.csv", mode);
        return fin;
    }

    void list() {
        fstream fin = Sales::parse();

        if (!fin.is_open()) {
            cout << "Unable to open file.\n---\nPlease input any value to continue: ";
            int selection;
            cin >> selection;
            return;
        }

        cout << " :: Name, Product, Date, Representative\n";

        string line; bool found = false;
        while (getline(fin, line))
        {
            cout << line << '\n';
            found = true;
        }

        fin.close();

        if (!found) {
            cout << "No Sales Found";
        }

        cout << "\n---\nPlease input any value to continue: ";
        int selection;
        cin >> selection;

        openSection(SECTION_SALES);
    }

    void specific() {
        cout << "\n---\nPlease input a name to search for: ";
        string input;
        getline(cin >> ws, input);

        fstream fin = Sales::parse();

        if (!fin.is_open()) {
            cout << "Unable to open file.\n---\nPlease input any value to continue: ";
            int selection;
            cin >> selection;
            return;
        }

        cout << " :: Name, Product, Date, Representative\n";

        string line;
        while (getline(fin, line)) {
            if (line.find(input) != string::npos) {
                cout << line << "\n";
            }
        }

        fin.close();

        cout << "\n---\nPlease input any value to continue: ";
        int selection;
        cin >> selection;

        openSection(SECTION_SALES);
    }

    void add() {
        cout << " :: Name, Product, Date, Representative\n";
        cout << "\n---\nPlease input a new sale: ";
        string input;
        getline(cin >> ws, input);

        fstream fin = Sales::parse();

        if (!fin.is_open()) {
            cout << "Unable to open file.\n---\nPlease input any value to continue: ";
            int selection;
            cin >> selection;
            return;
        }

        fin << input;
        cout << "Sale has been added: " << input;

        fin.close();

        cout << "\n---\nPlease input any value to continue: ";
        int selection;
        cin >> selection;

        openSection(SECTION_SALES);
    }

    void update() {
        cout << "\n---\nPlease input a name to search for: ";

        string search;
        getline(cin >> ws, search);

        fstream fin = Sales::parse();

        if (!fin.is_open()) {
            cout << "Unable to open file.\n---\nPlease input any value to continue: ";
            int selection;
            cin >> selection;
            return;
        }

        string line; bool found = false;
        while (getline(fin, line))
        {
            if (line.find(search) != string::npos) {
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Unable to find client.\n---\nPlease input any value to continue: ";
            int selection;
            cin >> selection;
            return;
        }

        fin.close();
        fin = Sales::parse();
        string sales = FinToStr(fin);
        fin.close();

        fstream fin2 = Sales::parse(true);

        if (!fin2.is_open()) {
            cout << "Unable to open temporary file.\n---\nPlease input any value to continue: ";
            int selection;
            cin >> selection;
            return;
        }

        cout << "Sales found: " << line << endl;
        cout << "\n---\nPlease input the updates: " << endl;
        cout << " :: Example: Name,Type,Price,Representative\n";
        cout << "Update to: ";

        string update;
        getline(cin >> ws, update);

        sales = ReplaceString(sales, line, update);

        fin2 << sales;
        fin2.close();

        cout << "\n---\nSales has been updated: " << update << "\n";

        if (remove("sales.csv")) {
            perror("Unknown error while deleting file 'sales.csv': ");
        }
        if (rename("sales2.csv", "sales.csv")) {
            perror("Unknown error while renaming file 'sales2.csv': ");
        }

        cout << "\n---\nPlease input any value to continue: ";
        int selection;
        cin >> selection;

        openSection(SECTION_SALES);
    }
}

char const* getSectionName(int section) {
    switch (section) {
        case 1: {
            return "Client Information";
        }
        case 2: {
            return "Sales Representatives";
        }
        case 3: {
            return "Products/Services";
        }
        case 4: {
            return "Sales";
        }
        case 5: {
            return "Dummy Data";
        }
        case 6: {
            return "Clear Data";
        }
    }
}

void createDummyData() {
    fstream fin;
    
    fin = Clients::parse();

    if (fin.is_open()) {
        cout << "[DEBUG] Creating clients dummy data...\n";
        fin << "Fraz,800 East 2nd St.,1\nRyan,902 Wakeway Rd.,1\nCourtney,128 West 12th St.,1\n";
        fin.close();
    }

    fin = Representatives::parse();

    if (fin.is_open()) {
        cout << "[DEBUG] Creating representatives dummy data...\n";
        fin << "John,100 South 12th St.,2\nTaylor,1024 North Rockford Dr.,0\nBrittney,64 Bitway Dr.,1\n";
        fin.close();
    }

    fin = Products::parse();

    if (fin.is_open()) {
        cout << "[DEBUG] Creating products dummy data...\n";
        fin << "Cake,product,$19.99\nDonuts,product,$5.99\nCookies,product,$3.99\nCustom,service,$100.00";
        fin.close();
    }

    fin = Sales::parse();

    if (fin.is_open()) {
        cout << "[DEBUG] Creating sales dummy data...\n";
        fin << "Fraz,Cake,1/1/2022,John\nRyan,Cake,2/3/2022,Brittney\nCourtney,Cookies,4/18/2022,John\n";
        fin.close();
    }
}

void clearData() {
    fstream fin;

    fin = Clients::parse(false, ios::out | ios::trunc);

    if (fin.is_open()) {
        cout << "[DEBUG] Clearing clients data...\n";
        fin.close();
    }

    fin = Representatives::parse(false, ios::out | ios::trunc);

    if (fin.is_open()) {
        cout << "[DEBUG] Clearing representatives data...\n";
        fin.close();
    }

    fin = Products::parse(false, ios::out | ios::trunc);

    if (fin.is_open()) {
        cout << "[DEBUG] Clearing products data...\n";
        fin.close();
    }

    fin = Sales::parse(false, ios::out | ios::trunc);

    if (fin.is_open()) {
        cout << "[DEBUG] Clearing sales data...\n";
        fin.close();
    }
}

void openMain() {
    system("cls");
    int section;

    cout << "Bakery Business\n - Main Menu\n";
    cout << "Available Options:\n";
    cout << " - 1. Client Information\n";
    cout << " - 2. Sales Representatives\n";
    cout << " - 3. Products/Services\n";
    cout << " - 4. Sales\n";

#if defined DEBUG
    cout << " - 5. (DEBUG) Create Dummy Data\n";
    cout << " - 6. (DEBUG) Clear All Data\n";
#endif

    cout << " - 10. Exit\n";
    
    cout << "Please choose: ";
    cin >> section;

    if (section == 10) {
        exit(EXIT_SUCCESS);
        return;
    }

    openSection(section);
}

void openSection(int section) {
    int selection;

    system("cls");
    cout << "Bakery Business\n";
    cout << " - " << getSectionName(section) << "\n";
    cout << "Available Options: \n";

    switch (section) {
        case 1: {
            cout << " - 1. List All Clients\n";
            cout << " - 2. Show Info For Specific Client\n";
            cout << " - 3. Add New Client\n";
            cout << " - 4. Update Client Information\n";
            break;
        }
        case 2: {
            cout << " - 1. List All Current Sales Representatives\n";
            cout << " - 2. Show Info For Specific Sales Representative\n";
            cout << " - 3. Add New Sales Representative\n";
            cout << " - 4. Update Sales Representative Information\n";
            cout << " - 5. Calculate Sales Bonuses\n";
            break;
        }
        case 3: {
            cout << " - 1. List All Current Products & Services\n";
            cout << " - 2. Show Info For Specific Product & Service\n";
            cout << " - 3. Add New Product & Service\n";
            cout << " - 4. Update Product & Service Information\n";
            cout << " - 5. Produce Monthly Sales Report\n";
            break;
        }
        case 4: {
            cout << "- 1. Purchase a Product/Service\n";
            cout << " - 2. List All Sales For The Year\n";
            cout << " - 3. List All Sales For The Year From A Specific Client\n";
            cout << " - 4. Update A Specific Sales Information\n";
            break;
        }
        case 5: {
            cout << "[DEBUG] Starting to create dummy data...\n";
            createDummyData();
            cout << "[DEBUG] Dummy data has been created in all .csv files.\n";

            cout << "---\nPlease input any value to continue: ";
            int selection;
            cin >> selection;

            openMain();
        }
        case 6: {
            cout << "[DEBUG] Starting to clear all data...\n";
            clearData();
            cout << "[DEBUG] All data has been cleared in all .csv files.\n";

            cout << "---\nPlease input any value to continue: ";
            int selection;
            cin >> selection;

            openMain();
        }
        default: {
            cout << "Invalid Option Specified.\n";
            break;
        }
    }

    cout << " - 9. Go Back\n";

    cout << " - 10. Exit\n";

    cout << "Please choose: ";
    cin >> selection;

    if (selection == 10) {
        exit(EXIT_SUCCESS);
        return;
    }

    openItem(section, selection);
}

void openItem(int section, int selection) {
    system("cls");
    cout << "Bakery Business\n";
    cout << getSectionName(section) << "\n------\n";

    //Gross...
    switch (section) {
        case SECTION_CLIENTS: {
            switch (selection) {
                case 1: {
                    Clients::list();
                    break;
                }
                case 2: {
                    Clients::specific();
                    break;
                }
                case 3: {
                    Clients::add();
                    break;
                }
                case 4: {
                    Clients::update();
                    break;
                }
                case 9: {
                    openMain();
                    break;
                }
            }
            break;
        }
        case SECTION_REPRESENTATIVES: {
            switch (selection) {
                case 1: {
                    Representatives::list();
                    break;
                }
                case 2: {
                    Representatives::specific();
                    break;
                }
                case 3: {
                    Representatives::add();
                    break;
                }
                case 4: {
                    Representatives::update();
                    break;
                }
                case 5: {
                    Representatives::report();
                    break;
                }
                case 9: {
                    openMain();
                    break;
                }
            }
            break;
        }
        case SECTION_PRODUCTS: {
            switch (selection) {
                case 1: {
                    Products::list();
                    break;
                }
                case 2: {
                    Products::specific();
                    break;
                }
                case 3: {
                    Products::add();
                    break;
                }
                case 4: {
                    Products::update();
                    break;
                }
                case 5: {
                    Products::report();
                    break;
                }
                case 9: {
                    openMain();
                    break;
                }
            }
            break;
        }
        case SECTION_SALES: {
            switch (selection) {
                case 1: {
                    Sales::add();
                    break;
                }
                case 2: {
                    Sales::list();
                    break;
                }
                case 3: {
                    Sales::specific();
                    break;
                }
                case 4: {
                    Sales::update();
                    break;
                }
                case 9: {
                    openMain();
                    break;
                }
            }
            break;
        }
    }

    openSection(section);
}

int main() {
    openMain();
    return 0;
}