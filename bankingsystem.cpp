#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;


class Account
{
	int acno;
	char name[50];
	int deposit;
	char type;
public:
	int create_Account();	//function to get data from user
	int show_Account() const;	//function to show data on screen
	int modify();	//function to add new data
	int dep(int);	//function to accept Amount and add to balance Amount
	int draw(int);	//function to accept Amount and subtract from balance Amount
	int report() const;	//function to show data in tabular format
	int retacno() const;	//function to return Account number
	int retdeposit() const;	//function to return balance Amount
	char rettype() const;	//function to return type of Account
};        

int Account::create_Account()
{
	cout<<"\nEnter The Account No. :";
	cin>>acno;
	cout<<"\n\nEnter The Name of The Account Holder : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter Type of The Account (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nEnter The Initial Amount : ";
	cin>>deposit;
	cout<<"\n\n\nAccount Created..";
}

int Account::show_Account() const
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nAccount Holder Name : ";
	cout<<name;
	cout<<"\nType of Account : "<<type;
	cout<<"\nBalance Amount : "<<deposit;
}


int Account::modify()
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nModify Type of Account : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nModify Balance Amount : ";
	cin>>deposit;
}

	
int Account::dep(int x)
{
	deposit+=x;
}
	
int Account::draw(int x)
{
	deposit-=x;
}
	
int Account::report() const
{
	cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
}

	
int Account::retacno() const
{
	return acno;
}

int Account::retdeposit() const
{
	return deposit;
}

char Account::rettype() const
{
	return type;
}



int write_Account();	//function to write record in binary file
int display_sp(int);	//function to display Account details given by user
int modify_Account(int);	//function to modify record of file
int delete_Account(int);	//function to delete record of file
int display_all();		//function to display all Account details
int deposit_withdraw(int, int); // function to desposit/withdraw Amount for given Account
int intro();	//introductory screen function




int main()
{
	char ch;
	int num;

	do
	{
		system("cls");
		cout<<"Made By Smile-17CE103"<<endl<<endl;
		cout<<"\t------------Welcome to Banking--------------"<<endl<<"\tDon't share your bank details with anyone"<<endl<<"\tFor any Queries call our Toll Free Number- XXXXXXXXXX"<<endl;
		cout<<"\n\tSelect Your Option (1-8)";
		cout<<"\n\n\t01. New Account";
		cout<<"\n\n\t02. Deposit Amount";
		cout<<"\n\n\t03. Withdraw Amount";
		cout<<"\n\n\t04. Balance Enquiry";
		cout<<"\n\n\t05. All Account Holders";
		cout<<"\n\n\t06. Close Account";
		cout<<"\n\n\t07. Modify Account";
		cout<<"\n\n\t08. Exit"<<endl<<endl;
		cout<<"\t";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			write_Account();
			break;
		case '2':
			cout<<"\n\n\tEnter The Account No. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout<<"\n\n\tEnter The Account No. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4': 
			cout<<"\n\n\tEnter The Account No. : "; cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout<<"\n\n\tEnter The Account No. : "; cin>>num;
			delete_Account(num);
			break;
		 case '7':
			cout<<"\n\n\tEnter The Account No. : "; cin>>num;
			modify_Account(num);
			break;
		 case '8':
			cout<<"\n\n\tThanks for using bank managemnt system";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!='8');
	return 0;
}



//function to write in file


int write_Account()
{
	Account ac;
	ofstream outFile;
	outFile.open("Account.dat",ios::binary|ios::app);
	ac.create_Account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(Account));
	outFile.close();
}


//function to read specific record from file


int display_sp(int n)
{
	Account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("Account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return 0;
	}
	cout<<"\nBALANCE DETAILS\n";

    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(Account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_Account();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nAccount number does not exist";
}



//function to modify record of file


int modify_Account(int n)
{
	bool found=false;
	Account ac;
	fstream File;
	File.open("Account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return 0;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(Account));
		if(ac.retacno()==n)
		{
			ac.show_Account();
			cout<<"\n\nEnter The New Details of Account"<<endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(Account));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(Account));
			cout<<"\n\n\t Record Updated";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}


//function to delete record of file



int delete_Account(int n)
{
	Account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("Account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return 0;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(Account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(Account));
		}
	}
	inFile.close();
	outFile.close();
	remove("Account.dat");
	rename("Temp.dat","Account.dat");
	cout<<"\n\n\tRecord Deleted ..";
}


//function to display all Accounts deposit list


int display_all()
{
	Account ac;
	ifstream inFile;
	inFile.open("Account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return 0;
	}
	cout<<"\n\n\t\tAccount HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.      NAME           Type  Balance\n";
	cout<<"====================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(Account)))
	{
		ac.report();
	}
	inFile.close();
}


//function to deposit and withdraw Amounts


int deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	Account ac;
	fstream File;
	File.open("Account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return 0;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(Account));
		if(ac.retacno()==n)
		{
			ac.show_Account();
			if(option==1)
			{
				
				cout<<"\n\nEnter The Amount to be deposited";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
				cout<<"\n\n\tTO WITHDRAW Amount ";
				cout<<"\n\nEnter The Amount to be withdraw";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
					cout<<"Insufficience balance";
				else
					ac.draw(amt);
			}
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(Account));
			cout<<"\n\n\t Record Updated";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}



//INTRODUCTION FUNCTION






//END OF PROJECT

