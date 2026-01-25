#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

const string client_fill = "myfill.txt";

struct client
{
    string account_number;
    string pincode;
    string name;
    string phone;
    float accountbalance;
    bool check_delet = false;
};

enum en_operation
{
    main_menue = 0,
    show = 1,
    add = 2,
    delet = 3,
    update = 4,
    find = 5,
    exsit = 6
};

void print_hader_screen(en_operation operation)
{

    switch (operation)
    {
    case en_operation::main_menue:
        cout << "___________________________________________\n";
        cout << "___________________________________________\n";
        cout << "              main menue screen            \n";
        cout << "___________________________________________\n";
        cout << "___________________________________________\n";
        break;
    case en_operation::show:
        cout << "___________________________________________\n";
        cout << "              show client list              \n";
        cout << "____________________________________________\n";
        break;
    case en_operation::add:
        cout << "___________________________________________\n";
        cout << "              add client list              \n";
        cout << "____________________________________________\n";
        break;
    case en_operation::delet:
        cout << "___________________________________________\n";
        cout << "              delet client list              \n";
        cout << "____________________________________________\n";
        break;
    case en_operation::update:
        cout << "___________________________________________\n";
        cout << "             update client list              \n";
        cout << "____________________________________________\n";
        break;
    case en_operation::find:
        cout << "___________________________________________\n";
        cout << "              find client list              \n";
        cout << "____________________________________________\n";
        break;
    default:
        cout << "___________________________________________\n";
        cout << "              exist client list              \n";
        cout << "____________________________________________\n";
        break;
    }
}

en_operation print_main_manue()
{

    cout << "show client  [1]\n";
    cout << "add client   [2]\n";
    cout << "delet client [3]\n";
    cout << "update client[4]\n";
    cout << "find client  [5]\n";
    cout << "exsit        [6]\n";
    cout << "______________________________________\n";
    int number;
    cout << "please inter your number of operation:";
    cin >> number;
    return en_operation(number);
}

vector<string> splitstring(string your_record, string delemiter = "#//#")
{
    short pos = 0;
    string worde = "";
    vector<string> storge;
    while ((pos = your_record.find(delemiter)) != std::string::npos)
    {
        worde = your_record.substr(0, pos);
        if (worde != "")
        {
            storge.push_back(worde);
        }
        your_record.erase(0, pos + delemiter.length());
    }
    if (your_record != "")
    {
        storge.push_back(your_record);
    }
    return storge;
}
client convert_line_recorde(string your_record, string delemiter = "#//#")
{
    client my_client;
    vector<string> your_storge;
    your_storge = splitstring(your_record, delemiter);
    my_client.account_number = your_storge[0];
    my_client.pincode = your_storge[1];
    my_client.name = your_storge[2];
    my_client.phone = your_storge[3];
    my_client.accountbalance = stod(your_storge[4]);
    return my_client;
}
vector<client> retreve_data(string your_fill)
{
    string line;
    fstream my_fill;
    client my_client;
    vector<client> my_vclient;
    my_fill.open(your_fill, ios::in);
    if (my_fill.is_open())
    {
        while (getline(my_fill, line))
        {
            my_client = convert_line_recorde(line);
            my_vclient.push_back(my_client);
        }
        my_fill.close();
    }
    return my_vclient;
}

void print_client_data(client your_client)
{
    cout << "|" << setw(15) << your_client.account_number << "|" << setw(10) << your_client.pincode << "|" << setw(40) << your_client.name << "|" << setw(12) << your_client.phone << "|" << setw(12) << your_client.accountbalance << "|" << endl;
}
void print_fill_data(vector<client> your_vclient)
{
    cout << "                               client list (" << your_vclient.size() << ") client(s)." << endl;
    cout << "_________________________________________________________________________________________________________________________________\n";
    cout << "|" << setw(15) << "accout number" << "|" << setw(10) << "pin code" << "|" << setw(40) << "client name" << "|" << setw(12) << "phone" << "|" << setw(12) << "balance" << "|" << endl;
    cout << "__________________________________________________________________________________________________________________________________\n";
    if (your_vclient.size() == 0)
    {
        cout << "no client found\n";
    }
    else
    {
        for (client i : your_vclient)
        {
            print_client_data(i);
            cout << endl;
        }
    }
}

