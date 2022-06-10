/*
CS221 Term Project: Delivery Service

Done by the Programmers:
	Shahad AlQarni
	Zainab AlRamadhan
	Maen AlHammadi
	Norah AlSalhi

This program offers delivery services for customers and employees
*/

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
using namespace std;

//Global variables & constants
const int SHIP_NUM = 100;
int myIndex = 4;


//Structures
struct Employee{
	string id, password, name;
};

struct Shipment{
	string number, phone, city, customer_name;
	double cost;
	char status;
} *ship = new Shipment[SHIP_NUM];

struct Date{
	int day, month, year;
};


//Functions Definitions

void view(){ //this function will print all the array (ship) elements
	for(int i=0 ; i <= myIndex ; i++){
		cout << "\n*************************\n"
			 << "Shipment " << i+1 << ":\n\n"
			 << "- Delivery number: " << ship[i].number << endl
			 << "- Customer name: " << ship[i].customer_name << endl
			 << "- Phone number: " << ship[i].phone << endl
			 << "- Recieving city: " << ship[i].city << endl
			 << "- Cost: " << ship[i].cost << endl
			 << "- Status: " << (ship[i].status == 'y' ? "Delivered" : "In way") << endl;
	}
} //end of view function

void display(int index){ //this function displays one element of ship array
	cout << "\n  Shipment information:\n"
		 << "\t- Delivery number: " << ship[index].number << endl
		 << "\t- Customer name: " << ship[index].customer_name << endl
		 << "\t- Phone number: " << ship[index].phone << endl
		 << "\t- City: " << ship[index].city << endl
		 << "\t- Cost: " << ship[index].cost << " SR" << endl
		 << "\t- Status: " << (ship[index].status == 'y' ? "Delivered" : "In way") << endl << endl;
}

void editFun(int index){ //this function updates one element of ship array
	cout << "\nNew name: ";
	cin >> ship[index].customer_name;
	cout << "New phone: ";
	cin >> ship[index].phone;
	while(ship[index].phone.length() != 10){
		cout << "Enter correct number (10 digits): ";
		cin >> ship[index].phone;
	}
	cout << "New city: ";
	cin >> ship[index].city;
	
	cout << endl;
}

void deleteFun(int index){ //this function deletes one element of ship array
	for(int i=index ; i <= myIndex-1 ; i++)
		ship[i] = ship[i+1]; //shift elements one cell to the left
	
	myIndex--;
	cout << "Deleted\n****************\n";
}

void sort(){ //this function will sort the shipments by number
	bool ordered = false;
	Shipment temp;
	
	for(int i=0 ; i<myIndex && !ordered ; i++){
		ordered = true;
		for(int j=0 ; j<myIndex ; j++){
			if(ship[j].number > ship[j+1].number){
				ordered = false;
				temp = ship[j];
				ship[j] = ship[j+1];
				ship[j+1] = temp;
			}
		}
	}
} //end of sort function

int search(string phone){ //sequential search
	for(int i=0 ; i <= myIndex ; i++) //search for this number
		if( phone == ship[i].phone )
			return i;
	return -1;
}

int search(string delivery_num, int first, int end){ //binary search
	int result=0;
	
	if(first > end){
		result = -1;
	}
	else{
		int mid = (first + end) / 2; //middle index
		
		if(delivery_num == ship[mid].number)
			result = mid;
		else if(delivery_num < ship[mid].number)
			result = search(delivery_num, first, mid-1);
		else
			result = search(delivery_num, mid+1 , end);
	}
	return result;
}

int search(const string branches[], int size, string city){
	for(int i=0 ; i<size ; i++)
		if(branches[i] == city)
			return i;
	return -1;
}

void letterCase(string &word){ //this function will modify the word letter case
	word[0] = toupper(word[0]);
	for(int i=1 ; i < word.length() ; i++)
		word[i] = tolower( word[i] );
}

bool login( Employee *emp, int size ){ //this function is for employee login
	string id, password;
	
	//input
	cout << "\n*********************************************************\n\t  To login, enter:\n"
		 << "\t- ID: ";
	cin >> id;
	cout << "\t- Password: ";
	cin.ignore();
	getline(cin, password);
	
	//check
	for(int i=0 ; i<=size ; i++){
		if(emp[i].id == id && emp[i].password == password){
			cout << "\n\tLogged in successfully.. Welcome again " << emp[i].name << endl;
			return true;
		}
	}
	return false;
} //end of login function

