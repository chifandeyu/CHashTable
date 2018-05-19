// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� CHASHTABLE_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// CHASHTABLE_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef CHASHTABLE_EXPORTS
#define CHASHTABLE_API __declspec(dllexport)
#else
#define CHASHTABLE_API __declspec(dllimport)
#endif

#pragma once
typedef struct CHashTable CHashTable;

#ifdef _cplusplus
extern "C"{
#endif
//////////////////////////////////////////////////////////////////////////
	//������ϣ��
	CHASHTABLE_API CHashTable* hash_table_new();
	//ɾ����ϣ��
	CHASHTABLE_API void hash_table_delete(CHashTable* ht);
	//����һ������
	CHASHTABLE_API int hash_table_put2(CHashTable* ht, char* key, void* value, void(*free_value)(void*));
	//��ȡһ������
	CHASHTABLE_API void* hash_table_get(CHashTable* ht, char* key);
	//ɾ��һ������
	CHASHTABLE_API void hash_table_remove(CHashTable* ht, char* key);
	unsigned int getIndex(char* key);
//////////////////////////////////////////////////////////////////////////
#ifdef _cplusplus
};
#endif