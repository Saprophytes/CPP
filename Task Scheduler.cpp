// these are the header files that we will be using throughout the program
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <conio.h>
#include<stdlib.h>

// uses the namespace "std"
using namespace std;

//these are the function prototypes. They contain arguments for the structures.
void add_rec(struct tasks st[],int& itemcount);
void delete_rec(struct tasks st[], int& itemcount);
void viewall(struct tasks st[], int itemcount);
void update_rec(struct tasks st[],int itemcount);
int search(struct tasks st[],string id, int itemcount);
void clean(struct tasks st[],int deleteitem);
void writeOutFile(struct tasks st[], int itemcount, fstream& myFile);

//these are the structure tasks. It is used for storing the data needed in the whole program.
struct tasks
{
	string stnumber;
	char task[100];
	char date[10];
	char time[10];
	char venue[100];
};

// declares the function main of int type
int main()
{
//This code block initializes the file stream
	tasks st[80];
	int itemcount=0;
	fstream myFile;
	string line;
	
//this code block will determine the task to be done
	int yourchoice;
	char confirm;
	do
	{
//willl display the menu on the screen
        cout<<"******************************************************************************\n";
		cout<<"*                          TASK SCHEDULER V1.0                               *\n";
		cout<<"******************************************************************************\n";
		cout<<"[1] Add Task\n[2] Delete task\n[3] Edit Task\n[4] View Tasks\n";
		cout<<"Enter Your Choice(1-4): ";
		cin>>yourchoice;
		system("cls");
		switch(yourchoice)
		{
			case 1:add_rec(st, itemcount);break;
			case 2:delete_rec(st, itemcount);break;
			case 3:update_rec(st, itemcount);break;
			case 4:viewall(st, itemcount);break;
			default:
				cout<<"*****************************************************************************\n";
				cout<<"*                             TASK SCHEDULER                                *\n";
				cout<<"*****************************************************************************\n";
				cout<<"Invalid Input!\n";
		}
// this will confirm and verify the writing to file.
		cout<<"\nPress Y To Return To The Menu.\nOr\nPress W to write it into a file and exit ";
		cin>>confirm;
		system("cls");
	}
    while(confirm=='y'||confirm=='Y');

// this will write the inputted data to a file
    while (confirm=='W'||confirm=='w')
	{
	myFile.open("Task Scheduler.txt", ios::out|ios::trunc);
    if (!myFile)
    {
      cout << "FILE OPEN ERROR!" << endl;
      return 0;
    }
    cout << "\nWe are now writing this data to a file...";
    writeOutFile(st,itemcount,myFile);
    cout << "Done." << endl;
    myFile.close();
    cout << "\nNow we will read back the data from the file..." << endl;
    viewall(st, itemcount);
    cout<<"\nThe .txt file is now saved in the directory of the program.\n";
    cout<<"It is named Task Scheduler.txt\n";
	
	myFile.close();
    cout<<"\nGoodbye!\n";
    getch();
    return 0;
    }
    getch();
	return 0;
}
// this is used in creating new records
void add_rec(struct tasks st[],int& itemcount)
{
        again:
        cout<<"******************************************************************************\n";
		cout<<"*                             A D D  T A S K                                 *\n"; 
		cout<<"******************************************************************************\n";

	cout<<"Enter Task Number: ";
	cin>>st[itemcount].stnumber;
	
//this will check if the task number inputted by the user already exist
	if(search(st,st[itemcount].stnumber,itemcount)!=-1)
	{
		system("cls");
		cout<<"******************************************************************************\n";
		cout<<"*                           Add Task Record                                  *\n";
		cout<<"******************************************************************************\n";
		cout<<"This Task Number Already Exists\n\n";
		system("cls");
        goto again;
	}
//this code block will instruct and allow the user to input the needed info
	cout<<"Task Detail\n"<<"Task Name (One word Only): ";
	cin>>st[itemcount].task;
	cout<<"Task date (MM-DD-YY) (Separate with dash): ";
	cin>>st[itemcount].date;
	cout<<"Task time (HH:MM)(Separate with colon): ";
	cin>>st[itemcount].time;
	cout<<"Venue (One word only): ";
	cin>>st[itemcount].venue;

	++itemcount;
}


//this is used to find the location of a task record
int search(struct tasks st[], string id,int itemcount)
{
	int found =-1;
	for (int i = 0; i < itemcount && found==-1; i++)
	{
		if (st[i].stnumber == id) found=i;
		else found=-1 ;
	}

	return found;
}
//will be used in viewing all the task records
void viewall(struct tasks st[], int itemcount)
{

	int i=0;
	cout<<"                                T A S K S\n";//This is for layout purposes
	cout<<"******************************************************************************\n";
	cout<<left<<setw(15)<<"* Task Number"<<setw(10)<<"Time"<<setw(10)<<"Task Name "<<setw(10)<<"Date"<<setw(5)<<"Venue        \t\t     *";
	cout<<"\n******************************************************************************\n";
	while(i<=itemcount)
	{
//this will display the stored records
		if(st[i].stnumber!="")
		{
			cout<<left<<setw(15)<<st[i].stnumber<<setw(10)<<st[i].time<<setw(10)<<st[i].task<<setw(10)<<st[i].date<<setw(5)
			<<st[i].venue;
	
			
			
		
			cout<<"\n";
		}

		i=i+1;
	}
}

