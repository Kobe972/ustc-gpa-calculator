#include<iostream>
#include<io.h>
#include<string.h>
using namespace std;

class GRADE
{
	public:
		int len;
		char name[500][30];
		double g[500];
		double score[500]; //ѧ�� 
		void insert(const char* _name,double _g,double _score);
		void del(const char* _name);
		void copy(const GRADE& a);
		void print();
		void giveup(); 
		GRADE();
		double GPA();
};
GRADE::GRADE()
{
	len=0;
}
void GRADE::print()
{
	if(len==0)
	{
		printf("���޳ɼ�\n");
		return;
	}
	printf("�γ�\tѧ��\t����\n");
	for(int i=0;i<len;i++)
	{
		printf("%s\t%.1f\t%.1f\n",name[i],score[i],g[i]);
	}
	return;
}
void GRADE::copy(const GRADE& a)
{
	this->len=a.len;
	for(int i=0;i<this->len;i++)
	{
		strcpy(this->name[i],a.name[i]);
		this->g[i]=a.g[i];
		this->score[i]=a.score[i];
	}
}
void GRADE::insert(const char* _name,double _g,double _score)
{
	strcpy(name[len],_name);
	g[len]=_g;
	score[len]=_score;
	len++;
}
void GRADE::del(const char* _name)
{
	for(int i=0;i<len;i++)
	{
		if(strcmp(name[i],_name)==0)
		{
			for(int j=i+1;j<len;j++)
			{
				strcpy(name[j-1],name[j]);
				g[j-1]=g[j];
				score[j-1]=score[j];
			}
		}
	}
	len--;
}
double GRADE::GPA()
{
	double tot_g=0,tot_score=0;
	for(int i=0;i<len;i++)
	{
		tot_g+=g[i]*score[i];
		tot_score+=score[i];
	}
	return tot_g/tot_score;
}
void GRADE::giveup()
{
	char chosen_name[30];
	char last_name[30];
	double last_score,last_g,chosen_score,chosen_g,best=0;
	GRADE tmp;
	tmp.copy(*this);
	for(int i=0;i<len;i++)
	{
		strcpy(last_name,tmp.name[i]);
		last_score=tmp.score[i];
		last_g=tmp.g[i];
		tmp.del(last_name);
		if(best<tmp.GPA()||best==tmp.GPA()&&last_score<chosen_score)
		{
			strcpy(chosen_name,last_name);
			chosen_score=last_score;
			chosen_g=last_g;
			best=tmp.GPA();
		}
		tmp.insert(last_name,last_g,last_score);
	}
	printf("��һ�ŷ����Ŀ�ĿΪ��%s\n",chosen_name);
	printf("�ÿ�Ŀѧ�֣�%.1f\n���㣺%.1f\n",chosen_score,chosen_g);
	printf("������GPA��%.2f\n",best);
	tmp.del(chosen_name);
	for(int i=0;i<len;i++)
	{
		strcpy(last_name,tmp.name[i]);
		last_score=tmp.score[i];
		last_g=tmp.g[i];
		tmp.del(last_name);
		if(best<tmp.GPA()||best==tmp.GPA()&&last_score<chosen_score)
		{
			strcpy(chosen_name,last_name);
			chosen_score=last_score;
			chosen_g=last_g;
			best=tmp.GPA();
		}
		tmp.insert(last_name,last_g,last_score);
	}
	printf("�ڶ��ŷ����Ŀ�ĿΪ��%s\n",chosen_name);
	printf("�ÿ�Ŀѧ�֣�%.1f\n���㣺%.1f\n",chosen_score,chosen_g);
	printf("������GPA��%.2f\n",best);
	tmp.del(chosen_name);
}
GRADE origin,tmp[3];
int main()
{
	FILE *grade;
	if(_access("grades.dat",0)==-1) grade=fopen("grades.dat","wb+");
	else grade=fopen("grades.dat","rb+");
	fread(&origin,sizeof(GRADE),1,grade);
	fclose(grade);
	grade=fopen("grades.dat","wb");
	start:;
	printf("1.�����³ɼ�\n2.ɾ���ɼ�\n3.ģ����ѧ�ڻ�Ԥ����ѧ��GPA\n4.����GPA\n5.��ӡ�ɼ���\n6.�����ɼ����Ų���\n7.�˳�\n");
	int choice;
	char _name[30];
	double _g,_score,_g2;
	cin>>choice;
	system("cls");
	switch(choice)
	{
		case 1:
			printf("��������γ������ո�ѧ�֣��ո񣩼��㣨�ո�+���У����γ�������end����\n");
			while(1)
			{
				cin>>_name>>_score>>_g;
				if(strcmp(_name,"end")==0) break;
				origin.insert(_name,_g,_score);
			}
			break;
		case 2:
			printf("����γ���\n");
			cin>>_name;
			origin.del(_name);
			break;
		case 3:
			printf("��������ѧ�֣��ո񣩼�����Сֵ���ո񣩼������ֵ���ո�+���У���ѧ������0����\n");
			tmp[0].copy(origin);
			tmp[1].copy(origin);
			tmp[2].copy(origin);
			while(1)
			{
				scanf("%lf %lf %lf",&_score,&_g,&_g2);
				if(_score==0) break;
				tmp[0].insert("prediction",_g,_score);
				tmp[1].insert("prediction",_g2,_score);
				tmp[2].insert("prediction",(_g+_g2)/2,_score);
			}
			printf("GPA��Сֵ��%.2f\nGPA���ֵ��%.2f\nGPAƽ��ֵ��%.2f\n",tmp[0].GPA(),tmp[1].GPA(),tmp[2].GPA());
			break;
		case 4:
			printf("GPA��%.2f\n",origin.GPA());
			break;
		case 5:
			origin.print();
			break;
		case 6:
			origin.giveup();
			break;
		case 7:
			fwrite(&origin,sizeof(GRADE),1,grade);
			fclose(grade);
			return 0;
		default:
			break; 
		
	}
	system("pause");
	system("cls");
	goto start;
	return 0;
}
