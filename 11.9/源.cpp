/*本程序使用爬山法解决八皇后问题并统计解决问题百分比以及所花费的代价*/
#include<iostream>
#include<stdlib.h>
#include<ctime>
#include<stdio.h>
#include<random>
#include<fstream>

using namespace std;
int S[65];
int T[65];
int max = 0, min = 0, countMax = 0, countMin = 0;
int fail = 0, step = 0;
int total = 0;
//生成随机数
std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(0, 7);
std::uniform_int_distribution<int> distribution1(0, 1);
//估计函数
int check(int idx) {
	int index = idx;  
	int row = index / 8;  
	int col = index % 8;  
	int j = 0, h = 0, i = 0;
	//没有统计同行的冲突数
	for(i=col; i<64; i+=8)   
		if(S[i]==1)    
			h++;
	//检查主对角线
	for(i=row,j=col; i>=0&&j>=0; i--,j--)   
		if(S[i*8+j]==1)    
			h++;
	for(i=row,j=col; i<8&&j<8; i++,j++)   
		if(S[i*8+j]==1)    
			h++;
	//检查副对角线
	for(i=row,j=col; i>=0&&j<8; i--,j++)   
		if(S[i*8+j]==1)    
			h++;  
	for(i=row,j=col; j>=0&&i<8; i++,j--)   
		if(S[i*8+j]==1)    
			h++;  
	return h; 
}
//最陡上升爬山法
void HILL_CLIMBING(){
	//当前状态S和T
	//找出S中h最大的行
	//在这行中找出h最小的位置，进行皇后的放置
	//不断进行直至每一个位置的h的最大值为0
	do{
		for (int i = 0; i < 64; i++) {
			T[i] = S[i];
		}
		for (int k = 0; k < 64; k++) {
			int h[64];       //用来存放每个点的h值   
			int f = 0;
			max = 0;
			for (int i = 0; i < 64; i++)  {
				int row;
				row = i / 8;       //当前所在行    
				int j;
				for (j = 0; j < 8; j++)
					S[row * 8 + j] = 0;    //该行清零（估价函数不考虑同行冲突）         
				h[i] = check(i);    //存放该位置的h值 （将每个位置的代价记录下来）  
				for (j = 0; j < 8; j++)
					S[row * 8 + j] = T[row * 8 + j]; //恢复该行  
			}
			//找出h的最大值max  
			for (int i = 0; i<64; i++)
				if (h[i]>max&&T[i] == 1){
					max = h[i];
					countMax = i;
				}
			//找到解
			if (max == 0) {
				total += step;
				step = 0;
				return;
			}
			int row;
			row = countMax / 8;      //h最大位置所在行，寻找这一行h最小的位置     
			min = 7;
			for (int i = 0; i < 8; i++)  {
				if (h[row * 8 + i] < min) {
					min = h[row * 8 + i];
					countMin = row * 8 + i;
					f = 1;
				}//找到要改变行的最佳位置
				//当可供选择的位置有多个时，随机选择一个
				if (h[row * 8 + i] == min&&min >= 1){
					int r = distribution1(generator);
					if (r == 1) {
						min = h[row * 8 + i];
						countMin = row * 8 + i;
						f = 1;
					}
				}
			}
			//超过特定步数还没有解决则失败
			if (step > 400){
				//记录失败的案例
				fail++;
				step = 0;
				return;
			}
			if (f == 1){
				for (int i = 0; i < 8; i++)
					T[row * 8 + i] = 0;     //h最大位置所在行清零  
				T[countMin] = 1;
				step++;    //h最小位置处放置皇后
			}
		
		}
	} while (max>0);
}
//首选爬山发
void HILL_CLIMBING1() {
	//与最陡上升爬山发相比，不同在于如何确定后继
	//前者遍历每个位置，找出最大;后者随机生成一个比之前大的(在找min时不一定要求其h整行最小，只要比原来的min小即可
	do{
		for (int i = 0; i < 64; i++) {
			T[i] = S[i];
		}
		for (int k = 0; k < 64; k++) {
			int h[64];       //用来存放每个点的h值   
			int f = 0;
			max = 0;
			for (int i = 0; i < 64; i++)  {
				int row;
				row = i / 8;       //当前所在行    
				int j;
				for (j = 0; j < 8; j++)
					S[row * 8 + j] = 0;    //该行清零（估价函数不考虑同行冲突）         
				h[i] = check(i);    //存放该位置的h值 （将每个位置的代价记录下来）  
				for (j = 0; j < 8; j++)
					S[row * 8 + j] = T[row * 8 + j]; //恢复该行  
			}
			//找出h的最大值max  
			for (int i = 0; i<64; i++)
				if (h[i]>max&&T[i] == 1){
					max = h[i];
					countMax = i;
				}
			//找到解
			if (max == 0) {
				total += step;
				step = 0;
				return;
			}
			int row;
			row = countMax / 8;      //h最大位置所在行，寻找这一行h最小的位置     
			min = 7;
			int r = distribution(generator);
			while (h[row * 8 + r] > min) {
				r = distribution(generator);
			}
			min = h[row * 8 + r];
			countMin = row * 8 + r;
			f = 1;
			//超过特定步数还没有解决则失败
			if (step > 400){
				//记录失败的案例
				fail++;
				step = 0;
				return;
			}
			if (f == 1){
				for (int i = 0; i < 8; i++)
					T[row * 8 + i] = 0;     //h最大位置所在行清零  
				T[countMin] = 1;
				step++;    //h最小位置处放置皇后
			}
		}
	} while (max>0);
}
//带重启的爬山法
void HILL_CLIMBING2() {
	int i;
	do{
		for (int i = 0; i < 64; i++) {
			T[i] = S[i];
		}
		int h[64];       //用来存放每个点的h值   
		int f = 0;
		max = 0;
		for (i = 0; i < 64; i++)  {
			int row;
			row = i / 8;       //当前所在行    
			int j;
			for (j = 0; j < 8; j++)
				S[row * 8 + j] = 0;    //该行清零（估价函数不考虑同行冲突）         
			h[i] = check(i);    //存放该位置的h值 （将每个位置的代价记录下来）  
			for (j = 0; j < 8; j++)
				S[row * 8 + j] = T[row * 8 + j]; //恢复该行  
		}
		//找出h的最大值max  
		for (int i = 0; i<64; i++)
			if (h[i]>max&&T[i] == 1){
				max = h[i];
				countMax = i;
			}
		//找到解
		if (max == 0) {
			cout << "The step is " << step << endl;
			total += step;
			return;
		}
		int row;
		row = countMax / 8;      //h最大位置所在行，寻找这一行h最小的位置     
		min = 7;
		for (i = 0; i < 8; i++)  {
			if (h[row * 8 + i] < min) {
				min = h[row * 8 + i];
				countMin = row * 8 + i;
				f = 1;
			}//找到要改变行的最佳位置
			//当可供选择的位置有多个时，随机选择一个
			if (h[row * 8 + i] == min&&min >= 1){
				int r = rand() % 2;
				if (r == 1) {
					min = h[row * 8 + i];
					countMin = row * 8 + i;
					f = 1;
				}
			}
		}
		//超过特定步数还没有解决则失败
		if (step > 300){
			//记录失败的案例
			fail++;
			step = 0;
			cout << "There is no solution." << endl;
			return;
		}
		if (f == 1){
			for (i = 0; i < 8; i++)
				T[row * 8 + i] = 0;     //h最大位置所在行清零  
			T[countMin] = 1;
			step++;    //h最小位置处放置皇后
		}
	} while (max>0);
}
//模拟退火算法
void SIMULATED_ANNEALING() {
	//退火的T与step有关，在选择min时，根据概率

}
int main(){
	cout << "This problem will create 100 8-queue instances and solve them!" << endl;
	fstream file;
	int count = 100;
	fail = 0;
	total = 0;
	//steepest
	file.open("./input.txt", ios::in);
	while (count--) {
		max = 1, countMax = 0, countMin = 0;
		step = 0;
		for (int i = 0; i < 64; i++) {
			file >> S[i];
		}
		HILL_CLIMBING();
	}
	file.close();
	cout << "The sovled cases percentage is: " << (100.0 - fail) / 100.0 << endl;
	cout << "The average step is " << (double)(total / 100.0) << endl;
	count = 100;
	total = 0;
	file.open("./input1.txt", ios::in);
	fail = 0;
	//first-choice
	while (count--) {
		max = 1, countMax = 0, countMin = 0;
		step = 0;
		for (int i = 0; i < 64; i++) {
			file >> S[i];
		}
		HILL_CLIMBING1();
	}
	file.close();
	cout << "The sovled cases percentage is: " << (100.0 - fail) / 100.0 << endl;
	cout << "The average step is " << (double)(total / 100.0) << endl;
	return 0;
}