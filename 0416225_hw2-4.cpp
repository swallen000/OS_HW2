#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <utility>
#include <cstdio>

using namespace std;

int main(int argc,char *argv[]){
	ifstream file;
	file.open("Q4.txt");
	int num;
	int cap1,cap2;
	int time=0,com=1e8,finish=0,pos;
	queue<int> que;
	map<int,int>  mlfq[3];
	map<int,int>::iterator iter,it;

	file>>num;
	int arrive[num],burst[num],burst2[num];
	int wait[num]={0};
	int visit[num]={0};
	for(int i=0;i<num;i++)
		file>>arrive[i];
	for(int i=0;i<num;i++){
		file>>burst[i];
		burst2[i]=burst[i];
	}
	file>>cap1>>cap2;
		
	for(; finish!=num ;){
		for(int i=0;i<num;i++){
			if(arrive[i]<=time && visit[i]==0 && arrive[i]<com){
				pos=i;
				com=arrive[i];
			}
		}
		if(com!=1e8){
			mlfq[0].insert( pair<int,int>(pos , burst[pos]) );
			visit[pos]=1;
			com=1e8;
		}

		if(!mlfq[0].empty()){
			for(iter = mlfq[0].begin() ; iter!=mlfq[0].end() ; iter++){
				if(iter->second <= cap1){
					//cout<<"first="<<iter->first<<" ";
					time+=iter->second;
					burst[iter->first]-=iter->second;
					burst[iter->first]--;
					for(int i=0 ; i<num ; i++){
						if(i!=iter->first && burst[i]>=0){
							wait[i]+=iter->second;
							//cout<<"time="<<time<<"i="<<i<<"   wait[i]="<<wait[i]<<endl;
						}
					}
					finish++;
					//cout<<"now queue0 with process "<<iter->first<<"  burst time is "<<iter->second<<endl; 
					mlfq[0].erase(iter);
				}
				else{
					time+=cap1;
					burst[iter->first]-=cap1;
					for(int i=0 ; i<num ; i++){
						if(i!=iter->first && burst[i]>=0){
							wait[i]+=cap1;
							//cout<<"time="<<time<<"i="<<i<<"   wait[i]="<<wait[i]<<endl;
						}
					}
					/*cout<<"now queue0 with process "<<iter->first<<"  burst time is "<<iter->second\
						<<" remain time is "<<burst[iter->first]<<endl;*/
					mlfq[1].insert( pair<int,int>(iter->first , burst[iter->first]) );
					que.push(iter->first);
					mlfq[0].erase(iter);
				}
			}
		}
		else if(!mlfq[1].empty()){
			int temp=que.front();
			que.pop();
			for(iter=mlfq[1].begin();iter!=mlfq[1].end();iter++){
				if(iter->first==temp)
					break;
			}
			if(iter->second <= cap2){
				time+=iter->second;
				burst[iter->first]-=iter->second;
				burst[iter->first]--;
				for(int i=0 ; i<num ; i++){
						if(i!=iter->first && burst[i]>=0)
							wait[i]+=iter->second;
					}
				finish++;
				//cout<<"now queue1 with process "<<iter->first<<"  burst time is "<<iter->second<<endl; 
				mlfq[1].erase(iter);
			}
			else{
				time+=cap2;
				burst[iter->first]-=cap2;
				for(int i=0 ; i<num ; i++){
						if(i!=iter->first && burst[i]>=0)
							wait[i]+=cap2;
					}
				/*cout<<"now queue1 with process "<<iter->first<<"  burst time is "<<iter->second\
						<<" remain time is "<<burst[iter->first]<<endl;*/
				mlfq[2].insert( pair<int,int>(iter->first , burst[iter->first]) );
				mlfq[1].erase(iter);
			}
			/*for(iter=mlfq[1].begin() ; iter!=mlfq[1].end() ; iter++){
				if(iter->second <= cap2){
					time+=iter->second;
					burst[iter->first]-=iter->second;
					cout<<"now queue1 with process "<<iter->first<<"  burst time is "<<iter->second<<endl; 
					mlfq[1].erase(iter);
					break;
				}
				else{
					time+=cap2;
					burst[iter->first]-=cap2;
					cout<<"now queue1 with process "<<iter->first<<"  burst time is "<<iter->second\
						<<" remain time is "<<burst[iter->first]<<endl;
					mlfq[2].insert( pair<int,int>(iter->first , burst[iter->first]) );
					mlfq[1].erase(iter);
					break;
				}
			}*/
		}
		else if(!mlfq[2].empty()){
			//cout<<"size="<<mlfq[2].size()<<endl;
			for( iter = mlfq[2].begin() ; iter!=mlfq[2].end() ; iter++){
				if(iter->second < com){
					com=iter->second;
					it=iter;
				}
			}
			com=1e8;
			//cout<<"now queue2 with process "<<it->first<<"  burst time is "<<it->second<<endl; 
			for(int i=0 ; i<num ; i++){
				if(i!=it->first && burst[i]>=0)
					wait[i]+=it->second;
			}
			finish++;
			burst[it->first]-=it->second;
			burst[it->first]--;
			time+=it->second;
			mlfq[2].erase(it);
		}
		else{
			time++;
			for(int i=0 ; i<num ; i++){
				if(burst[i]>=0)
					wait[i]++;
			}
		}
	}
	for(int i=0 ; i<num ; i++){
		wait[i]-=arrive[i];
		//cout<<wait[i]<<"   ";
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