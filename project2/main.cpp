// next line forces VS compilers to work with mysql include files
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

#include <my_global.h>
#include <mysql.h>

#include <conio.h>

using namespace std;

// reads in a password without echoing it to the screen
//    WARNING: Does not work in VS2015. 
string myget_passwd()
{
	string passwd;

	for (;;)
	{
		char ch;
		ch = _getch();           // get char WITHIOUT echo!
		if (ch == 13 || ch == 10) // if done ...
			break;           //  stop reading chars!
		cout << '*';  // dump * to screen
		passwd += ch;   // addd char to password
	}
	cin.sync(); // flush anything else in the buffer (remaining newline)
	cout << endl;  // simulate the enter that the user pressed

	return passwd;
}

int main()
{
	// mysql connection and query variables
	MYSQL* conn, // actual mysql connection
		mysql;   // local mysql data
	MYSQL_RES* res; // mysql query results
	MYSQL_ROW row;  // one row of a table (result)

	// strings for mysql hostname, userid, ...
	string db_host;
	string db_user;
	string db_password;
	string db_name;

	// set up the client (this machine) to use mysql
	cout << "initializing client DB subsystem ..."; cout.flush();
	mysql_init(&mysql);
	cout << "Done!" << endl;

	//get user credentials and mysql server info
	cout << "Enter MySQL database hostname (or IP adress):";
	cin >> db_host;
	//db_host = "lindenwoodcshome.ddns.net";

	cout << "Enter MySQL database username:";
	cin >> db_user;
	//db_user = "vukicn";

	cout << "Enter MySQL database password:";
	db_password = myget_passwd(); // WARNING does not work well in VS2015
	//db_password = "trewq123";
	//cin >> db_password; // WARNING: although this works in VS2015, it will echo your pasword to the terminal

	// could also prompt for this, if desired
	db_name = db_user;


	// go out and connect to the mysql server
	cout << "Connecting to remote DB ..."; cout.flush();
	conn = mysql_real_connect(&mysql,
		db_host.c_str(), db_user.c_str(), db_password.c_str(), db_user.c_str(),
		0, 0, 0); // last three are usually 0's

// if we couldn't setup the connection ...
	if (conn == NULL)
	{
		// print out the error message as to why ...
		cout << mysql_error(&mysql) << endl;
		return 1; // ... and exit the program. 
	}
	else
		cout << "DB connection established" << endl;

	// now, send mysql our query ...
	int status;
	string myQuery;

	//create new table with car invertory 
	myQuery = "create table if not exists Car_T ";
	myQuery += "(VIN char(3), Brand char(14), Miles int, ";
	myQuery += "Dealership char(40), Price int, ";
	myQuery += "primary key (VIN, Brand))";

	status = mysql_query(conn, myQuery.c_str());

	// if the query didn't work ...
	if (status != 0)
	{
		cout << mysql_error(&mysql) << endl;
		return 1;  // ... and exit program
	}

	//create new table with manufacturer invertory 
	myQuery = "create table if not exists Manufacturer_T ";
	myQuery += "(VIN char(3), Manufacturer char(40), ";
	myQuery += "primary key(VIN) )"; 

	status = mysql_query(conn, myQuery.c_str());
	if (status != 0)
	{
		cout << mysql_error(&mysql) << endl;
		return 1;  // ... and exit program
	}

	//create new table with Dealer invertory 
	myQuery = "create table if not exists Dealer_T ";
	myQuery += "(dealerName char(40), zipcode int, ";
	myQuery += " phone char(20), primary key(dealerName))";

	status = mysql_query(conn, myQuery.c_str());

	if (status != 0)
	{
		cout << mysql_error(&mysql) << endl;
		return 1;  // ... and exit program
	}

	char n, s;
	string vin3, vin17, dealerName, manufacturer;
	string miles, price, abbr, brand ,zipcode, phone;

	cout << "Enter a command:";//prompt user to enter a command
	cin >> ws;

	while (cin >> n)//it is going to run while there is no more commands
	{
		if( n == 'a')
		{
			cin >> ws;
			cin >> s;//reads second command 
			if (s == 'c')//compare if is the same char
			{
				cout << "Enter vin: ";
				cin >> ws;
				cin >> vin17;
				abbr = vin17.substr(0, 3);
				brand = vin17.substr(3, 17);
				cout << "Enter milage: ";
				cin >> ws;
				cin >> miles;
				cout << "Enter dealer's name: ";
				cin >> ws;
				cin >> dealerName;
				cout << "Enter price: ";
				cin >> ws;
				cin >> price;

				myQuery = "INSERT INTO Car_T VALUES ( \"";
				myQuery += abbr;
				myQuery += "\", \"";
				myQuery += brand;
				myQuery += "\", ";
				myQuery += miles;
				myQuery += ", \""; 
				myQuery += dealerName;
				myQuery += "\", ";
				myQuery += price;
				myQuery += ") ;";

				status = mysql_query(conn, myQuery.c_str());
				cout << "Done" << endl;
				// if the query didn't work ...
				if (status != 0)
				{
					// ... explain why ...
					cout << mysql_error(&mysql) << endl;
					cout << "Record doesn't exists";
					//return 1;  // ... and exit program
				}
				else
					cout << "Query succeeded" << endl;
			}
			if (s == 'm')
			{
				cout << "Enter a vin abbreviation of a manufacturer: ";
				cin >> ws;
				cin >> vin3;
				cout << "Enter a manufacturer name: ";
				cin >> ws;
				cin >> manufacturer;

				myQuery = "INSERT INTO Manufacturer_T VALUES ( \"";
				myQuery += vin3 + "\", \"";
				myQuery += manufacturer + "\");";

				status = mysql_query(conn, myQuery.c_str());
				cout << "Done" << endl;
				// if the query didn't work ...
				if (status != 0)
				{
					// ... explain why ...
					cout << mysql_error(&mysql) << endl;
					cout << "Record doesn't exists";
					//return 1;  // ... and exit program
				}
				else
					cout << "Query succeeded" << endl;
			}
			if (s == 'd')
			{
				cout << "Enter dealer's name ";
				cin >> ws >> dealerName;
				cout << "Enter dealer's zip code ";
				cin >> ws >> zipcode;
				cout << "Enter dealer's phone number ";
				cin >> ws>> phone;

				// creating an sql statement
				myQuery = "INSERT into Dealer_T values (\"";
				myQuery += dealerName + "\", ";
				myQuery += zipcode + ", \"";
				myQuery += phone + "\");";

				//cout << "The Query is:" << myQuery << endl;
				//cout << "Sending query ..."; cout.flush();
				status = mysql_query(conn, myQuery.c_str());
				cout << "Done" << endl;
				// if the query didn't work ...
				if (status != 0)
				{
					// ... explain why ...
					cout << mysql_error(&mysql) << endl;
					cout << "Record doesn't exists";
					//return 1;  // ... and exit program
				}
				else
					cout << "Query succeeded" << endl;
			}
		}
		if (n == 'l')
		{
			cin >> ws >> s;
			if (s == 'c')
			{
				myQuery = "SELECT * FROM Car_T order by VIN;";

				//cout << "The Query is:" << myQuery << endl;
				//cout << "Sending query ..."; cout.flush();
				status = mysql_query(conn, myQuery.c_str());
				cout << "Done" << endl;

				// if the query didn't work ...
				if (status != 0)
				{
					// ... explain why ...
					cout << mysql_error(&mysql) << endl;
					return 1;  // ... and exit program
				}
				else
					cout << "Query succeeded" << endl;
				// get the query result(s)
				res = mysql_store_result(conn);

				
				// go through each line (row) of the answer table
				for (row = mysql_fetch_row(res);
					row != NULL;
					row = mysql_fetch_row(res))
				{
					 
					// print out the first 5 colums; they are stored in
					//    an "array-like" manner
					cout << row[0] << row[1] << "  ";
					cout << row[2] << "  " << row[3];
					cout << "  $" << row[4] << endl;
				}

				// clean up the query
				mysql_free_result(res);

			}
			if (s == 'd')
			{
				myQuery = "SELECT * FROM Dealer_T order by zipcode, dealerName ";
			
				status = mysql_query(conn, myQuery.c_str());
				cout << "Done" << endl;

				// if the query didn't work ...
				if (status != 0)
				{
					// ... explain why ...
					cout << mysql_error(&mysql) << endl;
					return 1;  // ... and exit program
				}
				else
					cout << "Query succeeded" << endl;
				// get the query result(s)
				res = mysql_store_result(conn);

				// go through each line (row) of the answer table
				for (row = mysql_fetch_row(res);
					row != NULL;
					row = mysql_fetch_row(res))
				{

					// print out the first 3 colums; they are stored in
					//    an "array-like" manner
					cout << row[0] << "    " << row[1];
					cout << "    "<< row[2] << endl;
				}


				// clean up the query
				mysql_free_result(res);
			}
		
		}
		if (n == 'f')
		{
			cin >> ws >> s;
			if (s == 'm')
			{
				cout << "Enter a manufacturer: ";
				cin >> ws >> manufacturer;
		
				myQuery = "SELECT Car_T.Miles, Car_T.Price, Car_T.Dealership, Dealer_T.phone ";
				myQuery += "FROM Car_T, Dealer_T,Manufacturer_T Where ";
				myQuery += "Manufacturer_T.Manufacturer =  \"" + manufacturer + "\"";
				myQuery += " AND Manufacturer_T.VIN = Car_T.VIN AND Car_T.Dealership= Dealer_T.dealerName";


				status = mysql_query(conn, myQuery.c_str());
				cout << "Done" << endl;

				// if the query didn't work ...
				if (status != 0)
				{
					// ... explain why ...
					cout << mysql_error(&mysql) << endl;
					return 1;  // ... and exit program
				}
				else
					cout << "Query succeeded" << endl;
				// get the query result(s)
				res = mysql_store_result(conn);


				// go through each line (row) of the answer table
				for (row = mysql_fetch_row(res);
					row != NULL;
					row = mysql_fetch_row(res))
				{

					// print out the first 4 colums; they are stored in
					//    an "array-like" manner
					cout << row[0]<< "  "<< row[1] << "  ";
					cout << row[2] << "  " << row[3]<< endl;
				}

				// clean up the query
				mysql_free_result(res);

			}
			if (s == 'z')
			{
				cout << "Enter a Zip Code: ";
				cin >> ws >> zipcode;

				myQuery = "SELECT Manufacturer_T.Manufacturer, Car_T.Miles,  ";
				myQuery += "Car_T.Price, Car_T.Dealership, Dealer_T.phone";
				myQuery += " FROM Manufacturer_T, Car_T, Dealer_T ";
				myQuery += "WHERE Dealer_T.zipcode = " + zipcode;
				myQuery += " AND Dealer_T.dealerName = Car_T.Dealership ";
				myQuery += "AND Car_T.VIN = Manufacturer_T.VIN ";
				myQuery += "ORDER BY Manufacturer_T.Manufacturer ASC, ";
				myQuery += "Car_T.Price DESC, Car_T.Dealership";

				//cout << "The Query is:" << myQuery << endl;
				//cout << "Sending query ..."; cout.flush();
				status = mysql_query(conn, myQuery.c_str());
				cout << "Done" << endl;

				// if the query didn't work ...
				if (status != 0)
				{
					// ... explain why ...
					cout << mysql_error(&mysql) << endl;
					return 1;  // ... and exit program
				}
				else
					cout << "Query succeeded" << endl;
				// get the query result(s)
				res = mysql_store_result(conn);


				// go through each line (row) of the answer table
				for (row = mysql_fetch_row(res);
					row != NULL;
					row = mysql_fetch_row(res))
				{

					// print out the first 5 colums; they are stored in
					//    an "array-like" manner
					cout << row[0] << "  " << row[1] << "  $";
					cout << row[2] << "  " << row[3] << "  ";
					cout << row[4] << endl;
				}

				// clean up the query
				mysql_free_result(res);

			}
		}
		if (n == 'd')
		{	
			cin >> ws >> s;
			if (s == 'c')
			{
				cout << "Enter vin you would like to delete: ";
				cin >>ws>> vin17;
				abbr = vin17.substr(0, 3);
				brand = vin17.substr(3, 17);


				// creating an sql statement
				string myQuery = "delete from Car_T where ";
				myQuery += "VIN = \"";
				myQuery += abbr;
				myQuery += "\" AND Brand = \"";
				myQuery += brand + "\"";

				// delete the team from the table Teams_T 
				status = mysql_query(conn, myQuery.c_str());
				cout << "Done" << endl;

				// if the query didn't work ...
				if (status != 0)
				{
					// ... explain why ...
					cout << mysql_error(&mysql) << endl;
					cout<< "VIN "<<abbr<<brand<< " is not in the database";
					//return 1;  // ... and exit program
				}
				else
					cout << "The car with VIN "<< abbr<<brand <<" is removed from the database" << endl;
			}
			if (s == 'd')
			{
				cout << "Enter a dealer you want to delete: "; \
				cin >> ws >> dealerName;

				// creating an sql statement
				string myQuery = "delete from Car_T where ";
				myQuery += "Dealership = \"";
				myQuery += dealerName;
				myQuery += "\"";

				// delete the team from the table Teams_T 
				//cout << "The Query is:" << myQuery << endl;
				//cout << "Sending query ..."; cout.flush();
				status = mysql_query(conn, myQuery.c_str());
				cout << "Done" << endl;

				// if the query didn't work ...
				if (status != 0)
				{
					// ... explain why ...
					cout << mysql_error(&mysql) << endl;
					cout << "The dealer " << dealerName << "'s car is not in the database";
					//return 1;  // ... and exit program
				}
				else
					cout << "The dealer " << abbr << "'s car is removed from the database" << endl;


				// creating an sql statement
				myQuery = "delete from Dealer_T where ";
				myQuery += "dealerName = \"";
				myQuery += dealerName;
				myQuery += "\"";

				// delete the team from the table Teams_T 
				//cout << "The Query is:" << myQuery << endl;
				//cout << "Sending query ..."; cout.flush();
				status = mysql_query(conn, myQuery.c_str());
				cout << "Done" << endl;

				// if the query didn't work ...
				if (status != 0)
				{
					// ... explain why ...
					cout << mysql_error(&mysql) << endl;
					cout << "The dealer " << dealerName << " is not in the database";
					//return 1;  // ... and exit program
				}
				else
					cout << "The dealer " << abbr << " is also removed from the database" << endl;

			}
		}
		if (n == 's')
		{ 
			// creating an sql statement
			myQuery = "SELECT Manufacturer_T.Manufacturer, AVG(Car_T.Price) AS Average_Price ";
			myQuery += "FROM Manufacturer_T, Car_T WHERE Manufacturer_T.VIN = Car_T.VIN ";
			myQuery += "GROUP BY Manufacturer_T.Manufacturer";

			//cout << "The Query is:" << myQuery << endl;
			//cout << "Sending query ..."; cout.flush();
			status = mysql_query(conn, myQuery.c_str());
			cout << "Done" << endl;

			// if the query didn't work ...
			if (status != 0)
			{
				// ... explain why ...
				cout << mysql_error(&mysql) << endl;
				return 1;  // ... and exit program
			}
			else
				cout << "Query succeeded" << endl;
			// get the query result(s)
			res = mysql_store_result(conn);

			// go through each line (row) of the answer table
			for (row = mysql_fetch_row(res);
				row != NULL;
				row = mysql_fetch_row(res))
			{

				// print out the first 4 colums; they are stored in
				//    an "array-like" manner
				cout << row[0] << "  $" << row[1] << endl;
			}

			// clean up the query
			mysql_free_result(res);
		}

		if (n == 'q')
		{
			exit(1);
		}
		cout << "Enter a command:";// asking for next command when finish with one
	}
	// clean up the connection
	mysql_close(conn);


	exit(0); // uncomment to keep create table ...

	return 0;

}