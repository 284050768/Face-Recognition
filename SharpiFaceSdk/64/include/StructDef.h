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
	int nAge;		// ÄêÁä
	int nGender;	// 0:³ö´í£¬1£ºÄÐ£¬2£ºÅ®
}FaceRect;

typedef struct _stFaceInfos
{
	int nCount;
	int nMax;
	FaceRect* pFace;
	void* pTemData;
}FaceInfos;

#endif // !STRUCTDEF_H_