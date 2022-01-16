#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<malloc.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
typedef int ElemType;
//����Ķ���
//������ѧ������ϵͳΪ��
//Ϊ��ͳһ����ͨ������������
//typedef struct ElemType
//{
	//char num[8];//������     ѧ��
	//char name[8];//������    ���� 
	//int score;//������       �ɼ�
//}ElemType;
typedef struct LNode
{
	ElemType date;//������
	struct LNode* next;//ָ����
}LNode, * LinkList;//LinkListΪָ��ṹ��Lnode��ָ������

LinkList L;//����ͷָ�����

//������ĳ�ʼ��������һ���յı�
Status linitList_L(LinkList L)//  LinkList L ͷָ��
{
	L = (LinkList)malloc(sizeof(LNode));//��̬��ȡLNode���ֽ������Ӷ������µĿռ䣬�����½����ͷ��㣬��ͷָ��Lָ��ͷ���
	if (L == NULL)
	{
		exit(OVERFLOW);
	}
	else
	{
		L->next = NULL;

		return OK;
	}
}

//�����п�   �ж�ͷ����ָ�����Ƿ�Ϊ��
int ListEmpty(LinkList L)
{
	if (L->next)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//���������  ��ͷָ�뿪ʼ�������ͷ����н��  
Status DestroyList_L(LinkList L)
{
	LNode* p=L;//Ҫ���ٵĽ��
	while (L)  //ѭ��������L��=NULL   ��������  L==NULL
	{
		p = L;
		L = L->next;//����һ����㸳ֵ��L ����free
		free(p);
	}
	return OK;
}

//��յ�����  ������Ȼ���� ��Ϊ������  �����ͷ����н�㣬����ͷ���ָ�����ÿ�
Status ClearList(LinkList L)
{
	LNode* p=L, * q;
	p = L->next;//��һ�����
	while (p)
	{
		q = p->next;//q�����һ����� �ؼ�����
		free(p);//�ͷŵ�һ�����
		p = q;//�ѵڶ����ڵ㻹��p ����ѭ���ͷ�ֱ�����
	}
	L->next = NULL;//ͷ���ָ����Ϊ��
	return OK;
}

//������ı�
int ListLength_L(LinkList L)
{
	LNode* p=L;
	int i = 0;
	p = L->next;//pָ���һ�����
	while (p)
	{
		i++;
		p = p->next;
	}
	return i;
}

//ȡֵ��ȡ��i��Ԫ��ֵs
Status GetElem_L(LinkList L, int i, ElemType* e)//���ݵ�i��Ԫ����e������ֵ
{
	LNode* p=L;
	p = L->next;
	int j = 1;//��ʼ��
	while (p && j < i)
	{
		p = p->next;//���ɨ�裬ֱ��pָ���i��Ԫ�ػ�pΪ��
		++j;
	}
	if (!p || j > i)//��i��Ԫ�ز�����
	{
		return ERROR;
	}
	else
	{
		*e = p->date;//ȡ��i��Ԫ��
		return OK;
	}
}

//����  ��ֵ���� ���ص�ַ
//LNode* LocateELem_L(LinkList L, ElemType e)
//{
//	//�����Ա�L�в���ֵΪe������Ԫ��
//		//�ҵ����򷵻�L��ֵΪe������Ԫ�صĵ�ַ������ʧ�ܷ���NULL
//	LNode* p;
//	p = L->next;
//	while (p && p->date != e)
//	{
//		p = p->next;
//	}
//	return p;
//}


//���� ����λ�����
int LocateELem_L(LinkList L, ElemType e)
{
	LNode* p=L;
	p = L->next;//��ʼ����pָ����Ԫ���
	int j = 1;

	while (p && (p->date != e))
	{
		p = p->next;
		j++;
	}
	if (p)//���pΪ�գ�Ҳ����û�ҵ�Ϊ�٣�����else��ֵ0
		  //���p�ҵ��ˣ���ôp�Ͳ�Ϊ0 ִ�з���j
	{
		return j;
	}
	else
	{
		return 0;
	}
}

//���� �ڵ�i�����ǰ����ֵΪe���½��
Status LintInsert_L(LinkList L, int i, ElemType e)
{
	LNode* p = L;//����һ�����
	int j = 0;//������  ��ͷ��㿪ʼ
	while (p && j < i - 1)
	{
		p = p->next;//Ѱ�ҵ�i-1����㣬pָ��i-1���
		++j;
	}
	if (!p || j > i - 1)
	{
		return ERROR;
	}
	else
	{
		LNode* s =(LNode*)malloc(sizeof(LNode));//�����½��
		if (s == NULL)
		{
			exit(ERROR);
		}
		else
		{
			s->date = e;//���½�����������Ϊe
			s->next = p->next;//���½���ָ����ָ��ai ����һ����
			p->next = s;//��*P�Ľ��ָ���½��*s
			return OK;
		}
	}
}

//ɾ����i�����    �����Ա�L�е�i������Ԫ��ɾ��
Status ListDelete_L(LinkList L, int i, ElemType* e)//������Ҫ����������в�����Ҫ����ָ��
{
	LNode* p = L;
	LNode* q=L;//q��������Ҫɾ�����ĵ�ַ�������ͷ�
	int j = 0;
	while (p->next && j < i - 1) //Ҫɾ�����һ ����pֻ��Ҫ�ߵ������ڶ�������
	{
		p = p->next;
		++j;
	}
	if (!(p->next) || j > i - 1)  //p->next��λ�����Ϊ�գ���ɾ����λ�ò�������iҲҪ����0
	{
		return ERROR;
	}
	else
	{
		q = p->next;//����p��next���ŵ���Ҫɾ���Ľ��ĵ�ַ
		p->next = q->next;//�ı�ɾ�����ǰ������ָ����
		*e = q->date;//�ñ���e������ɾ������������
		free(q);
		return OK;
	}
}

//ͷ�巨����������   L��ͷ���
LinkList CreateList_H(LinkList L, int n)//n�ǽ������Ҫ������ٸ����
{
	L = (LinkList)malloc(sizeof(LNode));//����ͷ���
	if (L == NULL)
	{
		exit(ERROR);
	}
	else
	{
		L->next = NULL;
	}
	int i = 0;
	for (i = n; i > 0; --i)
	{
		LNode* p = (LNode*)malloc(sizeof(LNode));//�����½��
		if (p == NULL)
		{
			exit(ERROR);
		}
		else
		{
			printf("�������%d�����������", i);
			scanf_s("%d", &p->date);//����Ԫ��ֵ
			p->next = L->next;//���뵽��ͷ ��ͷ����ָ���򸳸��½���ָ����
			L->next = p;//�ٰ��½���ָ�븳��ͷ����ָ����
		}
	}
	return L;
}

//β�巨����������  ��λ������n��Ԫ�ص�ֵ
LinkList CreateList_R(LinkList L, int n)
{
	L = (LinkList)malloc(sizeof(LNode));//����ռ�
	if (L == NULL)
	{
		exit(ERROR);
	}
	else
	{
		L->next = NULL;
	}
	LNode* r = L;//�����rΪβָ�룬ֻ��һ�����ʱ��ͷָ����βָ��ͬʱָ��ͷ���
	for (int i = 0; i < n; ++i)
	{
		LNode* p = (LNode*)malloc(sizeof(LNode));//�����½��
		if (p == NULL)
		{
			exit(ERROR);
		}
		else
		{
			scanf_s("%d", &p->date);//����Ԫ��ֵ

			p->next = NULL;
			r->next = p;//���½��ĵ�ַ����һ������ָ����
			r = p;//rָ���µ�β���
		}
	}
	return L;
}

void PrintLinkList(LinkList L)
{
	LNode* p = L->next;
	while (p)
	{
		printf("-->%d ", p->date);
		p = p->next;
	}
	printf("\n");
}

void menu()
{
	printf("*******************************\n");
	printf("*     1.ͷ�巨��������        *\n");
	printf("*     2.β�巨��������        *\n");
	printf("*     3.����λ��              *\n");
	printf("*     4.ɾ�����              *\n");
	printf("*     5.������              *\n");
	printf("*     6.��ֵ                  *\n");
	printf("*     7.�����              *\n");
	printf("*     8.�������              *\n");
	printf("*     9.��������              *\n");
	printf("*     10.�鿴����             *\n");
	printf("*******************************\n");
}
int main()
{
	int a = 0;
	menu();
	int n =0;
	
	while (!a)
	{
		scanf_s("%d", &n);
		switch (n)
		{
		case 1:
		{
			int n = 0;
			printf("������Ҫ����Ľ������");
			scanf_s("%d", &n);
			linitList_L(L);
			L=CreateList_H(L, n);
			printf("\n����ɹ�����\n");
			break;
		}
		case 2:
		{
			int n = 0;
			printf("������Ҫ����Ľ������");
			scanf_s("%d", &n);
			linitList_L(L);
			L = CreateList_R(L, n);
			printf("\n����ɹ�����\n");
			break;
		}
		case 3:
		{
			ElemType e = 0;
			int sum = 0;
			printf("\n������Ҫ���ҵ�ֵ��");
			scanf_s("%d", &e);
			sum = LocateELem_L(L, e);
			if (sum == 0)
			{
				printf("����ʧ��\n");
			}
			else
			{
				printf("�������ֵ��λ���ڵ�%d�����\n", sum);
			}
			break;
		}
		case 4:
		{
			int e = 0;
			int i = 0;
			int sum = 0;
			printf("������Ҫɾ����λ�ã�\n");
			scanf_s("%d", &i);
			sum = ListDelete_L(L, i, &e);
			if (sum == ERROR)
			{
				printf("��㲻���ڻ��������\n");
			}
			else
			{
				printf("�ý����ɾ����ɾ���Ľ��Ϊ:%d\n", e);
			}
			break;
		}
		case 5:
		{
			int i = 0;//����λ��
			int e = 0;
			int sum = 0;
			printf("\n������Ҫ�����λ�ã�");
			scanf_s("%d", &i);
			printf("\n������Ҫ�����ֵ��");
			scanf_s("%d", &e);
			sum = LintInsert_L(L, i, e);
			if (sum == ERROR)
			{
				printf("����ʧ�ܣ�����λ�ò��Ϸ�\n");
			}
			else
			{
				printf("����ɹ�\n");
			}
			break;
		}
		case 6:
		{
			int i = 0;//λ��
			int sum = 0;
			int e = 0;
			printf("\n������Ҫ��ѯ��λ�ã�");
			scanf_s("%d", &i);
			sum = GetElem_L(L, i, &e);
			if (sum == ERROR)
			{
				printf("�ý�㲻����\n");
			}
			else
			{
				printf("�ý���ֵΪ��%d\n", e);
			}
			break;
		}
		case 7:
		{
			int i = 0;
			i = ListLength_L(L);
			printf("�������Ϊ��%d\n", i);
			break;
		}
		case 8:
		{
			int i = 0;
			i = ClearList(L);
			if (i == OK)
			{
				printf("������ճɹ�\n");
			}
			break;
		}
		case 9:
		{
			int i = 0;
			i = DestroyList_L(L);
			if (i == OK)
			{
				printf("�������ٳɹ�\n");
				return 0;

			}
			break;
		}
		case 10:
		{
			int i = 0;
			i = ListEmpty(L);
			if (i == 0)
			{
				printf("������Ϊ��\n");
			}
			else
			{
				printf("������Ϊ��\n");
			}
			PrintLinkList(L);
			break;
		}
		}
	}
	

	return 0;
}