void show_allclient(string fill)
{
    vector<client> my_vclient;
    my_vclient = retreve_data(client_fill);
    print_fill_data(my_vclient);
}

bool search_account(string your_account_number, vector<client> &your_vclient)
{
    for (client &i : your_vclient)
    {
        if (i.account_number == your_account_number)
        {
            return true;
        }
    }
    return false;
}
string read_account(vector<client> &your_vclient)
{

    string my_account_number;
    cout << "please inter your acccount_number of client  :";
    cin >> my_account_number;
    while (search_account(my_account_number, your_vclient))
    {
        cout << "client exsit enter another account_number:";
        cin >> my_account_number;
    }
    return my_account_number;
}

client read_client_info(string your_account_number)
{
    client your_client;
    your_client.account_number = your_account_number;
    cout << "please inter your pincode  :";
    getline(cin >> ws, your_client.pincode);

    cout << "please inter your name     :";
    getline(cin, your_client.name);
    cout << "pleaser inter your phone   :";
    getline(cin, your_client.phone);
    cout << "please inter accountbalance:";
    cin >> your_client.accountbalance;
    return your_client;
}

string convertrecord_toline(client your_client_info, string delemiter = "#//#")
{
    string line = "";
    line = line + your_client_info.account_number + delemiter;
    line = line + your_client_info.pincode + delemiter;
    line = line + your_client_info.name + delemiter;
    line = line + your_client_info.phone + delemiter;
    line = line + to_string(your_client_info.accountbalance);
    return line;
}

void storgeline_infill(string your_line, string fill)
{
    fstream ptfill;
    ptfill.open(fill, ios::app);
    if (ptfill.is_open())
    {
        ptfill << your_line << endl;
        ptfill.close();
    }
}

void add_client()
{
    vector<client> my_vclient = retreve_data(client_fill);
    string account_number = "";
    client my_client_info;
    string line = "";
    char answer = 'y';
    do
    {
        account_number = read_account(my_vclient);
        my_client_info = read_client_info(account_number);
        line = convertrecord_toline(my_client_info);
        storgeline_infill(line, client_fill);
        cout << "\nclient add successfull :  do you want to add mor client[y/n]:";
        cin >> answer;
    } while (answer == 'y' || answer == 'Y');
}

