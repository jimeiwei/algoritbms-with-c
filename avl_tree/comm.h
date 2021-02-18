//
// Created by 嵇美伟 on 2021/2/18.
//

#ifndef AVL_TREE_COMM_H
#define AVL_TREE_COMM_H

#include "stdlib.h"
#include "stdio.h"
#include "assert.h"
#include "string.h"

#define WORD32          unsigned int
#define SWORD32         int
#define FUN_STATUS      WORD32


#define COMM_OK         (0)
#define COMM_ERR        (1)



#define COMM_CHECK_POINT(point) \
        if (point == NULL)      \
        assert(0)




#endif //AVL_TREE_COMM_H
