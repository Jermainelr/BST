//Program Created by Jermaine Lara
// 3/28/18
// Program to create a BST from a file or user input, 
// and can insert remove and print the BST on user command
// Based on the algorithm from the book: Data Structures and Analysis in Java By: Clifford A. Shaffer
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct Node {
	int value;
	Node* left;
	Node* right;
};

Node* readFile(); 
Node* readInput(); 
Node* insert(Node* root,int value);
Node* remove(Node* root,int value);
void printFullTree(Node* root);
Node* getMinimum(Node* root);
Node* deleteMinimum(Node* root);

int main () {
	Node* root = NULL;
	cout << "Enter option:" << endl;
	cout << "1 to specify a file name" << endl;
	cout << "2 to enter numbers manually" << endl;
	int choice;
	cin >> choice;
	if (choice == 1) {
		root = readFile();
    }
    else if (choice == 2) {
		root = readInput();
	}
	else {
		cout << "Invalid option " << endl;
	}
	do {
		cout << "Enter option:" << endl;
		cout << "1 to print tree" << endl;
		cout << "2 to insert a value into the tree" << endl;
		cout << "3 to remove a value from the tree" << endl;
		cout << "4 to exit" << endl;
		cin >> choice;
		if (choice == 1) {
			printFullTree(root);
		}
		
		else if (choice == 2) {
		    cout << "Enter value to insert" << endl;
			int value;
			cin >> value;
			root = insert(root, value);
		}
		
		else if (choice == 3) {
			cout << "Enter value to remove" << endl;
			int value;
			cin >> value;
			root = remove(root, value);
		}
		
		else if (choice != 4) {
			cout << "Invalid option " << endl;
		}
	}
	while(choice != 4);
	
}

// Read the numbers from a file and build BST
Node* readFile() {
	char fileName[81];
    cout << "Enter file name: " << endl;
	cin >> fileName;
    int number;
	Node* root = NULL;
    ifstream file(fileName);
    if (file.is_open()) {
		while (file >> number)
		{
			if (number < 1 || number > 1000) {
				cout << number << " is out of range: number must be between 1 and 1000" << endl;
				break;
			}
			root = insert(root, number);
		}
		file.close();
    }
    else {
		cout << "Unable to open file"; 
    }
	return root;
}


// Insert a value into the BST at the correct position
Node* insert(Node* root,int value) {
	if (root == NULL) {
		Node* node = new Node;
		node->value = value;
		node->left = NULL;
		node->right = NULL;
		return node;
	}
    if (value < root->value) {
		root->left = insert(root->left, value);
	}
	else {
		root->right = insert(root->right, value);
	}
	return root;
}

// Prints the description of the BST			
void printFullTree(Node* root) {
	if(root != NULL) {
		cout << "Parent: " << root->value;
		if (root->left != NULL) {
			cout << ", Left Child: " << root->left->value;
		}
		if (root->right != NULL) {
			cout << ", Right Child: " << root->right->value;
		}
		cout << endl;
		printFullTree(root->left);
		printFullTree(root->right);
	}
	
}

// Reads the numbers from the user input and insert into BST
Node* readInput() {
	cout << "Enter space separated numbers" << endl;
	string input;
	cin.ignore();
	getline(cin, input);
	istringstream is(input);
	int number;
	Node* root = NULL;
	while (is >> number)
	{
		if (number < 1 || number > 1000) {
			cout << number << " is out of range: number must be between 1 and 1000" << endl;
			break;
		}
		root = insert(root, number);
	}
	return root;
}

//Removes a value from the BST and updates correctly
Node* remove(Node* root,int value) {
	if (root == NULL) {
		return NULL;
	}
	if (value < root->value) {
		root->left = remove(root->left, value);
	}
	else if (value > root->value) {
		root->right = remove(root->right, value);
	}
	else {
		if (root->left == NULL) {
			return root->right;
		}
		else if (root->right == NULL) {
			return root->left;
		}
		else {
			Node* temp = getMinimum(root->right);
			root->value = temp->value;
			root->right = deleteMinimum(root->right);
		}
	}
	return root;
}

//Recursively finds the minimum value in a subtree
Node* getMinimum(Node* root) {
	if (root->left == NULL) {
		return root;
	}
	return getMinimum(root->left);
}

//Recursively searches left until there is no node left
//and changes the parent pointer to the pointer of right child
Node* deleteMinimum(Node* root) {
	if (root->left == NULL) {
		return root->right;
	}
	root->left = deleteMinimum(root->left);
	return root;
}