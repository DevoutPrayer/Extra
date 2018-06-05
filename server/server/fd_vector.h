#ifndef FD_VECTOR_H
#define FD_VECTOR_H

//定义一个顺序表
typedef struct{
    int *fds;//数组 存放客户端的套解子描述符
    int count;//标记链接上来的客户端数量
    int max;//数组的容量 链接上来客户端的数量
}Fd_Vector;

//创建一个顺序表

extern Fd_Vector* create_fd_v();

//销毁一个顺序表
extern void destory_fd_v(Fd_Vector *v);

//往顺序表里面添加一个元素
extern void add_fs_v(Fd_Vector *v,int fd);

//从顺序表里面删除一个元素
extern void delete_fd_v(Fd_Vector *v,int fd);
//辅助功能
//查找fd在顺序表中的 数组的下标
//如果存在返回数组的下标，不然返回-1
extern int get_fd_index(Fd_Vector *v,int fd);

#endif // FD_VECTOR_H
