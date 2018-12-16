// Project2.cpp 
//Jacob Silva, Matt Hanley, and Jacob Leuquire
//


#include "stdafx.h"
#include "Project2.h"
#include <iostream>
using std::cout;
#include <vector>
using std::vector;


int main()
{
	string input, par, id, event;
	vector<struct node> tree;
	while (input != "quit")
	{
		cout << endl << "Tracking Tree" << endl << "----------------------------------" << endl;
		cout << "Instructions: \nnew	(create node) \ndisplay	(preorder traversal)";
		cout << " \nsearch	(finds/prints node data) \nupdate	(update contents of specific node)";
		cout << " \nquit	(closes application) " << endl;
		cout << "----------------------------------" << endl;


		cout << "Input:  ";
		cin >> input;
		if (input == "new")
		{
			cout << "Enter your raw event: ";
			cin.ignore();
			getline(cin, event);
			insert(tree, event);
			//cout << endl << "Node successfully added" << endl;

		}
		if (input == "display")
		{
			PreTrav(tree, 0);
			cout << endl;
		}
		if (input == "search")
		{
			cout << "Enter search ID: ";
			cin >> id;
			display(tree, id);

		}
		if (input == "update")
		{
			cout << "Enter update ID:  ";
			cin >> id;
			cout << endl << "Enter new event: ";
			cin.ignore();
			getline(cin, event);
			update(tree, id, event);
			//cout << endl << "Record Updated" << endl;

		}
		else
		{
			//cout << endl << "Invalid command" << endl;
		}
	}
	return 0;

}
