/*������ʹ����ɽ������˻ʺ����Ⲣͳ�ƽ������ٷֱ��Լ������ѵĴ���*/
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
//���������
std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(0, 7);
std::uniform_int_distribution<int> distribution1(0, 1);
//���ƺ���
int check(int idx) {
	int index = idx;  
	int row = index / 8;  
	int col = index % 8;  
	int j = 0, h = 0, i = 0;
	//û��ͳ��ͬ�еĳ�ͻ��
	for(i=col; i<64; i+=8)   
		if(S[i]==1)    
			h++;
	//������Խ���
	for(i=row,j=col; i>=0&&j>=0; i--,j--)   
		if(S[i*8+j]==1)    
			h++;
	for(i=row,j=col; i<8&&j<8; i++,j++)   
		if(S[i*8+j]==1)    
			h++;
	//��鸱�Խ���
	for(i=row,j=col; i>=0&&j<8; i--,j++)   
		if(S[i*8+j]==1)    
			h++;  
	for(i=row,j=col; j>=0&&i<8; i++,j--)   
		if(S[i*8+j]==1)    
			h++;  
	return h; 
}
//�������ɽ��
void HILL_CLIMBING(){
	//��ǰ״̬S��T
	//�ҳ�S��h������
	//���������ҳ�h��С��λ�ã����лʺ�ķ���
	//���Ͻ���ֱ��ÿһ��λ�õ�h�����ֵΪ0
	do{
		for (int i = 0; i < 64; i++) {
			T[i] = S[i];
		}
		for (int k = 0; k < 64; k++) {
			int h[64];       //�������ÿ�����hֵ   
			int f = 0;
			max = 0;
			for (int i = 0; i < 64; i++)  {
				int row;
				row = i / 8;       //��ǰ������    
				int j;
				for (j = 0; j < 8; j++)
					S[row * 8 + j] = 0;    //�������㣨���ۺ���������ͬ�г�ͻ��         
				h[i] = check(i);    //��Ÿ�λ�õ�hֵ ����ÿ��λ�õĴ��ۼ�¼������  
				for (j = 0; j < 8; j++)
					S[row * 8 + j] = T[row * 8 + j]; //�ָ�����  
			}
			//�ҳ�h�����ֵmax  
			for (int i = 0; i<64; i++)
				if (h[i]>max&&T[i] == 1){
					max = h[i];
					countMax = i;
				}
			//�ҵ���
			if (max == 0) {
				total += step;
				step = 0;
				return;
			}
			int row;
			row = countMax / 8;      //h���λ�������У�Ѱ����һ��h��С��λ��     
			min = 7;
			for (int i = 0; i < 8; i++)  {
				if (h[row * 8 + i] < min) {
					min = h[row * 8 + i];
					countMin = row * 8 + i;
					f = 1;
				}//�ҵ�Ҫ�ı��е����λ��
				//���ɹ�ѡ���λ���ж��ʱ�����ѡ��һ��
				if (h[row * 8 + i] == min&&min >= 1){
					int r = distribution1(generator);
					if (r == 1) {
						min = h[row * 8 + i];
						countMin = row * 8 + i;
						f = 1;
					}
				}
			}
			//�����ض�������û�н����ʧ��
			if (step > 400){
				//��¼ʧ�ܵİ���
				fail++;
				step = 0;
				return;
			}
			if (f == 1){
				for (int i = 0; i < 8; i++)
					T[row * 8 + i] = 0;     //h���λ������������  
				T[countMin] = 1;
				step++;    //h��Сλ�ô����ûʺ�
			}
		
		}
	} while (max>0);
}
//��ѡ��ɽ��
void HILL_CLIMBING1() {
	//���������ɽ����ȣ���ͬ�������ȷ�����
	//ǰ�߱���ÿ��λ�ã��ҳ����;�����������һ����֮ǰ���(����minʱ��һ��Ҫ����h������С��ֻҪ��ԭ����minС����
	do{
		for (int i = 0; i < 64; i++) {
			T[i] = S[i];
		}
		for (int k = 0; k < 64; k++) {
			int h[64];       //�������ÿ�����hֵ   
			int f = 0;
			max = 0;
			for (int i = 0; i < 64; i++)  {
				int row;
				row = i / 8;       //��ǰ������    
				int j;
				for (j = 0; j < 8; j++)
					S[row * 8 + j] = 0;    //�������㣨���ۺ���������ͬ�г�ͻ��         
				h[i] = check(i);    //��Ÿ�λ�õ�hֵ ����ÿ��λ�õĴ��ۼ�¼������  
				for (j = 0; j < 8; j++)
					S[row * 8 + j] = T[row * 8 + j]; //�ָ�����  
			}
			//�ҳ�h�����ֵmax  
			for (int i = 0; i<64; i++)
				if (h[i]>max&&T[i] == 1){
					max = h[i];
					countMax = i;
				}
			//�ҵ���
			if (max == 0) {
				total += step;
				step = 0;
				return;
			}
			int row;
			row = countMax / 8;      //h���λ�������У�Ѱ����һ��h��С��λ��     
			min = 7;
			int r = distribution(generator);
			while (h[row * 8 + r] > min) {
				r = distribution(generator);
			}
			min = h[row * 8 + r];
			countMin = row * 8 + r;
			f = 1;
			//�����ض�������û�н����ʧ��
			if (step > 400){
				//��¼ʧ�ܵİ���
				fail++;
				step = 0;
				return;
			}
			if (f == 1){
				for (int i = 0; i < 8; i++)
					T[row * 8 + i] = 0;     //h���λ������������  
				T[countMin] = 1;
				step++;    //h��Сλ�ô����ûʺ�
			}
		}
	} while (max>0);
}
//����������ɽ��
void HILL_CLIMBING2() {
	int i;
	do{
		for (int i = 0; i < 64; i++) {
			T[i] = S[i];
		}
		int h[64];       //�������ÿ�����hֵ   
		int f = 0;
		max = 0;
		for (i = 0; i < 64; i++)  {
			int row;
			row = i / 8;       //��ǰ������    
			int j;
			for (j = 0; j < 8; j++)
				S[row * 8 + j] = 0;    //�������㣨���ۺ���������ͬ�г�ͻ��         
			h[i] = check(i);    //��Ÿ�λ�õ�hֵ ����ÿ��λ�õĴ��ۼ�¼������  
			for (j = 0; j < 8; j++)
				S[row * 8 + j] = T[row * 8 + j]; //�ָ�����  
		}
		//�ҳ�h�����ֵmax  
		for (int i = 0; i<64; i++)
			if (h[i]>max&&T[i] == 1){
				max = h[i];
				countMax = i;
			}
		//�ҵ���
		if (max == 0) {
			cout << "The step is " << step << endl;
			total += step;
			return;
		}
		int row;
		row = countMax / 8;      //h���λ�������У�Ѱ����һ��h��С��λ��     
		min = 7;
		for (i = 0; i < 8; i++)  {
			if (h[row * 8 + i] < min) {
				min = h[row * 8 + i];
				countMin = row * 8 + i;
				f = 1;
			}//�ҵ�Ҫ�ı��е����λ��
			//���ɹ�ѡ���λ���ж��ʱ�����ѡ��һ��
			if (h[row * 8 + i] == min&&min >= 1){
				int r = rand() % 2;
				if (r == 1) {
					min = h[row * 8 + i];
					countMin = row * 8 + i;
					f = 1;
				}
			}
		}
		//�����ض�������û�н����ʧ��
		if (step > 300){
			//��¼ʧ�ܵİ���
			fail++;
			step = 0;
			cout << "There is no solution." << endl;
			return;
		}
		if (f == 1){
			for (i = 0; i < 8; i++)
				T[row * 8 + i] = 0;     //h���λ������������  
			T[countMin] = 1;
			step++;    //h��Сλ�ô����ûʺ�
		}
	} while (max>0);
}
//ģ���˻��㷨
void SIMULATED_ANNEALING() {
	//�˻��T��step�йأ���ѡ��minʱ�����ݸ���

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