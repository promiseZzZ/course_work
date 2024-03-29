#include<iostream>
#include<stack>
using namespace std;

template<typename E>class BinNode
{
public:
	virtual void setElement(const E&) = 0;
	virtual void setLeft(BinNode*) = 0;
	virtual void setRight(BinNode*) = 0;
};
template<typename Key, typename E>class BSTNode :public BinNode<E>
{
public:
	BSTNode()
	{
		lc = rc = NULL;
	}
	BSTNode(Key K, E e, BSTNode* l = NULL, BSTNode* r = NULL)
	{
		k = K;
		it = e;
		lc = l;
		rc = r;
	}
	~BSTNode()
	{
	}
	E& element()
	{
		return it;
	}
	void setElement(const E& e)
	{
		it = e;
	}
	Key& key()
	{
		return k;
	}
	void setKey(const Key& K)
	{
		k = K;
	}
	inline BSTNode* left()
	{
		return lc;
	}
	inline BSTNode* right()
	{
		return rc;
	}
	void setLeft(BinNode<E>* b)
	{
		lc = (BSTNode*)b;
	}
	void setRight(BinNode<E>* b)
	{
		rc = (BSTNode*)b;
	}
private:
	Key k;
	E it;
	BSTNode* lc;
	BSTNode* rc;

};
template<typename Key, typename E> class Dictionary
{
public:
	virtual void clear() = 0;
	virtual void insert(const Key& k, const E& e) = 0;
	virtual E remove(const Key& k) = 0;
	virtual E removeAny(const Key& k) = 0;
	virtual E find(const Key& k) const = 0;
	virtual int size() = 0;
};
template<typename Key, typename E> class BST : public Dictionary<Key,E>
{
private:
	BSTNode<Key, E>* root;
	int nodecount;

	void clearhelp(BSTNode<Key, E>* root)
	{
		if (root==NULL)
		{
			return;
		}
		clearhelp(root->left());
		clearhelp(root->right());
		delete root;
	}
	BSTNode<Key, E>* inserthelp(BSTNode<Key, E>* root, const Key& k, const E& it)
	{
		if (root==NULL)
		{
			return new BSTNode<Key, E>(k, it, NULL, NULL);
		}
		if (k < root->key())
		{
			root->setLeft(inserthelp(root->left(), k, it));
		}
		else 
		{
			root->setRight(inserthelp(root->right(), k, it));
		}
		return root;
	}
	BSTNode<Key, E>* deletemin(BSTNode<Key, E>* root)
	{
		if (root->left()==NULL)
		{
			return root->right();
		}
		else
		{
			root->setLeft(deletemin(root->right()));
			return root;
		}
	}
	BSTNode<Key, E>* getmin(BSTNode<Key, E>* root)
	{
		if (root->left()==NULL)
		{
			return root;
		}
		else
		{
			return getmin(root->left());
		}
	}
	BSTNode<Key, E>* removehelp(BSTNode<Key, E>* root, const Key& k)
	{
		if (root==NULL)
		{
			return NULL;
		}
		else if (k < root->key())
		{
			root->setLeft(removehelp(root->left(), k));
		}
		else if (k > root->key())
		{
			root->setRight(removehelp(root->right(), k));
		}
		else
		{
			BSTNode<Key, E>* temp = root;
			if (root->left()==NULL)
			{
				root = root->right();
				delete temp;
			}
			else if (root->right()==NULL)
			{
				root = root->left();
				delete temp;
			}
			else
			{
				BSTNode<Key, E>* temp = getmin(root->right());
				root->setElement(temp->element());
				root->setKey(temp->key());
				root->setRight(deletemin(root->right()));
				delete temp;
			}
		}
		return root;
	}
	E findhelp(BSTNode<Key, E>* root, const Key& k) const
	{
		if (root == NULL)
		{
			return NULL;
		}
		if (k < root->key())
		{
			return findhelp(root->left(), k);
		}
		else if (k > root->key())
		{
			return findhelp(root->right(), k);
		}
		else
		{
			return root->element();
		}
	}
	void printhelp(BSTNode<Key, E>* root, int level) const
	{
		if (root==NULL)
		{
			return;
		}
		printhelp(root->left(), level + 1);
		for (int i = 0; i < level; i++)
		{
			cout << " ";
		}
		cout << root->key() << "\n";
		printhelp(root->right(), level + 1);
	}
	void printvalues(BSTNode<Key, E>* root) const
	{
		if (root == NULL)
		{
			return;
		}
		printvalues(root->left());
		cout << root->key() << " ";
		printvalues(root->right());
	}
public:
	BST()
	{
		root = NULL;
		nodecount = 0;
	}
	~BST()
	{
		clearhelp(root);
	}
	void clear()
	{
		clearhelp(root);
		root = NULL;
		nodecount = 0;
	}
	void insert(const Key& k, const E& e)
	{
		root = inserthelp(root, k, e);
		nodecount++;
	}
	E remove(const Key& k)
	{
		E temp = findhelp(root,k);
		if (temp != NULL)
		{
			root = removehelp(root, k);
			nodecount--;
		}
		return temp;
	}
	E removeAny(const Key& k)
	{
		if (root!=NULL)
		{
			E temp = root->element();
			root = removehelp(root, root->key());
			nodecount--;
			return temp;
		}
		else
		{
			return NULL;
		}
	}
	E find(const Key& k) const
	{
		return findhelp(root, k);
	}
	int size()
	{
		return nodecount;
	}
	void print1() const
	{
		if (root==NULL)
		{
			cout << "The BST is empty" << endl;
		}
		else
		{
			printhelp(root, 0);
		}
	}
	void print2() const
	{
		if (root == NULL)
		{
			cout << "The BST is empty" << endl;
		}
		else
		{
			printvalues(root);
		}
	}
	int smallcount(BSTNode<Key, E>* root, const Key& k)
	{
		if (root == NULL)
		{
			return 0;
		}
		else if (k >= root->key())
		{
			return(1 + smallcount(root->left(), k) + smallcount(root->right(), k));
		}
		else
		{
			return smallcount(root->left(), k);
		}
	}
	BSTNode<Key,E>* getRoot()
	{
		return root;
	}
};

int main()
{
	BST<int, int> BST1;
	int data1[9] =
	{ 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	int data2[9] =
	{ 37,24,42,7,2,40,42,32,120};
	for (int i = 0; i < 9; i++)
	{
		BST1.insert(data2[i],data1[i]);
	}
	cout << BST1.smallcount(BST1.getRoot(), 42) << endl;
	BST1.print2();
}
