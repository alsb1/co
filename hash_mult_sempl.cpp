#include <iostream>
#include <fstream>
#include <list>
#include <math.h>
using namespace std;
template <class T>
class MultChainedHashTable{
	private:
		int slots;
		list<T>* table;
		int size;
		double c;
		int computeHashFunction(T x){
			double y=x*c;
			double a=y -(int)y;
			int h=(int)(a*this->getSlotNumber());
			return h;
		}
	public:
		MultChainedHashTable<T>(int x){
			this->slots=x;
			table=new list<T>[slots];
			size=0;
			c=0.61803;
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
			MultChainedHashTable<double>*t=new MultChainedHashTable<double>(m);
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
			MultChainedHashTable<char>*t=new MultChainedHashTable<char>(m);
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