double calDistance(int x1, int y1, int x2, int y2){
    double y = sqrt( pow(x2-x1 , 2) + pow(y2-y1 , 2) );
    return y ;
}

void costFun(double distance, double &cost){ //this function determines cost according to the distance
    if(distance > 100)
    	cost= 50;
	else
		cost= 25;
}

void guess_game(int correct){
	int guess, play;
	
	cout << "\n\tWhile waiting.. Do you want to play? Enter 1 to play: ";
	cin >> play;
	
	while(play == 1){
		cout << "\n\t Guess the branch of your shipment:\n"
			 << "0. Dammam\t" << "1. Jubail\t" << "2. Riyadh\n" << "3. Jeddah\t" << "4. Hail\n"
			 << "Enter a number: ";
		cin >> guess;
		
		if(guess == correct){
			cout << "\n\t ****---- Correct..You won! ----****\n";
			break; //break the while loop
		}
		else{
			cout << "\n\t xx Wrong guess xx  :( \n\n  Enter 1 to try again, other number to exit the game: ";
			cin >> play;
		}
	} //end of while
	
} //end of guess_game function

void recieve(const string branches[], int size, bool is_employee){
	int index, rand_branch, x_ship, y_ship, x_user, y_user;
	short int Choice, How, Payment;
	double distance, cost;
	string Phone, DeliveryNum;
	Date expected_date;
	
	cout<< "\nUsing:\n"
		<< "1. Phone number\n"
		<< "2. Delivery number\n"
		<< "Enter: ";
	choice_label:
	cin >> Choice;
	
	switch(Choice){
		case 1: //using phone number
			cout<<"\n - Enter phone number: ";
			phone_label:
			cin >> Phone;
			if(Phone.length() == 10){ //check phone number validation
				index = search(Phone);
				while(index == -1){
					cout << "Phone number is not found, enter again\n";
					cin >> Phone;
					index = search(Phone);
				}
				if(ship[index].status == 'y'){
					cout << "\n\tYour shipment is already delivered\n";
				}
				else{
					cout<< "\nRecieve from:\n"
						<< "1. A branch\n"
						<< "2. Your location\n";
					how_label:
					cin >> How;
					switch(How){
						case 1: //from a branch
							cout << "\t Processing....\n";
							rand_branch = 0 + rand() % (size-1 -0+1);
							guess_game(rand_branch);
							
							cout << "\n** Your shipment is in " << branches[rand_branch]
								 << " -- All branches open from 9 AM to 11 PM ** \n";
							break;
						case 2: //from your location
							cout << "\n - Enter your location coordinates:\n";
							cin >> x_user >> y_user;
							
							//branch coordinates
							x_ship = 10 + rand() % (300-10+1);
							y_ship = 10 + rand() % (300-10+1);
							distance = calDistance(x_ship, y_ship, x_user, y_user);
							cout << "\nDistance: " << distance << endl;
							
							expected_date.day = 1 + rand() % (30-1+1);
							expected_date.month = 1 + rand() % (12-1+1);
							expected_date.year = 2022;
							cout << "Expected delivery date: "<<expected_date.day<< "/" <<expected_date.month<< "/" <<expected_date.year << endl;
							
							if(is_employee)
								ship[index].cost = ship[index].cost - (ship[index].cost * 0.10);
							
							cout << "Cost: " << ship[index].cost << " SR\n"
								 << "\n - Choose payment method (1.cash\t 2.credit card)\n";
							cin >> Payment;
							
							cout << "\n ** Thank you for using our service **\n";
							break;
						default:
							cout << "Invalid choice, enter again: ";
							goto how_label;
					}//end of inner switch
				} //end of inner if-else
			}
			else{
				cout << "Invalid phone number, enter again: ";
				goto phone_label;
			} //end of outer if-else
			break;
		case 2: //using delivery number
			cout<<"\nEnter delivery number: ";
			del_label:
			cin >> DeliveryNum;
			
			if(DeliveryNum.length() == 6){ //check number validation
				index = search(DeliveryNum, 0, myIndex);
				
				if(index == -1){
					cout << "Delivery number is not found, try again:\n";
					goto del_label;
				}
				if(ship[index].status == 'y')
					cout << "\n\tYour shipment is already delivered\n";
				else{
					cout<< "\nRecieve from:\n"
						<< "1. A branch\n"
						<< "2. Your location\n";
					label:
					cin>>How;
					switch(How){
						case 1: //branch
							cout << "\t Processing....\n";
							rand_branch = 0 + rand() % (size-1-0+1);
							guess_game(rand_branch);
							
							cout<<"\n** Your shipment is in " << branches[rand_branch]
								<<" -- All branches open from 9 AM to 11 PM ** \n";
							break;
						case 2: //your location
							cout << "\n - Enter your corrdinates: \n";
							cin >> x_user >> y_user;
							
							x_ship = 1 + rand() % (300-1+1);
							y_ship = 1 + rand() % (300-1+1);
							
							distance = calDistance(x_user, y_user, x_ship, y_ship);
							cout << "\nDistance: " << distance << endl;
							
							expected_date.day = 1 + rand() % (30-1+1);
							expected_date.month = 1 + rand() % (12-1+1);
							expected_date.year = 2022;
							cout<<"Expted delivery date is "<<expected_date.day<<"/"<<expected_date.month<<"/"<<expected_date.year << endl;
							
							if(is_employee)
								ship[index].cost = ship[index].cost - (ship[index].cost * 0.10);
							
							cout << "Cost: " << ship[index].cost << " SR\n";
								
							cout<<"\n - Choose payment method (1. cash 2. credit card)\n";
							cin>>Payment;
							
							cout << "\n ** Thank you for using our service **\n";
							break;
						default:
							cout << "Invalid choice, enter again: ";
							goto label;
					} //end of inner switch
				} //end of inner if-else
			}
			else{
				cout << "Invalid delivery number, enter again: ";
				goto del_label;
			} //end of outer if-else
			
			break;
		default:
			cout<<"Invalid choice, enter again: ";
			goto choice_label;
	} //end of outer switch
} //end of recieveFun

