#include "TTST.h"
#include <chrono>
#include <vector>

void generateValues(int lBound, int uBound);

vector<int> myV;

int main(int argc, char **argv){

	int sizes[6] = {1000, 10000, 30000, 50000, 80000, 100000};
	// test with skewed tree
	{
		for(int i = 0; i < 6; ++i){
			auto timer = chrono::high_resolution_clock::now();
			TTST<int> *t = new TTST<int>();
			for(int j = 0; j < sizes[i]; ++j){
				t->insert(j);
			}
			auto timer2 = chrono::high_resolution_clock::now();
			auto span = chrono::duration_cast<chrono::duration<double>>(timer2 - timer);
			cout << "unbalanced insert took " << (span.count()/sizes[i]) << " for " << sizes[i] << " values" << endl;

			// test find
			auto timer3 = chrono::high_resolution_clock::now();
			for(int k = sizes[i]-1; k >= 0; --k){
				t->find(k);
			}	
			auto timer4 = chrono::high_resolution_clock::now();
			auto span2 = chrono::duration_cast<chrono::duration<double>>(timer4 - timer3);
			cout << "unbalanced find took " << (span2.count()/sizes[i]) << " for " << sizes[i] << " values" << endl;

			// test remove
			auto timer5 = chrono::high_resolution_clock::now();
			for(int h = sizes[i]; h >= 0; --h){
				t->remove(h);
			}	
			auto timer6 = chrono::high_resolution_clock::now();
			auto span3 = chrono::duration_cast<chrono::duration<double>>(timer6 - timer5);
			cout << "unbalanced remove took " << (span3.count()/sizes[i]) << " for " << sizes[i] << " values" << endl;
			delete t;
		}

	}

	// balanced tree
	{
		for(int i = 0; i < 6; ++i){
			generateValues(1, sizes[i]);
			// test insert
			auto timer = chrono::high_resolution_clock::now();
			TTST<int> t2;
			for(unsigned int j = 0; j < myV.size(); ++j){
				t2.insert(myV[j]);
			}
			auto timer2 = chrono::high_resolution_clock::now();
			auto span = chrono::duration_cast<chrono::duration<double>>(timer2 - timer);
			cout << "balanced insert took " << (span.count()/sizes[i]) << " for " << sizes[i] << " values" << endl;

			// test find
			auto timer3 = chrono::high_resolution_clock::now();
			for(int k = myV.size()-1; k >= 0; --k){
				t2.find(myV[k]);
			}	
			auto timer4 = chrono::high_resolution_clock::now();
			auto span2 = chrono::duration_cast<chrono::duration<double>>(timer4 - timer3);
			cout << "balanced find took " << (span2.count()/sizes[i]) << " for " << sizes[i] << " values" << endl;

			// test remove
			auto timer5 = chrono::high_resolution_clock::now();
			for(int h = sizes[i]; h > 0; --h){
				t2.remove(myV[h]);
			}	
			auto timer6 = chrono::high_resolution_clock::now();
			auto span3 = chrono::duration_cast<chrono::duration<double>>(timer6 - timer5);
			cout << "balanced remove took " << (span3.count()/sizes[i]) << " for " << sizes[i] << " values" << endl;
			myV.clear();
		}

	}

	// TTST<int> t;
	// // for(int i = 0; i < 10; ++i){
	// // 	t.insert(i);
	// // }
	// //t.display();

	// t.insert(5);
	// t.insert(8);
	// t.insert(6);
	// t.insert(10);
	// t.insert(11);
	// t.insert(7);
	// t.insert(2);
	// t.insert(4);
	// t.insert(1);
	// t.insert(9);
	// t.insert(12);
	// t.insert(15);
	// t.insert(3);
	// t.display();

	// cout << endl;
	// t.remove(11);
	// t.display();

	return 0;
}


// generate values that will result in a balanced tree
void generateValues(int lBound, int uBound){
	if(lBound == uBound){
		myV.push_back(lBound);
		return;
	} 
	// get middle value and add it to the vector
	int pivot = (lBound+uBound)/2;
	myV.push_back(pivot); 
	if(! (pivot-1 < lBound) ){
		//cout << "calling with " << lBound << "," << pivot-1 << endl;
		generateValues(lBound, pivot-1);
	}
	if(! (pivot+1 > uBound)){
		//cout << "calling with " << pivot+1 << "," << uBound << endl;
		generateValues(pivot+1, uBound);
	}
}