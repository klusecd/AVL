#include <iostream>

using namespace std;

class AVLtree
{
	struct node
	{
		int key;
		int height;
		node* left;
		node* right;
		node(int k)
		{
			key = k;
			height = 1;
		}
	};

	int height(node* p)
	{
		if (p != NULL)
			return p->height;
		else
			return 0;
	}

	int balfact(node* p)
	{
		return height(p->right) - height(p->left);
	}

	void fixheight(node* p)
	{
		if (p->left->height > p->right->height)
			p->height = p->left->height + 1;
		else
			p->right->height + 1;
	}

	node* rotateright(node* p)
	{
		node* q = p->left;
		p->left = q->right;
		q->right = p;
		fixheight(p);
		fixheight(q);
		return q;
	};

	node* rotateleft(node* q)
	{
		node* p = q->right;
		q->right = p->left;
		p->left = q;
		fixheight(q);
		fixheight(p);
		return p;
	};

	node* balance(node* p)
	{
		fixheight(p);
		if (balfact(p) == 2)
		{
			if (balfact(p->right) < 0)
				p->right = rotateright(p->right);
			return rotateleft(p);
		}
		if (balfact(p) == -2)
		{
			if (balfact(p->left) > 0)
				p->left = rotateleft(p->left);
			return rotateright(p);
		}
		return p;
	};

	node* search(node* p, size_t k)
	{
		while (p != NULL)
		{
			if (k < p->key)
				p = p->left;
			else if (k > p->key)
				p = p->right;
			else
				return p;
		}
	};

	node* insert(node* p, size_t k)
	{
		if (p == NULL) return new node(k);
		if (k < p->key)
			p->left = insert(p->left, k);
		else
			p->right = insert(p->right, k);
		return balance(p);
	};

	node* findmin(node* p)
	{
		if (p->left)
			return findmin(p->left);
		else
			return p;
	};

	node* deletemin(node* p)
	{
		if (p->left == 0)
			return p->right;
		p->left = deletemin(p->left);
		return balance(p);
	};

	node* del(node* p, size_t k)
	{
		if (p == NULL) return 0;
		if (k < p->key)
			p->left = del(p->left, k);
		else if (k > p->key)
			p->right = del(p->right, k);
		else
		{
			node* q = p->left;
			node* r = p->right;
			delete p;
			if (!r) return q;
			node* min = findmin(r);
			min->right = deletemin(r);
			min->left = q;
			return balance(min);
		}
		return balance(p);
	};
};
