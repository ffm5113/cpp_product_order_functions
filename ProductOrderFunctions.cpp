// Source(s) of logic assistance:  
// Gaddis, T. (2018). Starting out with C++:
// From control structures through objects. Pearson. 
// https://docs.microsoft.com/en-us/cpp/standard-library/iomanip-functions?view=msvc-170
// https://stackoverflow.com/questions/32556114/cin-fail-while-loop-input-re-entry

#include <iostream> // To use cin/cout
#include <iomanip>  // To access setw for output width
#include <string>   // To implement to_string function
using namespace std;

// Global Constant Initialization
const string TITLE = "Forrest's Lumber Factory Order Calculator";
const string AUTHOR_LINE = "By Forrest Moulin";
const double INCH_PER_FOOT = 12.0;
const double INCH_PER_SQ_FOOT = 144.0;
// Price in $ per board foot
const double PINE_RATE = 0.89;
const double FIR_RATE = 1.09;
const double CEDAR_RATE = 2.26;
const double MAPLE_RATE = 4.40;
const double OAK_RATE = 3.10;

// Function prototypes to notify compiler
bool validateType(char type);
double calculateBoardFt(double thickness, double width, double length);
double calculateCost(char type, int quantity, double boardFt);
string getTypeLabel(char type);
// Reference variables used as parameters
void getAllData(char &woodType, int &quantity, double &thickness, 
	double &width, double &length);

