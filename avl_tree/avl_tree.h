//
// Created by 嵇美伟 on 2021/2/18.
//

#ifndef AVL_TREE_AVL_TREE_H
#define AVL_TREE_AVL_TREE_H


#include "comm.h"


#define AVL_TREE_SEARCH_LEFT        (0x1000)
#define AVL_TREE_SEARCH_RIGHT       (0x1000 | 0X1)
#define AVL_TREE_SEARCH_EQUAL       (0x1000 | 0X2)
#define AVL_TREE_SEARCH_SUCC        (0x1000 | 0X3)
#define AVL_TREE_SEARCH_FAIL        (0x1000 | 0X4)

#define AVL_TREE_INSERT_UPDATE      (0x1000 | 0X5)
#define AVL_TREE_INSERT_SUCC_RIGHT  (0x1000 | 0X6)
#define AVL_TREE_INSERT_SUCC_LEFT   (0x1000 | 0X7)
#define AVL_TREE_INSERT_SUCC_ROOT   (0x1000 | 0X8)







typedef struct avl_tree_node_t
{
    void   *p_node_key;
    void   *p_node_conteny;
    struct avl_tree_node_t *p_left;
    struct avl_tree_node_t *p_right;
    struct avl_tree_node_t *p_parent;
}AVL_TREE_NODE_T;



typedef struct avl_tree_mng_t
{
    WORD32 node_num;
    WORD32 is_init;
    AVL_TREE_NODE_T *p_root_node;
}AVL_TREE_MNG_T;



typedef struct avl_tree_key_t
{
    WORD32  node_key_num;
}AVL_TREE_KEY_T;


typedef void (*AVL_TREE_PRE_ORDER_FUN) (AVL_TREE_KEY_T* p_key1, AVL_TREE_KEY_T* p_key2, void* p_fun_rtn);


WORD32 avl_tree_init(void);
WORD32 avl_tree_compare(AVL_TREE_NODE_T *p_tree_node, AVL_TREE_KEY_T *p_node_key);
AVL_TREE_NODE_T* avl_tree_search(AVL_TREE_KEY_T *p_node_key);
AVL_TREE_NODE_T* avl_tree_minumin(void);
AVL_TREE_NODE_T* avl_tree_maximun(void);
AVL_TREE_NODE_T* avl_tree_successor(AVL_TREE_KEY_T *p_node_key);
AVL_TREE_NODE_T* avl_tree_predecessor(AVL_TREE_KEY_T *p_node_key);
WORD32 avl_tree_insert(AVL_TREE_KEY_T *p_node_key);
WORD32 avl_tree_pre_order_traveral(AVL_TREE_PRE_ORDER_FUN p_pre_opder_fun, void* p_key1, void* p_fun_rtn);
WORD32 avl_tree_level_order_traveral(AVL_TREE_KEY_T *p_node_key, WORD32 *p_left_level, WORD32 *p_right_level);
WORD32 avl_tree_node_balance_para_get(AVL_TREE_KEY_T *p_node_key, WORD32* p_balance_para);


#endif //AVL_TREE_AVL_TREE_H
