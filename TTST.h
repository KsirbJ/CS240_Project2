#include <iostream>
#include <string>

using namespace std;

/**
 *	Templated 3-way search tree
 * 	Each node contains 2 values, and up to three children.
 *	Right value is bigger than left, values in the left subtree are smaller, values in middle subtree
 *	are between the two values, and values on the right are greater.
 *	Ex:
 *              [5|7]
 *             /  |  \
 *        [2|4] [6| ] [8|10]
 */
template <typename T>
class TTST{
public:
	TTST();
	TTST(T val);
	bool insert(const T &val);
	bool remove(const T &val);
	bool find(const T &val) const;
	void display() const;
	~TTST();
private:
	struct tNode{
		tNode *right, *middle, *left;
		T leftVal;
		T rightVal;
		bool valFilled;
	};
	tNode *root;
	void displayHelper(tNode *n) const;
	bool insertHelper(tNode *&n, const T &val);
	void destroy(tNode *n);
	bool removeHelper(tNode *prev, tNode *cur, const T &val);
};

#include "TTST.cpp"
