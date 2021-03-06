// Demo.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include "libSharpiFace.h"

#pragma comment(lib, "libSharpiFace.lib")

#define PIC1 "face1.jpg"
#define PIC2 "face2.jpg"

typedef struct _stDataBaseItem
{
	int nId;
	char* pFeature;
}DataBaseItem;

void testCmp2Pic();
void testFaceInfo();
void testSearch();

int main(int argc, char** argv)
{
	// 检查sdk授权
	char szMCode[64] = { 0 };
	cGetMachineCode(szMCode);
	if (argc != 2)
	{
		printf("eg:Demo.exe [ACode]\nMachine Code:%s\n", szMCode);
	}
	else
	{
		if (cMachineAuthorize(argv[1]) != 0)
			printf("cMachineAuthorize fail!\n");
	}

	testCmp2Pic();
	testFaceInfo();
	testSearch();
	
	return 0;
}

void testCmp2Pic()
{
	void* pWorker = cCreateFaceWorker(0, -1);	// 只加载人脸比对模块，不打开摄像头
	if (pWorker)
	{
		float fRet = cPictureCompare(pWorker, (const char*)PIC1, (const char*)PIC2);
		printf("testCmp2Pic compare score is %f;\n\n", fRet);
	}
	cReleaseFaceWorker(pWorker);
}

void testFaceInfo()
{
	void* pWorker = cCreateFaceWorker(1, -1);
	if (pWorker)
	{
		void* pFrame = cReadImage((const char*)PIC2);
		if (pFrame)
		{
			FaceInfos stFaces = { 0 };
			cFaceDetect(pWorker, pFrame, &stFaces);
			if (stFaces.nCount > 0)
			{
				cAgeDetect(pWorker, &stFaces);
				cGenderDetect(pWorker, &stFaces);
				for (int i = 0; i < stFaces.nCount; i++)
				{
					printf("[%d/%d] age:%d, gender:%d, {(%d, %d),(%d, %d)};\n", i,
						stFaces.nCount, stFaces.pFace[i].nAge, stFaces.pFace[i].nGender,
						stFaces.pFace[i].nLeft, stFaces.pFace[i].nTop, stFaces.pFace[i].nRight, stFaces.pFace[i].nBottom);
				}
			}
			else
			{
				printf("no face!\n");
			}
			cFaceRelease(pWorker, &stFaces);
			cReleaseImage(pFrame);
		}
		else
		{
			printf("cGetFram fail!\n");
		}
		
		cReleaseFaceWorker(pWorker);
	}
}

void testSearch()
{
	void* pWorker = cCreateFaceWorker(0, 0);	// 只加载人脸比对模块，打开摄像头0
	if (pWorker)
	{
		// 建库。本处不使用真正的数据库，用数组模拟
		DataBaseItem dbTtem[2] = {0};	
		int nSize = cGetFeatureSize(pWorker);
		char* pBuf1 = (char*)malloc(nSize);
		char* pBuf2 = (char*)malloc(nSize);
		dbTtem[0].pFeature = pBuf1;
		dbTtem[1].pFeature = pBuf2;

		// 录入
		dbTtem[0].nId = 1;
		int nR1 = cFeatureExtractP(pWorker, (const char*)PIC1, dbTtem[0].pFeature);
		dbTtem[1].nId = 2;
		int nR2 = cFeatureExtractP(pWorker, (const char*)PIC2, dbTtem[1].pFeature);

		// 摄像头抓拍并在库里搜索
		while (1)
		{
			void* pFrame = cGetFrame(pWorker);
			if (pFrame)
			{
				char* pBuf = (char*)malloc(nSize);
				if (cFeatureExtractF(pWorker, pFrame, pBuf) > 0)
				{
					float fS = 0.0;
					int nId = 0;
					for (int i = 0; i < 2; i++)
					{
						float fR = cFeatureCompare(pWorker, pBuf, dbTtem[i].pFeature);
						if (fR > fS)
						{
							fS = fR;
							nId = dbTtem[i].nId;
						}
					}

					if (fS > 0.5)
						printf("the face id is %d(%f);\n", nId, fS);
					else
						printf("not found in database(%f);\n", fS);
				}
				else
				{
					printf("no face;\n");
				}
			}
			else
			{
				printf("cGetFram fail!\n");
			}
			Sleep(40);
		}
	}
	cReleaseFaceWorker(pWorker);
}

