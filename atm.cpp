#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
#include <string>

class account
{
private:
    int accountNum;
    char name[100];
    char type;
    int balance;

public:
    void createAccount();
    void displayAccount();
    void editAccount();
    void depositAmount();
    void withdrawAmount();
    void report();
    int reportAccountNum();
    int reportBalance();
 
};

void account::createAccount(){
    std::cout << "\nEnter an Account Number You Would like to Use: ";
    std::cin >> accountNum;
    std::cout << "Enter Your Name: ";
    std::cin.ignore();
    std::cin.getline(name,50);
    std::cout << "Enter an Account Type (C/S): ";
    std::cin >> type;
    type = toupper(type);
    std::cout << "Enter the Amount You Would Like to Deposit: ";
    std::cin >> balance;
    std::cout << "\nAccount Created!";
    std::cout << std::endl;
}

void account::displayAccount(){
    std::cout << "\nAccount Number: " << accountNum;
    std::cout << "\nName on Account: " << name;
    std::cout << "\nAccount Type: " << type;
    std::cout << "\nAccount Balance: " << balance;
    std::cout << std::endl;
}

void account::editAccount(){
    std::cout << "\nAccount Number: " << accountNum;
    std::cout << "\nNew Name: ";
    std::cin.ignore();
    std::cin.getline(name,100);
    std::cout << "New Account Type (C/S): ";
    std::cin >> type;
    type = toupper(type);
    std::cout << "New Account Balance: ";
    std::cin >> balance;
    std::cout << "\nAccount Updated!";
    std::cout << std::endl;
}

void account::depositAmount(){
    int amount;

    std::cout << "\nEnter The Amount You would Like to Deposit: ";
    std::cin >> amount;

    balance = balance + amount;
    std::cout << "\nThe Account Was Updated.";
}

void account::withdrawAmount(){
    int amount;

    std::cout << "\nEnter The Amount You would Like to Withdraw: ";
    std::cin >> amount;

    if((balance - amount) < 0){
        std::cout << "\nThere Are Insufficient Funds";
    }else{
        balance = balance - amount;
        std::cout << "\nThe Account Was Updated.";
    }
    
}

void account::report(){
    std::cout  << '\n' << accountNum << "\t\t" << name << "\t" << type << "\t\t" << balance << '\n';
}

int account::reportAccountNum(){
    return accountNum;
}

int account::reportBalance(){
    return balance;
}

int main();
void create();
void display(int num);
void edit(int num);
void del(int num);
void reportAll();
void deposit(int num);
void withdraw(int num);

int main(){
    char choice;
    int accNum;
    std::string password;
    int e = 1;

    while(e != 0){
        std::cout << "\n\nPlease Choose From One of the Following Options.";
        std::cout << "\n\n1. Create a New Account.";
        std::cout << "\n2. Account Information.";
        std::cout << "\n3. Deposit Money.";
        std::cout << "\n4. Withdraw Money.";
        std::cout << "\n5. Edit Your Account.";
        std::cout << "\n6. Delete Your Account.";
        std::cout << "\n7. Account Holder Report.";
        std::cout << "\n8. Exit.\n\n";
        std::cin >> choice;

        if(choice == '1'){
            create();
        }else if(choice == '2'){
            std::cout << "\n\nEnter Your Account Number: ";
            std::cin >> accNum;
            display(accNum);
        }else if(choice == '3'){
            std::cout << "\n\nEnter Your Account Number: ";
            std::cin >> accNum;
            deposit(accNum);
        }else if(choice == '4'){
            std::cout << "\n\nEnter Your Account Number: ";
            std::cin >> accNum;
            withdraw(accNum);
        }else if(choice == '5'){
            std::cout << "\n\nEnter Your Account Number: ";
            std::cin >> accNum;
            edit(accNum);
        }else if(choice == '6'){
            std::cout << "\n\nEnter Your Account Number: ";
            std::cin >> accNum;
            del(accNum);
        }else if(choice == '7'){
            std::cout << "\n\nPlease Enter a Password: ";
            std::cin >> password;
            if(password == "abc123"){
                reportAll();
            }else{
                std::cout << "\n\nIncorrect Password, Please Try Again.";
            }
        }else if(choice == '8'){
            std::cout << "\n\nThank You For Using the ATM.\n\n";
            e = 0;
        }else{
            std::cout << "\n\nThat is Not a Valid Input, Please Try Again.";
        }
    }

    return 0;
}