void send(const string branches[], int size, bool is_employee){ //This function is to add an element to ship array
	myIndex++;
	
	string your_city, reciever_phone, reciever_name;
	int temp; //to help generate a delivery number
	short int choice;
	double cost, distance;
	
	cout << "\n - Enter your city: ";
	cin >> your_city;
	
	//Modify letter case
	letterCase(your_city);
	
	recieve_label:
	cout << "\nHow should we recieve your delivery?" << endl;
	cout << "1. Branch" << endl;
	cout << "2. Home" << endl;
	cout << "- Enter: ";
	cin >> choice;
	
	switch(choice){
		case 1: //branch choice
			if( search(branches, size, your_city) == -1){
				cout << "No branches in this city\n";
        		goto recieve_label;
			}
			else{
				cout << "\n - Enter the distination (city)" << endl;
				cin >> ship[myIndex].city;
				//Modify letter case
				letterCase(ship[myIndex].city);
				
				if( search(branches, size, ship[myIndex].city) == -1 ) //search for city in branches[]
					cout << "\nNo branches at " << ship[myIndex].city << ", the shipment will be delivered to reciever\'s home\n";
				else
					cout << "\nThe shipment will be delivered to the nearest branch at " << ship[myIndex].city << endl;
		
				cout << "\n*********\n"
					 << " - Enter the reciever phone number: ";
				cin >> ship[myIndex].phone; 
				while(ship[myIndex].phone.length() != 10){
					cout << "Enter a correct phone number(10 digits): ";
					cin >> ship[myIndex].phone;
				}
				cout << "\n - Enter the reciever name: ";
				cin >> ship[myIndex].customer_name;
				
				distance = 50 + rand() % (300-50+1);
				costFun(distance, cost);
	
				if(is_employee) //discount 10% for employees
					cost = cost - (cost * 0.10);
	
				ship[myIndex].status = 'n';
				ship[myIndex].cost = cost;
		
				ship[myIndex].number = "";
				for(int i=0 ; i<6 ; i++){
					//generate a random digit for each character of delivery number
					temp = 0 + rand() % (9-0+1);
					ship[myIndex].number += to_string(temp);
				}
				
				display(myIndex);
				
				int edit;
				cout << "\n If you want to edit, enter 1: ";
				cin >> edit;
				
				while(edit == 1){
					editFun(myIndex);
					display(myIndex);
					cout << "\n If you want to edit, enter 1: ";
					cin >> edit;
				}
				cout << "\n\tDone, thank you for using our service\n";
			}
			
			break; // end of case 1
		
		case 2: //home choice
			cout << "\n - Enter the distination (city)" << endl;
			cin >> ship[myIndex].city;
	
			//Modify letter case
			letterCase(ship[myIndex].city);
			
			if( search(branches, size, ship[myIndex].city) == -1 ) //search for the city in branches[]
				cout << "\nNo branches at " << ship[myIndex].city << ", the shipment will be delivered to reciever\'s home\n";
			else
				cout << "\nThe shipment will be delivered to the nearest branch at " << ship[myIndex].city << endl;
		
			cout << "\n*********\n"
				 << " - Enter the reciever phone number: ";
			cin >> ship[myIndex].phone;
		
			while(ship[myIndex].phone.length()!=10){
				cout << "Enter a correct phone number(10 digits): ";
				cin >> ship[myIndex].phone;
			}
			cout << "\n - Enter the reciever name: ";
			cin >> ship[myIndex].customer_name;
			
			distance = 50 + rand() % (300-50+1);
			costFun(distance, cost);
			
			if(is_employee) //discount 10% for employees
				cost = cost - (cost * 0.10);
		
			ship[myIndex].status = 'n';
			ship[myIndex].cost = cost;
		
			ship[myIndex].number = "";
			for(int i=0 ; i<6 ; i++){
				//generate a random digit for each character of delivery number
				temp = 0 + rand() % (9-0+1);
				ship[myIndex].number += to_string(temp);
			}
		
			display(myIndex);
			
			int edit;
			cout << "\n If you want to edit, enter 1: ";
			cin >> edit;
			
			while(edit == 1){
				editFun(myIndex);
				display(myIndex);
				cout << "\n If you want to edit, enter 1: ";
				cin >> edit;
			}
			cout << "\n\tDone, thank you for using our service\n";
		
		break; //end of case 2
		
		default:
			cout << "Invalid choice.. try again\n";
			goto recieve_label;
	} //end of switch
	
	sort(); //sort shipments after adding the new one
	
} //end of send function

