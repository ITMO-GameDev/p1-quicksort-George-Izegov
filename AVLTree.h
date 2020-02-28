#pragma once

template <typename K, typename V>
struct node // структура для представления узлов дерева
{
	K key;
	V value;
	int height;
	node* left;
	node* right;
	node(K k, V v) { key = k; value = v; left = right = 0; height = 1; }
};

template <typename K, typename V>
class AVLTree
{
public:

	AVLTree() { root = 0; }

	node<K, V>* insert(node<K, V>* p, K k, V v);
	node<K, V>* remove(node<K, V>* p, K k);
	node<K, V>* getRoot() { return root; }
	node<K, V>* get( K k);


private:
	node<K, V>* root;

private:

	int height(node<K,V>* p);
	int bfactor(node<K, V>* p);
	void fixheight(node<K, V>* p);
	node<K, V>* rotateright(node<K, V>* p);
	node<K, V>* rotateleft(node<K, V>* p);
	node<K, V>* balance(node<K, V>* p);
	node<K, V>* findmin(node<K, V>* p);
	node<K, V>* removemin(node<K, V>* p);
	

};

template <typename K, typename V>
int AVLTree<K, V>::height(node<K, V>* p)
{
	return p ? p->height : 0;
}

template <typename K, typename V>
int AVLTree<K, V>::bfactor(node<K, V>* p)
{
	return height(p->right) - height(p->left);
}

template <typename K, typename V>
void AVLTree<K, V>::fixheight(node<K, V>* p)
{
	int hl = height(p->left);
	int hr = height(p->right);
	p->height = (hl > hr ? hl : hr) + 1;
}

template <typename K, typename V>
node<K, V>* AVLTree<K, V>::rotateright(node<K, V>* p) // правый поворот вокруг p
{
	node<K, V>* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

template <typename K, typename V>
node<K, V>* AVLTree<K, V>::rotateleft(node<K, V>* q) // левый поворот вокруг q
{
	node<K, V>* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

template <typename K, typename V>
node<K, V>* AVLTree<K, V>::balance(node<K, V>* p) // балансировка узла p
{
	fixheight(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // балансировка не нужна
}

template <typename K, typename V>
node<K, V>* AVLTree<K, V>::insert(node<K, V>* p, K k, V v) // вставка ключа k в дерево с корнем p
{
	if (!p)
	{
		root = new node<K, V>(k, v);
		return root;
	}
	
	if (k < p->key)
		p->left = insert(p->left, k, v);
	else
		p->right = insert(p->right, k, v);

	root = balance(p);
	return root;
}

template <typename K, typename V>
node<K, V>* AVLTree<K, V>::findmin(node<K, V>* p) // поиск узла с минимальным ключом в дереве p 
{
	return p->left ? findmin(p->left) : p;
}

template <typename K, typename V>
node<K, V>* AVLTree<K, V>::removemin(node<K, V>* p) // удаление узла с минимальным ключом из дерева p
{
	if (p->left == 0)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

template <typename K, typename V>
node<K, V>* AVLTree<K, V>::remove(node<K, V>* p, K k) // удаление ключа k из дерева p
{
	if (!p) return 0;
	if (k < p->key)
		p->left = remove(p->left, k);
	else if (k > p->key)
		p->right = remove(p->right, k);
	else //  k == p->key 
	{
		node<K, V>* q = p->left;
		node<K, V>* r = p->right;
		delete p;
		if (!r)
		{
			root = q;
			return root;
		}
		node<K, V>* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		root = balance(min);
		return root;
	}
	root = balance(p);
	return root;
}

template <typename K, typename V>
node<K, V>* AVLTree<K, V>::get(K k)
{
	node<K, V>* curNode = 0;
	if (root) curNode = root;


	while (true)
	{
		if (!curNode) return curNode;

		if (curNode->key == k) return curNode;

		if (k > curNode->key)
		{
			curNode = curNode->right;
		}
		else
		{
			curNode = curNode->left;
		}
	}
}

