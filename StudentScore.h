#pragma warning(disable:4996)

//（1）预处理 
//文件包含
#include<stdio.h>         //标准输入/输出函数库 
#include<stdlib.h>         //标准函数库 
#include<string.h>       //字符串函数库 
#include<conio.h>        //控制台输入/输出函数库

//学生信息长度宏定义
#define  MAX_ID    14   //学号最大长度
#define  MAX_NAME  11   //姓名最大长度
#define  MAX_SEX   3    //性别最大长度

//系统菜单选项宏定义
#define  EXIT   0  //退出系统
#define  INPUT  1  //增加学生信息 
#define  DELETE 2  // 删除学生信息
#define  SEARCH 3  //查找学生信息
#define  UPDATE 4  //修改学生信息
#define  OUTPUT 5  //输出所有学生信息
#define  ABOUT  6   //关于作者 

//查找方式宏定义
#define  SEARCH_ID 1  //按学号查找
#define  SEARCH_NAME 2 //按姓名查找

//更新项目宏定义
#define  UPDATE_ID 1  //修改学号
#define  UPDATE_NAME 2 //修改姓名
#define  UPDATE_SEX 3 //修改性别
#define  UPDATE_C  4 //修改C语言成绩
#define  UPDATE_MATH 5 // 修改高数成绩
#define  UPDATE_ENG  6  //修改英语成绩
#define  UPDATE_PE 7   //修改体育成绩 

//（2）数据类型定义 
//学生信息结构体
typedef struct  StuScore     //用StuScore代替struct 
{
	char id[MAX_ID];    //学号   --学生唯一标识     //成员列表 
	char name[MAX_NAME];  //名字  --最长为5个汉字   
	char sex[MAX_SEX];   //性别   --男或女 
	int CLanguage;     //c语言成绩
	int Mathematics;   //高数成绩 
	int English;      //英语成绩
	int PE;      //体育 
	int Total;      //总分 
	float Average;    //平均数 
} StuScore;


//学生成绩链表结构体
typedef struct StuScoreNode   //（结构体） 
{
	StuScore data;                   //数据 
	struct _StuScoreNode* next;        //地址 
} StuScoreNode;
typedef   StuScoreNode* StuScoreList;  // 为自定义的数据类型定义一个新名字StuScoreList 

//（3）全局变量定义和函数声明 

StuScoreList score;  //全局变量定义，用于保存所有学生成绩的单链表         

//人机界面操作函数列表
void ShowMenu();     //人机界面函数 
void AddStu();        //增加学生
void DeleteStu();    //删除学生
void SearchStu();    //查找并显示学生信息
void SearchStuID();   //按学号查找
void SearchStuName();   //按姓名查找
void UpdateStu();  //修改学生信息
void OutputStu();  //输出所有学生信息
void Exit();     //退出学生成绩管理系统
void print_info();  //排序后的内容输出 

//辅助函数列表
void ReadFile();       //从文件读出学生成绩信息 
void WriteFile();       //将学生成绩信息写入文件
//查找学生在系统中是否已经存在，存在返回1，不存在返回0
int FindStu(char* id);
//（4）人机界面函数定义 
void ShowMenu()
{
	system("color F0"); //改变背景为黑色，文字为淡黄色

	int typeID = 0;

	ReadFile();//启动程序前从文件读出所有学生成绩信息

	while (1)
	{
		system("cls");//清屏(清除屏幕之前显示内容)
		printf(" \t\t\t\t\t ┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n");
		printf(" \t\t\t\t\t ┃     学生成绩管理系统     ┃\n");
		printf(" \t\t\t\t\t ┃━━━━━━━━━━━━━━━━━━━━━━━━━━┃ \n");
		printf(" \t\t\t\t\t ┃     0-退出系统           ┃\n");
		printf(" \t\t\t\t\t ┃     1-增加学生           ┃\n");
		printf(" \t\t\t\t\t ┃     2-删除学生           ┃\n");
		printf(" \t\t\t\t\t ┃     3-查找学生           ┃\n");
		printf(" \t\t\t\t\t ┃     4-修改学生信息    ┃\n");
		printf(" \t\t\t\t\t ┃     5-输出学生信息    ┃\n");
		printf(" \t\t\t\t\t ┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n");
		printf("\t\t\t\t\t->请选择操作: ");
		scanf("%d", &typeID);

		if (typeID == EXIT)//程序退出前将学生成绩信息写人文件
		{
			WriteFile();//退出系统
			Exit();
			break;
		}
		switch (typeID)
		{
		case INPUT:  //增加学生
			system("cls");
			AddStu();
			system("pause");//程序暂停
			break;
		case DELETE:
			system("cls");
			DeleteStu();//删除学生信息
			system("pause");
			break;
		case SEARCH:
			SearchStu();//查找学生信息
			break;
		case UPDATE:
			system("cls");
			UpdateStu();//更新学生信息
			system("pause");
			break;
		case OUTPUT:
			system("cls");
			OutputStu();//输出所有学生信息
			system("pause");
			break;
		case ABOUT:
			system("cls");
			About();//作者信息
			system("pause");
			break;
		default:
			printf("输人有误!\n");
			system("pause");
			break;
		}
	}
}

