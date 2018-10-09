#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

int main(int argc,char *argv[]){
	ifstream file;
	file.open("Q2.txt");
	int num;
	int now=0,start=0,com=1e8,finish=0;
	file>>num;
	int arrive[num],burst[num];
	int visit[num]={0};
	int wait[num]={0};
	for(int i=0;i<num;i++)
		file>>arrive[i];
	for(int i=0;i<num;i++)
		file>>burst[i];

	for(; finish!=num ;){
		for(int i=0;i<num;i++){
			if(arrive[i]<=now&&burst[i]<com&&visit[i]==0){
				start=i;
				com=burst[i];
			}
		}
		if(com != 1e8){
			now+=burst[start];
			visit[start]=1;
			finish++;
			for(int i=0;i<num;i++){
				if(visit[i]==0)
					wait[i]+=burst[start];
			}
		}
		else{
			now++;
			for(int i=0;i<num;i++){
				if(visit[i]==0)
					wait[i]+=1;
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
		cout<<"P["<<i+1<<"]\t\t"<<wait[i]<<"\t\t"<<burst[i]+wait[i]<<endl;
	}
	double total_wait=0;
	double total_turn=0;
	for(int i=0;i<num;i++){
		total_wait+=wait[i];
		total_turn+=(wait[i]+burst[i]);
	}
	printf("Average waiting time : %f\n",(total_wait/num));
	printf("Average turnaround time : %f\n",(total_turn/num) );
	file.close();
	return 0;
}