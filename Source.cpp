//Từ Điển Anh-Việt

#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>
#include<fstream>
using namespace std;
#define M 26
typedef struct tagnode
{
	char word[20];
	char mean[20];
	struct tagnode*pNext;
}NODE;
typedef struct tagList
{
	NODE* pHead;
	NODE* pTail;
}LIST;
NODE *new_ele;

void initList(LIST &l)
{
	l.pHead = l.pTail = NULL;
}
//Tao ra mot phan tu ,thong tin chua trong x
NODE* GetNode(char word[], char mean[])
{
	NODE *p;
	p = new NODE;
	if (p == NULL)
	{
		cout << "Khong du bo nho";
		return NULL;
	}
	strcpy_s(p->word, word);
	strcpy_s(p->mean, mean);
	p->pNext = NULL;
	return p;
}
///////Chen mot phan tu vao danh sach
//chen vao dau danh sach
void AddFirst(LIST &l, NODE* new_ele)
{
	if (l.pHead == NULL)
	{
		l.pHead = new_ele;
		l.pTail = l.pHead;
	}
	else
	{
		new_ele->pNext = l.pHead;
		l.pHead = new_ele;
	}
}
NODE* InsertHead(LIST &l, char word[], char mean[])
{
	NODE* new_ele = GetNode(word, mean);
	if (new_ele == NULL)
		return NULL;
	if (l.pHead == NULL)
	{
		l.pHead = new_ele;
		l.pTail = l.pHead;
	}
	else
	{
		new_ele->pNext = l.pHead;
		l.pHead = new_ele;
	}
	return new_ele;
}
//chen vao cuoi danh sach
void AddTail(LIST &l, NODE *new_ele)
{
	if (l.pHead == NULL)
	{
		l.pHead = new_ele;
		l.pTail = l.pHead;
	}
	else
	{
		l.pTail->pNext = new_ele;
		l.pTail = new_ele;
	}
}
NODE* InsertTail(LIST &l, char word[], char mean[])
{
	NODE* new_ele = GetNode(word, mean);
	if (new_ele == NULL)
		return NULL;
	if (l.pHead == NULL)
	{
		l.pHead = new_ele;
		l.pTail = l.pHead;
	}
	else
	{
		l.pTail->pNext = new_ele;
		l.pTail = new_ele;
	}
	return new_ele;
}

void xoafile()
{
	FILE*f;
	errno_t fin;
	fin = fopen_s(&f, "data.txt", "w");
	fclose(f);
}
void infile(LIST l)
{
	ofstream fg;
	fg.open("data.txt", ios::app);
	NODE *p;
	int i = -1;
	p = l.pHead;
	while (p != NULL)
	{
		fg << p->word;
		fg << " ";
		fg << p->mean;
		fg << endl;
		p = p->pNext;
	}
	fg.close();

}
//Chen vao danh sach sau phan tu q
void AddAfter(LIST &l, NODE *q, NODE* new_ele)
{
	if (q != NULL)
	{
		new_ele->pNext = q->pNext;
		q->pNext = new_ele;
		if (q == l.pTail)
			l.pTail = new_ele;
	}
	else
		AddFirst(l, new_ele);
}
NODE* InsertAfter(LIST &l, NODE *q, char word[], char mean[])
{
	NODE* new_ele = GetNode(word, mean);
	if (new_ele == NULL)
		return NULL;
	if (q != NULL)
	{
		new_ele->pNext = q->pNext;
		q->pNext = new_ele;
		if (q == l.pTail)
			l.pTail = new_ele;
	}
	else
		AddFirst(l, new_ele);
}
//Tim mot phan tu trong danh sach
NODE *Search(LIST l, char word[])
{
	NODE *p;
	p = l.pHead;
	while ((p != NULL) && (strcmp(p->word, word) != 0))
		p = p->pNext;
	return p;
}
//Huy mot phan tu khoi danh sach
int RemoveNode(LIST &l, char word[])
{
	NODE *p = l.pHead;
	NODE *q = NULL;
	while (p != NULL)
	{
		if (strcmp(p->word, word) == 0)
			break;
		q = p;
		p = p->pNext;
	}
	if (p == NULL)
		cout << "Khong co tu nay trong tu dien";
	if (q != NULL)
	{
		if (p == l.pTail)
			l.pTail = q;
		q->pNext = p->pNext;
		delete p;
	}
	else
	{
		l.pHead = p->pNext;
		if (l.pTail == NULL)
			l.pTail = NULL;
	}
	return 1;
}
int capnhat(LIST &l, char mean[], char word[])
{
	NODE *p;
	p = l.pHead;
	while ((p != NULL) && (strcmp(p->word, word) != 0))
		p = p->pNext;
	strcpy_s(p->mean, mean);
	return 1;
}
//Duyet danh sach

