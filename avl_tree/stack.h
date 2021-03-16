//
// Created by 嵇美伟 on 2021/3/11.
//

#ifndef AVL_TREE__STACK_H_
#define AVL_TREE__STACK_H_

#include "comm.h"
#include "avl_tree.h"
/*栈先进后出*/

#define STACK_RTN_CODE              (0x20000)
#define STACK_RTN_ONLY_ONE_NODE     (0x20000 | 0x1)


typedef struct stack_node_t
{
    struct stack_node_t *p_upper;
    struct stack_node_t *p_down;
    void* p_stack_content;
}STACK_NODE_T;


typedef struct stack_mng_t
{
  WORD32 node_num;
  WORD32 is_init;
  STACK_NODE_T *p_stack_root_node;
}STACK_MNG_T;


typedef struct stack_init_node_content_t
{
    char* p_root_str;
}STACK_INIT_NODE_CONTENT_T;


/* 获取管理结构
 * */
STACK_MNG_T* stack_mng_ctrl_get(void);


/* 将树的节点作为栈节点的信息传入
 * */
AVL_TREE_NODE_T* stack_node_content_init(void* p_stack_content);


/* 初始化栈的首节点
 * */
WORD32 stack_root_node_content_init(void* p_stack_content);

/* 栈管理结构初始化
 * */
WORD32 stack_mng_init(void);

/* 压栈
 * */
WORD32 stack_node_push(void *p_node_content);


/* 返回栈顶节点
 * */
STACK_NODE_T* stack_fisrt_node_get(void);


/* 出栈
 * */
STACK_NODE_T * stack_node_pop(void);


#endif //AVL_TREE__STACK_H_
