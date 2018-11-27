#include "fstream"
#include<stdio.h>
#include<stdlib.h> 
#include<string.h> 
#include<conio.h> 
#include <string>
#include <iostream>
#define M 26 
#define INPUT "bai4.inp"
#define OUTPUT "bai4.txt"
using namespace std;


/*dinh nghia cau truc tu dien */
typedef struct TuDien
{
	char tu[20];
	char nghia[20];
};

// dinh nghia cau truc nut cua buckets 
typedef struct node
{
	TuDien key;
	struct node *next;
} Nodetype;

//dinh nghia nut con tro kieu Nodetype 
typedef Nodetype *Nodeptr;

//mang con tro Bucket gom M bucket 
Nodeptr Bucket[M];

void Initialize()
{
	for (int i = 0; i<M; i++)
		Bucket[i] = NULL;
}

//hàm bam 
int HashFunc(char c)
{
	if (c >= 97) c = c - 32;
	return (c % 65);
}

//hàm này de tao nút có chua khóa k,tra ve kieu con tro Nodeptr 
Nodeptr MakeNode(TuDien k)
{
	Nodeptr p;
	p = (Nodeptr)malloc(sizeof(Nodetype));
	p->key = k;
	p->next = NULL;
	return p;
}

// hàm này dùng de chèn tu vào Bucket, sau dó sap xep theo thu tu tang 
void  InsertListOrder(Nodeptr &Head, Nodeptr G)
{
	Nodeptr  P;
	Nodeptr Q;
	P = Head;
	while (P != NULL)
	{
		if (strcmp(P->key.tu, G->key.tu)>0) break;
		else
		{
			Q = P;
			P = Q->next;
		}
	}
	if (P == Head)
	{
		G->next = Head;
		Head = G;
	}
	else
	{
		/*Q->next = G->next;
		Q->next = G;*/
	}
}


//hàm này dùng de chèn khóa k vào Bucket th? b 
void Place(int b, TuDien k)
{
	Nodeptr p, t;
	p = Bucket[b];
	t = MakeNode(k);
	if (p == NULL) Bucket[b] = t;
	else InsertListOrder(Bucket[b], t);
}
//hàm này dùng d? chèn khóa k vào b?ng bam 
void Insert(TuDien k)
{
	int b = HashFunc(k.tu[0]);
	Place(b, k);
}

//duy?t Bucket 
void TraverseBucket(int b)
{
	Nodeptr p;
	p = Bucket[b];
	while (p != NULL)
	{
		printf("%3s,", p->key.tu);
		p = p->next;
	}
}
//duy?t toàn b? b?ng bam 
void Traverse()
{
	for (int b = 0; b<M; b++)
	{
		printf("\nBucket[%d]:", b);
		TraverseBucket(b);
	}
}

//hàm này dùng d? tra nghia c?a 1 t? trong t? di?n 
void TraNghia(char *s)
{
	int b = HashFunc(s[0]);

	Nodeptr p = Bucket[b];
	while (p != NULL && strcmp(p->key.tu, s) != 0)
		p = p->next;
	if (p == NULL) printf("\n\nKhong tim thay \"%s\" trong tu dien", s);
	else
		printf("\n\nNghia cua tu \"%s\":%s", s, p->key.nghia);
}

//hàm này dùng d? c?p nh?t nghia cho 1 t? 
void CapNhatTu(char *s, char *s1)
{
	fflush(stdin);
	int b = HashFunc(s[0]);
	Nodeptr p = Bucket[b];
	while (p != NULL && strcmp(p->key.tu, s) != 0)
		p = p->next;
	if (p == NULL) printf("\n\nKhong tim thay \"%s\" trong tu dien", s);
	else
	{
		strcat_s(p->key.nghia, ",");
		strcat_s(p->key.nghia, s1);
	}
}

void Pop(Nodeptr &p)     // lay phan tu dau xau 
{
	TuDien k;
	Nodeptr q;
	q = p;
	p = p->next;
	q->next = NULL;
	k = q->key;
	free(q);
}

