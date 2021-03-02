//
// Created by 嵇美伟 on 2021/2/18.
//

#include "avl_tree.h"


AVL_TREE_NODE_T *p_inital_node = NULL;
AVL_TREE_MNG_T *p_avl_tree_mng = NULL;

void avl_tree_init(void)
{
    p_avl_tree_mng = (AVL_TREE_MNG_T *)malloc(sizeof(AVL_TREE_MNG_T));
    COMM_CHECK_POINT(p_avl_tree_mng);

    //p_inital_node = (AVL_TREE_NODE_T *)malloc(sizeof(AVL_TREE_NODE_T));
    //COMM_CHECK_POINT(p_inital_node);

    p_avl_tree_mng->p_root_node = NULL;
    p_avl_tree_mng->is_init = 1;
    p_avl_tree_mng->node_num += 1;
}



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



/*后继，需要等到遍历完成*/
AVL_TREE_NODE_T* avl_tree_successor(void)
{
    AVL_TREE_NODE_T *p_tree_successor_node = NULL;

    assert(p_avl_tree_mng->is_init);
    return p_tree_successor_node;
}



/*前驱*/
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






/*avl树的旋转*/

/* 获取红黑树某个节点的平衡因子
 * 传参为节点的键值
 */
WORD32 avl_tree_node_balance_para_get(AVL_TREE_KEY_T *p_node_key)
{

}






