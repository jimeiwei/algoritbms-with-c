//
// Created by 嵇美伟 on 2021/2/18.
//

#include "avl_tree.h"
#include "stack.h"
#include "comm.h"

AVL_TREE_NODE_T *p_inital_node = NULL;
AVL_TREE_MNG_T *p_avl_tree_mng = NULL;



/** 红黑树初始化
 * @param   :
 * @auther  : jimw
 * @return  : TT_OK: 成功 TT_ERR: 失败
 * @data    :
 * @remark  :
 */
WORD32 avl_tree_init(void)
{
	WORD32 rtn = 0;

	if(p_avl_tree_mng->is_init)
	{
		printf("Tree mng is init already\n");
		return COMM_OK;
	}
    p_avl_tree_mng = (AVL_TREE_MNG_T *)malloc(sizeof(AVL_TREE_MNG_T));
    COMM_CHECK_POINT(p_avl_tree_mng);

    p_avl_tree_mng->p_root_node = NULL;
    p_avl_tree_mng->is_init = 1;
    p_avl_tree_mng->node_num += 1;

	rtn = stack_mng_init();
	COMM_CHECK_RC(rtn);
	return COMM_OK;
}



/** 节点对比
 * @param   :
 * @auther  : jimw
 * @return  : TT_OK: 成功 TT_ERR: 失败
 * @data    :
 * @remark  :
 */
WORD32 avl_tree_compare(AVL_TREE_NODE_T *p_tree_node, AVL_TREE_KEY_T *p_node_key)
{
    SWORD32 rc = 0;
    AVL_TREE_KEY_T *p_tree_node_key = NULL;
    AVL_TREE_KEY_T *p_input_node_key = NULL;

    COMM_CHECK_POINT(p_tree_node);
    COMM_CHECK_POINT(p_node_key);
    assert(p_avl_tree_mng->is_init);

    p_tree_node_key = (AVL_TREE_KEY_T *)(p_tree_node->p_node_key);
    p_input_node_key = p_node_key;

    rc = memcmp(p_input_node_key, p_tree_node_key, sizeof(AVL_TREE_KEY_T));

    if (rc < 0)
    {
        return AVL_TREE_SEARCH_LEFT;
    }
    else if(rc > 0)
    {
        return AVL_TREE_SEARCH_RIGHT;
    }
    else
    {
        return AVL_TREE_SEARCH_EQUAL;
    }
}

/** 根据键值查找节点
 * @param   :
 * @auther  : jimw
 * @return  : TT_OK: 成功 TT_ERR: 失败
 * @data    :
 * @remark  :
 */
AVL_TREE_NODE_T* avl_tree_search(AVL_TREE_KEY_T *p_node_key)
{
    WORD32 rc = 0;
    AVL_TREE_NODE_T *p_tree_node = NULL;

    assert(p_avl_tree_mng->is_init);
    COMM_CHECK_POINT(p_node_key);

    p_tree_node = p_inital_node;

    while(p_tree_node != NULL)
    {
        rc = avl_tree_compare(p_tree_node->p_node_key, p_node_key);

        if(rc == AVL_TREE_SEARCH_EQUAL)
        {
            break;
        }
        else if (rc == AVL_TREE_SEARCH_LEFT)
        {
            p_tree_node = p_tree_node->p_left;
        }
        else
        {
            p_tree_node = p_tree_node->p_right;
        }
    }

    return p_tree_node;
}

/**
 * @param   :
 * @auther  : jimw
 * @return  : TT_OK: 成功 TT_ERR: 失败
 * @data    :
 * @remark  :
 */
AVL_TREE_NODE_T* avl_tree_minumin(void)
{
    AVL_TREE_NODE_T *p_tree_left_node = NULL;

    assert(p_avl_tree_mng->is_init);

    p_tree_left_node = p_tree_left_node->p_left;
    while(p_tree_left_node->p_left != NULL)
    {
        p_tree_left_node = p_tree_left_node->p_left;
    }

    return p_tree_left_node;
}



AVL_TREE_NODE_T* avl_tree_maximun(void)
{
    AVL_TREE_NODE_T *p_tree_right_node = NULL;

    assert(p_avl_tree_mng->is_init);

    p_tree_right_node = p_tree_right_node->p_left;
    while(p_tree_right_node->p_right != NULL)
    {
        p_tree_right_node = p_tree_right_node->p_right;
    }

    return p_tree_right_node;
}



/** 获取后继节点
 * @param   :
 * @auther  : jimw
 * @return  : TT_OK: 成功 TT_ERR: 失败
 * @data    :
 * @remark  :
 */