void Display(LIST l)
{
	NODE *p;
	p = l.pHead;
	while (p != NULL)
	{
		cout << "\"" << p->word << "\"";
		cout << " nghia cua tu : ";
		cout << p->mean;
		cout << endl;
		p = p->pNext;
	}

}
///////////////////////////////
//DA XAY DUNG XONG MOT DANH SACH LIEN KET
//Bang bam
LIST bucket[M];
//Ham bam
int hashfunc(char word[])
{
	char c = toupper(word[0]);
	return ((c - 65) % 26);
}
//Khoi tao thung bucket
void initbucket()
{
	for (int i = 0; i < M; i++)
		initList(bucket[i]);
}
//Them mot nut vao thung bucket
void Insert(NODE *p)
{
	int i = hashfunc(p->word);
	AddTail(bucket[i], p);
}
//Tim kiem mot tu tra ve dia chi tu do
NODE* Find(char word[])
{
	int i = hashfunc(word);
	return (Search(bucket[i], word));
}

//Huy mot tu khoi tu dien,tra ve 1 neu thanh cong,0 neu khong co tu nay
int RemoveWord()
{
	char word[20];
	fflush(stdin);
	cout << "Nhap tu can huy bo : "; gets_s(word); fflush(stdin); cout << endl;
	int i = hashfunc(word);
	return RemoveNode(bucket[i], word);
}
int Capnhattu()
{
	char word[20];
	char mean[20];
	fflush(stdin);
	cout << "Nhap tu can cap nhat: "; gets_s(word); fflush(stdin); cout << endl;
	int i = hashfunc(word);
	if (Search(bucket[i], word) == NULL)
	{
		cout << "Khong co tu nay trong tu dien ! " << endl;
		return 0;
	}
	else
		cout << "Nhap nghia tu can cap nhat: "; gets_s(mean); fflush(stdin); cout << endl;

	return capnhat(bucket[i], mean, word);
}
//Ham tao tu dien
void MakeDictionary()
{
	NODE*p;
	char word[20];
	char mean[100];
	char c;
	int n;

	cout << "Ban muon nhap bao nhieu tu : " << endl;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		fflush(stdin);
		cout << "Nhap tu thu " << i + 1 << " can tao:" << endl;
		gets_s(word);
		if (Find(word) != NULL)
		{
			cout << "Tu nay da co trong tu dien, moi ban cap nhat tu" << endl;
		}
		else 
		{
			if (strcmp(word, "") == 0)
				break;
			fflush(stdin);
			cout << "Nhap cac nghia cua tu thu " << i + 1 << " :" << endl;
			gets_s(mean);
			p = GetNode(word, mean);
			Insert(p);
		}
	}
	
}

void FindWord()
{
	NODE* p;
	char word[20];
	fflush(stdin);
	cout << "Nhap tu can tim :"; gets_s(word);
			p = Find(word);
	if (p == NULL)
		cout << "Khong co tu nay trong tu dien" << endl;
	else
		cout << "Nghia cua tu :" << p->mean << endl;
	return;
}
void DislayDictionary()
{
	xoafile();
	for (int i = 0; i < M; i++)
	{
		Display(bucket[i]);
		infile(bucket[i]);
	}
}
//Ham nay lay du lieu tu file
bool ischar(char kitu)
{
	int temp;
	temp = int(kitu);
	if ((temp >= 65 && temp <= 90) || (temp >= 97 && temp <= 122))
		return true;
	return false;
}
void MakeFromFile()
{
	NODE*p;
	char c;
	int dem = 0;
	int i = 0; int j = 0;
	char word[20];
	char mean[100];
	FILE*f;
	errno_t fin;
	fin = fopen_s(&f, "data.txt", "rt");
	if (f == NULL)
	{
		cout << "Khong mo duoc file ! " << endl;
		exit(0);
	}
	while (!(feof(f)))
	{
		c = getc(f);
		if (dem == 0)
		{
			if (!(ischar(c)) && c != '\n')
			{
				word[i] = '\0';
				dem = 1;
			}
			else
				word[i++] = c;
		}
		else
		{
			if (c != '\n')
			{
				mean[j++] = c;
			}
			else
			{
				mean[j] = '\0';
				if (strlen(word) != 0 || strlen(mean) != 0)
				{
					p = GetNode(word, mean);
					Insert(p);
				}
				dem = 0; i = 0; j = 0;
			}
		}
	}
	fclose(f);
}

void main()
	{
		MakeFromFile();
		int chon;
		do
		{
			cout << "CHUONG TRINH TU DIEN DON GIAN" << endl;
			cout << "Cac chuc nang:" << endl;
			cout << "1:xay dung tu dien" << endl;
			cout << "2:Tra tu" << endl;
			cout << "3:Xem toan bo tu dien" << endl;
			cout << "4:Huy mot tu khoi tu dien" << endl;
			cout << "5:Cap nhat nghia cho tu " << endl;
			cout << "0:Quit" << endl;
			chon = getchar();
			cout << endl;
			switch (chon)
			{
			case '1':MakeDictionary(); break;
			case '2':FindWord(); break;
			case '3':DislayDictionary(); break;
			case '4':RemoveWord(); break;
			case '5':Capnhattu(); break;

			}
		} while (chon != '0');
	}