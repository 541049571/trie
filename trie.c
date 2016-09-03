/*************************************************************************
    > File Name: trie.c
    > Author: zwker
    > Mail: xiaoyu0720@gmail.com 
    > Created Time: 2016年09月03日 星期六 09时18分57秒
 ************************************************************************/

#include "trie.h"
#include <assert.h>



/*创建前缀树，空树 */
int trie_create( trie_node_st **root)
{
	int l_ret = 0;

	if( *root == NULL )
		*root = (trie_node_st *)malloc( sizeof(trie_node_st) );
	memset( *root, 0 , sizeof(trie_node_st));
	return l_ret;
}

/*销毁前缀树*/
int trie_destory(trie_node_st *root)
{
	int l_ret = 0;
	int i = 0;
	trie_node_st *l_ptr = root;
	for( i = 0; i < MAX_NODE_NUM ; i++ )
	{
		if( l_ptr->next[i] != NULL )
		{
			l_ret = trie_destory( l_ptr->next[i] );
			l_ptr->next[i] = NULL;
		}
	}
	free( l_ptr );
	return l_ret;
}

int trie_insert( trie_node_st *root, char *str_key, void *value)
{
	/*
		1. 根据str_key 创建前缀树路径 
		2. 创建路径后将value记录
	*/

	char *ch;
	int l_ret = 0;
	trie_node_st *l_ptr,*l_tmp_trie;

	if( root == NULL )
		return -1;

	l_ptr = root;
	for( ch = str_key; *ch ; ++ch )
	{
		assert(( *ch >= 0) && (*ch < MAX_NODE_NUM ) );
		if( l_ptr->next[*ch] == NULL )
		{
			l_tmp_trie = (trie_node_st *)malloc( sizeof(trie_node_st));
			l_ptr->next[*ch] = l_tmp_trie;
		}
		l_ptr = l_ptr->next[*ch];
	}

	if( *ch == '\0' )
	{
		l_ptr->value = value;
	}

	return l_ret;
}


int trie_query( trie_node_st *root, char *str_key, trie_node_st **result)
{
	/*
		1.查找str_key，并返回查找结果
	*/
	int l_ret = 0;
	char *ch;

	trie_node_st *l_ptr = root;

	for( ch = str_key ; *ch ; ++ch )
	{
		if( l_ptr->next[*ch] == NULL )
		{
			break;
		}
		l_ptr = l_ptr->next[ *ch ] ;
	}
	if( *ch == '\0' )
	{
		*result = l_ptr;
		l_ret = 0;/*完全匹配*/
	}
	else if( l_ptr->next[ *ch ] == NULL )
	{
		*result = l_ptr;
		l_ret = (int )(ch - str_key) ;/*部分匹配成功*/
	}
	return l_ret;
}


void print_trie_node( trie_node_st *node)
{
	int i = 0;
	if( node != NULL )
	{
		printf("value:%d\n", (int )(node->value));
		for( i = 0; i < MAX_NODE_NUM ; i++)
		{
			if( node->next[i] != NULL )
			{
				printf("key:%c,",i);
				print_trie_node( node->next[i]);
			}
		}
	}
}

int main( int argc , char **argv)
{
	trie_node_st  *result;

	root = NULL;

	trie_create( &root );

	char l_buf[1024] ;
	

	strcpy( l_buf ,"Hello");
	trie_insert( root , l_buf , (void *) 1 );

	strcpy( l_buf ,"world");
	trie_insert( root , l_buf , (void *) 2 );
	strcpy( l_buf ,"Hellg");
	trie_insert( root , l_buf , (void *) 3 );

	strcpy(l_buf , "Helto");
	int l_ret = trie_query( root , l_buf , &result );
	if( l_ret >= 0 )
	{
		if( l_ret > 0 ) 
			l_buf[ l_ret ] = '\0';
		printf("ret:%d, match:%s\n",l_ret, l_buf );
		print_trie_node( result );
	}
	strcpy(l_buf , "world");
	l_ret = trie_query( root , l_buf , &result );
	if( l_ret >= 0 )
	{
		if( l_ret > 0 ) 
			l_buf[ l_ret ] = '\0';
		printf("ret:%d, match:%s\n",l_ret, l_buf );
		print_trie_node( result );
	}
	printf("----root---\n");
	print_trie_node( root );
	trie_destory( root );
	return 0;
}