void track(){
	short int choice;
	string delivery_num, phone_num;
	
	cout << "\nUsing:\n"
		 << "1. Delivery number\n"
		 << "2. Phone number\n";
	track_label:
	cout << "- Enter: ";
	cin >> choice;
	
	switch(choice){
		case 1:{ //delivery number
			cout << "\n - Enter delivery number: ";
			cin >> delivery_num;
			
			while(delivery_num.length() != 6){
				cout << "\nInvalid.. try again\n";
				cin >> delivery_num;
			}
			
			//search function
			int ship_index = search(delivery_num, 0, myIndex);
			
			while(ship_index == -1){
				cout << "\nNot found, try again\n";
				cin >> delivery_num;
			}
			display(ship_index);
			
			if(ship[ship_index].status == 'n'){
				int x_ship, y_ship;
				x_ship = 5 + rand() % (200-5+1);
				y_ship = 5 + rand() % (200-5+1);
				//location of the in-way shipment:
				cout<< "Location: (" << x_ship << ", " << y_ship << ") \n";
				
				Date expect;
				expect.day = rand() % 30-1+1;
				expect.month = rand() % 12-1+1;
				expect.year = 2022;
				cout << "Expected delivery date: "<<expect.day<<"/"<<expect.month<<"/"<<expect.year << endl
					 << "\n If you want to cancel the shipment, enter 1: ";
				
				int cancel;
				cin >> cancel;
				
				if(cancel == 1){
					deleteFun(ship_index);
				}
			} //end of if
			else
				cout << "\nThe shipment is already delivered\n";
				
			short int other;
			cout << "\n - Tracking other shipment?\n 1.yes \t 2.no\n";
			cin >> other;
			if(other == 1)
				track();
			else if(other == 2)
				return;
			else
				cout << "Invalid choice\n";
			
			break;
		}
		case 2: //phone number
		{
			int index;
			cout << "\n - Enter phone number: ";
			phone_num_label:
				cin >> phone_num;
			
			if(phone_num.length() == 10){
				index = search(phone_num);
				
				while(index == -1){
					cout << "\nPhone number is not found, enter again\n";
					cin >> phone_num;
					index = search(phone_num);
				}
				display(index);
				
				if(ship[index].status == 'n'){
					int x_ship, y_ship;
					x_ship = 5 + rand() % (200-1+1);
					y_ship = 5 + rand() % (200-1+1);
					cout<< "Location: (" << x_ship << ", " << y_ship << ") \n";
					
					Date expect;
					expect.day = rand() % 30-1+1;
					expect.month = rand() % 12-1+1;
					expect.year = 2022;
					cout << "Expected delivery date: "<<expect.day<<"/"<<expect.month<<"/"<<expect.year << endl
						 << "\n If you want to cancel the shipment, enter 1: ";
					
					int cancel;
					cin >> cancel;
					
					if(cancel == 1)
						deleteFun(index);
				}
				else{
					cout << "\nYour shipment is already delivered\n";
				} //end of inner if-else
			}
			else{
				cout << "\nInvalid phone number, enter again\n";
				goto phone_num_label;
			} //end of outer if-else
			
			short int other;
			cout << "\n - Tracking other shipment?\n 1.yes \t 2.no\n";
			cin >> other;
		
			if(other == 1)
				track();
			else if(other == 2)
				return;
			else
				cout << "Invalid choice\n";
			
			break;
		}
		default:
			cout << "Invalid choice, try again\n";
			goto track_label;
	}
} //end of track function

