//LIBRARY MANAGEMENT SOFTWARE

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <time.h>
#include <cstring>
#include<conio.h>
#include <ctime>
using namespace std;

class BookOperation
{
public:
    // Function to add a new book entry to the library management system
    void bookDetailsEntry()
    {
        // Declare variables to store book details
        int book_id;
        char book_name[50], book_author[50];
        // Open file stream to write book details to
        fstream fobj("lib_book_details.txt", ios::out | ios::app);

        // Prompt user to enter book details
        cout << "\nEnter book ID : ";
        cin >> book_id;

        cout << "\nEnter book name : ";
        cin.ignore();
        cin.getline(book_name, 50);

        cout << "\nEnter book author : ";
        cin.getline(book_author, 50);

        // Write book details to file stream
        fobj << " " << book_id << "      " << book_name << "      " << book_author << endl;
        fobj.close();

        cout << "\n--------Successfully Saved--------";
    }

    // Function to search for book details in the library management system
    void searchBookDetails()
    {
        // Clear console screen
        system("cls");
        // Open file stream to read book details from
        fstream fobj1("lib_book_details.txt", ios::in);

    label_search:
        // Display search menu
        cout << "\n\nSEARCH MENU ";
        cout << "\n1. Display all";
        cout << "\n2. Search";
        cout << "\n3. Exit";

        cout << "\nEnter your choice (1-3) : ";

        int choose;
        cin >> choose;
        switch (choose)
        {
        // Case 1: Display all book details
        case 1:
            char str_line[500];
            char str_line1[500];
            if (fobj1.getline(str_line1, 500))
            {
                cout << "\n\n================================================================================";

                cout << "\n\n" << str_line1;

                while (fobj1.getline(str_line, 500))
                {
                    cout << "\n\n" << str_line;
                }
                cout << "\n\n================================================================================\n\n";
            }
            else
                cout << "\nNo books found.";
            break;

        // Case 2: Search for book details by book name
        case 2:
            char str_line2[500], str_line5[500];
            cout << "\nEnter book name : ";
            char bookname[10];
            cin.ignore();
            cin.getline(bookname, 50);
            if (fobj1.getline(str_line2, 500))
            {
                fobj1.seekg(0, ios::beg);
                int s = 1;
                cout << "\n\n================================================================================";
                while (fobj1.getline(str_line2, 500))
                {
                    if (strstr(str_line2, bookname) != NULL )
                    {
                        cout << "\n\n" << str_line2;
                        s = 0;
                    }
                }
                if (s == 1)
                {
                    cout << "\nBook not found";
                }
                cout << "\n\n================================================================================\n\n";
            }
            else
                cout << "\nBook not found";
            break;

        // Case 3: Exit search menu


case 3:
{
    // Pause the program for 500 milliseconds
    Sleep(500);

    // Display message indicating program is exiting
    cout << "\n\nExiting ";

    // Loop through and display a series of dots to simulate waiting
    for (int i = 0; i <= 4; i++)
    {
        Sleep(500);
        cout << ".";
    }

    // Exit the program with a status code of 0
    exit(0);

    // Exit the switch statement
    break;
}

// Function for deleting a book from the library
void delete_book()
{
    // Declare variables for file operations and user input
    char temp_str[500];
    char temp_search[500], temp_search1[500];
    fstream fin("lib_book_details.txt", ios::in);

    // Prompt the user for the name of the book to be deleted
    cout << "\nEnter the full book name to delete that book data : ";

    // Read in the user input and ignore any remaining characters in the input buffer
    cin.ignore();
    cin.getline(temp_search, 500);

    // Check if there is at least one record in the file
    if (fin.getline(temp_search1, 500))
    {
        // If there is at least one record, move the file position indicator to the beginning of the file
        fin.seekg(0, ios::beg);

        // Declare a variable for user confirmation and prompt the user for input
        char q;
        cout << "\nAre you sure you want to delete the record (Y/N)? ";
        cin >> q;

        // If the user confirms the deletion, create a temporary output file and move the file position indicator to the beginning of the file
        if (q == 'Y' | q == 'y')
        {
            fstream fout("temp_lib.txt", ios::out | ios::app);
            fout.seekg(0, ios::beg);

            // Loop through each record in the file, and if the book name to be deleted is not found, write the record to the temporary file
            while (fin.getline(temp_str, 500))
            {
                if (strstr(temp_str, temp_search) == NULL)
                {
                    fout << temp_str << endl;
                }
            }

            // Close the input and output files
            fin.close();
            fout.close();

            // Delete the original file and rename the temporary file to the original file name
            remove("lib_book_details.txt");
            rename("temp_lib.txt", "lib_book_details.txt");

            // Display message indicating successful deletion
            cout << "\n....Successfully Deleted....";
        }
    }
    else
    {
        // If there are no records in the file, display an appropriate message
        cout << "\nNo books are found to be deleted";
    }
}
if (admin_pass == "admin")
{
    // Clear console screen and play alert sound
    system("cls");
    cout << "\a";
    
    // Display administrator menu options
    cout << "\n\nADMINISTRATOR MENU";
    cout << "\n1. Delete Book Data";
    cout << "\n2. Reset Program";
    cout << "\n3. Exit Program";
    cout << "\nEnter choice (1-3) : ";

    // Read administrator's choice from input
    int choose_admin;
    cin >> choose_admin;

    // Create an instance of BookOperation class
    BookOperation bookop;

    // Switch statement to perform corresponding action based on administrator's choice
    switch (choose_admin)
    {
        case 1:
            bookop.delete_book(); // Call delete_book() method of BookOperation class
            break;

        case 2:
        {
            // Prompt user to confirm reset action
            char q_reset;
            cout << "\nAll saved data will be deleted and the program will be restored to defaults. Continue anyway? (Y/N) : ";
            cin >> q_reset;
            
            // If user confirms reset action, delete all saved data and restore program to defaults
            if (q_reset == 'Y' | q_reset == 'y')
            {
                // Display progress dots while resetting
                cout << "\nResetting";
                for (int i = 0; i < 5; i++)
                {
                    Sleep(500);
                    cout << ".";
                }
                
                // Delete all saved data files
                remove("lib_book_details.txt");
                remove("lib_issue_return.txt");
                remove("temp_id.txt");
                remove("issue_return.txt");
                remove("temp_return.txt");
                
                // Display success message after program is restored to defaults
                cout << "\n....Restored to defaults....";
            }
            break;
        }
        case 3:
            // Display progress dots while exiting program
            Sleep(500);
            cout << "\n\nExiting ";
            for (int i = 0; i <= 4; i++)
            {
                Sleep(500);
                cout << ".";
            }
            
            // Exit program
            exit(0);
            break;
        default:
            // Display error message for invalid choice
            cout << "\n....Invalid Choice....";
            break;
    }
}
else
{
    // Display error message for invalid password and prompt user to try again
    cout << "\n....Invalid Password....";
    goto label_admin; // Jump back to label_admin for user to try entering password again
}
class BookIssueReturn
{
public:
	char date1[10];

	void issue_return()
	{
                     system("cls");

			cout << "\a";
			BookIssueReturn bIR;
			cout << "\nISSUE AND RETURN SECTION";
			cout << "\n1. Issue book";
			cout << "\n2. Return book";
			cout << "\n3. Issue and Return status";
			cout << "\n4. Exit Program";

			cout << "\nEnter your choice (1-4) : ";

			int bir;
			cin >> bir;
			switch (bir)
			{
			case 1:
				bIR.issue_book();
				break;
			case 2:
				bIR.return_book();
				break;
			case 3:
			{
				fstream BIR("lib_issue_return.txt", ios::in);
				fstream BIR2("lib_issue_return.txt", ios::in);
				char tempstr[500], tempstr1[500];
				if (BIR.getline(tempstr1, 500))
				{
					cout << "\n\n===================================================================================================\n\n";
					while (BIR2.getline(tempstr, 500))
					{
						cout << tempstr << endl;
					}
					cout << "\n===================================================================================================";
					BIR.close();
					BIR2.close();
				}
				else
					cout << "\nNo books have been issued or returned.";
				break;
			}
			case 4:
			{
				Sleep(500);
				cout << "\n\nExiting ";
				for (int i = 0; i <= 4; i++)
				{
					Sleep(500);
					cout << ".";
				}
				exit(0);
				break;
			}
			default:
				cout << "\n....Invalid Choice....";
				break;
			}

	}

	void issue_book()
	{
                  system("cls");

		ifstream File;
		string filepath = "temp_id.txt";
		File.open(filepath.c_str(), std::ifstream::out | std::ifstream::trunc);
		File.close();
		int len = 0, i, j, serial, bookid;
		char book_name_copy[50], str_copy[50];
		fstream bi_in("lib_issue_return.txt", ios::out | ios::in | ios::app);
		fstream temp_id("temp_id.txt", ios::out | ios::app);
		fstream bd_out("lib_book_details.txt", ios::in);
		fstream ir("issue_return.txt", ios::in);
		fstream ir2("issue_return.txt", ios::out | ios::app);
		char temp_copy[500], stu_name[50], book_id[10];
		cout << "\nEnter serial number : ";
		cin >> serial;
		cout << "\nEnter the name of the user you want to issue book to : ";
		cin.ignore();
		cin.getline(stu_name, 50);
		cout << "\nEnter the ID of the book you want to issue to the user : ";
		cin >> bookid;
		temp_id << " " << bookid << "  " << endl;
		fstream temp_id2("temp_id.txt", ios::in);
		temp_id2.seekg(0, ios::beg);
		temp_id2.getline(book_id, 10);
		cout << book_id << endl;
		temp_id2.close();
		remove("temp_id.txt");
		len = strlen(book_id);
		int flag1 = 0;
		while (bd_out.getline(temp_copy, 500))
		{

			char num[10];
				int len2 = 0;
				for (int op = 0; op < len; op++) {
					num[op] = temp_copy[op];
				}for (int op = len; op < 10; op++) {
					num[op] = '\0';
				}

				if (strstr(num, book_id) != NULL)
				{
					flag1 = 1;
					for (i = len; temp_copy[i] != '\0'; i++)
						len2++;
					for (i = len + 4, j = 0; temp_copy[i] != '\0', j < len2; i++, j++)
						book_name_copy[j] = temp_copy[i];

			}
		}

		int flag = 0;
		char temp[500];
		while (ir.getline(temp, 500))
		{
			if (strstr(temp, book_name_copy) == NULL)
				continue;
			else
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0 && flag1 == 1)
		{
			cin.ignore();
			bi_in << " " << serial << "    " << stu_name << "    " << book_name_copy << "    " << _strdate(date1) << endl;
			ir2 << book_name_copy << endl;
			bi_in.close();
			bd_out.close();
			ir.close();
			ir2.close();
			remove("temp_id.txt");
			remove("temp_id2.txt");
			cout << "\n....Book Issued....";
		}
		else
		{
			bi_in.close();
			bd_out.close();
			ir.close();
			ir2.close();
			remove("temp_id.txt");
			remove("temp_id2.txt");
			cout << "\nBook not available for issue.";
		}
	}


	void return_book()
	{

                 system("cls");

		char temp_str[500];
		char date2[10];
		cout << "\nRETURN MENU";
		cout << "\n1. Return by serial no.";
		cout << "\n2. Return by full book name";
		cout << "\nEnter your choice (1-2) : ";
		int choose_return;
		cin >> choose_return;
		switch (choose_return)
		{
		case 1:
		{ifstream File;
		string filepath = "temp_id.txt";
		File.open(filepath.c_str(), std::ifstream::out | std::ifstream::trunc);
		File.close();
			int serial;
			cout << "\nEnter serial no of the issue return list : ";
			cin >> serial;
			fstream ser("temp.txt", ios::out | ios::app);
			ser.seekg(0, ios::beg);
			cin.ignore();
			ser << " " << serial << "    ";
			ser.close();
			char serial_copy[50];
			fstream ser1("temp.txt", ios::in);
			ser1.seekg(0, ios::beg);
			ser1.getline(serial_copy, 50);
			ser1.close();
			remove("temp.txt");
			int len = 0;
			len = strlen(serial_copy);
			fstream out_book_return("lib_issue_return.txt", ios::in);
			char book_return[500], temp_copy[500];
			while (out_book_return.getline(book_return, 500))
			{
				char num[10];
				int len2 = 0;
				for (int op = 0; op < len; op++) {
					num[op] = book_return[op];
				}for (int op = len; op < 10; op++) {
					num[op] = '\0';
				}

				if (strstr(num, serial_copy) != NULL)
				{

					int i;
					for (i = len; book_return[i] != '\0'; i++)
						len2++;
					int j;
					for (i = len + 4, j = 0; book_return[i] != '\0', j < len2; i++, j++)
						temp_copy[j] = book_return[i];
				}
			}
			out_book_return.close();
			fstream check("issue_return.txt", ios::in);
			char str_cpy[500];
			int flag = 0;
			while (check.getline(str_cpy, 500))
			{
				if (strstr(temp_copy, str_cpy) == NULL)
					continue;
				else
				{
					cout << "Book returned successfully\n";
					flag = 1;
					break;
				}
			}
			check.close();
			if (flag == 1)
			{
				fstream book_rn("lib_issue_return.txt", ios::in);
				fstream bo_return("temp_ir.txt", ios::out | ios::app);
				while (book_rn.getline(book_return, 500))
				{
					if (strstr(book_return, serial_copy) == NULL)
						bo_return << book_return << endl;
					else
						bo_return << book_return << "    " << _strdate(date2) << endl;
				}
				book_rn.close();
				bo_return.close();
				remove("lib_issue_return.txt");
				rename("temp_ir.txt", "lib_issue_return.txt");
			}
			else
			{
				cout << "\nNo such book have been issued.";
			}
			break;
		}

		case 2:
		{
			fstream br_out("lib_issue_return.txt", ios::in);
			fstream temp_return("temp_return.txt", ios::out | ios::app);
			int flag = 0;
			char temp_bn[50], temp[500], temp1[500];
			fstream ir("issue_return.txt", ios::in);
			fstream teir("issue_return.txt", ios::in);
			cout << "\nEnter full book name : ";
			cin.ignore();
			cin.getline(temp_bn, 50);
			ir.seekg(0, ios::beg);
			if (!teir.getline(temp1, 500))
			{

			}
			else
			{
				ir.seekg(0, ios::beg);
				while (ir.getline(temp1, 500))
				{
					if (strstr(temp1, temp_bn) != NULL)
					{
						flag = 1;
						break;
					}
				}
			}
			teir.close();
			ir.close();
			if (flag == 0)
				cout << "\nNo books are found to be returned";
			else
			{
				fstream ir2("issue_return_temp.txt", ios::out | ios::app);
				cin.ignore();
				while (br_out.getline(temp, 500))
				{
					if (strstr(temp, temp_bn) != NULL)
					{
						temp_return << temp;
						temp_return << "    " << _strdate(date2) << endl;
					}
					else
					temp_return << temp << endl;
				}

				while (ir2.getline(temp1, 500))
				{
					if (strstr(temp1, temp_bn) == NULL)
						ir2 << temp_bn << endl;
				}
				br_out.close();
				remove("lib_issue_return.txt");
				temp_return.close();
				rename("temp_return.txt", "lib_issue_return.txt");
				ir2.close();
				remove("issue_return.txt");
				rename("issue_return_temp.txt", "issue_return.txt");
				cout << "\n....Book Returned....";
			}
			break;
		}

		default:
			cout << "\n....Invalid Choice....";
			break;
		}

	}
};



void home(){

                     printf("The last stand *team_8* present");

printf("\n\n\n\n\n");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t        =                 WELCOME                   =");
    printf("\n\t\t\t        =                   TO                      =");
    printf("\n\t\t\t        =                 LIBRARY                   =");
    printf("\n\t\t\t        =               MANAGEMENT                  =");
    printf("\n\t\t\t        =                 SYSTEM                    =");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");



}



int main()
{
	system("COLOR 8F");
	time_t now = time(0);
	char* date = ctime(&now);

	tm *gmtm = gmtime(&now);
          date = asctime(gmtm);

         cout << "\n                                  ** LIBRARY MANAGEMENT project **                         " << date ;

          home();

	BookOperation bo;
	BookIssueReturn bir;
	string pass = "";
label_main:
	char c = ' ';
	cout << "\nEnter Program Password : ";
	while (c != 13)
	{
		c = _getch();
		if (c != 13)
		{
			pass += c;
			cout << "*";
		}
	}



	if (pass == "123456")
	{
               system("cls");
		cout << "\a";
		int choice;
		while (1)
		{
			cout << "\n\nMAIN MENU";
			cout << "\n1. Book Details Entry";
			cout << "\n2. Search Book Details";
			cout << "\n3. Administrator Menu";
			cout << "\n4. Issue and Return Section";
			cout << "\n5. Exit Program";

			cout << "\nEnter your choice (1-5) : ";
			cin >> choice;

			switch (choice)
			{
			case 1:
				bo.bookDetailsEntry();
				break;
			case 2:
				bo.searchBookDetails();
				break;
			case 3:
				bo.admin_menu();
				break;
			case 4:
				bir.issue_return();
				break;

			case 5:
				Sleep(500);
				cout << "\n\nExiting ";
				for (int i = 0; i <= 4; i++)
				{
					Sleep(500);
					cout << ".";
				}
				exit(0);
				break;
			default:
				cout << "\n....Invalid Choice....";
			}
		}
	}
	else
	{
		cout << "\n....Invalid Password....";
		goto label_main;
	}
}