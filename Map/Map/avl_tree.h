#ifndef AVL_TREE_H_
#define AVL_TREE_H_

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#define COUNT 10
namespace nwacc
{
	template<typename T, typename K>
	class avl_tree
	{
	private:
		/**
		 * the node that contains the key and value stored in the map.
		 */
		struct node
		{

			T element;
			node * left;
			node * right;
			node * parent;
			K key;
			int height;

			node(const T & the_element, node * the_left, node * the_right,node * the_parent, const K & the_key, int the_height = 0)
				: element{ the_element }, left{ the_left },
				right{ the_right }, parent(the_parent) , key{ the_key }, height{ the_height }{}

			node(T && the_element, node * the_left, node * the_right, node * the_parent, const K & the_key, int the_height = 0)
				: element{ std::move(the_element) }, left{ the_left },
				right{ the_right }, parent(the_parent), key{ std::move(the_key) }, height{ the_height } {}
		};
	public:
		#pragma region iterators
		class const_iterator
		{
		public:
			K& get_key()
			{
				return current->key;
			}

			/**
			 *the default constructor initializes the current pointer.
			 */
			const_iterator() : current{ nullptr } {}

			/**
			 *summary
			 *@returns T the element held in the current node.
			 */
			const T & operator*() const
			{
				return this->retrieve();
			}

			// prefix ++ operator
			/**
			 * summary
			 * increments the current pointer
			 * @return const_iterator
			 */
			const_iterator & operator++()
			{
				if (this->current->right != nullptr) {
					this->current = this->find_left(this->current->right);
					return *this;
				}
				else {
					while (this->current->parent != nullptr && this->current == this->current->parent->right) {
						this->current = this->current->parent;
					}
					this->current = this->current->parent;
				}

				return *this;
			}
			// c++ REQUIRES! single anonymous int param
			// so the signatures of the methods are different. 
			// this is the postfix operator.
			/**
			 * summary
			 * increments the current pointer
			 * @return const_iterator
			 */
			const_iterator operator++(int)
			{
				auto old = *this;
				++(*this);
				return old;
			}
			/**
			 * summary
			 * decrements the current pointer
			 * @return const_iterator
			 */
			const_iterator & operator--()
			{
				if (this->current->left != nullptr) {
					this->current = this->find_right(this->current->left);
					return *this;
				}
				else {
					while (this->current->parent != nullptr && this->current == this->current->parent->left) {
						this->current = this->current->parent;
					}
					this->current = this->current->parent;
				}

				return *this;
			}
			/**
			 * summary
			 * decrements the current pointer
			 * @return const_iterator
			 */
			const_iterator operator--(int)
			{
				auto old = *this;
				--(*this);
				return old;
			}

			/**
			 * summary
			 * checks if the right hand and left hand are equal
			 *
			 * @return bool
			 */
			bool operator== (const const_iterator & rhs) const
			{
				return this->current == rhs.current;
			}
			/**
			 * summary
			 * checks if the right hand and left hand are not equal
			 *
			 * @return bool
			 */
			bool operator!= (const const_iterator & rhs) const
			{
				return !(*this == rhs);
			}

		protected:
			/**
			 *summary
			 *this it the pointer that keeps track of where you are in the list
			 */
			node * current;
			/**
			 *finds the left most node from a given position.
			 *@param start
			 *@returns node*
			 */
			static node * find_left(node * start)
			{
				while (start->left != nullptr) {
					start = start->left;
				}
				return start;
			}

			/**
			 *finds the right most node from a given position.
			 *@param start
			 *@returns node*
			 */
			static node * find_right(node * start)
			{
				while (start->right != nullptr) {
					start = start->right;
				}
				return start;
			}
			/**
			 * summary
			 * @return T returns the element held at the current node.
			 */
			T &retrieve() const
			{
				return this->current->element;
			}
			/**
			 * crates a new const_iterator at a given node pointer
			 * @param current
			 */
			const_iterator(node *current) : current{ current } {}
			/**
			 *summary
			 *makes linked_list<T,K> a friend of this class so it has access to the protected elements and methods.
			 */
			friend class avl_tree<T,K>;
		};

		class iterator : public const_iterator
		{
		public:
			/**
			 *summary
			 *empty constructor calls the const_iterator constructor
			 */
			iterator() {}

			/**
			 * summary
			 * @return T& returns the value held in the current node.
			 */
			T & operator*()
			{
				return const_iterator::retrieve();
			}

			// Return the object stored at the current position.
			// For iterator, there is an accessor with a
			// const reference return type and a mutator with
			// a reference return type. The accessor is shown first.
			/**
			 *summary
			 *@return const T& returns the value held in the current node.
			 */
			const T & operator* () const
			{
				return const_iterator::operator*();
			}



