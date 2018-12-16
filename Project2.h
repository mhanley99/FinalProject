//Project 2.h
//Jacob Silva, Matt Hanley, and Jacob Leuquire
#pragma once
#include <vector>
using std::vector;
#include <string>
using std::string;
using std::to_string;
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include<functional>
using std::hash;

//calculate index of left child v[2*k+1]
//calc ind of rchild v[2*k +2]
//calc ind of root v[(k-1)/2


struct node
{

	string ID;
	string parentID;
	string rEvent;

	int leftInd;
	int rightInd;

	string LHASH;
	string RHASH;

	vector<string>LHIST, RHIST;

};

string hashID(string parent, string rawEvent)
{
	string id = rawEvent + parent;
	hash<string> hash_fn;
	size_t ID = hash_fn(id);
	unsigned int a = ID;
	string b = to_string(a).substr(0, 8);
	return b;

}


void rootNode(vector<struct node> &tree, string rawEvent)
{
	string id = rawEvent + "No Parent";
	string parId = "No Parent";
	std::hash<string> hash_fn;
	size_t ID = hash_fn(id);
	size_t par = hash_fn(parId);
	unsigned int a = ID;
	string b = to_string(a).substr(0, 8);
	a = par;
	string c = to_string(a).substr(0, 8);



	struct node root = { b,c,rawEvent,NULL,NULL };
	tree.push_back(root);
}



void fillNode(vector<struct node> &tree, string rawEvent, int i)
{
	tree[i].rEvent = rawEvent;
	tree[i].ID = hashID(tree[i].parentID, rawEvent);

}

void updateRightHist(vector <struct node> &tree, int index)
{
	string a = tree[index].RHASH;
	string b = a.substr(0, 8);
	tree[index].RHIST.push_back(b);
}

void updateLeftHist(vector <struct node> &tree, int index)
{
	string a = tree[index].LHASH;
	string b = a.substr(0, 8);
	tree[index].LHIST.push_back(b);
}

void updateRightHash(vector <struct node> &tree, int index)
{
	int rchildindex = (2 * index) + 2;
	node r = tree[rchildindex];
	string theID = r.ID;
	string parent = r.parentID;
	string rawE = r.rEvent;
	string left = r.LHASH;
	string right = r.RHASH;
	string a = theID + parent + rawE + right + left;
	hash<string> hash_fn;
	size_t h = hash_fn(a);
	unsigned int z = h;
	string b = to_string(z).substr(0, 8);
	tree[index].RHASH = b;
	int parentIndex = (index - 1) / 2;
	if (parentIndex > 0)
	{
		updateRightHash(tree, parentIndex);
	}
	//updateRightHist(tree, index); //Dunno yet if this was the HASH problem


}

void updateLeftHash(vector <struct node> &tree, int index)
{
	int lchildindex = (2 * index) + 1;
	node m = tree[lchildindex];
	string theID = m.ID;
	string parent = m.parentID;
	string rawE = m.rEvent;
	string left = m.LHASH;
	string right = m.RHASH;
	string a = theID + parent + rawE + right + left;
	hash<string> hash_fn;
	size_t h = hash_fn(a);
	unsigned int z = h;
	string b = to_string(z).substr(0, 8);
	tree[index].LHASH = b;
	int parentIndex = (index - 1) / 2;
	if (parentIndex > 0)
	{
		updateLeftHash(tree, parentIndex);
	}

	//updateLeftHist(tree, index); //Dunno yet if this was the HASH problem
}

void insert(vector<struct node> &tree, string rawEvent)
{

	int size = tree.size();
	if (size == 0)
	{
		rootNode(tree, rawEvent);
	}
	else
	{
		for (int i = 0; i<size; i++)
		{

			if (tree[i].leftInd == NULL && tree[i].rightInd == NULL)
			{
				struct node a = { hashID(tree[i].ID,rawEvent), tree[i].ID, rawEvent, NULL, NULL };
				tree.push_back(a);
				tree[i].leftInd = (2 * i) + 1;
				updateLeftHist(tree, i);
				updateLeftHash(tree, i);

				struct node empty = { "NULL",tree[i].ID,"null",NULL,NULL };
				tree.push_back(empty);
				tree[i].rightInd = (2 * i) + 2;
				break;
			}
			else if (tree[tree[i].leftInd].rEvent != "null"  && tree[tree[i].rightInd].rEvent == "null")
			{
				fillNode(tree, rawEvent, (2 * i + 2));
				updateRightHist(tree, i);
				updateRightHash(tree, i);
				break;
			}
			else if (tree[tree[i].rightInd].rEvent != "null"  && tree[tree[i].leftInd].rEvent == "null")
			{
				fillNode(tree, rawEvent, (2 * i + 1));
				updateLeftHist(tree, i);
				updateLeftHash(tree, i);
				break;
			}

		}
	}
}


void PreTrav(vector <struct node> &tree, int Idx)
{
	
	int a = -2;
	int index = 0;
	int divisor[7] = { 1, 3, 7, 15, 31, 63, 127 };
	while (a != 0)
	{
		a = (Idx / divisor[index]);
		index++;
	}
	if (index != 1)
	{
		for (int c = 0; c < index - 1; c++)
		{
			cout << "| ";
		}
	}
	cout << tree[Idx].ID << endl;
	if (tree[Idx].leftInd != NULL && tree[Idx].rEvent != "null")	//help for this recursive function from:
		PreTrav(tree, tree[Idx].leftInd);			// https://www.codeproject.com/Articles/602805/Creating-a-Binary-Search-Tree-B 
	if (tree[Idx].rightInd != NULL && tree[Idx].rEvent != "null")
		PreTrav(tree, tree[Idx].rightInd);
}

void display(vector<struct node> &tree, string id)
{
	for (int i = 0; i < tree.size(); i++)
	{
		if (tree[i].ID == id)
		{
			cout << "ID: " << tree[i].ID << endl;
			cout << "Parent ID: " << tree[i].parentID << endl;
			cout << "Raw Event: " << tree[i].rEvent << endl;
			cout << "LHASH: " << tree[i].LHASH << endl;
			cout << "RHASH: " << tree[i].RHASH << endl;
			cout << "LHIST:";
			for (int x = 0; x < tree[i].LHIST.size(); x++)
			{
				cout << tree[i].LHIST[x] << " | ";
			}
			cout << endl << "RHIST: ";
			for (int x = 0; x < tree[i].RHIST.size(); x++)
			{
				cout << tree[i].RHIST[x] << " | ";
			}

		}


	}
}

void update(vector <struct node> &tree, string searchID, string newEvent)
{
	int idx = -1;
	for (int index = 0; index < tree.size(); index++)
	{
		if (tree[index].ID == searchID)
		{
			idx = index;
		}
	}
	if (idx == -1)
	{
		cout << "ID not found" << endl;
	}
	else
	{
		int parentidx = (idx - 1) / 2;
		if (idx % 2 == 1)
		{
			updateLeftHist(tree, parentidx);
		}
		else if (idx != 0 && idx % 2 == 0)
		{
			updateRightHist(tree, parentidx);
		}
		tree[idx].rEvent = newEvent;
		tree[idx].ID = hashID(tree[idx].parentID, newEvent);
		if (idx % 2 == 1)
		{
			updateLeftHash(tree, parentidx);
		}
		else if (idx != 0 && idx % 2 == 0)
		{
			updateRightHash(tree, parentidx);
		}
	}
}
