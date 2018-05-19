// CHashTable.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "CHashTable.h"

#define TABLE_SIZE (1024*1024)

struct kv
{
	char* key;
	void* value;
	void(*free_value)(void*);
	struct kv* next;
};

struct CHashTable
{
	//stuct kv *[];//存着数组指针的数组（链表头节点）
	struct kv ** table;
};

/* the classic Times33 hash function */
static unsigned int hash_33(char* key)
{
	unsigned int hash = 0;
	while(*key)
	{
		hash = (hash << 5) + hash + *key++;
	}
	return hash;
}

static void init_kv(struct kv* pkv)
{
	pkv->next = NULL;
	pkv->key = NULL;
	pkv->value = NULL;
	pkv->free_value = NULL;
}

static void free_kv(struct kv* pkv)
{
	if (pkv) {
		if (pkv->free_value) {
			pkv->free_value(pkv->value);
		}
		free(pkv->key);
		pkv->key = NULL;
		free(pkv);
	}
}

_declspec(dllexport) CHashTable* hash_table_new()
{
	CHashTable* ht = (CHashTable*)malloc(sizeof(CHashTable));
	if(NULL == ht)
	{
		hash_table_delete(ht);
		return NULL;
	}
	ht->table = (struct kv **)malloc(sizeof(struct kv*) * TABLE_SIZE);
	if(NULL == ht->table)
	{
		hash_table_delete(ht);
		return NULL;
	}
	memset(ht->table, 0, sizeof(struct kv*) * TABLE_SIZE);

	return ht;
}

_declspec(dllexport) void hash_table_delete( CHashTable* ht )
{
	if(ht && ht->table)
	{
		for (unsigned int i=0; i<TABLE_SIZE; i++)
		{
			struct kv* pKv = ht->table[i];
			struct kv* pTemp = NULL;
			while(pKv) //遍历链表
			{
				pTemp = pKv->next;
				free_kv(pKv);
				pKv = pTemp;
			}
		}
		free(ht->table);
		ht->table = NULL;
		free(ht);
		ht = NULL;
	}
}

_declspec(dllexport) int hash_table_put2( CHashTable* ht, char* key, void* value, void(*free_value)(void*) )
{
	int index = getIndex(key);
	struct kv* pKv = ht->table[index];
	struct kv* pTemp = pKv;
	while(pKv)
	{
		if(strcmp(key, pKv->key) == 0)
		{
			if(pKv->free_value)
			{
				pKv->free_value(pKv->value);
			}
			pKv->value = value;
			pKv->free_value = free_value;
			break;
		}
		pTemp = pKv;
		pKv = pKv->next;
	}

	if(pKv == NULL)
	{
		char* kstr = (char*)malloc(strlen(key) + 1);
		if(NULL == kstr)
		{
			return -1;
		}
		struct kv* kkv = (struct kv*)malloc(sizeof(struct kv));
		if(NULL == kkv)
		{
			free(kstr);
			kstr = NULL;
			return -1;
		}
		init_kv(kkv);
		kkv->next = NULL;
		strcpy_s(kstr, strlen(key)+1, key);
		kkv->key = kstr;
		kkv->value = value;
		kkv->free_value = free_value;

		if(NULL == pTemp)
		{
			ht->table[index] = kkv;
		}
		else
		{
			pTemp->next = kkv;
		}
	}

	return 0;
}

_declspec(dllexport) void* hash_table_get( CHashTable* ht, char* key )
{
	int index = getIndex(key);
	struct kv* pKv = ht->table[index];
	while(pKv)
	{
		if(strcmp(key, pKv->key) == 0)
		{
			return pKv->value;
		}
		pKv = pKv->next;
	}
	return NULL;
}

void hash_table_remove( CHashTable* ht, char* key )
{
	int index = getIndex(key);
	struct kv* pKv = ht->table[index];
	struct kv* pTemp = pKv;
	while(pKv)
	{
		if(strcmp(key, pKv->key) == 0)
		{
			free_kv(pKv);
			if(pKv == pTemp)
			{
				ht->table[index] = NULL;
			}
			else
			{
				pTemp->next = pKv->next;
			}
		}
		pTemp = pKv;
		pKv = pKv->next;
	}
}

unsigned int getIndex( char* key )
{
	unsigned int hashValue = hash_33(key);
	return hashValue % TABLE_SIZE;
}