void archived(){ //this function reads the archived shipments and displays it
	ifstream inFile;
	
	string delivery_number, phone, city, name;
	double cost;
	char status;
	
	inFile.open("archive.txt", ios::in);
	
	if( inFile.is_open() == true || inFile.is_open() ){
		getline(inFile, delivery_number, '\t');
		getline(inFile, phone, '\t');
		getline(inFile, city, '\t');
		getline(inFile, name, '\t');
		
		inFile >> cost;
		
		inFile.ignore();
		inFile.get(status);
		//reading done
		cout << "\n --------------------------------------\n"
			 << "|                                      |"
			 << "\n|      *** Archived Shipments ***      |\n"
			 << "|                                      |"
			 << "\n --------------------------------------\n";
		
		while( !inFile.eof() ){
			cout << "- Delivery number: " << delivery_number << endl;
			cout << "- Phone number: " << phone << endl;
			cout << "- City: " << city << endl;
			cout << "- Customer name: " << name << endl;
			cout << "- Cost: " << cost << endl;
			cout << "- Status: " << status << endl;
			cout << "\n --------------------------------------\n";
			
			inFile.ignore();
			getline(inFile, delivery_number, '\t');
			getline(inFile, phone, '\t');
			getline(inFile, city, '\t');
			getline(inFile, name, '\t');
			
			inFile >> cost;
			
			inFile.ignore();
			inFile.get(status);
		} //end of while
	} //end of if
	
	inFile.close();
	
} //end of archived function


