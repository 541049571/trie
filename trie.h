/*************************************************************************
    > File Name: trie.h
    > Author: zwker
    > Mail: xiaoyu0720@gmail.com 
    > Created Time: 2016年09月03日 星期六 09时00分31秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

/* 同层节点最多数量 */
#define MAX_NODE_NUM  256

typedef struct trie_node_st
{
	void *value;/*匹配成功的value指针*/
	struct trie_node_st *next[MAX_NODE_NUM];
} trie_node_st; 


trie_node_st *root;

/*创建前缀树，空树 */
int trie_create( trie_node_st **root);

/*销毁前缀树*/
int trie_destory(trie_node_st *root);

int trie_insert( trie_node_st *root, char *str_key, void *value);

int trie_query( trie_node_st *root, char *str_key, trie_node_st **result);

