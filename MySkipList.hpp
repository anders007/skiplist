#ifndef __H__MY_SKIPLIST__
#define __H__MY_SKIPLIST__

#include <string.h>
#include <vector>
#include "replace.h"

using namespace std;


//根据指针值删除内存
#ifndef SAFE_DELETE
#define SAFE_DELETE(x)	if( (x)!=NULL ) { delete (x); (x)=NULL; }
#endif
//根据指针值删除数组类型内存
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x)	if( (x)!=NULL ) { delete[] (x); (x)=NULL; }
#endif


namespace SkipListModule
{
#define SKIPLIST_MAXLEVEL 32
#define SKIPLIST_P 0.25

	template<class T>
	class CMySkipList
	{
	public:
		struct SkipListNode
		{
			T* m_pObj;
			SkipListNode* m_pBackward;
			SkipListNode* m_szLevel[SKIPLIST_MAXLEVEL];

			SkipListNode()
			{
				cleanUp();
			}

			void cleanUp(void)
			{
				m_pObj = NULL;
				m_pBackward = NULL;
				for (int i = 0; i < SKIPLIST_MAXLEVEL; ++i)
				{
					m_szLevel[i] = NULL;
				}
			}
		};

	public:

		CMySkipList() : m_nLength(0)
			, m_nLevel(0)
			,m_pHeader(NULL)
			,m_pTail(NULL)
			,m_bInited(false)
		{

		}

		virtual ~CMySkipList()
		{
			DelAll();
		}

		SkipListNode* createNode(int a_nLevel, const T* a_pData)
		{
			SkipListNode* pNode = new SkipListNode;

			if (pNode)
			{
				if (NULL!=a_pData)
				{
					pNode->m_pObj   = new T;
					if (pNode->m_pObj)
					{
						memcpy(pNode->m_pObj, a_pData, sizeof(T));
					}
				}
				return pNode;
			}
			return NULL;
		}

		void Init(void)
		{
			m_nLevel = 1;
			m_nLength = 0;
			m_pHeader = createNode(SKIPLIST_MAXLEVEL, NULL);
			for (int j=0; j < SKIPLIST_MAXLEVEL; j++) {
				m_pHeader->m_szLevel[j] = NULL;
			}
			m_pHeader->m_pBackward = NULL;
			m_pTail = NULL;

			m_bInited = true;
		}

		int RandomLevel(void)
		{
			int level = 1;
			while((random() & 0xffff) < (SKIPLIST_P * 0xffff))
			{
				level += 1;
			}
			return (level < SKIPLIST_MAXLEVEL) ? level : SKIPLIST_MAXLEVEL;
		}

		void Insert(const T& a_rData)
		{
			SkipListNode* update[SKIPLIST_MAXLEVEL];
			
			SkipListNode* x = m_pHeader;
			for (int i = m_nLevel-1; i >= 0; --i)
			{
				while (x->m_szLevel[i] &&
					x->m_szLevel[i]->m_pObj &&
					*(x->m_szLevel[i]->m_pObj) < a_rData)
				{
					x = x->m_szLevel[i];
				}
				update[i] = x;
			}
			
			int level = RandomLevel();
			if (level > m_nLevel)
			{
				for (int i = m_nLevel; i < level; ++i)
				{
					update[i] = m_pHeader;
				}
				m_nLevel = level;
			}
			x = createNode(level,&a_rData);
			for (int i = 0; i < level; ++i)
			{
				x->m_szLevel[i] = update[i]->m_szLevel[i];
				update[i]->m_szLevel[i] = x;
			}

			x->m_pBackward = (update[0] == m_pHeader) ? NULL : update[0];
			if (x->m_szLevel[0])
			{
				x->m_szLevel[0]->m_pBackward = x;
			}
			else
			{
				m_pTail = x;
			}
			++m_nLength;
		}

		void DeleteNode(SkipListNode* a_pNode, SkipListNode** a_szUpdate)
		{
			for (int i = 0; i < m_nLevel; i++)
			{
				if (a_szUpdate[i]->m_szLevel[i] == a_pNode)
				{
					a_szUpdate[i]->m_szLevel[i] = a_pNode->m_szLevel[i];
				}
			}
			if (a_pNode->m_szLevel[0])
			{
				a_pNode->m_szLevel[0]->m_pBackward = a_pNode->m_pBackward;
			} else
			{
				m_pTail = a_pNode->m_pBackward;
			}
			while(m_nLevel > 1 && m_pHeader->m_szLevel[m_nLevel-1] == NULL)
			{
				--m_nLevel;
			}
			--m_nLength;

			SAFE_DELETE(a_pNode->m_pObj);
			SAFE_DELETE(a_pNode);
		}

		int Delete(const T& a_rData)
		{
			SkipListNode* update[SKIPLIST_MAXLEVEL];
			
			SkipListNode* x = m_pHeader;
			for (int i = m_nLevel; i >= 0; --i)
			{
				while (x->m_szLevel[i] &&
					x->m_szLevel[i]->m_pObj &&
					*(x->m_szLevel[i]->m_pObj) < a_rData)
				{
					x = x->m_szLevel[i];
				}
				update[i] = x;
			}
			
			x = x->m_szLevel[0];
			if (x && *(x->m_pObj) == a_rData)
			{
				DeleteNode(x, update);
				return 0;
			} else {
				return -1;
			}
			return -1;
		}

		void DelAll(void) {
			SkipListNode* pNode = m_pHeader->m_szLevel[0];
			SkipListNode* pNextNode;

			SAFE_DELETE(m_pHeader);
			while(pNode) {
				pNextNode = pNode->m_szLevel[0];
				SAFE_DELETE(pNode->m_pObj);
				SAFE_DELETE(pNode);
				pNode = pNextNode;
			}
			
			m_pHeader = NULL;
			m_pTail = NULL;
			m_nLength = 0;
			m_nLevel = 0;
			m_bInited = false;
		}

		void Dump(vector<T>& a_rVec)
		{
			SkipListNode*x = m_pHeader;
			while(x->m_szLevel[0]) {
				x = x->m_szLevel[0];
				a_rVec.push_back(*(x->m_pObj));
			}
		}


	private:
		SkipListNode* m_pHeader;
		SkipListNode* m_pTail;
		unsigned long m_nLength;
		int m_nLevel;
		bool m_bInited;
	};

}//end of namespace SkipListModule


#endif //__H__MY_SKIPLIST__
