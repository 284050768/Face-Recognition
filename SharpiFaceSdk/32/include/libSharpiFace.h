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
	* @brief      获取机器码，把机器码发给厂商注册后获得注册码
	* @param[in]  pBuf		存放机器码的buf，大小为64字节
	* @return     失败返回-1， 成功返回0
	*/
	LIBFACE_API int cGetMachineCode(char* pBuf);

	/**
	* @brief      检查授权，未授权时能用管理员身份试用60天
	* @param[in]  pMachineSN	从厂商获得的注册码
	* @return     失败返回负数， 成功返回0
	*/
	LIBFACE_API int cMachineAuthorize(const char* pMachineSN);

	/**
	* @brief      创建人脸识别对象
	* @param[in]  nFlag		初始化标志，0：只加载人脸比对模块，1：加载人脸比对和性别年龄检测模块
	* @param[in]  nCam		要打开的摄像头序号，-1不打开
	* @return     失败返回NULL， 成功返回人脸识别对象
	*/
	LIBFACE_API void* cCreateFaceWorker(int nFlag, int nCam);

	/**
	* @brief      获取摄像头的帧。注意不要释放返回的内存空间
	* @param[in]  pWorker		人脸识别对象
	* @return     失败返回NULL， 成功返回图像帧，实际是cv::IplImage*
	*/
	LIBFACE_API void* cGetFrame(void* pWorker);

	/**
	* @brief      读取照片,用完需要cReleaseImage释放内存
	* @param[in]  file		照片路径
	* @return     失败返回NULL， 成功返回图像帧，实际是cv::IplImage*
	*/
	LIBFACE_API void* cReadImage(const char* file);

	/**
	* @brief      把帧保存为图片
	* @param[in]  file		照片路径
	* @param[in]  pFrame		图像帧，实际是cv::IplImage*
	* @return     失败返回-1， 成功返回0
	*/
	LIBFACE_API int cSaveImage(const char* file, void* pFrame);

	/**
	* @brief      释放cReadImage返回的内存空间
	* @param[in]  pFrame		图像帧，实际是cv::IplImage*
	* @return     void
	*/
	LIBFACE_API void cReleaseImage(void* pFrame);

	/**
	* @brief      图像格式转换，cv::IplImage*转HBITMAP。注意需要cReleasehBitmap释放返回的内存空间
	* @param[in]  pFrame		图像帧，实际是cv::IplImage*
	* @return     失败返回NULL， 成功返回HBITMAP
	*/
	LIBFACE_API void* cIplImage2hBitmap(void* pFrame);

	/**
	* @brief      释放cIplImage2hBitmap返回的内存空间
	* @param[in]  hBitmap		图像hBitmap
	* @return     void
	*/
	LIBFACE_API void cReleasehBitmap(void* hBitmap);

	/**
	* @brief      人脸检测
	* @param[in]  pWorker	人脸识别对象
	* @param[in]  pFrame	图像帧，实际是cv::IplImage*
	* @param[in]  pFaces	用于存放检测结果
	* @return     失败返回-1， 成功返回0
	*/
	LIBFACE_API int cFaceDetect(void* pWorker, void* pFrame, FaceInfos* pFaces);

	/**
	* @brief      年龄检测，需先进行人脸检测
	* @param[in]  pWorker	人脸识别对象
	* @param[in]  pFaces	人脸检测时的pFaces，同时也保存结果在FaceRect.nAge
	* @return     失败返回-1， 成功返回0
	*/
	LIBFACE_API int cAgeDetect(void* pWorker, FaceInfos* pFaces);

	/**
	* @brief      性别检测，需先进行人脸检测
	* @param[in]  pWorker	人脸识别对象
	* @param[in]  pFaces	人脸检测时的pFaces，同时也保存结果在FaceRect.nGender
	* @return     失败返回-1， 成功返回0
	*/
	LIBFACE_API int cGenderDetect(void* pWorker, FaceInfos* pFaces);

	/**
	* @brief      获取特征值大小
	* @param[in]  pWorker		人脸识别对象
	* @return     失败返回-1， 成功返回特征值大小
	*/
	LIBFACE_API int cGetFeatureSize(void* pWorker);

	/**
	* @brief      提取第nIndex张脸特征值，需先进行人脸检测
	* @param[in]  pWorker	人脸识别对象
	* @param[in]  pFaces	人脸检测时的pFaces
	* @param[in]  nIndex	第nIndex张脸
	* @param[in]  pFeature	存放特征值的内存空间，应预先申请，大小为cGetFeatureSize()
	* @return     失败返回-1， 成功返回0
	*/
	LIBFACE_API int cFeatureExtract(void* pWorker, FaceInfos* pFaces, int nIndex, void* pFeature);

	/**
	* @brief      提取帧中最大脸的特征值
	* @param[in]  pWorker	人脸识别对象
	* @param[in]  pFrame	帧
	* @param[in]  pFeature	存放特征值的内存空间，应预先申请，大小为cGetFeatureSize()
	* @return     失败返回-1， 成功返回脸数
	*/
	LIBFACE_API int cFeatureExtractF(void* pWorker, void* pFrame, void* pFeature);

	/**
	* @brief      提取图片中最大脸的特征值
	* @param[in]  pWorker	人脸识别对象
	* @param[in]  file		照片
	* @param[in]  pFeature	存放特征值的内存空间，应预先申请，大小为cGetFeatureSize()
	* @return     失败返回-1， 成功返回脸数
	*/
	LIBFACE_API int cFeatureExtractP(void* pWorker, const char* file, void* pFeature);

	/**
	* @brief      特征值比对
	* @param[in]  pWorker		人脸识别对象
	* @param[in]  pFeature1		待比对特征值1
	* @param[in]  pFeature2		待比对特征值2
	* @return     失败返回-1， 成功返回相似度（0.0 - 1.0）
	*/
	LIBFACE_API float cFeatureCompare(void* pWorker, void* pFeature1, void* pFeature2);

	/**
	* @brief      比对两帧中的最大脸
	* @param[in]  pWorker		人脸识别对象
	* @param[in]  pFrame1		照片1
	* @param[in]  pFrame2		照片2
	* @return     失败返回-1， 成功返回相似度（0.0 - 1.0）
	*/
	LIBFACE_API float cFrameCompare(void* pWorker, void* pFrame1, void* pFrame2);

	/**
	* @brief      比对两张图片中的最大脸
	* @param[in]  pWorker		人脸识别对象
	* @param[in]  file1		照片1
	* @param[in]  file2		照片2
	* @return     失败返回-1， 成功返回相似度（0.0 - 1.0）
	*/
	LIBFACE_API float cPictureCompare(void* pWorker, const char* file1, const char* file2);

	/**
	* @brief      释放人脸
	* @param[in]  pWorker	人脸识别对象
	* @param[in]  pFaces	人脸检测时的pFaces
	* @return     失败返回-1， 成功返回0
	*/
	LIBFACE_API int cFaceRelease(void* pWorker, FaceInfos* pFaces);

	/**
	* @brief      反初始化SDK
	* @param[in]  pWorker			人脸识别对象
	* @return     失败返回-1， 成功返回0
	*/
	LIBFACE_API int cReleaseFaceWorker(void* pWorker);
#ifdef __cplusplus
}
#endif

#endif
