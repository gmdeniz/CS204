#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// Mirac Deniz Gozen

struct node {
	/// struct for the node structure
	int value;
	node* next;

	node()
	{}

	node(const int& s, node* link) // constructs node with value "s" pointing to node "link"
	{
		value = s;
		next = link;
	}
};

void DeleteNodesOf(node* head) {
	/// Summary: Deletes the nodes of a linked list given the head pointer

	node* pointer;
	while (head != NULL) {
		pointer = head;
		head = head->next;
		delete pointer;
	}
}

/* Begin: code taken from ptrfunc.cpp and updated*/
void DisplayList(node* head) {
	/// Summary: prints the values of a linked list given the head pointer

	node* ptr = head;
	while (ptr != NULL) {
		cout << ptr->value << " ";
		ptr = ptr->next;
	}
	cout << endl;
}
/* End: code taken from ptrfunc.cpp and updated*/


bool hasDigits(string str) {
	/// Summary: checks if the input string has any numbers in it
	/// Returns: true if there are any numbers in the string "str", else false

	for (int i = 0; i < str.length(); i++) {
		if (isdigit(str[i])) {
			return true;
		}
	}
	return false;
}

int main() {
	string mode, line, numbers;
	bool awaitCorrectInput = false;

	cout << "Please enter the order mode (A/D): "; // asks for order mode (A or D)

	getline(cin, line); 
	istringstream input(line);
	input >> mode; // first word of the input is read as mode input

	if (mode != "A" && mode != "D") awaitCorrectInput = true; // if the input for order mode is not A or D, bool is set to true

	while (awaitCorrectInput) { // keeps asking for user to enter either "A" or "D" as input if the controller bool is true - (see above comment)

		if (mode != "A" && mode != "D") {

			cout << "Please enter the order mode again (A/D): ";
			getline(cin, line);
			istringstream input(line);
			input >> mode;
		}

		else awaitCorrectInput = false;
	}

	cout << "Please enter the numbers in a line: "; // asks for numbers to be inputted in a line
	getline(cin, numbers);
	cout << endl;

	if (numbers == "" || !hasDigits(numbers)) {     // ends the program if no numbers are entered
		cout << "The list is empty at the end of the program and nothing is deleted" << endl;
		return 0;
	}

	istringstream numsInput(numbers);
	int currentNum;   // variable to be used for number inputs

	node* head; // head pointer for main list
	node* temp; // temporary pointer, used to link or unlink nodes
	node* n;    // points to created node in the current iteration (value set to current number, next is NULL)
	node* del;  // head pointer for the list of deleted nodes

	numsInput >> currentNum; // first number is read and immediately appended to the list (as no condition check is needed)
	cout << "Next number: " << currentNum << endl;
	cout << "Deleted nodes: None" << endl;
	cout << "Appended: " << currentNum << endl;
	cout << "List content: " << currentNum << endl << endl;

	n = new node(currentNum, NULL); // pointer "n" points to a newly created node with value "currentNum" and next adress as NULL"
	temp = n;                 // temporary pointer points to the node created above
	head = n;                 // head pointer points to the node created above

	while (numsInput >> currentNum) {

		bool exists = false;       // bool to be used for values that already exist in the list
		bool deleted = false;      // bool to state if any nodes were deleted in the current iteration

		n = new node(currentNum, NULL);  // pointer "n" points to a newly created node with value "currentNum" and next adress as "NULL"
		del = NULL;                      // head pointer of deleted nodes list is set to NULL

		cout << "Next number: " << currentNum << endl; // number in the current iteration is printed
		temp = head;                                   // temporary node now points to head node

		if (mode == "A") {          // checks if order mode is "ascending"
			while (temp != NULL) {  // iterates over the linked list
				if (temp->value == n->value) { // checks if the value in the current node in the list is equal to the "currentNum" in the current iteration
					cout << currentNum << " is already in the list!" << endl;
					exists = true;
					break;
				}
				else if (temp->value < n->value && temp->next == NULL) { // checks if the value of current node in the list is less than the "currentNum" in the current iteration
					temp->next = n;
					break;
				}
				else if (temp->value < n->value && temp->next->value > n->value) { // checks if the current node value is less than "currentNum" AND value of next nodes is more than "currentNum"
					del = temp->next; // deleted nodes pointer now points to the node after the current node
					temp->next = n;   // list is unlinked from the later nodes and current node is linked to the node with value "currentNum" and next adress "NULL"
					deleted = true; 
					break;
				}
				else if (temp->value > n->value) { // checks if the current node value is more than "currentNum"
					del = temp; // deleted nodes pointer now points to the node after the current node
					temp = n;   // list is unlinked from the current and later nodes and current node is replaced by node with value "currentNum" and next adress "NULL"
					head = temp;
					deleted = true;
					break;
				}
				temp = temp->next; // moves to the next element of the list
			}
		}

		else if (mode == "D") {  // Same functionality as the above if statement with mode == "A" ( "<" and ">"s in the if statements are reversed)
			while (temp != NULL) {
				if (temp->value == n->value) {
					cout << currentNum << " is already in the list!" << endl;
					exists = true;
					break;
				}
				else if (temp->value > n->value && temp->next == NULL) {
					temp->next = n;
					break;
				}
				else if (temp->value > n->value && temp->next->value < n->value) {
					del = temp->next;
					temp->next = n;
					deleted = true;
					break;
				}
				else if (temp->value < n->value) {
					del = temp;
					temp = n;
					head = temp;
					deleted = true;
					break;
				}
				temp = temp->next;
			}
		}

		if (deleted && !exists) { // prints deleted nodes and appended number if any nodes are deleted and if "currentNum" does not already exist in the list
			cout << "Deleted Nodes: ";
			DisplayList(del);     // displays the list of nodes to be deleted by the next line
			DeleteNodesOf(del);   // deletes the nodes pointed by the "del" pointer
			cout << "Appended: " << currentNum << endl;
		}

		else if (!exists) { // states no nodes were deleted (deleted == false) and prints the appended value if "currentNum" does not already exist in the list
			cout << "Deleted Nodes: None" << endl;
			cout << "Appended: " << currentNum << endl;
		}
		cout << "List content: ";
		DisplayList(head); // displays the list
		cout << endl;
	}
	cout << "All the nodes are deleted at the end of the program: ";
	DisplayList(head);   // displays the list
	DeleteNodesOf(head); // deletes the nodes pointed by the "head" pointer

	return 0;
}