//*************************  PROGRAM IDENTIFICATION  **************************
//*                                                                           *
//*  PROGRAM FILE NAME: prog1.cpp    ASSIGNMENT #:  1     Grade: _________    *
//*                                                                           *
//*                    ____________________________________                   *
//*                                Nikola Vukic                               *
//*                                                                           *
//*   COURSE #:  CSC 30500 11             DUE DATE:  September 8, 2019        *
//*                                                                           *
//*****************************************************************************

//**************************  PROGRAM DESCRIPTION  ****************************
//*                                                                           *
//*   PROCESS: program that keeps track of car dealers, cars,                 *
//*   and a list of manufacturers. essentially prompt the user to enter       *
//*   a one letter command, and process the command.                          *
//*                                                                           *
//*****************************************************************************

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <string>

using namespace std;

int main() {
	//variables
	char n,s, vins; //used for reading commands from user and reading Vins
	char carVin[17], manufacturerVin[3], phoneNum[10], findVin[3]; //used for temporary comparing vins, and phone number
	int numOfMiles, carPrice,zipCode, zip; //number of miles, car price, zip code and another zip for searching the same zipCode
	string dealerName, manuName, carName, dealer;//dealers name, dealer for comparing dealers, manufacturer name, and car name

	cout << "Enter a command:";//prompt user to enter a command
	
	while (cin>>n)//it is going to run while there is no more commands
	{
		
		if (n == 'a') //compare if is the same char
		{
			cin >> s; //reads second command 
			if (s == 'c')//compare if is the same char
			{
				ofstream carFile;
				carFile.open("car.txt", ios::app); //open existing file with cars
				for (int i = 0; i < 17; i++) //reads all 17 char Vin and write in file where are other cars
				{
					cin >> vins;
					carVin[i] = vins;
					carFile << vins;
				}
				carFile << " "; //print space between words in the file
				cin >> numOfMiles; //reads from user number of miles
				carFile << numOfMiles;//print number of miles in the file
				carFile << " ";
				cin >> dealerName;//reads name of dealer
				carFile << dealerName;//print it in the file
				carFile << " ";
				cin >> carPrice;//read car price
				carFile << carPrice;//print it in the file
				carFile << endl;
				
			}
			if (s == 'm')//compare if is the same char
			{
				ofstream manuFile;
				manuFile.open("manufacturer.txt", ios::app);//open existing file with manufactures
				for (int i = 0; i < 3; i++) //reads vin and print it in the file
				{
					cin >> vins;
					manufacturerVin[i] = vins;
					manuFile << vins;
				}
				manuFile << " ";
				cin >> manuName;//reads car name
				manuFile << manuName;//print it in the file
				manuFile << endl;
				
			}
			if (s == 'd')//compare if is the same char
			{
				ofstream dealerFile;
				dealerFile.open("dealer.txt", ios::app);//open existing file for dealers
				cin >> dealerName;//reads dealers name
				dealerFile << dealerName;//print it in the file
				dealerFile << " ";
				cin >> zipCode;//reads zip code
				dealerFile << zipCode;//print it in the file
				dealerFile << " ";
				for (int i = 0; i < 10; i++)//reads phone number of a dealer and print it in the file
				{
					cin >> n;
					phoneNum[i] = n;
					dealerFile << n;
				}
				dealerFile << endl;
				
			}
		}
		if (n == 'l') //compare if is the same char
		{
			cin >> s;//reads second ommand
			if (s == 'c') //compare if is the same char
			{
				string line;//hold the data per line
				ifstream carFile;
				carFile.open("car.txt", ios::in);//opens file with cars
				while (getline(carFile, line))//reads line by line while there is no more and print them line by line
				{
					cout << line << endl;
				}
			}
			if (s == 'd')//compare if is the same char
			{
				ifstream dealerFile;
				dealerFile.open("dealer.txt", ios::in);//opens file with dealrs
				while (dealerFile >> dealerName >> zipCode >> phoneNum)//reads all data per line while there is some
				{
					cout <<left<< setw(30) << dealerName << setw(7) << zipCode << "  " << phoneNum<<endl;//3print it in comsole
				}
			}	
		}
		if (n == 'f')//compare if is the same char
		{
			cin >> s;//reads second commmand
			
			if (s == 'm')//compare if is the same char
			{
				cin >> manuName; //reads name of car name from user, used same variable as manufacture name to save memeory
				
				fstream manuFile;
				manuFile.open("manufacturer.txt", ios::in);//opens file with manufacturers
				while (!manuFile.eof())//reads through whole file
				{
					for (int i = 0; i < 3; i++)//first read VIN code
					{
						manuFile >> s;	
						manufacturerVin[i] = s;
					}
					manuFile >> carName; // reads car name
					
					if (carName == manuName)//compare if car name in the file is same as user entered, if it is same look for its VIn codo
					{
						for (int i=0; i<3; i++)//save vin code to another array so we can use later
						{
							findVin[i] = manufacturerVin[i];
						}
					}
				}

				fstream carFile;
				carFile.open("car.txt", ios::in);//open the file with cars
				while (!carFile.eof())//reads through whole file
				{
					for (int i = 0; i < 17; i++)// reads Vin code
					{
						carFile >> vins;
						carVin[i] = vins;
					}
					carFile>> numOfMiles >>dealer >> carPrice;//reads data from the file
					if (findVin[0] == carVin[0] &&
						findVin[1] == carVin[1] &&
						findVin[2] == carVin[2]) //check if vin is same as car's Vin
					{
						
						fstream dealerFile;
						dealerFile.open("dealer.txt", ios::in);//opens file with dealers
						while (!dealerFile.eof())//reads through whole file
						{
							dealerFile >> dealerName >> zipCode >> phoneNum;// reads other data
							if (dealer == dealerName)//check if dealer is same as we had it
							{
								//print in instructed design
								cout << manuName << ":" << numOfMiles << " miles, $"
									<< carPrice << ": " << dealer<< "[(";
								for (int i = 0; i < 10; i++) 
								{
									if (i == 0) 
									{
										cout ;
									}
									if(i==3)
									{
										cout << ")";
									}
									if (i == 6)
									{
										cout << "-";
									}
									cout << phoneNum[i];
									
								}
								cout << "]" << endl;
							}
						}
					}
				}

			}
			if (s == 'z')//compare if is the same char
			{
				cin >> zipCode;//reads zipcode from the user
				
				ifstream dealerFile;
				dealerFile.open("dealer.txt", ios::in);//opens dealer file
				while (!dealerFile.eof()) //reads through whole file
				{
					dealerFile >> dealer >> zip >> phoneNum;//reads other data
					if (zip == zipCode)//compare zip code in file with zipcode user entered
					{
						fstream carFile;
						carFile.open("car.txt", ios::in);//opens file with cars
						while (!carFile.eof())//reads through whole file
						{
							carFile >> carVin >> numOfMiles >> dealerName >> carPrice;//reads other data in the file
							if (dealer == dealerName)// compare if dealer's name is same as we looked at before
							{
								
								for (int i = 0; i < 3; i++)//save vin code in separate array 
								{
									findVin[i] = carVin[i];
								}
								fstream manuFile;
								manuFile.open("manufacturer.txt", ios::in);//opens manufacturer file
								while (!manuFile.eof())//reads thorugh wheole file
								{
									manuFile >> manufacturerVin >> carName;//reads other data from the file
									
									if (manufacturerVin[0] == findVin[0] &&
										   manufacturerVin[1] == findVin[1] &&
										     manufacturerVin[2] == findVin[2])//compare if vin code is same as dealers
									{
										//print in instructed design
										cout << carName << ":" << numOfMiles << " miles, $"
											<< carPrice << ": " << dealer << "[(";
										for (int i = 0; i < 10; i++)
										{
											if (i == 0)
											{
												cout;
											}
											if (i == 3)
											{
												cout << ")";
											}
											if (i == 6)
											{
												cout << "-";
											}
											cout << phoneNum[i];
										}
										cout << "]" << endl;
									}
								}
							}
						}
					}
				}
			}
			
		}
		if(n == 'q')//compare if is the same char, if used press 'q' it is going to exit pogram
		{
			exit(1);
		}
		
		cout << "Enter a command:";// asking for next command when finish with one
	}
}