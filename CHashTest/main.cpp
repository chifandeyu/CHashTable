#include <CHashTable.h>
#include <iostream>
using namespace std;
#include <time.h>
#include <vector>
#include <hash_map>
struct Student
{
	int age;
	float score;
	char name[32];
};

static void free_student(void * pStudent)
{
	struct Student* stu = (struct Student*)pStudent;
	free(pStudent);
	//pStudent = nullptr;
}

static void showStudentInfo(struct Student* pStudent)
{
	if(NULL == pStudent)
		return;

	printf("姓名：%s, 年龄：%d, 学分: %.2f\n", pStudent->name, pStudent->age, pStudent->score);
}
int main()
{
	CHashTable* ht = NULL;
	clock_t startT;
	clock_t endT;
	startT = clock();
	ht  = hash_table_new();
	endT = clock();
	printf("new table time=%.0f ms\n", (double)(endT- startT));
	if(NULL == ht)
		return -1;

	startT = clock();
	for (int i=0; i<100000; i++)
	{
		struct Student *pstu = (struct Student*)malloc(sizeof(struct Student));
		pstu->age = 18 + rand() % 5;
		pstu->score = 50.0f + rand() % 100;
		sprintf_s(pstu->name, "student%d", i+1);
		//插入一个学生信息
		hash_table_put2(ht, pstu->name, pstu, free_student);
	}
	endT = clock();
	printf("put time=%.0f ms\n", (double)(endT- startT));

	for(int i = 0; i < 100000; i++)
	{
		char name[32];
		sprintf_s(name, "student%d", i+1);
		//获取一个学生信息
		struct Student* stu = (struct Student*)hash_table_get(ht, name);
		showStudentInfo(stu);
	}

	startT = clock();
	hash_table_delete(ht);
	endT = clock();
	printf("delete table time=%.0f ms\n", (double)(endT- startT));

	return 0;
}