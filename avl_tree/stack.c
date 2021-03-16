//
// Created by 嵇美伟 on 2021/3/11.
//


#include "stack.h"
#include "comm.h"
#include "avl_tree.h"

char init_node_strs[10] = "init_node";
STACK_MNG_T* g_stack_mng_t = NULL;


/* 获取管理结构
 * */
STACK_MNG_T* stack_mng_ctrl_get(void)
{
	return g_stack_mng_t;
}


/* 将树的节点作为栈节点的信息传入
 * */
AVL_TREE_NODE_T* stack_node_content_init(void* p_stack_content)
{
	COMM_CHECK_POINT(p_stack_content);

	return (AVL_TREE_NODE_T*)p_stack_content;
}

/* 初始化栈的首节点
 * */
WORD32 stack_root_node_content_init(void* p_stack_content)
{
	COMM_CHECK_POINT(g_stack_mng_t);
	assert(g_stack_mng_t->is_init);

	g_stack_mng_t->p_stack_root_node->p_stack_content = g_stack_mng_t;

	return COMM_OK;
}


/* 栈初始化
 * */
WORD32 stack_mng_init(void)
{
	STACK_NODE_T *p_root_node = NULL;

	g_stack_mng_t = (STACK_MNG_T *) malloc(sizeof(STACK_MNG_T));
	COMM_CHECK_POINT(g_stack_mng_t);

	p_root_node = (STACK_NODE_T *) malloc(sizeof(STACK_NODE_T));
	COMM_CHECK_POINT(p_root_node);
	p_root_node->p_stack_content = (void *) init_node_strs;
	p_root_node->p_down = NULL;

	g_stack_mng_t->is_init = 1;
	g_stack_mng_t->p_stack_root_node = p_root_node;
	g_stack_mng_t->node_num += 1;

	return COMM_OK;
}




/* 压栈
 * */
WORD32 stack_node_push(void *p_node_content)
{

	STACK_NODE_T *p_first_node = NULL;
	STACK_NODE_T *p_stack_push_node = NULL;

	p_stack_push_node = (STACK_NODE_T *) malloc(sizeof(STACK_NODE_T));
	COMM_CHECK_POINT(p_stack_push_node);
	p_stack_push_node->p_stack_content = (void*)stack_node_content_init(p_node_content);
	p_stack_push_node->p_upper = NULL;

	p_first_node = stack_fisrt_node_get();

	p_stack_push_node->p_down = p_first_node;
	p_first_node->p_upper = p_stack_push_node;
	g_stack_mng_t->node_num += 1;

	return COMM_OK;
}


/* 返回栈顶节点
 * */
STACK_NODE_T* stack_fisrt_node_get(void)
{
	WORD32 loop_num = 0;
	STACK_NODE_T *p_first_node = NULL;

	COMM_CHECK_POINT(g_stack_mng_t);
	assert(g_stack_mng_t->is_init);

	p_first_node = g_stack_mng_t->p_stack_root_node;
	loop_num = g_stack_mng_t->node_num;

	while(loop_num > 1)
	{
		loop_num -= 1;
		p_first_node = p_first_node->p_upper;
	}

	return p_first_node;
}



/* 出栈
 * */
STACK_NODE_T * stack_node_pop()
{
	WORD32 loop_num = 0;
	STACK_NODE_T *p_first_node = NULL;

	COMM_CHECK_POINT(p_first_node);
	COMM_CHECK_POINT(g_stack_mng_t);
	assert(g_stack_mng_t->is_init);

	p_first_node = stack_fisrt_node_get();

	p_first_node->p_down->p_upper = NULL;
	g_stack_mng_t->node_num -= 1;

	return p_first_node;
}