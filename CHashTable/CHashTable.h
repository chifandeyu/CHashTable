// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 CHASHTABLE_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// CHASHTABLE_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
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
	//创建哈希表
	CHASHTABLE_API CHashTable* hash_table_new();
	//删除哈希表
	CHASHTABLE_API void hash_table_delete(CHashTable* ht);
	//插入一个对象
	CHASHTABLE_API int hash_table_put2(CHashTable* ht, char* key, void* value, void(*free_value)(void*));
	//获取一个对象
	CHASHTABLE_API void* hash_table_get(CHashTable* ht, char* key);
	//删除一个对象
	CHASHTABLE_API void hash_table_remove(CHashTable* ht, char* key);
	unsigned int getIndex(char* key);
//////////////////////////////////////////////////////////////////////////
#ifdef _cplusplus
};
#endif