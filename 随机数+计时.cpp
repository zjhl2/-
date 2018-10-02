#include<bits/stdc++.h>
using namespace std;

// default_random_engine e; // cost 3 times than rand()
mt19937 e;  //cost 4 times than default_randome_engine
uniform_real_distribution<double> rand_db(0,1.5);
uniform_int_distribution<long long> rand_ll(0,20);

int main(){
    clock_t start,finish;
    double totaltime;
    start=clock();
//-----------------------
    e.seed(time(0));
    for (int i=1;i<=1e8;i++){
        // rand();
		// rand_db(e);
		rand_ll(e);
	}
    cout<<"OK"<<endl;
//-----------------------
    finish=clock();
    totaltime=finish-start;
    cout<<"time: "<<totaltime<<"ms"<<endl;
}