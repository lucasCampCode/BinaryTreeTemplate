#include "BinaryTree.h"
#include "TreeNode.h"
#include "raylib.h"

BinaryTree::~BinaryTree()
{
	//while tree is not empty
	while (!isEmpty())
		//remove root
		remove(m_root->getData());
}
void BinaryTree::insert(int value)
{
	TreeNode* newNode = new TreeNode(value);
	//If the tree is empty, set the root to be a new node with the given value.
	if (isEmpty()) {
		m_root = newNode;
	}
	//Create a TreeNode pointer that will act as an iterator pointing to the current node and set it to the root.
	TreeNode* current = m_root;
	TreeNode* parent = current;
	//Create a TreeNode pointer that will act as an iterator pointing to the parent 
	//of the current node and set it to the root.

	//Loop until the the current node iterator reaches a nullptr.
	while (current != nullptr) {
		//Check if the value we want to add to the tree is less than the value at the current node.
			//Set the parent node to be the current node before the current node moves positions.
			//Change the current node to be the child to its left and continue.
		if (value < current->getData()) {
			parent = current;
			current = current->getLeft();
		}
		//Check if the value we want to add to the tree is greater than the value at the current node.
			//Set the parent node to be the current node before the current node moves positions.
			//Change the current node to be the child to its right and continue.
		else if (value > current->getData()) {
			parent = current;
			current = current->getRight();
		}
		//If the value is the same as a value already in the list return 
		else if (value == current->getData()) {
			return;
		}
	}
	//end loop

	//If the value we want to add is less than the value of the parent node, insert the value to the left.
	if(value < parent->getData())
		parent->setLeft(newNode);
	else if(value > parent->getData())//Otherwise, insert the value to the right.
		parent->setRight(newNode);
}

void BinaryTree::remove(int value)
{
	//Create two TreeNode pointers: one to hold a reference to the node we want to remove
	//and another to hold a reference to its parent.
	TreeNode* current;
	TreeNode* parent;
	//Try to find the node that matches the value given and its parent in the tree.
	//If the node cannot be found return.
	if (!findNode(value, current, parent))
		return;

	//Check to see if the node has a right
	if (current->hasRight())
	{
		//Initialize two iterators to find the node whose data will be copied and its parent.
		TreeNode* minNode = current;

		//Set the first iterator to point to the right child of the node we want to remove.
		TreeNode* minNodeP = minNode;
		minNode = minNode->getRight();

		//Loop while the first iterator has a value to its left
		while (minNode->hasLeft()) 
		{
			//Set the second iterator to be the value of the first iterator.
			minNodeP = minNode;
			//Set the first iterator to be the value to the left of it
			minNode = minNode->getLeft();
		//end loop
		}

		//Once the smallest value has been found, copy the data in first iterator to the node we want to remove.
		current->setData(minNode->getData());

		//Check if the second iterator has a left child.
		if (minNodeP->hasLeft())
			//Check if the left child stores the same data as the node we wanted to remove.
			if (minNodeP->getLeft() == minNode)
				//Set the second iterators left child to be the first iterators right child.
				minNodeP->setLeft(minNode->getRight());
		
		//Check if the second iterator has a right child.
		if (minNodeP->hasRight())
			//Check if the right child contains the same data as the node we want to remove.
			if (minNodeP->getRight() == minNode)
				//Set the right child of the second iterator to be the right child of the first iterator.
				minNodeP->setRight(minNode->getRight());

		//Delete the first iterator
			minNode = nullptr;
	}
	//Otherwise, if the node doesn't have a right child
	else 
	{
		//check if the parent of the node to remove has a left child.
		if (parent->hasLeft())
			//Check if the data that the left child holds is the same as the data the node to remove holds.
			if (parent->getLeft()->getData() == value)
				//Set the left child of the parent node to be the left child of the node to remove.
				parent->setLeft(current->getLeft());

		//Check if the parent of the node to remove has a right child.
		if (parent->hasRight())
			//Check if the data the right child holds is the same as the data the node to remove holds.
			if (parent->getRight()->getData() == value)
				//Set the right child of the parent node to be the left child of the node to remove.
				parent->setRight(current->getLeft());

		//Check if the node we want to remove is the root.
		if (current == m_root)
			//Set the root to be its left child.
			m_root = m_root->getLeft();

		//Delete the pointer that points to the node to remove.
		delete current;
	}
}

TreeNode* BinaryTree::find(int value)
{
	//Initialize an iterator starting at the root.
	TreeNode* current = m_root;
	//Loop through the tree while the iterator isn't nullptr.
	while (current)
	{
		//Check if the node has the data we want
		if (current->getData() == value)
			return current;
		//Return the iterator
	//If the node doesn't have the data we want, check to see if it's higher in value.
		else if (current->getData() < value)
			current = current->getRight();
		//Set the iterator to be its current right child.
	//If the node doesn't have the data we want, check to see if it's lower in value.
		else if (current->getData() > value)
			current = current->getLeft();
		//Set the iterator to be its current left child.
//end loop
	}
	return nullptr;
	//Return nullptr
}

void BinaryTree::draw(TreeNode* selected)
{
	//draws the tree
	draw(m_root, 400, 40, 400, selected);
}
bool BinaryTree::findNode(int searchValue, TreeNode*& nodeFound, TreeNode*& nodeParent)
{
	TreeNode* current = m_root;
	TreeNode* parent = current;
	//Create two iterators: one that will point to the current node to compare the search value to,
	//and the other to hold a reference to the parent.

	//Loop while the current node iterator isn't nullptr/
	while (current != nullptr)
	{
		//Check if the search value is the same as the current nodes data.
			//Set the node found argument to be the current node and the parent node to be the parent node iterator.
			//Return true.
		if (current->getData() == searchValue)
		{
			nodeFound = current;
			nodeParent = parent;
			return true;
		}
		//Check if the search value is greater than the value at the current node.
			//Set the parent node to be the current node.
			//Set the current node to be the child to the right of the current node.
		else if (searchValue > current->getData())
		{
			parent = current;
			current = current->getRight();
		}
		//Check if the search value is less than the value at the current node.
			//Set the parent node to be the current node.
			//Set the current node to be its left child.
		else if (searchValue < current->getData())
		{
			parent = current;
			current = current->getLeft();
		}
	}
	//end loop
	return false;
	//Return false.
}
void BinaryTree::draw(TreeNode* currentNode, int x, int y, int horizontalSpacing, TreeNode* selected)
{
	//decrease spacing by half each time it goes down the tree
	horizontalSpacing /= 2;
	//if the current node has a node
	if (currentNode)
	{
		//Draws a line child if this node has one
		if (currentNode->hasLeft())
		{
			//Draws a line between the left child and the current node
			DrawLine(x, y, x - horizontalSpacing, y + 80, RED);
			//Draws the left child
			draw(currentNode->getLeft(), x - horizontalSpacing, y + 80, horizontalSpacing, selected);
		}
		//draws the right child if this node has one
		if (currentNode->hasRight())
		{
			//Draws a line between the right child and the current node
			DrawLine(x, y, x + horizontalSpacing, y + 80, RED);
			//Draws the right child
			draw(currentNode->getRight(), x + horizontalSpacing, y + 80, horizontalSpacing, selected);
		}
		//draws the current node
		currentNode->draw(x, y, (selected == currentNode));
	}
}