			/**
			 *summary
			 *increments to the next node in the list.
			 *
			 *@return iterator
			 */
			iterator & operator++ ()
			{
					if (this->current->right != nullptr) {
					this->current = this->find_left(this->current->right);
					return *this;
				}
				else {
					while (this->current->parent != nullptr && this->current == this->current->parent->right) {
						this->current = this->current->parent;
					}
					this->current = this->current->parent;
				}

				return *this;
			}

			/**
			 *summary
			 *increments to the next node in the list.
			 *
			 *@return iterator
			 */
			iterator operator++ (int)
			{
				auto old = *this;
				++(*this);
				return old;
			}

			/**
			 *summary
			 *decrements to the previous node in the list.
			 *
			 *@return iterator
			 */
			iterator & operator-- ()
			{
				if (this->current->left != nullptr) {
					this->current = this->find_right(this->current->left);
					return *this;
				}
				else {
					while (this->current->parent != nullptr && this->current == this->current->parent->left) {
						this->current = this->current->parent;
					}
					this->current = this->current->parent;
				}

				return *this;
			}

			/**
			 *summary
			 *decrements to the previous node in the list.
			 *
			 *@return iterator
			 */
			iterator operator-- (int)
			{
				auto old = *this;
				--(*this);
				return old;
			}
		protected:
			/**
			 *summary
			 *Protected constructor for iterator.Expects the current position.
			 *@param current
			 */
			iterator(node *current) : const_iterator{ current } { }

			/**
			 *finds the left most node from a given position.
			 *@param start
			 *@returns node*
			 */
			static node * find_left(node * start)
			{
				while (start->left != nullptr) {
					start = start->left;
				}
				return start;
			}

			/**
			 *finds the right most node from a given position.
			 *@param start
			 *@returns node*
			 */
			static node * find_right(node * start)
			{
				while (start->right != nullptr) {
					start = start->right;
				}
				return start;
			}
			/**
			 *summary
			 *makes the avl tree class a friend of this class so it has access to its attributes and methods.
			 */
			friend class avl_tree<T,K>;
		};
#pragma endregion 
#pragma region public
		/**
		 * @ return returns an iterator to a nullptr indicating that there are no more nodes;
		 */
		iterator begin() const
		{
			return iterator(nullptr);
		}
		/**
		 *@returns an iterator to the smallest element in the set
		 */
		iterator first() const
		{
			return iterator(this->find_min(this->root));
		}

		/**
		 * @ return returns an iterator to a nullptr indicating that there are no more nodes;
		 */
		iterator end() const
		{
			return iterator(nullptr);
		}

		/**
		 *@returns an iterator to the largest element in the set
		 */
		iterator last() const
		{
			return iterator(this->find_max(this->root));
		}


		/**
		 *this is the default constructor
		 */
		avl_tree() : root{ nullptr } {}

		/**
		 *this constructor creates a copy of another map
		 */
		avl_tree(const avl_tree & rhs) : root{ nullptr }
		{
			this->root = this->clone(rhs.root);
		}
		/**
		 *this constructor creates a copy of another map
		 */
		avl_tree(avl_tree && rhs) : root{ rhs.root }
		{
			rhs.root = nullptr;
		}
		/**
		 *this is the deconstructor.
		 */
		~avl_tree()
		{
			this->empty();
		}
		/**
		 *swaps the right hand side with the left.
		 *@param rhs
		 */
		avl_tree & operator=(const avl_tree & rhs)
		{
			auto copy = rhs;
			std::swap(*this, copy);
			return *this;
		}
		/**
		 *swaps the right hand side with the left.
		 *@param rhs
		 */
		avl_tree & operator=(avl_tree && rhs)
		{
			std::swap(this->root, rhs.root);
			return *this;
		}
		/**
		 *checks if the map is empty
		 */
		bool is_empty() const
		{
			return this->root == nullptr;
		}
		/**
		 *empties out the map
		 */
		void empty()
		{
			this->empty(this->root);
		}

		/**
		 *checks the map for the given value
		 */
		bool contains(const T & value) const
		{
			return this->contains(value, this->root);
		}
		/**
		 *@returns the smallest value in the map
		 */
		iterator find_min() const
		{
			if (this->is_empty())
			{
				throw new std::range_error("Tree is empty");
			}
			else
			{
				return iterator(this->find_min(this->root));
			}
		}
		/**
		 *@returns the largest value in the map
		 */
		iterator find_max() const
		{
			if (this->is_empty())
			{
				throw new std::range_error("Tree is empty");
			}
			else
			{
				return iterator(this->find_max(this->root));
			}
		}
		/**
		 *inserts the given value into the map
		 *@param value
		 *@param key
		 */
		iterator insert(const T & value,const K & key)
		{
			return this->insert(value, key, this->root);
		}
		/**
		 *inserts the given value into the map
		 *@param value
		 *@param key
		 */
		iterator insert(T && value,K && key)
		{
			this->insert(std::move(value),std::move(key), this->root);
		}
		/**
		 *removes the given value form the map
		 *@param key
		 */
		void remove(const K & key)
		{
			this->remove(key, this->root);
		}

