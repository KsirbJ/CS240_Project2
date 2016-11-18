
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
		if(ptr->rightVal == val || ptr->leftVal == val){
			return true;
		}else if(val < ptr->leftVal && val < ptr->rightVal){
			ptr = ptr->left;
		}else if(val > ptr->leftVal && val < ptr->rightVal){
			ptr = ptr->middle;
		}else if(val > ptr->leftVal && val > ptr->rightVal){
			ptr = ptr->right;
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
 *	--------------- NOT YET IMPLEMENTED FOR 3-WAY TREE ------------------
 * 
 */
template <typename T>
bool TTST<T>::removeHelper(tNode *prev, tNode *cur, const T &val){
	if(cur == nullptr) return false;
	int RL = 0; // 1 => node is parent's right child, 0 => node is parent's left child.
	// find the node
	while(cur != nullptr && cur->val != val){
		if(val > cur->val){
			prev = cur;
			cur = cur->right;
			RL = 1;
		} else if(val < cur->val){
			prev = cur;
			cur = cur->left;
			RL = 0;
		}
	}
	if(cur != nullptr && cur->val == val){
		// edge case, deleting the root with no, or one child
		if(cur == root){
			if(cur->right == nullptr && cur->left == nullptr){
				delete root;
				root = nullptr;
				return true;
			}else if(cur->right != nullptr && cur->left == nullptr){
				tNode *tmp = cur->right;
				delete root;
				root = tmp;
				return true;
			}else if(cur->right == nullptr && cur->left != nullptr){
				tNode *tmp = cur->left;
				delete root;
				root = tmp;
				return true;
			}
		}
		// case 1 - no children
		if(cur->right == nullptr && cur->left == nullptr){
			if(RL) prev->right = nullptr; 
			else prev->left = nullptr;
			delete cur;
		// case 2 - one child
		}else if(cur->right == nullptr){ // only left child
			if(RL) prev->right = cur->left;
			else prev->left = cur->left;
			delete cur;
		}else if(cur->left == nullptr){ // only right child
			if(RL) prev->right = cur->right;
			else prev->left = cur->right;
			delete cur;
		// case 3 - 2 children
		}else{
			tNode *tmp = cur;
			tNode *tmpParent = cur;
			cur = cur->right;
			// find smallest successor 
			while(cur->left != nullptr) {
				tmpParent = cur;
				cur = cur->left;
			}
			T tmpVal = cur->val; // store value of successor
			// delete the successor, and handle parent's right/left pointer
			if(cur->right != nullptr){
				if(tmpParent->right != nullptr && tmpParent->right == cur)
					tmpParent->right = cur->right;
				else tmpParent->left = cur->right;
			}else{
				if(tmpParent->right != nullptr && tmpParent->right == cur)
					tmpParent->right = nullptr;
				else tmpParent->left = nullptr;
			}
			delete cur;
			tmp->val = tmpVal; // replace value that we want to delete with successor
		}
		return true;
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
