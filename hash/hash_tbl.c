//
// Created by 嵇美伟 on 2021/2/27.
//

#include "hash_tbl.h"

//typedef void (*hash_key_fun)(WORD32*, WORD32*);

HASH_TBL_MNG *g_hash_tbl_mng = NULL;
HASH_BUCKET_BUFF *p_hash_bucket_list = NULL;   /*hash 每个桶首节点组成的列表，每个索引所指向的为每个桶的首节点*/


/*初始化*/
WORD32 hash_tbl_init(HASH_TBL_MNG* p_init_buff)
{
	WORD32 i = 0;
	HASH_BUCKET_BUFF *p_hash_bucket_buff = NULL;
	COMM_CHECK_POINT(p_init_buff);

	g_hash_tbl_mng = (HASH_TBL_MNG*)malloc(sizeof(HASH_TBL_MNG));
	COMM_CHECK_POINT(g_hash_tbl_mng);

	if(g_hash_tbl_mng->is_init)
	{
		return COMM_OK;
	}
	else
	{
		g_hash_tbl_mng->is_init = 1;
	}
	g_hash_tbl_mng->element_num  = p_init_buff->element_num;
	g_hash_tbl_mng->hash_confict_fun = p_init_buff->hash_confict_fun;
	g_hash_tbl_mng->hash_key_fun = p_init_buff->hash_key_fun;
	g_hash_tbl_mng->hash_tbl_num = p_init_buff->hash_tbl_num;
	g_hash_tbl_mng->hash_tbl_destroy_fun = p_init_buff->hash_tbl_destroy_fun;
	g_hash_tbl_mng->bucket_size  = p_init_buff->element_num / p_init_buff->hash_tbl_num;

	p_hash_bucket_list = (HASH_BUCKET_BUFF*)malloc(sizeof(HASH_BUCKET_BUFF) * g_hash_tbl_mng->bucket_size);
	COMM_CHECK_POINT(p_hash_bucket_list);

	return COMM_OK;
}



/*销毁hash表*/
void hash_tbl_destroy(void)
{
	WORD32 i = 0;
	HASH_BUCKET_BUFF *p_currrent_node = NULL;
	HASH_BUCKET_BUFF *p_init_node = NULL;
	HASH_BUCKET_BUFF *p_before_node = NULL;


	if(g_hash_tbl_mng->is_init)
	{
		for (i = 0; i < g_hash_tbl_mng->bucket_size; i++)
		{
			p_currrent_node = p_hash_bucket_list + i;
			p_init_node = p_hash_bucket_list + i;

			while(p_currrent_node->p_next != NULL)
			{
				p_currrent_node = p_currrent_node->p_next;
			}

			if (p_init_node->p_next == NULL)
			{
				continue;
			}
			p_before_node = p_init_node->p_next;

			while ( memcmp(p_init_node, p_before_node, sizeof(HASH_BUCKET_BUFF)) != 0 )
			{
				p_currrent_node = p_before_node;
				p_before_node = p_currrent_node->p_before;
				free(p_currrent_node);
			}
		}
		free(g_hash_tbl_mng);
		free(p_hash_bucket_list);

		printf("what malloc in hash tbl have freed!\n");
	}
}



/*hash key 计算公式,乘法*/
void hash_tbl_key_fun(WORD32* p_put_key, WORD32* p_hash_index)
{
	COMM_CHECK_POINT(p_put_key);
	COMM_CHECK_POINT(p_hash_index);
	COMM_CHECK_POINT(g_hash_tbl_mng);

	*p_hash_index = 0.618 * (*(double*)(p_put_key)) + g_hash_tbl_mng->hash_tbl_num;
}



/*hash key 冲突解决方法,线性探测再散列，即将 key+1 在除表长（即每个桶的深度）*/
void hash_tbl_key_conflic_fun(const WORD32* p_put_key, WORD32* p_hash_index, HASH_BUCKET_BUFF* p_bucket_init_node)
{
	COMM_CHECK_POINT(p_put_key);
	COMM_CHECK_POINT(p_hash_index);
	COMM_CHECK_POINT(g_hash_tbl_mng);
	COMM_CHECK_POINT(p_bucket_init_node);


}



WORD32 hash_tbl_key_insert(void* p_put_key, void* p_concent, size_t size_of_content)
{
	WORD32 hash_tbl_index = 0;
	HASH_BUCKET_BUFF *p_currrent_node = NULL;
	HASH_BUCKET_BUFF *p_insert_hash_node = NULL;

	COMM_CHECK_POINT(p_put_key);
	COMM_CHECK_POINT(p_concent);
	COMM_CHECK_POINT(p_hash_bucket_list);

	if(g_hash_tbl_mng->is_init)
	{
		g_hash_tbl_mng->hash_key_fun( (WORD32*)p_put_key, &hash_tbl_index);
		p_currrent_node = p_hash_bucket_list + hash_tbl_index;

		while(p_currrent_node->p_next != NULL)
		{
			p_currrent_node = p_currrent_node->p_next;
		}

		p_insert_hash_node = (HASH_BUCKET_BUFF*)malloc(sizeof(HASH_BUCKET_BUFF));
		p_insert_hash_node->p_next = NULL;
		p_currrent_node->p_next = p_insert_hash_node;
		p_insert_hash_node->p_before = p_currrent_node;

		memcpy(p_insert_hash_node->content, p_concent, size_of_content);
	}
	else
	{
		return COMM_ERR;
	}

	return COMM_ERR;
}