void create(){
    account user;
    std::ofstream writeFile;
    writeFile.open("account.txt", std::ios::binary|std::ios::app);
    user.createAccount();
    writeFile.write((char*) &user, sizeof(account));
    writeFile.close();
}

void display(int num){
    account user;
    bool found = false;
    std::ifstream readFile;
    readFile.open("account.txt", std::ios::binary);

    if(!readFile){
        std::cout << "\nThe File Could Not be Opened.";
        return;
    }

    while(readFile.read((char*) &user, sizeof(account))){
        if(user.reportAccountNum() == num){
            std::cout << "\nAccount Details.\n";
            user.displayAccount();
            found = true;
        }
    }

    if(found == false){
        std::cout << "\nThe Account Was Not Found.";
    }

    readFile.close();
}   

void edit(int num){
    account user;
    bool found = false;
    std::fstream writeFile;
    writeFile.open("account.txt", std::ios::binary|std::ios::in|std::ios::out);

    if(!writeFile){
        std::cout << "\nThe File Could Not be Opened.";
        return;
    }

    while(!writeFile.eof() && found == false){
        writeFile.read((char*) &user, sizeof(account));
        if(user.reportAccountNum() == num){
            user.displayAccount();
            user.editAccount();
            int pos = (-1)*static_cast<int>(sizeof(account));
   			writeFile.seekp(pos, std::ios::cur);
            writeFile.write((char*) &user, sizeof(account));
            found = true;
        }
    }

    if(found == false){
        std::cout << "\nThe Account Was Not Found.";
    }

    writeFile.close();
}

void del(int num){
    account user;
    std::ifstream readFile;
    std::ofstream writeFile;
    readFile.open("account.txt", std::ios::binary);
    writeFile.open("temp.txt", std::ios::binary);

    if(!readFile){
        std::cout << "\nThe File Could Not be Opened.";
        return;
    }

    readFile.seekg(0, std::ios::beg);

    while(readFile.read((char*) &user, sizeof(account))){
        if(user.reportAccountNum() != num){
            writeFile.write((char*) &user, sizeof(account));
        }
    }
    readFile.close();
    writeFile.close();
    remove("account.txt");
    rename("temp.txt", "account.txt");
    std::cout << "\nThe Account Was Deleted.";
}

void reportAll(){
    account user;
    std::ifstream readFile;
    readFile.open("account.txt", std::ios::binary);

    if(!readFile){
        std::cout << "\nThe File Could Not be Opened.";
        return;
    }
    
    std::cout << '\n' << "Account Number" << '\t' << "Name" << '\t' << "Account Type" << '\t' << "Balance" << '\n';

    while(readFile.read((char*) &user, sizeof(account))){
        user.report();
    }

    readFile.close();
}

void deposit(int num){
    account user;
    bool found = false;
    std::fstream writeFile;
    writeFile.open("account.txt", std::ios::binary|std::ios::in|std::ios::out);
    
    if(!writeFile){
        std::cout << "\nThe File Could Not be Opened.";
        return;
    }

    while(!writeFile.eof() && found == false){
        writeFile.read((char*) &user, sizeof(account));
        if(user.reportAccountNum() == num){
            user.displayAccount();
            user.depositAmount();
            int pos = (-1)*static_cast<int>(sizeof(account));
   			writeFile.seekp(pos, std::ios::cur);
            writeFile.write((char*) &user, sizeof(account));
            found = true;
        }
    }

    if(found == false){
        std::cout << "\nThe Account Was Not Found.";
    }

    writeFile.close();
}

void withdraw(int num){
    account user;
    bool found = false;
    std::fstream writeFile;
    writeFile.open("account.txt", std::ios::binary|std::ios::in|std::ios::out);

    if(!writeFile){
        std::cout << "\nThe File Could Not be Opened.";
        return;
    }

    while(!writeFile.eof() && found == false){
        writeFile.read((char*) &user, sizeof(account));
        if(user.reportAccountNum() == num){
            user.displayAccount();
            user.withdrawAmount();
            int pos = (-1)*static_cast<int>(sizeof(account));
            writeFile.seekp(pos, std::ios::cur);
            writeFile.write((char*) &user, sizeof(account));
            found = true;
        } 
    }

    if(found == false){
        std::cout << "\nThe Account Was Not Found.";
    }

    writeFile.close();    
}