AVL_TREE_NODE_T* avl_tree_successor(AVL_TREE_KEY_T *p_node_key)
{
    AVL_TREE_NODE_T *p_tree_successor_node = NULL;
    AVL_TREE_NODE_T *p_tree_searched_node = NULL;

	COMM_CHECK_POINT(p_node_key);

	assert(p_avl_tree_mng->is_init);
	p_tree_searched_node = avl_tree_search(p_node_key);

	if(p_tree_searched_node != NULL)
	{
		if(p_tree_searched_node->p_right != NULL)
		{
			p_tree_successor_node = p_tree_searched_node->p_right;
		}
		else
		{
			if(p_avl_tree_mng->p_root_node->p_right != NULL)
			{
				p_tree_successor_node = p_avl_tree_mng->p_root_node->p_right;
			}
		}
	}

	/*没有找到节点，返回空节点*/
    return p_tree_successor_node;
}

/** 前驱
 * @param   :
 * @auther  : jimw
 * @return  : TT_OK: 成功 TT_ERR: 失败
 * @data    :
 * @remark  :
 */
AVL_TREE_NODE_T* avl_tree_predecessor(AVL_TREE_KEY_T *p_node_key)
{
    WORD32 rc = 0;
    AVL_TREE_NODE_T  *p_avl_tree_curr_node = NULL;      /*key值所对应的节点*/

    assert(p_avl_tree_mng->is_init);
    COMM_CHECK_POINT(p_node_key);

    p_avl_tree_curr_node = avl_tree_search(p_node_key);

    if(p_avl_tree_curr_node != NULL && p_avl_tree_curr_node->p_parent != NULL)
    {
        return p_avl_tree_curr_node->p_parent;
    }
    else
    {
        return NULL;
    }
}






/** 插入节点
 * @param   :
 * @auther  : jimw
 * @return  : TT_OK: 成功 TT_ERR: 失败
 * @data    :
 * @remark  :
 */
WORD32 avl_tree_insert(AVL_TREE_KEY_T *p_node_key)
{
    WORD32 rc = 0;
    AVL_TREE_NODE_T *p_avl_tree_insert_node = NULL;
    AVL_TREE_NODE_T *p_avl_tree_curr_parent_node = NULL;
    AVL_TREE_NODE_T *p_avl_tree_curr_node = NULL;

    COMM_CHECK_POINT(p_node_key);
    assert(p_avl_tree_mng->is_init);

    p_avl_tree_insert_node = (AVL_TREE_NODE_T *)malloc(sizeof(AVL_TREE_NODE_T));
    COMM_CHECK_POINT(p_avl_tree_insert_node);
    memcpy(p_avl_tree_insert_node->p_node_key, p_node_key, sizeof(AVL_TREE_KEY_T));
	p_avl_tree_insert_node->p_left  = NULL;
	p_avl_tree_insert_node->p_right = NULL;

	p_avl_tree_curr_node = p_avl_tree_mng->p_root_node;
	if (p_avl_tree_curr_node == NULL)
	{
		/*empty tree*/
		p_avl_tree_mng->p_root_node = p_avl_tree_insert_node;
		p_avl_tree_insert_node->p_parent = NULL;

		return AVL_TREE_INSERT_SUCC_ROOT;
	}
	else
	{
		while (p_avl_tree_curr_node != NULL)
		{
			p_avl_tree_curr_parent_node = p_avl_tree_curr_node;

			rc = avl_tree_compare(p_avl_tree_curr_parent_node->p_node_key, p_avl_tree_insert_node->p_node_key);
			if(rc == AVL_TREE_SEARCH_LEFT)
			{
				p_avl_tree_curr_node = p_avl_tree_curr_parent_node->p_left;
			}
			else if (rc == AVL_TREE_SEARCH_RIGHT)
			{
				p_avl_tree_curr_node = p_avl_tree_curr_parent_node->p_right;
			}
			else        /*相同节点，更新*/
			{
				return AVL_TREE_INSERT_UPDATE;
			}
		}

		if(rc == AVL_TREE_SEARCH_RIGHT)
		{
			p_avl_tree_curr_parent_node->p_right = p_avl_tree_insert_node;

			return AVL_TREE_INSERT_SUCC_RIGHT;
		}
		else
		{
			p_avl_tree_curr_parent_node->p_left = p_avl_tree_insert_node;

			return AVL_TREE_INSERT_SUCC_LEFT;
		}
	}
}





/** 前序遍历，非递归方法
 * @param   :
 * @auther  : jimw
 * @return  : TT_OK: 成功 TT_ERR: 失败
 * @data    :
 * @remark  :
 */