void DelAfter(Nodeptr &q)   //xoa nut sau q 
{
	Nodeptr p;
	p = q->next;
	q->next = p->next;
	p->next = NULL;
	free(p);
}

//xóa 1 từ trong từ điển 
void XoaTu(char *s)
{
	int b = HashFunc(s[0]);
	Nodeptr p, q;
	p = Bucket[b];
	while (p != NULL && strcmp(p->key.tu, s) != 0)
	{
		q = p;
		p = p->next;
	}
	if (p == NULL) printf("\n\nKhong tim thay \"%s\" trong tu dien", s);
	if (p == Bucket[b]) Pop(Bucket[b]);
	else DelAfter(q);
}

bool Isempty(TuDien k)
{
	int dem = 0;
	for (int i = 0; i < M; i++)
	{
		if (Bucket[i] != NULL)
			dem++;
	}
	if (dem == 0)
		return true;
	else
		return false;
}
void Display(TuDien k)						   // Duyet toan bo bucket
{
	if (Isempty(k) == true)
		cout << "\nTu Dien rong \n";
	Nodeptr  n;
	for (int i = 0; i<M; i++)
	{
		n = Bucket[i];
		while (n != NULL)
		{
			cout << n->key.tu << "Co nghia la: " << n->key.nghia << endl;
			n = n->next;
		}
	}
};

//void docfile(int &a, int &b, int &c, int &d)
//{
//	int i, j;
//	fstream file;
//	file.open(INPUT, ios::in);
//	file >> a >> b >> c >> d;
//	file.close();
//}
void xuatfile(TuDien k)
{
	int i, j;
	fstream file;
	file.open(OUTPUT, ios::out);
	Nodeptr  n;
	for (int i = 0; i<M; i++)
	{
		n = Bucket[i];
		while (n != NULL)
		{
			file << n->key.tu << " " << n->key.nghia;
			n = n->next;
			file << endl;
		}
	}
	file.close();
}

//menu c?a chuong trình 
void MENU()
{
	printf("\n\n\t\t\t\tTU DIEN ANH-VIET");
	printf("\n\nCac chuc nang chinh cua tu dien:");
	printf("\n\n1.Them tu moi vao tu dien");
	printf("\n\n2.Xoa mot tu khoi tu dien");
	printf("\n\n3.Cap nhat tu");
	printf("\n\n4.Tra nghia cua tu");
	printf("\n\n5.Coi Toan bo tu dien ");
	printf("\n\n0.Thoat khoi tu dien");
	printf("\n\nBan chon chuc nang nao:");
}

int main()
{
	char s[M], s1[M];
	TuDien td;
	int choice;
	Initialize();
	do
	{
		MENU();
		scanf_s("%d", &choice);
		switch (choice)
		{
		case 1:
			system("cls");
			printf("THEM TU MOI VAO TU DIEN");
			printf("\n\nNhap tu can them:"); fflush(stdin);
			gets_s(td.tu);
			printf("\n\nNhap nghia cua tu \"%s\":", td.tu);
			fflush(stdin);
			gets_s(td.nghia);
			Insert(td);
			break;
		case 2:
			system("cls");
			printf("\n\nNhap tu can xoa:"); fflush(stdin);
			gets_s(s);
			XoaTu(s);
			break;
		case 3:
			system("cls");
			printf("CAP NHAT NGHIA CUA TU");
			printf("\n\nNhap tu can cap nhat:");
			fflush(stdin);
			gets_s(s);
			printf("\n\nNhap nghia cap nhat cua \"%s\":");
			fflush(stdin);
			gets_s(s1);
			CapNhatTu(s, s1);
			break;
		case 4:
			system("cls");
			printf("TRA NGHIA CUA TU");
			printf("\n\nNhap tu can tra nghia:"); fflush(stdin);
			gets_s(s);
			TraNghia(s);
			break;
		case 5:
			system("cls");
			printf("TOAN BO TU DIEN");
			Display(td);
			xuatfile(td);

		}
	} while (choice != 0);
	return 0;
}