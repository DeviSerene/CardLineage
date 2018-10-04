#pragma once
#include "CardHolder.h"
#include <string>
#include <memory>

struct BSTNode 
{
	std::shared_ptr<CardHolder> data;
	BSTNode* left;
	BSTNode* right;
	BSTNode* parent;
};

class BinaryTreeCardSorter
{
public:
	BinaryTreeCardSorter();
	~BinaryTreeCardSorter();
	BSTNode* Insert(BSTNode* root, std::shared_ptr<CardHolder> _data, BSTNode* _parent);
	BSTNode* CreateNewNode(std::shared_ptr<CardHolder> _data, BSTNode* _parent = NULL);
	void Sort(BSTNode* root);
	std::vector <std::shared_ptr<CardHolder>> GetData() { return m_returnData; }
private:
	std::vector <std::shared_ptr<CardHolder>> m_returnData;
};