		/**
		 * @returns the value associated with the given key
		 */
		T get(const K & key)
		{
			return this->get(key,this->root);
		}
#pragma endregion
#pragma region overloads
		
		iterator operator[](K & key)
		{
			return get(key,this->root);
		}

		iterator operator[](K && key)
		{
			return get_key_iterator(key, this->root);
			
		}

		friend std::ostream & operator<< (std::ostream & out, const avl_tree &rhs)
		{
			for (iterator current_item = rhs.first(); current_item != rhs.end(); current_item++)
			{
				out << current_item.get_key() << ", " << *current_item << std::endl;
			}
			out << std::endl;
			out << std::endl;
			for (iterator current_item = rhs.last(); current_item != rhs.begin(); current_item--)
			{
				out << current_item.get_key() << ", " << *current_item <<  std::endl;
			}
			return out;
		}
#pragma endregion 

	private:
		
		/**
		 * the first node inserted into the map
		 */
		node * root;
		/**
		 *returns the value associated with the given key
		 *@param key
		 *@param current
		 *@returns T
		 */
		T get(K key, node * current)
		{
			if(current == nullptr)
			{
				return {};
			}
			if(current->key < key)
			{
				get(key, current->right);
			}
			else if (key < current->key)
			{
				get(key, current->left);
			}
			return current->element;
		}
		/**
		 *returns the value associated with the given key
		 *@param key
		 *@param current
		 *@returns iterator
		 */
		iterator get_key_iterator(K key, node * current)
		{
			if (current == nullptr)
			{
				return {};
			}
			if (current->key < key)
			{
				get(key, current->right);
			}
			else if (key < current->key)
			{
				get(key, current->left);
			}
			return iterator(current);
		}

		/**
		 * removes all nodes in the map.
		 * @param current
		 */
		void empty(node * & current)
		{
			if (current != nullptr)
			{
				this->empty(current->left);
				this->empty(current->right);
				delete current;
			} // else, current is null, do_nothing();

			current = nullptr;
		}

		/**
		 * creates a copy of the map
		 * @param current
		 * @returns node*
		 */
		node * clone(node * current) const
		{
			if (current == nullptr)
				return nullptr;
			else
				return new node{ current->element, clone(current->left), clone(current->right), current->parent, current->key, current->height };
		}

		/**
		 *inserts the given value into the map
		 *@param value
		 *@param key
		 *@param current
		 *@param previous
		 */
		iterator insert(const T & value,const K & key, node * & current, node * previous = nullptr)
		{
			if (current == nullptr)
			{
				current = new node{ value, nullptr, nullptr,
					((previous == nullptr)? nullptr : previous),
					key };
			}
			else if (key < current->key)
			{
				this->insert(value,key, current->left,current);
			}
 			else if (current->key < key)
			{
				this->insert(value,key, current->right,current);
			} 
			else
			{
				current->element = value;
			}

			this->balance(current);
			return iterator(current);
		}
		/**
		 *inserts the given value into the map
		 *@param value
		 *@param key
		 *@param current
		 *@param previous
		 */
		iterator insert(T && value, const K && key, node * & current, node * previous = nullptr)
		{
			if (current == nullptr)
			{
				current = new node{ std::move(value), nullptr, nullptr,
				((previous == nullptr) ? nullptr : previous),
					std::move(key) };
			}
			else if (key < current->key)
			{
				this->insert(std::move(value), std::move(key), current->left,current);
			}
			else if (current->key < key)
			{
				this->insert(std::move(value), std::move(key), current->right,current);
			}
			else
			{
				current->element = value;
			}

			this->balance(current);
			return iterator(current);
		}

		/**
		 *removes the given value from the map
		 *@param key
		 *@param current
		 */
		void remove(const K & key, node * & current)
		{
			if (current == nullptr)
			{
				// we did not find the item to remove. 
				return; 
			} // else, we found the item do_nothing();

			if (key < current->key)
			{
				this->remove(key, current->left);
			}
			else if (current->key < key)
			{
				this->remove(key, current->right);
			}
			else if (current->left != nullptr && current->right != nullptr)
			{
				// here we have two children
				current->key = this->find_min(current->right)->key;
				this->remove(current->key, current->right);
			}
			else
			{
				// here we have no children :( or one child. 
				node * old_node = current;
				current = (current->left != nullptr) ? current->left : current->right;
				delete old_node;
			}

			this->balance(current);
		}
		/**
		 *checks the map for the given value
		 *@param value
		 *@param current
		 *@returns bool
		 */
		bool contains_value(const T & value, node * current) const
		{
			if (current == nullptr)
			{
				return false; // Does not exist in the tree :(
			} 
			else if (value < current->element)
			{
				return this->contains(value, current->left);
			} 
			else if (current->element < value)
			{
				return this->contains(value, current->right);
			}
			else
			{
				return true; // We found it!
			}
		}

