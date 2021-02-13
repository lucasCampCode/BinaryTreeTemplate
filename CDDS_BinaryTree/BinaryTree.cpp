#include "BinaryTree.h"
#include "TreeNode.h"
#include "raylib.h"

BinaryTree::~BinaryTree()
{
}

void BinaryTree::insert(int value)
{
	//If the tree is empty, set the root to be a new node with the given value.
	if (isEmpty())
		m_root = new TreeNode(value);
	//Create a TreeNode pointer that will act as an iterator pointing to the current node and set it to the root.
	TreeNode* iter1 = m_root;
	TreeNode* iter2 = m_root;
	//Create a TreeNode pointer that will act as an iterator pointing to the parent 
	//of the current node and set it to the root.

	//Loop until the the current node iterator reaches a nullptr.
	while (iter1 != nullptr) {
		//Check if the value we want to add to the tree is less than the value at the current node.
			//Set the parent node to be the current node before the current node moves positions.
			//Change the current node to be the child to its left and continue.
		if (value < iter1->getData()) {
			iter2 = iter1;
			iter1 = iter1->getLeft();
		}
		//Check if the value we want to add to the tree is greater than the value at the current node.
			//Set the parent node to be the current node before the current node moves positions.
			//Change the current node to be the child to its right and continue.
		if (value > iter1->getData()) {
			iter2 = iter1;
			iter1 = iter1->getRight();
		}
		//If the value is the same as a value already in the list return 
		if (value == iter1->getData()) {
			return;
		}
	}
	//end loop
	if (value > iter2->getData())
		iter2->setRight(new TreeNode(value));
	else
		iter2->setLeft(new TreeNode(value));
	//If the value we want to add is less than the value of the parent node, insert the value to the left.
	//Otherwise, insert the value to the right.
}

void BinaryTree::remove(int value)
{
	//Create two TreeNode pointers: one to hold a reference to the node we want to remove
	//and another to hold a reference to its parent.
	TreeNode* selected;
	TreeNode* selectedParent;
	//Try to find the node that matches the value given and its parent in the tree.
	//If the node cannot be found return.
	if (!findNode(value, selected, selectedParent))
		return;

	//Check to see if the node has a right
	if (selected->hasRight()) 
	{
		//Initialize two iterators to find the node whose data will be copied and its parent.
		TreeNode* iter1 = selected->getRight();
		TreeNode* iter2;
		//Set the first iterator to point to the right child of the node we want to remove.

		//Loop while the first iterator has a value to its left
		while (iter1->hasLeft())
		{
			//Set the second iterator to be the value of the first iterator.
			//Set the first iterator to be the value to the left of it
			iter2 = iter1;
			iter1 = iter1->getLeft();
		//end loop
		}
		//Once the smallest value has been found, copy the data in first iterator to the node we want to remove.
		selected->setData(iter1->getData());
		//Check if the second iterator has a left child.
			//Check if the left child stores the same data as the node we wanted to remove.
				//Set the second iterators left child to be the first iterators right child.
		if (iter2->hasLeft())
			if (iter2->getLeft()->getData() == value)
				iter2->setLeft(iter1->getRight());
		//Check if the second iterator has a right child.
			//Check if the right child contains the same data as the node we want to remove.
				//Set the right child of the second iterator to be the right child of the first iterator.
		if (iter2->hasRight())
			if (iter2->getRight()->getData() == value)
				iter2->setRight(iter1);
		//Delete the first iterator
		delete iter1;
	}
	//Otherwise, if the node doesn't have a right child
	else {
		//check if the parent of the node to remove has a left child.
			//Check if the data that the left child holds is the same as the data the node to remove holds.
				//Set the left child of the parent node to be the left child of the node to remove.
		if (selectedParent->hasLeft())
			if (selectedParent->getLeft()->getData() == value)
				selectedParent->setLeft(selected->getLeft());
		//Check if the parent of the node to remove has a right child.
			//Check if the data the right child holds is the same as the data the node to remove holds.
				//Set the right child of the parent node to be the left child of the node to remove.
		if (selectedParent->hasRight())
			if (selectedParent->getRight()->getData() == value)
				selectedParent->setRight(selected->getLeft());
		//Check if the node we want to remove is the root.
			//Set the root to be its left child.
		if (m_root->getData() == value)
			m_root = m_root->getLeft();
		//Delete the pointer that points to the node to remove.
		delete selected;
	}
}

TreeNode* BinaryTree::find(int value)
{
	//Initialize an iterator starting at the root.
	TreeNode* iter = m_root;
	//Loop through the tree while the iterator isn't nullptr.
	while (iter != nullptr)
	{
		//Check if the node has the data we want
		if (iter->getData() == value)
			return iter;
		//Return the iterator
	//If the node doesn't have the data we want, check to see if it's higher in value.
		if (iter->getData() > value)
			iter = iter->getRight();
		//Set the iterator to be its current right child.
	//If the node doesn't have the data we want, check to see if it's lower in value.
		if (iter->getData() < value)
			iter = iter->getLeft();
		//Set the iterator to be its current left child.
//end loop
	}
	return nullptr;
	//Return nullptr
}

void BinaryTree::draw(TreeNode* selected)
{
}

bool BinaryTree::findNode(int searchValue, TreeNode*& nodeFound, TreeNode*& nodeParent)
{
	TreeNode* iter1 = m_root;
	TreeNode* iter2 = nodeParent;
	//Create two iterators: one that will point to the current node to compare the search value to,
	//and the other to hold a reference to the parent.

	//Loop while the current node iterator isn't nullptr/
	while (iter1 != nullptr)
	{
		//Check if the search value is the same as the current nodes data.
			//Set the node found argument to be the current node and the parent node to be the parent node iterator.
			//Return true.
		if (iter1->getData() == searchValue)
		{
			nodeFound = iter1;
			nodeParent = iter2;
			return true;
		}
		//Check if the search value is greater than the value at the current node.
			//Set the parent node to be the current node.
			//Set the current node to be the child to the right of the current node.
		if (iter1->getData() > searchValue)
		{
			iter2 = iter1;
			iter1 = iter1->getRight();
		}
		//Check if the search value is less than the value at the current node.
			//Set the parent node to be the current node.
			//Set the current node to be its left child.
		if (iter1->getData() < searchValue)
		{
			iter2 = iter1;
			iter1 = iter1->getLeft();
		}
	}
	//end loop
	return false;
	//Return false.
}

void BinaryTree::draw(TreeNode* currentNode, int x, int y, int horizontalSpacing, TreeNode* selected)
{

}