// this is used to delete task records
void delete_rec(struct tasks st[], int& itemcount)
{
	string id;
	int index;
	cout<<"******************************************************************************\n";
	cout<<"*                          Delete Task Record                                *\n"; 
	cout<<"******************************************************************************\n";
	viewall(st, itemcount); //Call to viewall function
	if (itemcount > 0)
	{
//will ask the task number from the user
		cout<<"\nEnter Task Number: ";
		cin>>id;
		system("cls");
		index = search(st, id,itemcount); 
		
//below will delete the record
		if ((index!=-1) && (itemcount != 0))
		{
			if (index == (itemcount-1)) 
			{
				clean(st, index);
				--itemcount;
				
			    cout<<"******************************************************************************\n";
				cout<<"*                       Delete Task Records                                  *\n"; 
				cout<<"******************************************************************************\n";
				viewall(st, itemcount);

				cout<<"\nThe Record Was Deleted.\n";
			}
	
// this code block is used in cleaning the records
			else 
			{
				for (int i=index; i<itemcount+1; i++)
				{
					st[i] = st[i + 1];
					clean(st, itemcount);
					--itemcount ;
				}
			}	

		}	
		
//This message will appear if no record will be found in the specified task num
		else cout<<"No Record Exists On This Task Number\n";
	}
//this will appear if the data doesn't exist
	else cout<<"No Records To Delete\n";
}

//Below are used in cleaning deleted records
void clean(struct tasks st[],int index)
{
	memset(st[index].venue, 0, sizeof(st[index].venue));
	memset(st[index].task, 0, sizeof(st[index].task));
	memset(st[index].time, 0, sizeof(st[index].time));
	memset(st[index].date, 0, sizeof(st[index].date));
	st[index].stnumber="";
	/*strcpy(st[index].task,"");
	&st[index].venue={};
	&st[index].time = "";
	&st[index].date = "";*/
}


//The code block below is the function used to update records
void update_rec(struct tasks st[],int itemcount)
{
	string id;
	int column_index,index;//This is for layout purposes
	cout<<"******************************************************************************\n";
	cout<<"*                        Update Task Records                                 *\n"; 
	cout<<"******************************************************************************\n";
	viewall(st, itemcount);

//This code block will ask the task number from the user
	cout<<"\nEnter Task Number: ";
	cin>>id;
	system("cls");
	index = search(st, id,itemcount);
	
//This code block runs if index is not equal to -1
	if (index != -1)
	{
		cout<<"******************************************************************************\n";
		cout<<"*                        Edit Task Records                                   *\n"; 
		cout<<"******************************************************************************\n";
		cout<<"  1. Task Detail\n"<<"  2. Task Venues\n";
		cout<<"\nEnter Field You Want To Update(1-2): ";
		cin>>column_index;
		system("cls");
		
//This runs if column_index is equal to 1	
		if (column_index == 1)
		{
			cout<<"******************************************************************************\n";
			cout<<"*                       Edit Task Detail                                     *\n"; 
			cout<<"******************************************************************************\n";
			int name;
			cout<<"  1. Task Name\n"<<"  2. Task Date\n"<<"  3. Task Time\n";
			cout<<"\nEnter Your Choice(1-3): ";
			cin>>name;
			system("cls");

			cout<<"******************************************************************************\n";
			cout<<"*                        Edit Task Detail                                    *\n"; 
			cout<<"******************************************************************************\n";
			
//This code block will run if name is equal to 1	
            if(name==1)
			{
				cout<<"Enter Task Name: ";
				cin>>st[index].task;
				system("cls");
				viewall(st, itemcount);
			}
//This code block will run if name is equal to 2
			else if(name==2)
			{
				cout<<"Enter Date (MM-DD-YY)(Separate with dash): ";
				cin>>st[index].date;
				system("cls");
				viewall(st, itemcount);
			}
//This code block will run if name is equal to 3
			else if(name==3)
			{
				cout<<"Enter Time (HH:MM)(Separate with dash): ";
				cin>>st[index].time;
				system("cls");
				viewall(st, itemcount);
			}
		
//This will run if the user inputted a wrong value
			else
			{
				cout<<"Invalid Input!\n";
			}
		}

//This will run if column_index is equal to 1	
		else if (column_index == 2)
		{
			cout<<"******************************************************************************\n";
			cout<<"*                         Edit Task Venue                                    *\n"; 
			cout<<"******************************************************************************\n";
			cout<<"Task Venue(One word only): ";
			cin>>st[index].venue;
			system("cls");
			viewall(st, itemcount);
		}
//This will be displyed on the screen if the user inputted a wong value
			else
			{
				cout<<"Invalid Input!\n";
			}
		}
//This code block will run if the conditions above is false
		else
		{
			cout<<"******************************************************************************\n";
			cout<<"*                       Update Task Records                                  *\n"; 
			cout<<"******************************************************************************\n";
			cout<<"Invalid Column Index!\n";
		}
		
	}

//This is used in writing to a file. It is the function writeOutFile
void writeOutFile(struct tasks st[], int itemcount, fstream& myFile)
{
   	int i=0;
	myFile <<"                                T A S K S\n"
	       <<"******************************************************************************\n";
	myFile <<left<<setw(15)<<"* Task Number"<<setw(10)<<"Time"<<setw(10)<<"Task Name "<<setw(10)<<"Date"<<setw(5)<<"Venue        \t\t     *"
	       <<"\n******************************************************************************\n";
//This will run if i is less than or equal to itemcount
	while(i<=itemcount)
	{
		if(st[i].stnumber!="")//This checks if st[i].stnumber is not equal to ""
		{
                                     //This writes to a file
			myFile <<left<<setw(15)<<st[i].stnumber<<setw(10)<<st[i].time<<setw(10)<<st[i].task<<setw(10)<<st[i].date<<setw(5)
			    <<st[i].venue;
	
			
			
		
			myFile <<"\n";
		}

		i=i+1;
	}
}