string read_account()
{
    string account_number;
    cout << "please inter your account number:";
    cin >> account_number;
    return account_number;
}
bool search_account(string your_account_number, vector<client> &your_vclient, client &your_client)
{
    for (client &i : your_vclient)
    {
        if (i.account_number == your_account_number)
        {
            your_client = i;
            return true;
        }
    }
    return false;
}
void show_client(client your_client)
{
    cout<<"___________________________________________________\n";
    cout << "the client is exist and information is\n";
    cout<<"___________________________________________________\n";
    cout << " your account_number:" << your_client.account_number << endl;
    cout << " your pincode       :" << your_client.pincode << endl;

    cout << " your name          :" << your_client.name << endl;
    cout << " your phone         :" << your_client.phone << endl;
    cout << " accountbalance     :" << your_client.accountbalance << endl;
}
bool ensur_delet(vector<client> &your_vclient, string your_account)
{
    for (client &i : your_vclient)
    {
        if (i.account_number == your_account)
        {
            i.check_delet = true;
            return true;
        }
    }
    return false;
}
void loaddata_tofill(vector<client> &your_vclient, string your_fill)
{
    fstream ptfill;
    string line = "";
    ptfill.open(your_fill, ios::out);
    if (ptfill.is_open())
    {
        for (client &i : your_vclient)
        {
            if (i.check_delet == false)
            {
                line = convertrecord_toline(i);
                ptfill << line << endl;
            }
        }
        ptfill.close();
    }
}
void delete_client()
{
    vector<client> my_vclient;
    client my_client;
    my_vclient = retreve_data(client_fill);
    string account_number = "";
    char answer = 'y';
    char check_delet = 'n';

    do
    {
         
        account_number = read_account();
    
        if (search_account(account_number, my_vclient, my_client))
        {
            show_client(my_client);
            cout << "are you sure your want to delet client:";
            cin >> check_delet;
            if (check_delet == 'y' || check_delet == 'Y')
            {
                ensur_delet(my_vclient, account_number);
                loaddata_tofill(my_vclient, client_fill);
    
                cout << "\nclient are delet successful\n";
            }
            else {
                cout << "client not delet\n";
            }
        }
        else
        {
            cout << "client not found:\n";
        }
        cout << "\ndo you want to delet more client[y/n]:";
        cin >> answer;
    } while (answer == 'y' || answer == 'Y');
}
bool change_data(client your_client, vector<client> &my_vector)
{
    for (client &i : my_vector)
    {
        if (i.account_number == your_client.account_number)
        {
            i.pincode = your_client.pincode;
            i.name = your_client.name;
            i.phone = your_client.phone;
            i.accountbalance = your_client.accountbalance;
            return true;
        }
    }
    return false;
}
void update_client()
{
    string account_number = "";
    vector<client> my_vclient;
    client my_client;
    char answer = 'y';

    my_vclient = retreve_data(client_fill);
    account_number = read_account();

    if (search_account(account_number, my_vclient, my_client))
    {
        show_client(my_client);
        cout << "are you sure your want to update client:";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {

            cout << "please inter your pincode       :";
            getline(cin >> ws, my_client.pincode);
            cout << "please inter your name          :";
            getline(cin, my_client.name);
            cout << "please inter your phone         :";
            getline(cin, my_client.phone);
            cout << "please inter your accountbalance:";
            cin >> my_client.accountbalance;

            change_data(my_client, my_vclient);
            loaddata_tofill(my_vclient, client_fill);

            cout << "client are update successful\n";
        }
    }
    else
    {
        cout << "client not found:\n";
    }
}

void find_client()
{
    string account_number = "";
    vector<client> my_vclient;
    client my_client;

    my_vclient = retreve_data(client_fill);
    account_number = read_account();

    if (search_account(account_number, my_vclient, my_client))
    {
        show_client(my_client);
    }
    else
    {
        cout << "client not found:\n";
    }
}

void exsit_client()
{
    cout << "program end";
}

void main_manue_screen();
void gobacke_mainmenue()
{
    cout << "\n\n press any key to go backt o main menue";
    system("pause>0");
    main_manue_screen();
}

void apply_operation_choees(en_operation operation)
{
    switch (operation)
    {

    case en_operation::show:
        system("cls");
        print_hader_screen(en_operation::show);
        show_allclient(client_fill);
        gobacke_mainmenue();

        break;
    case en_operation::add:
        system("cls");
        print_hader_screen(en_operation::add);
        add_client();
        gobacke_mainmenue();
        break;
    case en_operation::delet:
        system("cls");
        print_hader_screen(en_operation::delet);
        delete_client();
        gobacke_mainmenue();
        break;
    case en_operation::update:
        system("cls");
        print_hader_screen(en_operation::update);
        update_client();
        gobacke_mainmenue();
        break;
    case en_operation::find:
        system("cls");
        print_hader_screen(en_operation::find);
        find_client();
        gobacke_mainmenue();
        break;
    default:
        system("cls");
        print_hader_screen(en_operation::exsit);
        exsit_client();

        break;
    }
}

void main_manue_screen()
{
    system("cls");
    print_hader_screen(en_operation::main_menue);
    en_operation your_operation = print_main_manue();
    apply_operation_choees(your_operation);
}

int main()
{
    main_manue_screen();
}
