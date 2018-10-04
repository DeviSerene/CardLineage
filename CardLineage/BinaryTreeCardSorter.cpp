#include "BinaryTreeCardSorter.h"



BinaryTreeCardSorter::BinaryTreeCardSorter()
{
}


BinaryTreeCardSorter::~BinaryTreeCardSorter()
{
}

BSTNode* BinaryTreeCardSorter::CreateNewNode(std::shared_ptr<CardHolder> _data, BSTNode* _parent)
{
	BSTNode* Node = new BSTNode();
	Node->data = _data;
	Node->left = NULL;
	Node->right = NULL;
	if (_parent == NULL)
		Node->parent = NULL;
	else
		Node->parent = _parent;
	return Node;
}

BSTNode* BinaryTreeCardSorter::Insert(BSTNode* root, std::shared_ptr<CardHolder> _data, BSTNode* _parent)
{
	if (root == NULL)
	{
		return root = CreateNewNode(_data, _parent);
	}
	else if (root->data->GetCol() < _data->GetCol() || (root->data->GetCol() == _data->GetCol() && root->data->GetName().compare(_data->GetName()) <= 0))
	{
		root->right = Insert(root->right, _data, root);
	}
	else
	{
		root->left = Insert(root->left, _data, root);
	}
	return root;
}

void BinaryTreeCardSorter::Sort(BSTNode* root)
{
	//this needs to go down the tree, collect the data going upwards, and clean itself up, ready for deletion

	//does this node have a left side?
	if (root->left != NULL)
	{
		//we need to go down this route
		Sort(root->left);
		return;
	}
	else
	{
		//we need to add this node's data to the vector
		m_returnData.push_back(root->data);
	}

	//does this node have a right side?
	if (root->right != NULL)
	{
		//yes? make its parent link to its right then delete it
		//if it doesnt have a parent, then we remove the parent from its right side, and go down that side
		if (root->parent != NULL)
		{
			root->parent->left = root->right;
			root->right->parent = root->parent;
			Sort(root->parent->left);
			delete root;
			return;
		}
		else
		{
			root->right->parent = NULL;
			Sort(root->right);
			delete root;
			return;
		}
	}
	else
	{
		//no? delete it and return to the parent
		if (root->parent != NULL)
		{
			root->parent->left = NULL;
			Sort(root->parent);
			delete root;
			return;
		}
		else
		{
			//this means we are at the end
			return;
		}
	}

}