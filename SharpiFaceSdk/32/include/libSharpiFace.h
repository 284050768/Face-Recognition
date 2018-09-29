#ifndef _LIB_SHARPIFACE_H_
#define _LIB_SHARPIFACE_H_

#ifdef LIBSHARPIFACE_EXPORTS
#define LIBFACE_API	__declspec(dllexport)
#else
#define LIBFACE_API	__declspec(dllimport)
#endif // LIBSLIVENESS_EXPORTS
#define SDK_VER "0.18.0929.0"

#include "StructDef.h"

#ifdef __cplusplus
extern "C" {
#endif
	/**
	* @brief      ��ȡ�����룬�ѻ����뷢������ע�����ע����
	* @param[in]  pBuf		��Ż������buf����СΪ64�ֽ�
	* @return     ʧ�ܷ���-1�� �ɹ�����0
	*/
	LIBFACE_API int cGetMachineCode(char* pBuf);

	/**
	* @brief      �����Ȩ��δ��Ȩʱ���ù���Ա�������60��
	* @param[in]  pMachineSN	�ӳ��̻�õ�ע����
	* @return     ʧ�ܷ��ظ����� �ɹ�����0
	*/
	LIBFACE_API int cMachineAuthorize(const char* pMachineSN);

	/**
	* @brief      ��������ʶ�����
	* @param[in]  nFlag		��ʼ����־��0��ֻ���������ȶ�ģ�飬1�����������ȶԺ��Ա�������ģ��
	* @param[in]  nCam		Ҫ�򿪵�����ͷ��ţ�-1����
	* @return     ʧ�ܷ���NULL�� �ɹ���������ʶ�����
	*/
	LIBFACE_API void* cCreateFaceWorker(int nFlag, int nCam);

	/**
	* @brief      ��ȡ����ͷ��֡��ע�ⲻҪ�ͷŷ��ص��ڴ�ռ�
	* @param[in]  pWorker		����ʶ�����
	* @return     ʧ�ܷ���NULL�� �ɹ�����ͼ��֡��ʵ����cv::IplImage*
	*/
	LIBFACE_API void* cGetFrame(void* pWorker);

	/**
	* @brief      ��ȡ��Ƭ,������ҪcReleaseImage�ͷ��ڴ�
	* @param[in]  file		��Ƭ·��
	* @return     ʧ�ܷ���NULL�� �ɹ�����ͼ��֡��ʵ����cv::IplImage*
	*/
	LIBFACE_API void* cReadImage(const char* file);

	/**
	* @brief      ��֡����ΪͼƬ
	* @param[in]  file		��Ƭ·��
	* @param[in]  pFrame		ͼ��֡��ʵ����cv::IplImage*
	* @return     ʧ�ܷ���-1�� �ɹ�����0
	*/
	LIBFACE_API int cSaveImage(const char* file, void* pFrame);

	/**
	* @brief      �ͷ�cReadImage���ص��ڴ�ռ�
	* @param[in]  pFrame		ͼ��֡��ʵ����cv::IplImage*
	* @return     void
	*/
	LIBFACE_API void cReleaseImage(void* pFrame);

	/**
	* @brief      ͼ���ʽת����cv::IplImage*תHBITMAP��ע����ҪcReleasehBitmap�ͷŷ��ص��ڴ�ռ�
	* @param[in]  pFrame		ͼ��֡��ʵ����cv::IplImage*
	* @return     ʧ�ܷ���NULL�� �ɹ�����HBITMAP
	*/
	LIBFACE_API void* cIplImage2hBitmap(void* pFrame);

	/**
	* @brief      �ͷ�cIplImage2hBitmap���ص��ڴ�ռ�
	* @param[in]  hBitmap		ͼ��hBitmap
	* @return     void
	*/
	LIBFACE_API void cReleasehBitmap(void* hBitmap);

	/**
	* @brief      �������
	* @param[in]  pWorker	����ʶ�����
	* @param[in]  pFrame	ͼ��֡��ʵ����cv::IplImage*
	* @param[in]  pFaces	���ڴ�ż����
	* @return     ʧ�ܷ���-1�� �ɹ�����0
	*/
	LIBFACE_API int cFaceDetect(void* pWorker, void* pFrame, FaceInfos* pFaces);

	/**
	* @brief      �����⣬���Ƚ����������
	* @param[in]  pWorker	����ʶ�����
	* @param[in]  pFaces	�������ʱ��pFaces��ͬʱҲ��������FaceRect.nAge
	* @return     ʧ�ܷ���-1�� �ɹ�����0
	*/
	LIBFACE_API int cAgeDetect(void* pWorker, FaceInfos* pFaces);

	/**
	* @brief      �Ա��⣬���Ƚ����������
	* @param[in]  pWorker	����ʶ�����
	* @param[in]  pFaces	�������ʱ��pFaces��ͬʱҲ��������FaceRect.nGender
	* @return     ʧ�ܷ���-1�� �ɹ�����0
	*/
	LIBFACE_API int cGenderDetect(void* pWorker, FaceInfos* pFaces);

	/**
	* @brief      ��ȡ����ֵ��С
	* @param[in]  pWorker		����ʶ�����
	* @return     ʧ�ܷ���-1�� �ɹ���������ֵ��С
	*/
	LIBFACE_API int cGetFeatureSize(void* pWorker);

	/**
	* @brief      ��ȡ��nIndex��������ֵ�����Ƚ����������
	* @param[in]  pWorker	����ʶ�����
	* @param[in]  pFaces	�������ʱ��pFaces
	* @param[in]  nIndex	��nIndex����
	* @param[in]  pFeature	�������ֵ���ڴ�ռ䣬ӦԤ�����룬��СΪcGetFeatureSize()
	* @return     ʧ�ܷ���-1�� �ɹ�����0
	*/
	LIBFACE_API int cFeatureExtract(void* pWorker, FaceInfos* pFaces, int nIndex, void* pFeature);

	/**
	* @brief      ��ȡ֡�������������ֵ
	* @param[in]  pWorker	����ʶ�����
	* @param[in]  pFrame	֡
	* @param[in]  pFeature	�������ֵ���ڴ�ռ䣬ӦԤ�����룬��СΪcGetFeatureSize()
	* @return     ʧ�ܷ���-1�� �ɹ���������
	*/
	LIBFACE_API int cFeatureExtractF(void* pWorker, void* pFrame, void* pFeature);

	/**
	* @brief      ��ȡͼƬ�������������ֵ
	* @param[in]  pWorker	����ʶ�����
	* @param[in]  file		��Ƭ
	* @param[in]  pFeature	�������ֵ���ڴ�ռ䣬ӦԤ�����룬��СΪcGetFeatureSize()
	* @return     ʧ�ܷ���-1�� �ɹ���������
	*/
	LIBFACE_API int cFeatureExtractP(void* pWorker, const char* file, void* pFeature);

	/**
	* @brief      ����ֵ�ȶ�
	* @param[in]  pWorker		����ʶ�����
	* @param[in]  pFeature1		���ȶ�����ֵ1
	* @param[in]  pFeature2		���ȶ�����ֵ2
	* @return     ʧ�ܷ���-1�� �ɹ��������ƶȣ�0.0 - 1.0��
	*/
	LIBFACE_API float cFeatureCompare(void* pWorker, void* pFeature1, void* pFeature2);

	/**
	* @brief      �ȶ���֡�е������
	* @param[in]  pWorker		����ʶ�����
	* @param[in]  pFrame1		��Ƭ1
	* @param[in]  pFrame2		��Ƭ2
	* @return     ʧ�ܷ���-1�� �ɹ��������ƶȣ�0.0 - 1.0��
	*/
	LIBFACE_API float cFrameCompare(void* pWorker, void* pFrame1, void* pFrame2);

	/**
	* @brief      �ȶ�����ͼƬ�е������
	* @param[in]  pWorker		����ʶ�����
	* @param[in]  file1		��Ƭ1
	* @param[in]  file2		��Ƭ2
	* @return     ʧ�ܷ���-1�� �ɹ��������ƶȣ�0.0 - 1.0��
	*/
	LIBFACE_API float cPictureCompare(void* pWorker, const char* file1, const char* file2);

	/**
	* @brief      �ͷ�����
	* @param[in]  pWorker	����ʶ�����
	* @param[in]  pFaces	�������ʱ��pFaces
	* @return     ʧ�ܷ���-1�� �ɹ�����0
	*/
	LIBFACE_API int cFaceRelease(void* pWorker, FaceInfos* pFaces);

	/**
	* @brief      ����ʼ��SDK
	* @param[in]  pWorker			����ʶ�����
	* @return     ʧ�ܷ���-1�� �ɹ�����0
	*/
	LIBFACE_API int cReleaseFaceWorker(void* pWorker);
#ifdef __cplusplus
}
#endif

#endif