int main(){
	const int EMP_NUM = 100;
	short int choice, service; //to store the choices of user
	
	string branches[] = {"Dammam" , "Jubail" , "Riyadh" , "Jeddah" , "Hail"};
	int noBranches = sizeof(branches) / sizeof(branches[0]);
	
	Employee *emp = new Employee [EMP_NUM];
	int empIndex;
	//employees information:
	//		   ID	  Password	  Name
	emp[0] = {"111" , "ss111" , "Shahad"};
	emp[1] = {"222" , "zz222" , "Zainab"};
	emp[2] = {"333" , "nn333" , "Norah"};
	emp[3] = {"444" , "mm444" , "Maeen"};
	empIndex = 3;
	
	//shipments information:
	//		Delivery Num	Phone Num		City	 	Name	  Cost  status
	ship[0] = { "210012" , "0555555555" , "Dammam" , "Mohammad" , 50 , 'y'};
	ship[1] = { "520025" , "0577755599" , "Riyadh" , "Khalid" , 50 , 'y'};
	ship[2] = { "890098" , "0572211359" , "Hail" , "Jumana" , 25 , 'n'};
	ship[3] = { "870078" , "0573311295" , "Riyadh" , "Ayah" , 25 , 'y'};
	ship[4] = { "660066" , "0577332441" , "Jeddah" , "Ahmed" , 50 , 'n'};
	
	//writing the archived shipments (delivered) to a file
	ofstream outArch;
	outArch.open("archive.txt" , ios::out);
	
	if(outArch.is_open() == true || outArch.is_open() ){
		for(int i=0 ; i <= myIndex ; i++){
			if(ship[i].status == 'y'){
				outArch << ship[i].number << '\t'
						<< ship[i].phone << '\t'
						<< ship[i].city << '\t'
						<< ship[i].customer_name << '\t'
						<< ship[i].cost << '\t'
						<< ship[i].status << endl;
			}
		}
	}
	
	outArch.close();

	//writing employees information to a file
	ofstream outEmp;
	outEmp.open("employees.txt" , ios::app);
	
	if( outEmp.is_open() == true || outEmp.is_open() ){
		for(int i=0 ; i<=empIndex ; i++){
			outEmp << emp[i].id << "\t " << emp[i].password << "\t " << emp[i].name << endl;
		}
	}
	
	outEmp.close();
	
	srand(time(0));
	
	//sort the shipments
	sort();
	
	//output beginning
	cout << "  ----- Welcome to Delivery Service -----\n"
		 << "\n** Enter the number of option when you choose **\n";
	cout << "\n---------------------------------";
	begin_label:
	cout << "\n\t  Are you:\n"
		 << " \t1. Customer\n"
		 << " \t2. Employee\n"
		 << "\t- Enter: ";
	cin >> choice;
	
	switch(choice){
		case 1: //customer options
			do{
				cout << "\n*********************************************************\n"
					 << "Select a service:\n"
		 			 << " 1. Send\n"
			 		 << " 2. Track\n"
			 		 << " 3. Recieve\n"
			 		 << " 4. Back to the beginning\n"
					 << " 5. End\n";
			 	service1_label:
				cout << "\n- Enter: ";
		 		cin >> service;
		 	
			 	switch(service){
			 		case 1:
			 			send(branches, noBranches, false);
			 			break;
			 		case 2:
		 				track();
		 				break;
			 		case 3:
		 				recieve(branches, noBranches, false);
		 				break;
		 			case 4:
		 				cout << "\n---------------------------------";
		 				goto begin_label;
		 				break;
		 			case 5:
		 				break;
			 		default:
			 			cout << "Wrong choice of service\n\n";
		 				goto service1_label;
				 } //end of inner switch 1
			}
			while (service != 5);
			
			break;
		
		case 2: //employee options
			//login
			login_label:
			if( login(emp, empIndex) ){ //this block will not be excuted unless the login is successfull
				do{
					cout << "\n*********************************************************\n"
						 << "Select a service:\n"
			 			 << " 1. Send\n"
			 			 << " 2. Track\n"
			 			 << " 3. Recieve\n"
						 << " 4. View all shipments\n" //the additional service for employee
						 << " 5. View archive\n"
						 << " 6. Back to the beginning (log out)\n"
						 << " 7. End\n";
					service2_label:
					cout << "\n- Enter: ";
			 		cin >> service;
			 		
		 			switch(service){
			 			case 1:
			 				send(branches, noBranches, true);
			 				break;
			 			case 2:
			 				track();
			 				break;
				 		case 3:
			 				recieve(branches, noBranches, true);
			 				break;
			 			case 4:
			 				view();
		 					break;
		 				case 5:
		 					archived();
		 					break;
		 				case 6:
		 					cout << "\n---------------------------------";
		 					goto begin_label;
		 					break;
		 				case 7:
		 					break;
		 				default:
		 					cout << "Wrong choice of service\n\n";
		 					goto service2_label;
			 		} //end of inner switch 2
				}
				while(service != 7);
			} //end if
			else{
				cout << "Wrong name/password.. Please try again\n";
				goto login_label;
			} //end else
			
			break;
			
			default:
				cout << "  Wrong choice.. Try again\n";
				goto begin_label;
	} //end of outer switch
	
	cout << "\n Thank you for using our service\n Bye Bye.";
	
	/*deleting dynamic variables*/
	delete [] emp;
	delete [] ship;
	emp= NULL;	ship= NULL;
	
	return 0;
} //end of main
