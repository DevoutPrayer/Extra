#include "fd_vector.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
//#include <>
Fd_Vector *create_fd_v(){

    Fd_Vector *p  = (Fd_Vector *)calloc(1,sizeof(Fd_Vector));
    assert(p != NULL);
    p->fds = (int*)calloc(10,sizeof(int));
    assert(p->fds != NULL);

    p->count = 0;
    p->max = 10;

}

void destory_fd_v(Fd_Vector *v){
    assert(v != NULL);
    //销毁表中的数据
    free(v->fds);
    v->fds = NULL;
    //销毁表
    free(v);
    v = NULL;
}
//扩展顺序表的容量
static void en_fd_v(Fd_Vector *v){
    int *p = (int *)realloc(v->fds,sizeof(int)*(v->max+5));
    assert(p!=NULL);
    if(p!=v->fds){
        //首先释放之前的数组空间
        free(v->fds);
        //给fds重新赋值，指向一块新的内存空间
        v->fds = p;
        p = NULL;
    }
    v->max += 5;
}

//往顺序表里面添加一个元素
void add_fs_v(Fd_Vector *v,int fd){
    int index = get_fd_index(v,fd);
    if(index < 0){
        //判断顺序表容量是否够用，如果不过，扩展空间
        if(v->count >= v->max){
            en_fd_v(v);
        }
        v->fds[v->count] = fd;
        v->count++;
    }else{//该客户端套解子描述符已存在
        return;
    }
}

//从顺序表里面删除一个元素
void delete_fd_v(Fd_Vector *v,int fd){
    assert(v != NULL);
    int index = get_fd_index(v,fd);
    if(index < 0){
        //不存在
        return;

    }else{
        for(int i=index;i < v->count-1;i++){
            v->fds[i] = v->fds[i+1];
        }
        //    v->fds[v->count-1] = 0;
        v->count--;
    }

}
//辅助功能
//查找fd在顺序表中的 数组的下标
//如果存在返回数组的下标，不然返回-1
int get_fd_index(Fd_Vector *v,int fd){
    //循环遍历
    assert(v != NULL);
    for(int i = 0;i<v->count;i++){
        if(v->fds[i] == fd)
            return i;
    }
    return -1;
}
