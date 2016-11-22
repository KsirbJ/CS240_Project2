
// default constructor
template <typename T>
TTST<T>::TTST(){
	root = nullptr;
}

// val constructor. Creates root
template <typename T>
TTST<T>::TTST(T val){
	root = new tNode;
	root->leftVal = val;
	root->valFilled = false;
	root->right = root->middle = root->left = nullptr;
}

// display all of the nodes in the tree - inorder
template <typename T>
void TTST<T>::display() const{
	displayHelper(root);
}

// helper function for display
template <typename T>
void TTST<T>::displayHelper(tNode *n) const{
	if(n == nullptr){
		return;
	}
	displayHelper(n->left);
	cout << n->leftVal << " " ;
	displayHelper(n->middle);
	if(n->valFilled)
		cout << n->rightVal << " ";
	displayHelper(n->right);
} 


// insert a value into the tree
template <typename T>
bool TTST<T>::insert(const T &val){
	return insertHelper(root, val);
}

/**
 *	Helper function for insert.
 *	Recursively looks for the position where to insert the value, then
 *	fills in nodes from left to right, using INT_MIN to mark empty right values.
 * 	Ignores duplicates
 */
template <typename T>
bool TTST<T>::insertHelper(tNode *&n, const T &val){
	if(n == nullptr){
		n = new tNode;
		n->leftVal = val;
		n->right = n->middle = n->left = nullptr;
		n->valFilled = false;
		return true;
	// If both values of this node are filled in
	}else if(n->valFilled){ 
		// Figure out where to add the new node
		if(val > n->leftVal && val > n->rightVal){
			return insertHelper(n->right, val);
		}else if(val > n->leftVal && val < n->rightVal){
			return insertHelper(n->middle, val);
		}else if(val < n->leftVal && val < n->rightVal){
			return insertHelper(n->left, val);
		}
	// Only left value is filled in
	}else if(!n->valFilled){ 
		if(val > n->leftVal){
			n->rightVal = val;
			n->valFilled = true;
			return true;
		}else if(val < n->leftVal){
			n->rightVal = n->leftVal;
			n->leftVal = val;
			n->valFilled = true;
			return true;
		}
	}
	return false;
}


// find a value in the tree
template <typename T>
bool TTST<T>::find(const T &val) const{
	tNode *ptr = root;
	while(ptr != nullptr){
		if(ptr->valFilled){
			if(ptr->rightVal == val || ptr->leftVal == val){
				return true;
			}else if(val < ptr->leftVal && val < ptr->rightVal){
				ptr = ptr->left;
			}else if(val > ptr->leftVal && val < ptr->rightVal){
				ptr = ptr->middle;
			}else if(val > ptr->leftVal && val > ptr->rightVal){
				ptr = ptr->right;
			}
		}else{
			// If the node is not filled in, then it cannot have any children.
			// So if we don't find the value at this level, we can stop
			if(ptr->leftVal == val){
				return true;
			}else{
				return false;
			}
		}

	}
	return false;
}

// remove a node from the tree
template <typename T>
bool TTST<T>::remove(const T &val){
	return removeHelper(nullptr, root, val);
}

/**
 *	Remove a node from the tree.
 *	Check the many cases, and replace values / remove nodes accordingly
 * 
 */
