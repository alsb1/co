#include <iostream>
#include <fstream>
#include <list>
#include <math.h>
using namespace std;
template <class T>
class DivisionChainedHashTable{
	private:
		int slots;
		list<T>* table;
		int size;
		int computeHashFunction(T x){
			int h=((int)x%this->getSlotNumber());
			return h;
		}
	public:
		DivisionChainedHashTable<T>(int x){
			this->slots=x;
			table=new list<T>[slots];
			size=0;
		}
		int getSlotNumber(){
			return slots;
		}
		int getSize(){
			return size;
		}
		int insertKey(T key){
			int pos=computeHashFunction(key);
			table[pos].push_back(key);
			size++;
			return pos;
		}
		
};

int main(){
	ifstream in("input.txt");
	ofstream out("output.txt");
	
	for(int t=0;t<100;t++){
		string s;
		in>>s;
		int m;
		in>>m;
		int n;
		in>>n;
		if(s=="int" || s=="double" || s=="bool"){
			DivisionChainedHashTable<double>*t=new DivisionChainedHashTable<double>(m);
			double tmp;
			int a[m];
			for(int i=0;i<m;i++){
				a[i]=0;
			}
			for(int i=0;i<n;i++){
				in>>tmp;
				int pos=t->insertKey(tmp);
				a[pos]++;
			}
			for(int i=0;i<m;i++)
			 out<<a[i]<<" ";
		}
		else
		{
			DivisionChainedHashTable<char>*t=new DivisionChainedHashTable<char>(m);
			char tmp;
			int a[m];
			for(int i=0;i<m;i++){
				a[i]=0;
			}
			for(int i=0;i<n;i++){
				in>>tmp;
				int pos=t->insertKey(tmp);
				a[pos]++;
			}
			for(int i=0;i<m;i++)
			 out<<a[i]<<" ";
			
		}
		out<<endl;
	}
	return 0;
}
