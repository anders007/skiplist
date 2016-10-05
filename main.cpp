
#include <cstdio>
#include <time.h>
#include <string>
#include "mtrand.h"
#include "MySkipList.hpp"

using namespace std;
using namespace SkipListModule;

typedef CMySkipList<int> TIntSkipList;



int main(int argc, char* argv[])
{

	/*skiplist* sl = slCreate();
	slobj* pObj = slCreateObj("hahah", strlen("hahah"));
	slInsert(sl, 20, pObj);

	pObj = slCreateObj("fuck", strlen("fuck"));
	slInsert(sl, 30, pObj);

	pObj = slCreateObj("wsd", strlen("wsd"));
	slInsert(sl, 25, pObj);

	slDump(sl);*/

	TIntSkipList sl;
	sl.Init();

	for (int i = 0; i < 100; ++i)
	{
		int a = (random() & 0xffff) % 10000;
		sl.Insert(a);
	}

	vector<int> vc;
	sl.Dump(vc);

	for (int i = 0; i < vc.size(); ++i)
	{
		int a = vc[i];
		printf("%d ", a);
		if ((i % 5) == 4) printf("\n");
	}

	printf("\n");
	printf("\n");
	printf("-------------------------------------------------");
	printf("\n");

	sl.DelAll();
	vc.clear();

	sl.Init();
	for (int i = 0; i < 100; ++i)
	{
		sl.Insert(i);
	}

	for (int i = 0; i < 10; ++i)
	{
		sl.Delete(i);
	}
	sl.Dump(vc);

	for (int i = 0; i < vc.size(); ++i)
	{
		int a = vc[i];
		printf("%d ", a);
		if ((i % 5) == 4) printf("\n");
	}

	printf("\n");
	printf("\n");
	printf("-------------------------------------------------");
	printf("\n");


	sl.DelAll();
	vc.clear();

	sl.Init();
	for (int i = 0; i < 100; ++i)
	{
		sl.Insert(i);
	}

	for (int i = 0; i < 30; ++i)
	{
		int a = (random() & 0xffff) % 100;
		sl.Delete(a);
	}
	sl.Dump(vc);

	for (int i = 0; i < vc.size(); ++i)
	{
		int a = vc[i];
		printf("%d ", a);
		if ((i % 5) == 4) printf("\n");
	}

	return 0;
}