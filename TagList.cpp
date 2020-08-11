#include <iostream>
#include <stdlib.h>

#define MAXSIZE 100
#define OK 1
#define ERROR 0
#define OVERFLOW -2

using namespace std;

typedef int ElemType;
typedef int Status;

typedef struct Tag_List
{
    ElemType *e;
    int len;
}List;

//构造一个空的线性表
Status initlist(List &L)
{
    L.e = new ElemType[MAXSIZE];
    if(!L.e)
        exit(OVERFLOW);
    L.len = 0;
    return OK;
}

//求线性表的长度
int Len(List L)
{
    return L.len;
}

//查找指定元素所在位置，若存在返回实际位置（使用时须在减1），否则返回0
int getLocate(List L, ElemType e)
{
    int i;
    for(i = 0 ; i < L.len ; i++)
        if(L.e[i] == e)
            return i+1;
    return 0;
}

//获取线性表中位置为i的元素值，并赋给变量
Status getELem(List L, int i, ElemType &e)
{
    if(i > L.len || i < 1)
    {
        std::cout << "位置信息错误" << std::endl;
        return ERROR;
    }
    e = L.e[i-1];
    return OK;
}

//在线性表的第i个位置上插入一个元素
Status ListInsert(List &L, int i, ElemType e)
{
    if(L.len == MAXSIZE || i < 1 || i > L.len+1)
    {
        std::cout << "位置信息错误" << std::endl;
        return ERROR;
    }
    for(int j = L.len-1 ; j >= i-1 ; j--)
    {
        L.e[j+1] = L.e[j];
    }
    L.e[i-1] = e;
    L.len++;
    return OK;
}

//遍历线性表
void sysout(List L)
{
    for(int i = 0 ; i < L.len ; i++)
        cout << L.e[i] << "    ";
    cout << endl;
}

//合并线性表
void CombList(List &L1, List L2)
{
    int len1, len2;
    len1 = L1.len;
    len2 = L2.len;
    for(int i = 1 ; i <= len2 ; i++)
    {
        ElemType e;
        getELem(L2, i, e);
        if(!getLocate(L1, e))
            ListInsert(L1, ++len1, e);
    }
}

//顺序有序表的合并
void MergeList_sq(List L1, List L2, List &L3)
{
    ElemType *pa, *pb, *pc, *pa_last, *pb_last;
    pc = L3.e;
    pa = L1.e;
    pb = L2.e;
    pa_last = L1.e + L1.len-1;
    pb_last = L2.e + L2.len-1;
    while((pa <= pa_last) && (pb <= pb_last))
    {
        if(getLocate(L3, *pa)) //如果L3中已经存在*pa，向后移动
            ++pa;
        if(getLocate(L3, *pb)) //如果L3中已经存在*pb，向后移动
            ++pb;
        if(*pa < *pb)   //小的放在前面
            *pc++ = *pa++;
        else if(*pa == *pb) //相等的只存一个
        {
            *pc++ = *pa++;
            ++pb;
        }
        else
            *pc++ = *pb++;
        L3.len = (int)(pc - L3.e);  //修改L3的长度
    }
    while(pa <= pa_last)
        *pc++ = *pa++;
    while(pb <= pb_last)
        *pc++ = *pb++;
    L3.len = (int)(pc - L3.e);
}

//顺序有序表的交集
void IntersectionList(List L1, List L2, List &L3)
{
    ElemType *pa, *pc, *pb, *pa_last, *pb_last;
    pa = L1.e;
    pb = L2.e;
    pc = L3.e;
    pa_last = L1.e + L1.len - 1;
    pb_last = L2.e + L2.len - 1;
    while ((pa <= pa_last) && (pb <= pb_last)) {
        if(getLocate(L3, *pa)) //如果L3中已经存在*pa，向后移动
            ++pa;
        if(getLocate(L3, *pb)) //如果L3中已经存在*pb，向后移动
            ++pb;
        if(*pa == *pb)
        {
            *pc++ = *pa++;
            ++pb;
        }
        else
        {
            ++pa;
            ++pb;
        }
        L3.len = (int)(pc - L3.e);  //修改L3的长度
    }
    while(pa <= pa_last)
    {
        if(getLocate(L3, *pa)) //如果L3中已经存在*pa，向后移动
            ++pa;
        if(getLocate(L2, *pa))
            *pc++ = *pa++;
        else
            ++pa;
        L3.len = (int)(pc - L3.e);  //修改L3的长度
    }
    while(pb <= pb_last)
    {
        if(getLocate(L3, *pb)) //如果L3中已经存在*pa，向后移动
            ++pb;
        if(getLocate(L1, *pb))
            *pc++ = *pb++;
        else
            ++pb;
        L3.len = (int)(pc - L3.e);  //修改L3的长度
    }
//    L3.len = (int)(pc - L3.e);  //修改L3的长度
}

//顺序有序表的差集
void DiffsectionList(List L1, List L2, List &L3)
{
    ElemType *pa, *pc, *pa_last;
    pa = L1.e;
    pa_last = L1.e + L1.len - 1;
    pc = L3.e;
    while (pa <= pa_last) {
        if(getLocate(L3, *pa)) //如果L3中已经存在*pa，向后移动
            ++pa;
        if(!getLocate(L2, *pa))
            *pc++ = *pa++;
        else
            ++pa;
        L3.len = (int)(pc - L3.e);
    }
}

int main() {
    List tg1, tg2, tg3, tg4, tg5;
    initlist(tg1);
    initlist(tg2);
    initlist(tg3);
    initlist(tg4);
    initlist(tg5);
    //tg1元素为[2,4,6]，tg2元素为[3,5,6,7]
    ListInsert(tg1, 1, 2);
    ListInsert(tg1, 2, 4);
    ListInsert(tg1, 3, 6);
    ListInsert(tg2, 1, 3);
    ListInsert(tg2, 2, 5);
    ListInsert(tg2, 3, 6);
    ListInsert(tg2, 4, 7);
    //查看tg1，tg2顺序表元素
    cout << "tg1元素为；";
    sysout(tg1);
    cout << "tg2元素为；";
    sysout(tg2);
    //合并
    MergeList_sq(tg1, tg2, tg3);
    cout << "tg3元素为；";
    sysout(tg3);
    //交集
    IntersectionList(tg1, tg2, tg4);
    cout << "tg4元素为；";
    sysout(tg4);
    //差集
    DiffsectionList(tg1, tg2, tg5);
    cout << "tg5元素为；";
    sysout(tg5);
return 0;
}

