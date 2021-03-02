#include "comm.h"
#include "hash_tbl.h"

int main()
{

	WORD32 rc = 0;
	HASH_TBL_MNG hash_tbl_init_buff = {0};

	hash_tbl_init_buff.hash_tbl_num = 100;
	hash_tbl_init_buff.element_num = 10000;

	hash_tbl_init_buff.hash_key_fun = hash_tbl_key_fun;
	hash_tbl_init_buff.hash_tbl_destroy_fun = hash_tbl_destroy;

	rc = hash_tbl_init(&hash_tbl_init_buff);
	COMM_CHECK_RC(rc);

	printf("hash tbl init is ok\n");
	hash_tbl_init_buff.hash_tbl_destroy_fun();

	return COMM_OK;
}
