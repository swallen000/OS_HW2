#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

int main(int argc,char *argv[]){
	ifstream file;
	file.open("Q3.txt");
	int num;
	int total=0,com=1e8,start=0,finish=0;
	file>>num;
	int arrive[num],burst[num],burst2[num];
	int wait[num]={0};
	for(int i=0;i<num;i++)
		file>>arrive[i];
	for(int i=0;i<num;i++){
		file>>burst[i];
		burst2[i]=burst[i];
		total+=burst[i];
	}
	for(int i=0;i<num;i++){
		if(burst[i]==0){
			finish++;
			wait[i]=arrive[i];
		}
	}
	for(int j=0 ; finish!=num ; j++){
		for(int i=0;i<num;i++){
			if(arrive[i]<=j && burst[i]<com && burst[i]>0){
				start=i;
				com=burst[i];
			}
		}
		if(com != 1e8){
			burst[start]--;
			if(burst[start] == 0)
				finish++;
			for(int i=0;i<num;i++){
				if(i!=start&&burst[i]>0)
					wait[i]++;
			}
		}
		else{
			for(int i=0;i<num;i++){
				if(burst[i]>0)
					wait[i]++;
			}
		}
		com=1e8;
	}
	for(int i=0;i<num;i++){
		wait[i]-=arrive[i];
		//cout<<wait[i]<<" ";
	}
	cout<<"Process\t\tWaiting Time\tTurnaround Time\n";
	for(int i=0;i<num;i++){
		cout<<"P["<<i+1<<"]\t\t"<<wait[i]<<"\t\t"<<burst2[i]+wait[i]<<endl;
	}
	double total_wait=0;
	double total_turn=0;
	for(int i=0;i<num;i++){
		total_wait+=wait[i];
		total_turn+=(wait[i]+burst2[i]);
	}
	printf("Average waiting time : %f\n",(total_wait/num));
	printf("Average turnaround time : %f\n",(total_turn/num) );
	file.close();
	return 0;
}