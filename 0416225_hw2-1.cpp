#include <iostream>
#include <cstdio>

using namespace std;

int main(int argc,char *argv[]){
	int num,i;

	FILE *file;
	file=fopen("Q1.txt","r");
	fscanf(file , "%d" , &num );
	int burst[num],wait[num]={0};
	for(i=0;i<num;i++){
		fscanf(file , "%d" , &burst[i]);
	}
	for(int i=0;i<num;i++){
		if(i==0)
			wait[i]=0;
		else{
			for(int j=0;j<i;j++)
				wait[i]+=burst[j];
		}
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

	fclose(file);
	return 0;
}