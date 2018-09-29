#ifndef STRUCTDEF_H_
#define STRUCTDEF_H_

#include <vector>
using namespace std;

typedef struct _stFaceRect
{
	int nLeft;
	int nTop;
	int nRight;
	int nBottom;
	int nAge;		// ����
	int nGender;	// 0:����1���У�2��Ů
}FaceRect;

typedef struct _stFaceInfos
{
	int nCount;
	int nMax;
	FaceRect* pFace;
	void* pTemData;
}FaceInfos;

#endif // !STRUCTDEF_H_