		/**
		 *checks the map for the given value
		 *@param key
		 *@param current
		 *@returns bool
		 */
		bool contains_key(const K & key, node * current) const
		{
			if (current == nullptr)
			{
				return false; // Does not exist in the tree :(
			}
			else if (key < current->element)
			{
				return this->contains(key, current->left);
			}
			else if (current->element < key)
			{
				return this->contains(key, current->right);
			}
			else
			{
				return true; // We found it!
			}
		}

		/**
		 *finds the smallest node
		 *@param current
		 *@returns node*
		 */
		node * find_min(node * current) const
		{
			if (current == nullptr)
			{
				return nullptr;
			} // else, we are at the end, do_nothing();

			if (current->left == nullptr)
			{
				return current;
			} // else, we have found the smallest, do_nothing();

			return this->find_min(current->left);
		}

		/**
		 *finds the largest node
		 *@param current
		 *@returns node*
		 */
		node * find_max(node * current) const
		{
			if (current != nullptr)
			{
				while (current->right != nullptr)
				{
					current = current->right;
				}
			}
			return current;
		}
		/**
		 *determines the height of the map
		 *@param current
		 *@returns int
		 */
		int height(node * current) const
		{
			return current == nullptr ? -1 : current->height;
		}

		/**
		 * Rotate binary tree node with left child. This is a 
		 * single rotation. 
		 * @param current
		 */
		void rotate_with_left_child(node * & current)
		{
			auto * temp = current->left;
			current->left = temp->right; // current->left->right;
			temp->right = current;
			temp->parent = current->parent;
			current->parent = temp;
			if (current->right->parent != current)
			{
				current->right->parent = current;
			}
			if (current->left->parent != current)
			{
				current->left->parent = current;
			}

			current->height = std::max(this->height(current->left), this->height(current->right)) + 1;
			temp->height = std::max(this->height(temp->left), current->height) + 1;
			
			current = temp;
		}
		/**
		 * Rotate binary tree node with right child. This is a
		 * single rotation.
		 * @param current
		 */
		void rotate_with_right_child(node * & current)
		{
			auto * temp = current->right;
			current->right = temp->left;
			temp->left = current;
			temp->parent = current->parent;
			current->parent = temp;
			if(current->right != nullptr && current->right->parent != current)
			{
				current->right->parent = current;
			}
			if (current->left != nullptr && current->left->parent != current)
			{
				current->left->parent = current;
			}
			current->height = std::max(this->height(current->left), this->height(current->right)) + 1;
			temp->height = std::max(this->height(temp->right), current->height) + 1;

			current = temp;
		}

		/**
		 * Double rotate binary tree node - first rotate the left child
		 * with its right child; then with the new left child. 
		 * @param current
		 */
		void double_rotate_with_left_child(node * & current)
		{
			this->rotate_with_right_child(current->left);
			this->rotate_with_left_child(current);
		}
		/**
		 * Double rotate binary tree node - first rotate the right child
		 * with its right child; then with the new right child.
		 * @param current
		 */
		void double_rotate_with_right_child(node * & current)
		{
			this->rotate_with_left_child(current->right);
			this->rotate_with_right_child(current);
		}

		/**
		 * re-balances the map the ensure the fastest runtime for the contains method
		 * @param current
		 */
		void balance(node * & current)
		{
			if (current == nullptr)
			{
				return;
			} // else, we have a valid node do_nothing();

			if (this->height(current->left) - 
				this->height(current->right) > 1)
			{
				// left side has a greater height
				if (this->height(current->left->left) >=
					this->height(current->left->right))
				{
					this->rotate_with_left_child(current);
				}
				else
				{
					this->double_rotate_with_left_child(current);
				}
			}
			else if (this->height(current->right) - 
				     this->height(current->left) > 1) 
			{
				// right side has a greater height
				if (this->height(current->right->right) >= 
					this->height(current->right->left))
				{
					this->rotate_with_right_child(current);
				}
				else
				{
					this->double_rotate_with_right_child(current);
				}
			} // else, the nodes are balanced within 1, do_nothing();

			current->height = std::max(
				this->height(current->left),
				this->height(current->right)) + 1;
		}
	};
}

#endif // AVL_TREE_H_