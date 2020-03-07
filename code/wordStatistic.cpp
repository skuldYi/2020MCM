#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>


using namespace std;
#define MAX_LENGTH 1<<10//单词的最大长度


typedef struct{
	string str;
	int cnt;
}word;


int number_of_words=0;//记录单词统计总数
vector<string> virtual_word;//需要被除去的虚词集
vector<string> raw_word;//资源文本中的单词集
vector<word> word_statistics;//统计结果集


/*字典排序比较函数*/
bool cmp_raw_word(const string &a,const string &b){return a<b;}


/*词汇出现次数降序排序比较函数*/
bool cmp_word_statistics(const word &a,const word &b){return a.cnt>b.cnt;}


/*虚读取以处理资源文件以及虚词文件除大小写字母外的所有汉字及字符*/
bool skip(){ scanf("%*[^a-z||A-Z]"); return true;}


int main()
{
	/*初始化时间*/
	clock_t start,finish;
	double totaltime;
	start=clock();


	printf("Wait for a moment please.\n");


	/*定义缓存空间*/
	word w;
	char _word[MAX_LENGTH];


	vector<string>::iterator it,last;
	vector<word>::iterator wit;


	/*重定向输入流至 virtual.txt 文件,读取 virtual.txt 文件所有英文单词*/
	freopen("virtual.txt","r",stdin);
	while(skip()&&scanf("%[a-zA-Z]",_word)!=EOF) virtual_word.push_back(_word);


	/*对虚词表进行排序以便其后的搜索操作*/
	sort(virtual_word.begin(),virtual_word.end(),cmp_raw_word);


	/*重定向输入流至 in.txt 文件,并读取 in.txt 文件中所有英文单词*/
	freopen("in.txt","r",stdin);
	while(skip()&&scanf("%[a-zA-Z]",_word)!=EOF)
	{
	 	number_of_words++;
	 	/*将只有首字母大写的单词的首字母转换成小写*/
	 	if(_word[1]!='\0'&&isupper(_word[0])&&islower(_word[1])) _word[0]|=1<<5;
	 	raw_word.push_back(_word);
	}


	/*重定向输出流至 out.txt 文件并输出相关说明信息*/
	freopen("out.txt","w",stdout);
	printf("-----------------------------------------------\n");
	printf("%d words be counted! \nDetails are as follow:\n",number_of_words);
	printf("no.\tword\ttime\tfrequency\n");
	printf("-----------------------------------------------\n");


	/*若没有检测到输入时,结束程序并返回提示信息*/
	if(!raw_word.size())
	{
	 	printf("There is no word in the \"in.txt\" or \"in.txt\" inexistence!\n");
	 	printf("-----------------------------------------------\n");
	 	return 0;
	}


	/*对单词集进行字典排序以便进行出现次数统计操作*/
	sort(raw_word.begin(),raw_word.end(),cmp_raw_word);
	for(last=raw_word.begin(),it=raw_word.begin()+1;it!=raw_word.end();it++)
	{
	 	if(*it!=*last)
	 	{
	 	  w.str=*last;
	 	  w.cnt=it-last;
	 	  /*得到的统计结果在 virtual_word 集合中验证,未在 virtual_word 集合中出现才计入结果*/
	 	  if(!binary_search(virtual_word.begin(),virtual_word.end(),*last)) word_statistics.push_back(w);
	 	  last=it;
	 	}
	}


	/*弥补跳出循环时最后一个未被计入单词*/
	w.str=*last;
	w.cnt=it-last;
	if(!binary_search(virtual_word.begin(),virtual_word.end(),*last)) word_statistics.push_back(w);


	/*对结果集进行出现次数关键词降序排序*/
	sort(word_statistics.begin(),word_statistics.end(),cmp_word_statistics);
	bool b=false;
	for(wit=word_statistics.begin();wit!=word_statistics.end();wit++)
	{
	 	/*为保证统计有意义,对统计数据输出进行调节*/
	 	if((*wit).cnt*1.0/number_of_words>=0.05||((*wit).cnt>=2&&(*wit).cnt*100.0/number_of_words>=0.01)){
	 	 	printf("%-5d\t%-16s\t%5d\t%17.3lf%%\n",wit-word_statistics.begin()+1,((*wit).str).c_str(),(*wit).cnt,(*wit).cnt*100.0/number_of_words);
	 	 	b=true;
	 	}
	}


	/*因统计数据输出调节引起的空输出提示*/
	if(!b)printf("no appropriate word!\n");
	printf("-----------------------------------------------\n");


	/*计算并输出统计程序消耗的时间*/
	finish=clock();
	totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
	printf("The program cost %.4lf second(s)",totaltime);
	return 0;
}