//（5）增加学生函数定义 
void AddStu()
{
	//分配存储空间
	StuScoreNode* p = (StuScoreNode*)malloc(sizeof(StuScoreNode));
	printf(" \t\t\t\t\t ┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n");
	printf(" \t\t\t\t\t ┃     请输人学生信息       ┃\n");
	printf(" \t\t\t\t\t ┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n");
	printf("\t\t\t\t\t-请输人学号(最大长度为%d个字符)\n\t\t\t\t\t->", MAX_ID - 1);
	scanf("%s", p->data.id);
	while (FindStu(p->data.id) == 1)
	{
		printf("\t\t\t\t\t-此学生已经存在，请重新输人\n\t\t\t\t\t->");
		scanf("%s", p->data.id);
	}
	printf("\t\t\t\t\t请输人姓名(最大长度为%d个字符)\n\t\t\t\t\t->", MAX_NAME - 1);
	scanf("%s", p->data.name);
	printf("\t\t\t\t\t-请输人性别('男'或'女')\n\t\t\t\t\t->");
	scanf("%s", p->data.sex);
	printf("\t\t\t\t\t-请输人C语言成绩(0~100)\n\t\t\t\t\t->");
	scanf("%d", &p->data.CLanguage);
	p->data.Total = p->data.CLanguage;
	printf("\t\t\t\t\t-请输人高数成绩(0~100)\n\t\t\t\t\t->");
	scanf("%d", &p->data.Mathematics);
	p->data.Total += p->data.Mathematics;
	printf("\t\t\t\t\t-请输人英语成绩(0~100)\n\t\t\t\t\t->");
	scanf("%d", &p->data.English);
	p->data.Total += p->data.English;
	printf("\t\t\t\t\t-请输人体育成绩(0~100)\n\t\t\t\t\t->");
	scanf("%d", &p->data.PE);
	p->data.Total += p->data.PE;
	p->data.Average = p->data.Total / 4;


	p->next = score;

	score = p;
	printf(" \t\t\t\t\t ┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf(" \t\t\t\t\t ┃┃      添加成功!         ┃┃\n");
	printf(" \t\t\t\t\t ┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
}
//（6）删除学生函数定义 
void DeleteStu()
{
	StuScoreNode* pre = score;//前一结点
	StuScoreNode* p = score;//当前结点
	char  id[MAX_ID];
	printf(" \t\t\t\t\t ┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n");
	printf(" \t\t\t\t\t ┃┃ 请输人要删除学生的学号:┃┃\n");
	printf(" \t\t\t\t\t ┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n\t\t\t\t\t->");
	scanf("%s", id);

	while (p)                 //查找待删除结点
	{
		if (strcmp(p->data.id, id) == 0)
			break;
		pre = p;
		p = p->next;
	}
	if (!p)
		printf(" \t\t\t\t\t ┃┃     此学生不存在！     ┃┃\n");
	else
	{
		char ch;
		printf("\t\t\t\t\t->输人'y'或'Y'删除记录!\n");
		ch = getch();
		if (ch == 'y' || ch == 'Y')
		{
			if (p == score) score = p->next;
			else
				pre->next = p->next;  // 后驱节点指向前驱节点 
			free(p);
			printf(" \t\t\t\t\t ┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n");
			printf(" \t\t\t\t\t ┃┃        删除成功        ┃┃\n");
		}
	}
	printf(" \t\t\t\t\t ┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n");
}

//（7）查找学生信息函数定义 
void SearchStu()
{
	int type, flag = 1;
	while (flag)
	{
		system("cls");
		printf(" \t\t\t\t\t ┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n");
		printf(" \t\t\t\t\t ┃     1 - 按学号查找       ┃ \n");
		printf(" \t\t\t\t\t ┃     2 - 按姓名查找       ┃ \n");
		printf(" \t\t\t\t\t ┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n");
		printf("\t\t\t\t\t->选择查找方式：");
		scanf("%d", &type);
		switch (type)
		{
		case SEARCH_ID:
			system("cls");
			SearchStuID();    //按学号查找 
			flag = 0;
			break;
		case SEARCH_NAME:
			system("cls");
			SearchStuName();
			flag = 0;
			break;
		default:
			printf("\t\t\t\t\t输入有误!\n");
			break;
		}
		system("pause");
	}
}
//（8）按学号查找函数定义
void SearchStuID()
{
	StuScoreNode* p = score;
	char id[MAX_ID];
	printf(" \t\t\t\t\t ┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n");
	printf(" \t\t\t\t\t ┃┃ 请输入要查找学生的学号:┃┃\n\t\t\t\t\t->");
	scanf("%s", id);

	while (p)   //检查学生是否存在 
	{
		if (strcmp(p->data.id, id) == 0)
			break;
		p = p->next;
	}
	if (!p)
	{
		printf(" \t\t\t\t\t ┃┃     此学生不存在！     ┃┃\n");
		printf(" \t\t\t\t\t ┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n");
	}
	else
	{
		printf(" \t\t\t\t\t ┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n");
		printf(" \t\t\t\t\t ┃┃        学生信息        ┃┃\n");
		printf(" \t\t\t\t\t ┃━━━━━━━━━━━━━━━━━━━━━━━━━━┃ \n");
		printf("\t\t\t\t\t   -学    号：%s\n", p->data.id);
		printf("\t\t\t\t\t   -姓    名：%s\n", p->data.name);
		printf("\t\t\t\t\t   -性    别：%s\n", p->data.sex);
		printf("\t\t\t\t\t   -C语言成绩：%d\n", p->data.CLanguage);
		printf("\t\t\t\t\t   -高数成绩：%d\n", p->data.Mathematics);
		printf("\t\t\t\t\t   -英语成绩:%d\n", p->data.English);
		printf("\t\t\t\t\t   -体育成绩:%d\n", p->data.PE);
		//printf("\t\t\t\t\t   -总    分：%d\n", p->data.Total);
		//printf("\t\t\t\t\t   -平 均 分：%.2f\n", p->data.Average);
		printf(" \t\t\t\t\t ┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n");
	}
}
//（9）按姓名查找函数定义
void SearchStuName()
{
	StuScoreNode* p = score;
	char name[MAX_NAME];
	printf(" \t\t\t\t\t ┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n");
	printf(" \t\t\t\t\t ┃┃ 请输入要查找学生的姓名:┃┃\n\t\t\t\t\t->");
	scanf("%s", name);
	while (p)
	{
		if (strcmp(p->data.name, name) == 0)
			break;
		p = p->next;
	}
	if (!p)
	{
		printf(" \t\t\t\t\t ┃┃     此学生不存在！     ┃┃\n");
		printf(" \t\t\t\t\t ┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n");
	}
	else
	{
		printf(" \t\t\t\t\t ┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n");
		printf(" \t\t\t\t\t ┃┃        学生信息        ┃┃\n");
		printf(" \t\t\t\t\t ┃━━━━━━━━━━━━━━━━━━━━━━━━━━┃ \n");
		printf("\t\t\t\t\t   -学    号：%s\n", p->data.id);
		printf("\t\t\t\t\t   -姓    名：%s\n", p->data.name);
		printf("\t\t\t\t\t   -性    别：%s\n", p->data.sex);
		printf("\t\t\t\t\t   -C语言成绩：%d\n", p->data.CLanguage);
		printf("\t\t\t\t\t   -高数成绩：%d\n", p->data.Mathematics);
		printf("\t\t\t\t\t   -英语成绩:%d\n", p->data.English);
		printf("\t\t\t\t\t   -体育成绩:%d\n", p->data.PE);
		//printf("\t\t\t\t\t   -总    分：%d\n",p->data.Total);
		//printf("\t\t\t\t\t   -平 均 分：%.2f\n", p->data.Average);
		printf("\t\t\t\t\t ┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n");
	}
}
//（10）修改学生信息函数定义 
void UpdateStu()
{
	StuScoreNode* p = score;
	char id[MAX_ID];
	printf(" \t\t\t\t\t ┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n");
	printf(" \t\t\t\t\t ┃┃ 请输入要更新学生的学号:┃┃\n\t\t\t\t\t->");
	scanf("%s", id);

	while (p) //查找待修改结点
	{
		if (strcmp(p->data.id, id) == 0)
			break;
		p = p->next;
	}
	if (!p)
	{
		printf(" \t\t\t\t\t ┃┃     此学生不存在！     ┃┃\n");
		printf(" \t\t\t\t\t ┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n");
	}
	else
	{
		int type;
		while (1)
		{
			system("cls");
			printf(" \t\t\t\t\t ┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n");
			printf(" \t\t\t\t\t ┃┃        学生信息        ┃┃\n");
			printf(" \t\t\t\t\t ┃━━━━━━━━━━━━━━━━━━━━━━━━━━┃ \n");
			printf("\t\t\t\t\t   -学   号：%s\n", p->data.id);
			printf("\t\t\t\t\t   -姓   名：%s\n", p->data.name);
			printf("\t\t\t\t\t   -性   别：%s\n", p->data.sex);
			printf("\t\t\t\t\t   -C语言成绩：%d\n", p->data.CLanguage);
			printf("\t\t\t\t\t   -高数成绩：%d\n", p->data.Mathematics);
			printf("\t\t\t\t\t   -英语成绩：%d\n", p->data.English);
			printf("\t\t\t\t\t   -体育成绩:%d\n", p->data.PE);
			//printf("\t\t\t\t\t   -总   分：%d\n",  p->data.Total);
			printf(" \t\t\t\t\t ┃━━━━━━━━━━━━━━━━━━━━━━━━━━┃ \n");
			printf(" \t\t\t\t\t ┃    0 - 退 出             ┃\n");
			printf(" \t\t\t\t\t ┃    1 - 修 改 学 号       ┃\n");
			printf(" \t\t\t\t\t ┃    2 - 修 改 姓 名       ┃\n");
			printf(" \t\t\t\t\t ┃    3 - 修 改 性 别       ┃\n");
			printf(" \t\t\t\t\t ┃    4 - 修改C语言成绩     ┃\n");
			printf(" \t\t\t\t\t ┃    5 - 修改高数成绩      ┃\n");
			printf(" \t\t\t\t\t ┃    6 - 修改英语成绩      ┃\n");
			printf(" \t\t\t\t\t ┃    7 - 修改体育成绩      ┃\n");
			printf(" \t\t\t\t\t ┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n");
			printf("\t\t\t\t\t->选择修改项目：");
			scanf("%d", &type);
			if (type == 0)
				break;
			switch (type)
			{
			case UPDATE_ID:
				printf("\t\t\t\t\t->输入学号：");
				scanf("%s", p->data.id);
				break;
			case UPDATE_NAME:
				printf("\t\t\t\t\t->输入姓名：");
				scanf("%s", p->data.name);
				break;
			case UPDATE_SEX:
				printf("\t\t\t\t\t->输入性别：");
				scanf("%s", p->data.sex);
				break;
			case UPDATE_C:
				printf("\t\t\t\t\t->输入C语言成绩：");
				scanf("%d", &p->data.CLanguage);
				break;
			case UPDATE_MATH:
				printf("\t\t\t\t\t->输入高数成绩：");
				scanf("%d", &p->data.Mathematics);
				break;
			case UPDATE_ENG:
				printf("\t\t\t\t\t->输入英语成绩：");
				scanf("%d", &p->data.English);
				break;
			case UPDATE_PE:
				printf("\t\t\t\t\t->输入体育成绩：");
				scanf("%d", &p->data.PE);
				break;
			default:
				printf("\t\t\t\t\t输入错误！\n");
				system("pause");
				break;
			}
			if (type >= 4 && type <= 7)      //更新总成绩
				p->data.Total = p->data.CLanguage + p->data.Mathematics + p->data.English + p->data.PE;
			if (type >= 1 && type <= 7)
			{
				printf("\t\t\t\t\t修改成功！\n");
				system("pause");
			}

		}
	}
}
//（11）显示所有学生信息函数定义 
void OutputStu()
{
	int  i = 0;
	StuScoreNode* p = score;
	if (!p)  //链表为空
	{
		printf(" \t\t\t\t\t ┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n");
		printf(" \t\t\t\t\t ┃ 成绩管理系统中无学生记录 ┃\n");
		printf(" \t\t\t\t\t ┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n");
		return;
	}
	while (p)
	{
		printf(" \t\t\t\t\t ┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n");
		printf(" \t\t\t\t\t ┃         学生%d信息        ┃\n", ++i);
		printf(" \t\t\t\t\t ┃━━━━━━━━━━━━━━━━━━━━━━━━━━┃ \n");
		printf("\t\t\t\t\t    -学   号：%s\n", p->data.id);
		printf("\t\t\t\t\t    -姓   名：%s\n", p->data.name);
		printf("\t\t\t\t\t    -性   别：%s\n", p->data.sex);
		printf("\t\t\t\t\t    -C语言成绩：%d\n", p->data.CLanguage);
		printf("\t\t\t\t\t    -高数成绩：%d\n", p->data.Mathematics);
		printf("\t\t\t\t\t    -英语成绩：%d\n", p->data.English);
		printf("\t\t\t\t\t    -体育成绩:%d\n", p->data.PE);
		//printf("\t\t\t\t\t    -平 均 分：%.2f\n", p->data.Average);
		//printf("\t\t\t\t\t    -总   分：%d\n",  p->data.Total);
		printf(" \t\t\t\t\t ┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n");
		p = p->next;
	}

}
// （12）退出学生成绩管理系统函数定义 
void Exit()
{
	StuScoreNode* p = score;
	while (p)                        //释放每一结点内存空间 
	{
		score = p->next;
		free(p);
		p = score;
	}
}
// （13）从文件读出学生信息函数定义 
void ReadFile()
{
	StuScoreNode* p;
	char id[MAX_ID];
	FILE* pf = fopen("score.txt", "r");      //以读方式打开文件
	if (!pf) return;                      //打开文件失败
	//从文件中逐一读出每一联系人信息
	while (fscanf(pf, "%s", id) != EOF)
	{
		p = (StuScoreNode*)malloc(sizeof(StuScoreNode));
		strcpy(p->data.id, id);
		fscanf(pf, "%s", p->data.name);
		fscanf(pf, "%s", p->data.sex);
		fscanf(pf, "%d", &p->data.CLanguage);
		fscanf(pf, "%d", &p->data.Mathematics);
		fscanf(pf, "%d", &p->data.English);
		fscanf(pf, "%d", &p->data.PE);
		//fscanf(pf,"%.2f",&p->data.Average);
		//fscanf(pf,"%d",&p->data.Total);
		//将每一学生信息（结点）加入到链表中
		p->next = score;
		score = p;
		p = NULL;
	}
	fclose(pf);                        //关闭文件 
}
//（14）将学生信息写入文件函数定义 
void WriteFile()
{
	StuScoreNode* p = score;
	FILE* pf = fopen("score.txt", "w");                 //以写方式打开文件 
	if (!pf)return;                                 //打开文件失败 
	while (p)                                       //将链表中的每一结点（联系点）写入文件 
	{
		fprintf(pf, "%s\n", p->data.id);
		fprintf(pf, "%s\n", p->data.name);
		fprintf(pf, "%s\n", p->data.sex);
		fprintf(pf, "%d\n", p->data.CLanguage);
		fprintf(pf, "%d\n", p->data.Mathematics);
		fprintf(pf, "%d\n", p->data.English);
		fprintf(pf, "%d\n", p->data.PE);
		//fprintf(pf,"%.2f\n",p->data.Average);
		//fprintf(pf,"%d\n",p->data.Total);
		p = p->next;
	}
	fclose(pf);                                   //关闭文件 
}
//（15）查找学生是否存在其函数定义 
int FindStu(char* id)
{
	StuScoreNode* p = score;
	while (p)                                      //在链表中以学号方式查找某一联系人是否存在
	{
		if (strcmp(id, p->data.id) == 0)
			return 1;                                  //存在则返回 1
		p = p->next;
	}
	return 0;                                      //不存在则返回 
}