WORD32 avl_tree_pre_order_traveral(AVL_TREE_PRE_ORDER_FUN p_pre_opder_fun, void* p_key1, void* p_fun_rtn)
{
	WORD32 rtn = 0;
	AVL_TREE_NODE_T *p_left_child_node = NULL;
	AVL_TREE_NODE_T *p_left_child_node_poped = NULL;
	STACK_NODE_T *p_stack_node_poped = NULL;
	STACK_MNG_T *p_stack_ctrl = NULL;
	AVL_TREE_KEY_T *p_avl_tree_key = NULL;

	COMM_CHECK_POINT(p_fun_rtn);
	COMM_CHECK_POINT(p_key1);
	COMM_CHECK_POINT(p_avl_tree_mng);
	COMM_CHECK_POINT(p_pre_opder_fun);
	assert(p_avl_tree_mng->is_init);
	assert(p_avl_tree_mng->p_root_node);

	p_left_child_node = p_avl_tree_mng->p_root_node->p_left;

	/*遍历左子树*/
	while (p_left_child_node != NULL)
	{
		rtn = stack_node_push((void*) p_left_child_node);
		COMM_CHECK_RC(rtn);

		p_left_child_node = p_left_child_node->p_left;
	}
	p_stack_ctrl = stack_mng_ctrl_get();
	COMM_CHECK_POINT(p_stack_ctrl);

	while(p_stack_ctrl->node_num > 1)
	{
		p_stack_node_poped = stack_node_pop();
		COMM_CHECK_POINT(p_stack_node_poped);

		p_left_child_node_poped = (AVL_TREE_NODE_T*)p_stack_node_poped->p_stack_content;
		COMM_CHECK_POINT(p_stack_node_poped);

		/*调用传入的函数指针*/
		p_avl_tree_key = (AVL_TREE_KEY_T *)p_key1;
		p_pre_opder_fun(p_avl_tree_key, p_left_child_node_poped->p_node_key, p_fun_rtn);

		if (p_left_child_node_poped->p_right != NULL)
		{
			p_left_child_node = p_left_child_node_poped->p_right;

			while (p_left_child_node != NULL)
			{
				rtn = stack_node_push((void*) p_left_child_node);
				COMM_CHECK_RC(rtn);

				p_left_child_node = p_left_child_node->p_left;
			}
		}
	}

	p_left_child_node = p_avl_tree_mng->p_root_node->p_right;
	/*遍历右子树*/
	while (p_left_child_node != NULL)
	{
		rtn = stack_node_push((void*) p_left_child_node);
		COMM_CHECK_RC(rtn);

		p_left_child_node = p_left_child_node->p_left;
	}

	p_stack_ctrl = stack_mng_ctrl_get();
	COMM_CHECK_POINT(p_stack_ctrl);

	while(p_stack_ctrl->node_num > 1)
	{
		p_stack_node_poped = stack_node_pop();
		COMM_CHECK_POINT(p_stack_node_poped);

		p_left_child_node_poped = (AVL_TREE_NODE_T*)p_stack_node_poped->p_stack_content;
		COMM_CHECK_POINT(p_stack_node_poped);

		/*调用传入的函数指针*/
		p_avl_tree_key = (AVL_TREE_KEY_T *)p_key1;
		p_pre_opder_fun(p_avl_tree_key, p_left_child_node_poped->p_node_key, p_fun_rtn);

		if (p_left_child_node_poped->p_right != NULL)
		{
			p_left_child_node = p_left_child_node_poped->p_right;

			while (p_left_child_node != NULL)
			{
				rtn = stack_node_push((void*) p_left_child_node);
				COMM_CHECK_RC(rtn);

				p_left_child_node = p_left_child_node->p_left;
			}
		}
	}

	return COMM_OK;
}




/** 中序遍历
 * @param   :
 * @auther  : jimw
 * @return  : TT_OK: 成功 TT_ERR: 失败
 * @data    :
 * @remark  : 为了获取平衡因子
 */
