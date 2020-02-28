#pragma once

#include "AVLTree.h"

template <typename K, typename V>
class Dictionary final
{

public:
	Dictionary();

	~Dictionary();

	void put(const K& key, const V& value);

	void remove(const K& key);

	bool contains(const K& key);

	V& operator[](const K& key);

	int size() const;

	class Iterator
	{
	public:

		friend class Dictionary;

		Iterator() {};

		Iterator(Dictionary<K,V>* dict):curPos(0), visited(0), _dict(dict), curNode(dict->_tree->getRoot()) {}

		const K& key() const;

		const V& get() const;

		void set(const V& value);

		void next();

		void prev();

		bool hasNext() const;

		bool hasPrev() const;

	private:
		int curPos;
		int visited;
		node<K, V>* curNode;
		Dictionary<K, V>* _dict;

	private:
		void preorder_traverse(node<K, V>* p);
		void visit(node<K, V>* p);
	};

	Iterator* iterator()
	{
		return new Iterator(this);
	}

private:
	AVLTree<K, V>* _tree;
	Iterator _it;
	int _size;

};

template <typename K, typename V>
Dictionary<K, V>::Dictionary()
{
	_size = 0;
	_tree = new AVLTree<K, V>;
}

template <typename K, typename V>
Dictionary<K, V>::~Dictionary()
{
}

template <typename K, typename V>
void Dictionary<K, V>::put(const K& key, const V& value)
{
	remove(key); //if contains

	_tree->insert(_tree->getRoot(), key, value);
	_size++;
}

template <typename K, typename V>
void Dictionary<K, V>::remove(const K& key)
{
	if (contains(key))
	{
		_tree->remove(_tree->getRoot(), key);
		_size--;
	}

}

template <typename K, typename V>
bool Dictionary<K, V>::contains(const K& key)
{
	node<K, V>* ret = 0;
	if (_tree->getRoot()) ret = _tree->get(key);
	return ret ? true : false;
}

template <typename K, typename V>
int Dictionary<K, V>::size() const
{
	return _size;
}

/*template <typename K, typename V>
const V& Dictionary<K, V>::operator[](const K& key) const
{
	if (contains(key))
	{
		return (tree->get(key)->value);
	}

	else
	{
		return 0;
	}
}*/

template <typename K, typename V>
V& Dictionary<K, V>::operator[](const K& key)
{
	if (contains(key))
	{
		return (_tree->get(key)->value);
	}

	else
	{
		V retV = 0;
		return retV;
	}
}


template <typename K, typename V>
void Dictionary<K, V>::Iterator::preorder_traverse(node<K, V>* p)
{
	if (!p) return;

	visit(p);
	preorder_traverse(p->left);
	preorder_traverse(p->right);
}

template <typename K, typename V>
void Dictionary<K, V>::Iterator::visit(node<K, V>* p)
{

	if (curPos == visited)
	{
		curNode = p;
	}
	visited++;
	
}

template <typename K, typename V>
const K& Dictionary<K, V>::Iterator::key() const
{
	return curNode->key;
}

template <typename K, typename V>
const V& Dictionary<K, V>::Iterator::get() const
{
	return curNode->value;
}

template <typename K, typename V>
void Dictionary<K, V>::Iterator::set(const V& newVal)
{
	curNode->value = newVal;
}

template <typename K, typename V>
void Dictionary<K, V>::Iterator::next()
{
	if (hasNext())
	{
		curPos++;
		preorder_traverse(_dict->_tree->getRoot());
		visited = 0;
	}

}

template <typename K, typename V>
void Dictionary<K, V>::Iterator::prev()
{
	if (hasPrev())
	{
		curPos--;
		preorder_traverse(_dict->_tree->getRoot());
		visited = 0;
	}

}

template <typename K, typename V>
bool Dictionary<K, V>::Iterator::hasNext() const
{
	return curPos < (_dict->size()-1);
}

template <typename K, typename V>
bool Dictionary<K, V>::Iterator::hasPrev() const
{
	return curPos > 0;
}