int main()
{
	// Dynamic Variable Initialization
	char woodType, keepLooping;
	int quantity, transactionCount = 0, orderCount = 1;
	double thickness, width, length, boardFt, cost, totalCost;
	string woodTypeLabel;

	// Program Logic
	cout << fixed << setprecision(2) << TITLE << endl
		<< AUTHOR_LINE << endl;
	do
	{
		totalCost = 0.0;
		do
		{
			getAllData(woodType, quantity, thickness, width, length);
			if (woodType != 't' && woodType != 'T')
			{
				// Call functions for calculations
				boardFt = calculateBoardFt(thickness, width, length);
				cost = calculateCost(woodType, quantity, boardFt);

				// Track transaction # as OrderNumber.TransactionNumber
				transactionCount++;
				cout << "Transaction # " << orderCount << "." 
					<< transactionCount << endl;

				// Print transaction details to console
				woodTypeLabel = getTypeLabel(woodType) + " cost: $";
				cout << quantity << " units of " << thickness
					<< "in X " << width << "ft X " << length
					<< "ft " << endl << woodTypeLabel 
					<< cost << endl;

				// Track total order cost for multiple transactions
				totalCost += cost;
			}
		} while (woodType != 't' && woodType != 'T');

		// Reset transaction count for each order
		transactionCount = 0;
		// Print order #/cost
		cout << endl << "Order #" << orderCount
			<< " total cost: $" << totalCost << endl 
			<< "Would you like to make another order?" 
			<< endl << endl;
		orderCount++;

		// Read user input char
		cin >> keepLooping;
		// Avoid infinite loop
		cin.ignore(1000, '\n');

		if (keepLooping == 'n' || keepLooping == 'N')
		{
			cout << endl << "Thank you for shopping with us!"
				<< endl << "Until next time :)"
				<< endl;
			break;
		}
	} while (keepLooping == 'y' || keepLooping == 'Y');

}
bool validateType(char type)
{
	// True if correct letter is lowercase/uppercase
	if (type == 'p' || type == 'f' || type == 'c'
		|| type == 'm' || type == 'o')
	{
		return true;
	}
	else if (type == toupper('p') 
		|| type == toupper('f') || type == toupper('c')
		|| type == toupper('m') || type == toupper('o'))
	{
		return true;
	}
	else
	{
		return false;
	}
}
double calculateBoardFt(double thickness, double width, double length)
{
	return thickness * width * length;
}
double calculateCost(char type, int quantity, double boardFt)
{
	double calcProduct = quantity * boardFt;

	switch (type)
	{
	case 'c':
		return CEDAR_RATE * calcProduct;
	case 'f':
		return FIR_RATE * calcProduct;
	case 'm':
		return MAPLE_RATE * calcProduct;
	case 'o':
		return OAK_RATE * calcProduct;
	case 'p':
		return PINE_RATE * calcProduct;
	default:
		return 0.0;
	}
}
string getTypeLabel(char type)
{
	switch (type) {
	case 'c':
		return "Cedar";
	case 'f':
		return "Fir";
	case 'm':
		return "Maple";
	case 'o':
		return "Oak";
	case 'p':
		return "Pine";
	case 't':
		return "Total";
	default:
		return "Default switch label error";
	}
}
// Changes to arg values update original
// variable values since reference variable
// aliases are used 
void getAllData(char &woodType, int &quantity, 
	double &thickness, double &width, double &length)
{
	bool isValid = false;
	while (isValid == false)
	{
		cout << endl << "Please enter a letter for the wood type" 
			<< endl << "(C: Cedar, F: Fir, M: Maple, O: Oak, P: Pine),"
			<< endl << "or enter T to total the previous transactions."
			<< endl << endl;

		cin >> woodType;

		if (validateType(woodType) == true)
		{
			isValid = true;
			woodType = tolower(woodType);
			cout << getTypeLabel(woodType) << " selected" << endl;
			cout << endl << "Please enter the quantity, thickness, width, and length"
				<< endl << "(separated by spaces)." << endl << endl;
			cin >> quantity >> thickness >> width >> length;
			break;
		}
		else
		{
			if (woodType == 't' || woodType == 'T')
			{
				// Exit loop if user enters T for total
				break;
			}
			else
			{
				cout << endl << "Invalid selection type. Try again." << endl;
			}
		}
		// Avoid infinite loop if more than one woodType char is entered
		cin.ignore(1000, '\n');
	}
}
/*
* CONSOLE OUTPUT
* Forrest's Lumber Factory Order Calculator
* By Forrest Moulin
*
* Please enter a letter for the wood type
* (C: Cedar, F: Fir, M: Maple, O: Oak, P: Pine),
* or enter T to total the previous transactions.
*
* ;lkjasdf
*
* Invalid selection type. Try again.
*
* Please enter a letter for the wood type
* (C: Cedar, F: Fir, M: Maple, O: Oak, P: Pine),
* or enter T to total the previous transactions.
*
* c
* Cedar selected
*
* Please enter the quantity, thickness, width, and length
* (separated by spaces).
*
* 10 1 10 10
* Transaction # 1.1
* 10 units of 1.00in X 10.00ft X 10.00ft
* Cedar cost: $2260.00
*
* Please enter a letter for the wood type
* (C: Cedar, F: Fir, M: Maple, O: Oak, P: Pine),
* or enter T to total the previous transactions.
*
* M
* Maple selected
*
* Please enter the quantity, thickness, width, and length
* (separated by spaces).
*
* 5 2 5 5
* Transaction # 1.2
* 5 units of 2.00in X 5.00ft X 5.00ft
* Maple cost: $1100.00
*
* Please enter a letter for the wood type
* (C: Cedar, F: Fir, M: Maple, O: Oak, P: Pine),
* or enter T to total the previous transactions.
*
* p
* Pine selected
*
* Please enter the quantity, thickness, width, and length
* (separated by spaces).
*
* 20 1.5 20 10
* Transaction # 1.3
* 20 units of 1.50in X 20.00ft X 10.00ft
* Pine cost: $5340.00
*
* Please enter a letter for the wood type
* (C: Cedar, F: Fir, M: Maple, O: Oak, P: Pine),
* or enter T to total the previous transactions.
*
* T
*
* Order #1 total cost: $8700.00
* Would you like to make another order?
*
* Y
*
* Please enter a letter for the wood type
* (C: Cedar, F: Fir, M: Maple, O: Oak, P: Pine),
* or enter T to total the previous transactions.
*
* o
* Oak selected
*
* Please enter the quantity, thickness, width, and length
* (separated by spaces).
*
* 5 1 5 5
* Transaction # 2.1
* 5 units of 1.00in X 5.00ft X 5.00ft
* Oak cost: $387.50
*
* Please enter a letter for the wood type
* (C: Cedar, F: Fir, M: Maple, O: Oak, P: Pine),
* or enter T to total the previous transactions.
*
* t
*
* Order #2 total cost: $387.50
* Would you like to make another order?
*
* n
*
* Thank you for shopping with us!
* Until next time :)
*/
