//
// Created by 嵇美伟 on 2021/2/27.
//

#ifndef HASH__HASH_TBL_H_
#define HASH__HASH_TBL_H_

#include "comm.h"

/*每个桶的管理结构，链表结构*/
typedef struct hash_bucket_buff
{
  void *content;
  struct hash_bucket_buff *p_next;
  struct hash_bucket_buff *p_before;
}HASH_BUCKET_BUFF;



/*hash表的管理结构*/
typedef struct hash_tbl_mng
{
    WORD32 is_init;
    WORD32 hash_tbl_num;                    /*每个“桶”都是⼀个链表，共有多少个桶*/
    WORD32 element_num;                     /*hash表中共有的元素个数*/
    WORD32 bucket_size;                     /*每个桶的深度*/
    void (*hash_key_fun)(WORD32*, WORD32*); /*hash key公式*/
    void (*hash_confict_fun)(WORD32*, WORD32*, HASH_BUCKET_BUFF*);   /*hash 解决冲突的方法*/
	void (*hash_tbl_destroy_fun)(void);
}HASH_TBL_MNG;


WORD32 hash_tbl_init(HASH_TBL_MNG* p_init_buff);

void hash_tbl_destroy(void);

void hash_tbl_key_fun(WORD32* p_put_key, WORD32* p_hash_index);

WORD32 hash_tbl_key_insert(void* p_put_key, void* p_concent, size_t size_of_content);



#endif //HASH__HASH_TBL_H_