template <typename T>
bool TTST<T>::removeHelper(tNode *prev, tNode *cur, const T &val){
	if(cur == nullptr) return false;
	// edge case - deleting the root with only one value
	if(cur == root && (cur->rightVal == val || cur->leftVal == val)){
		if(!cur->valFilled){
			delete root;
			root = nullptr;
			return true;
		}
	}
	int RML = 0; // 2 => node is parent's right child, 1 => node is parent's middle child, 0 => left child
	// find the node
	while(cur != nullptr && (cur->leftVal != val && cur->rightVal != val)){
		if(val > cur->rightVal){
			prev = cur;
			cur = cur->right;
			RML = 2;
		} else if(val < cur->leftVal){
			prev = cur;
			cur = cur->left;
			RML = 0;
		}else if(val > cur->leftVal){
			prev = cur;
			cur = cur->middle;
			RML = 1;
		}
	}
	if(cur != nullptr && (cur->leftVal == val || cur->rightVal == val)){
		// Case 0 - no children, and only one value
		if(cur->leftVal == val && !cur->valFilled){ 
			if(RML == 2) prev->right = nullptr;
			else if(RML == 1) prev->middle = nullptr;
			else prev->left = nullptr;
			delete cur;
		}else if(cur->valFilled){ // both values in the node are filled in
			// Case 1, no children
			if(cur->left == nullptr && cur->middle == nullptr && cur->right == nullptr){
				if(cur->leftVal == val) cur->leftVal = cur->rightVal;
				cur->valFilled = false;
			// case 2 - 1 child
			}else if(cur->left == nullptr && cur->middle == nullptr){ // only right child
				T tmpVal = cur->right->leftVal;
				if(cur->right->valFilled){
					removeHelper(cur, cur->right, cur->right->leftVal);
				}else{
					delete cur->right;
					cur->right = nullptr;
				}
				
				if(cur->leftVal == val){
					cur->leftVal = cur->rightVal;
				}
				cur->rightVal = tmpVal;
				return true;
			}else if(cur->left == nullptr && cur->right == nullptr){ // only middle child
				T tmpVal;
				if(cur->middle->valFilled){
					tmpVal = cur->middle->rightVal;
					removeHelper(cur, cur->middle, cur->middle->rightVal);
				}else{
					tmpVal = cur->middle->leftVal;
					delete cur->middle;
					cur->middle = nullptr;
				}
				// replace the value
				if(cur->rightVal == val) cur->rightVal = tmpVal;
				else cur->leftVal = tmpVal;
				return true;
			}else if(cur->middle == nullptr && cur->right == nullptr){ // only left child
				T tmpVal;
				if(cur->left->valFilled){
					tmpVal = cur->left->rightVal;
					removeHelper(cur, cur->left, cur->left->rightVal);
				}else{
					tmpVal = cur->left->leftVal;
					delete cur->left;
					cur->left = nullptr;
				}
				if(cur->rightVal == val){
					cur->rightVal = cur->leftVal;
				}
				cur->leftVal = tmpVal;
				return true;
			// case 3, 2 children
			}else if(cur->left == nullptr){ // has right and middle child
				if(cur->leftVal == val){
					T tmpVal;
					if(cur->middle->valFilled){
						tmpVal = cur->middle->rightVal;
						removeHelper(cur, cur->middle, cur->middle->rightVal);
					}else{
						tmpVal = cur->middle->leftVal;
						delete cur->middle;
						cur->middle = nullptr;
					}
					// replace the value
					if(cur->rightVal == val) cur->rightVal = tmpVal;
					else cur->leftVal = tmpVal;
					return true;
				}else if(cur->rightVal == val){
					T tmpVal = cur->right->leftVal;
					if(cur->right->valFilled){
						removeHelper(cur, cur->right, cur->right->leftVal);
					}else{
						delete cur->right;
						cur->right = nullptr;
					}
					
					if(cur->leftVal == val){
						cur->leftVal = cur->rightVal;
					}
					cur->rightVal = tmpVal;
					return true;
				}
			}else if(cur->middle == nullptr){ // right and left children only
				if(cur->leftVal == val){
					T tmpVal;
					if(cur->left->valFilled){
						tmpVal = cur->left->rightVal;
						removeHelper(cur, cur->left, cur->left->rightVal);
					}else{
						tmpVal = cur->left->leftVal;
						delete cur->left;
						cur->left = nullptr;
					}
					if(cur->rightVal == val){
						cur->rightVal = cur->leftVal;
					}
					cur->leftVal = tmpVal;
					return true;
				}else if(cur->rightVal == val){
					T tmpVal = cur->right->leftVal;
					if(cur->right->valFilled){
						removeHelper(cur, cur->right, cur->right->leftVal);
					}else{
						delete cur->right;
						cur->right = nullptr;
					}
					
					if(cur->leftVal == val){
						cur->leftVal = cur->rightVal;
					}
					cur->rightVal = tmpVal;
					return true;
				}
			}else if(cur->right == nullptr ){ // has left and middle children
				T tmpVal;
				if(cur->middle->valFilled){
					tmpVal = cur->middle->rightVal;
					removeHelper(cur, cur->middle, cur->middle->rightVal);
				}else{
					tmpVal = cur->middle->leftVal;
					delete cur->middle;
					cur->middle = nullptr;
				}
				// replace the value
				if(cur->rightVal == val) cur->rightVal = tmpVal;
				else cur->leftVal = tmpVal;
				return true;
			}
		// case 4, has all 3 children - follow same rules as case 2
		}else{
			if(cur->leftVal == val){
				T tmpVal;
				if(cur->middle->valFilled){
					tmpVal = cur->middle->rightVal;
					removeHelper(cur, cur->middle, cur->middle->rightVal);
				}else{
					tmpVal = cur->middle->leftVal;
					delete cur->middle;
					cur->middle = nullptr;
				}
				// replace the value
				if(cur->rightVal == val) cur->rightVal = tmpVal;
				else cur->leftVal = tmpVal;
				return true;
			}else if(cur->rightVal == val){
				T tmpVal = cur->right->leftVal;
				if(cur->right->valFilled){
					removeHelper(cur, cur->right, cur->right->leftVal);
				}else{
					delete cur->right;
					cur->right = nullptr;
				}
				
				if(cur->leftVal == val){
					cur->leftVal = cur->rightVal;
				}
				cur->rightVal = tmpVal;
				return true;
			}
		}
		
	}
	return false;
}


// recursively delete the nodes
template <typename T>
void TTST<T>::destroy(tNode *n){
	if(n != nullptr){
		destroy(n->left);
		destroy(n->middle);
		destroy(n->right);
		delete n;
	}
}

// Destructor
template <typename T>
TTST<T>::~TTST(){
	destroy(root);
}
