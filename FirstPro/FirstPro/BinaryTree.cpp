#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define SUCCESS 1
#define UNSUCCESS 0
#define dataNum 5
int i = 0;
int dep = 0;
char data[dataNum] = { 'A', 'B', 'C', 'D', 'E' };

typedef int Status;
typedef char TElemType;

// �������ṹ
typedef struct BiTNode
{
	TElemType data;
	struct BiTNode* lchild, * rchild;
}BiTNode, * BiTree;

// ��ʼ��һ������
void InitBiTree(BiTree& T)
{
	T = NULL;
}

// ����������
BiTree MakeBiTree(TElemType e, BiTree L, BiTree R)
{
	BiTree t;
	t = (BiTree)malloc(sizeof(BiTNode));
	if (NULL == t) return NULL;
	t->data = e;
	t->lchild = L;
	t->rchild = R;
	return t;
}

// ���ʽ��
Status visit(TElemType e)
{
	printf("%c", e);
	return OK;
}

// �Զ�����T��Ҷ�ӽ����Ŀ
int Leaves(BiTree T)
{
	int l = 0, r = 0;
	if (NULL == T) return 0;
	if (NULL == T->lchild && NULL == T->rchild) return 1;

	// ��������Ҷ����Ŀ
	l = Leaves(T->lchild);
	// ��������Ҷ����Ŀ
	r = Leaves(T->rchild);
	// ���
	return r + l;
}

// ��α�����dep�Ǹ�ȫ�ֱ���,�߶�
int depTraverse(BiTree T)
{
	if (NULL == T) return ERROR;

	dep = (depTraverse(T->lchild) > depTraverse(T->rchild)) ? depTraverse(T->lchild) : depTraverse(T->rchild);

	return dep + 1;
}

// �߶ȱ�����lev�Ǿֲ����������
void levTraverse(BiTree T, Status(*visit)(TElemType e), int lev)
{
	if (NULL == T) return;
	visit(T->data);
	printf("�Ĳ����%d\n", lev);

	levTraverse(T->lchild, visit, ++lev);
	levTraverse(T->rchild, visit, lev);
}

// num�Ǹ�ȫ�ֱ���
void InOrderTraverse(BiTree T, Status(*visit)(TElemType e), int& num)
{
	if (NULL == T) return;
	visit(T->data);
	if (NULL == T->lchild && NULL == T->rchild) { printf("��Ҷ�ӽ��"); num++; }
	else printf("����Ҷ�ӽ��");
	printf("\n");
	InOrderTraverse(T->lchild, visit, num);
	InOrderTraverse(T->rchild, visit, num);
}

// �������п�
Status BiTreeEmpty(BiTree T)
{
	if (NULL == T) return TRUE;
	return FALSE;
}

// ��϶��������ÿն���������������
Status BreakBiTree(BiTree& T, BiTree& L, BiTree& R)
{
	if (NULL == T) return ERROR;
	L = T->lchild;
	R = T->rchild;
	T->lchild = NULL;
	T->rchild = NULL;
	return OK;
}

// �滻������
Status ReplaceLeft(BiTree& T, BiTree& LT)
{
	BiTree temp;
	if (NULL == T) return ERROR;
	temp = T->lchild;
	T->lchild = LT;
	LT = temp;
	return OK;
}

// �滻������
Status ReplaceRight(BiTree& T, BiTree& RT)
{
	BiTree temp;
	if (NULL == T) return ERROR;
	temp = T->rchild;
	T->rchild = RT;
	RT = temp;
	return OK;
}

// �ϲ�������
void UnionBiTree(BiTree& Ttemp)
{
	BiTree L = NULL, R = NULL;
	L = MakeBiTree(data[i++], NULL, NULL);
	R = MakeBiTree(data[i++], NULL, NULL);
	ReplaceLeft(Ttemp, L);
	ReplaceRight(Ttemp, R);
}

int main()
{
	BiTree T = NULL, Ttemp = NULL;

	InitBiTree(T);
	if (TRUE == BiTreeEmpty(T)) printf("��ʼ��TΪ��\n");
	else printf("��ʼ��T��Ϊ��\n");

	T = MakeBiTree(data[i++], NULL, NULL);

	Ttemp = T;
	UnionBiTree(Ttemp);

	Ttemp = T->lchild;
	UnionBiTree(Ttemp);

	Status(*visit1)(TElemType);
	visit1 = visit;
	int num = 0;
	InOrderTraverse(T, visit1, num);
	printf("Ҷ�ӽ���� %d\n", num);

	printf("Ҷ�ӽ���� %d\n", Leaves(T));

	int lev = 1;
	levTraverse(T, visit1, lev);

	printf("�߶��� %d\n", depTraverse(T));

	getchar();
	return 0;
}