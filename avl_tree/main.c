#include <stdio.h>
#include "avl_tree.h"

int main()
{
	WORD32 rc = 0;
	SWORD32 balance_para = 0;

	AVL_TREE_KEY_T avl_tree_key_buff_1 = {0};
	AVL_TREE_KEY_T avl_tree_key_buff_2 = {0};
	AVL_TREE_KEY_T avl_tree_key_buff_3 = {0};
	AVL_TREE_KEY_T avl_tree_key_buff_4 = {0};

	rc = avl_tree_init();
	COMM_CHECK_RC(rc);

	avl_tree_key_buff_1.node_key_num = 30;
	avl_tree_key_buff_2.node_key_num = 27;
	avl_tree_key_buff_3.node_key_num = 35;
	avl_tree_key_buff_4.node_key_num = 38;

	rc = avl_tree_insert(&avl_tree_key_buff_1);
	rc = avl_tree_insert(&avl_tree_key_buff_2);
	rc = avl_tree_insert(&avl_tree_key_buff_3);
	rc = avl_tree_insert(&avl_tree_key_buff_4);

	rc = avl_tree_node_balance_para_get(&avl_tree_key_buff_1, &balance_para);
	COMM_CHECK_RC(rc);

	rc = avl_tree_delete(&avl_tree_key_buff_1);


    printf("Hello, World!\n");
    return 0;
}