WORD32 avl_tree_level_order_traveral(AVL_TREE_KEY_T *p_node_key, WORD32 *p_left_level, WORD32 *p_right_level)
{
	WORD32 rtn = 0;
	WORD32 i   = 0;
	WORD32 tree_left_level  = 0;
	WORD32 tree_right_level = 0;
	WORD32 level_node_num = 0;
	WORD32 loop_level_node_num = 0;
	AVL_TREE_NODE_T *p_searched_child_node  = NULL;
	AVL_TREE_NODE_T *p_left_child_node  = NULL;
	AVL_TREE_NODE_T *p_right_child_node = NULL;
	AVL_TREE_NODE_T *p_left_child_node_poped  = NULL;
	AVL_TREE_NODE_T *p_right_child_node_poped = NULL;
	STACK_NODE_T *p_stack_node_poped = NULL;

	assert(p_avl_tree_mng->is_init);
	assert(p_avl_tree_mng->p_root_node);
	COMM_CHECK_POINT(p_node_key);
	COMM_CHECK_POINT(p_left_level);
	COMM_CHECK_POINT(p_right_level);

	p_searched_child_node = avl_tree_search(p_node_key);

	p_left_child_node = p_searched_child_node->p_left;
	if(p_left_child_node == NULL)
	{
		tree_left_level = 0;
	}
	else
	{
		if(p_left_child_node->p_left)
		{
			loop_level_node_num += 1;
			rtn  = stack_node_push((void*) p_left_child_node->p_left);
			COMM_CHECK_RC(rtn);
		}

		if(p_left_child_node->p_right)
		{
			loop_level_node_num += 1;
			rtn  = stack_node_push((void*) p_left_child_node->p_right);
			COMM_CHECK_RC(rtn);
		}

		/*遍历左子树*/
		while (1)
		{
			tree_left_level += 1;

			for (i = 0; i < loop_level_node_num; i++)
			{
				p_stack_node_poped = stack_node_pop();
				COMM_CHECK_POINT(p_stack_node_poped);

				p_left_child_node_poped = (AVL_TREE_NODE_T*)p_stack_node_poped->p_stack_content;
				COMM_CHECK_POINT(p_stack_node_poped);

				if(p_left_child_node->p_left)
				{
					level_node_num += 1;
					rtn  = stack_node_push((void*) p_left_child_node->p_left);
					COMM_CHECK_RC(rtn);
				}

				if(p_left_child_node->p_right)
				{
					level_node_num += 1;
					rtn  = stack_node_push((void*) p_left_child_node->p_right);
					COMM_CHECK_RC(rtn);
				}
			}

			if(level_node_num == 0)
			{
				break;
			}

			loop_level_node_num = level_node_num;
			level_node_num = 0;
		}
	}
	*p_left_level = tree_left_level;

	p_right_child_node = p_searched_child_node->p_right;
	if(p_right_child_node == NULL)
	{
		tree_right_level = 0;
	}
	else
	{
		if(p_right_child_node->p_right)
		{
			loop_level_node_num += 1;
			rtn  = stack_node_push((void*) p_right_child_node->p_right);
			COMM_CHECK_RC(rtn);
		}

		if(p_right_child_node->p_right)
		{
			loop_level_node_num += 1;
			rtn  = stack_node_push((void*) p_right_child_node->p_right);
			COMM_CHECK_RC(rtn);
		}

		/*遍历左子树*/
		while (1)
		{
			tree_right_level += 1;

			for (i = 0; i < loop_level_node_num; i++)
			{
				p_stack_node_poped = stack_node_pop();
				COMM_CHECK_POINT(p_stack_node_poped);

				p_right_child_node_poped = (AVL_TREE_NODE_T*)p_stack_node_poped->p_stack_content;
				COMM_CHECK_POINT(p_stack_node_poped);

				if(p_right_child_node->p_right)
				{
					level_node_num += 1;
					rtn  = stack_node_push((void*) p_right_child_node->p_right);
					COMM_CHECK_RC(rtn);
				}

				if(p_right_child_node->p_right)
				{
					level_node_num += 1;
					rtn  = stack_node_push((void*) p_right_child_node->p_right);
					COMM_CHECK_RC(rtn);
				}
			}

			if(level_node_num == 0)
			{
				break;
			}

			loop_level_node_num = level_node_num;
			level_node_num = 0;
		}
	}
	*p_right_level = tree_right_level;

	return COMM_OK;
}




/** 获取红黑树某个节点的平衡因子
 * @param   : 传参为节点的键值
 * @auther  : jimw
 * @return  : TT_OK: 成功 TT_ERR: 失败
 * @data    :
 * @remark  : 节点从左算，到某个叶子节点最长路径为左深度，往右算为右深度，平衡因子 = 右深度 - 左深度
 */
WORD32 avl_tree_node_balance_para_get(AVL_TREE_KEY_T *p_node_key, WORD32* p_balance_para)
{
	WORD32 rtn = 0;
	WORD32 tree_left_depth  = 0;
	WORD32 tree_right_depth = 0;
	AVL_TREE_NODE_T *p_search_node = NULL;

	COMM_CHECK_POINT(p_node_key);
	COMM_CHECK_POINT(p_balance_para);

	rtn = avl_tree_level_order_traveral(p_node_key, &tree_left_depth, &tree_right_depth);
	COMM_CHECK_RC(rtn);

	*p_balance_para = tree_right_depth - tree_left_depth;

	return COMM_OK;
}






