#ifndef _DHPLAY_EX_H
#define _DHPLAY_EX_H

#include "dhplay.h"

#ifdef	__cplusplus
extern "C" {
#endif

/***********************************************************************************************/
/* 常量定义																					   */
/***********************************************************************************************/

#define PIC_BMP_32                      0       // BMP32
#define PIC_BMP_24                      1       // BMP24

/* 大华SVAC相关 */
#define SVC_LAYER_BASE					0x0001	// SVAC基本层
#define SVC_LAYER_ENHANCE				0x0002	// SVAC增强层
#define MAX_CUSTOM_EXT_COUNT            8
#define MAX_EXT_ROI_REGION_NUM          32		// 最大ROI区域扩展的个数    
#define MAX_EXT_EVENT_REGION_NUM        32		// 最大监控事件扩展的个数
#define MAX_EXT_ALERT_NUM               32		// 最大监控报警扩展的个数
#define EXT_TYPE_ROI					0x0001  // ROI区域扩展
#define EXT_TYPE_TIME					0x0002  // 绝对时间扩展
#define EXT_TYPE_ALERT					0x0004  // 报警扩展
#define EXT_TYPE_EVENT					0x0008  // 监控事件扩展
#define EXT_TYPE_AUTH					0x0010  // 认证数据
#define EXT_TYPE_CUSTOM					0x1000  // 自定义扩展

/* 中星微SVAC相关 */
#define ZXW_OSD_MAX_LEN					243     // 中星微OSD_DATA的最长字符数
#define ZXW_OSD_TYPE_NUM				3       // 中星微OSD的种类，目前支持三种：时间、通道、地点标注
#define MAX_CAR_RECORD_NUM				20		// 此定义根据与智能交通约定的一次传输最大车牌数
#define CAR_PLATE_CHARACTERS			11		// 车牌字符数
#define ID_NUMBER_CHAR					18		// 身份证号个数
#define ID_NAME_CHAR					30		// 身份证上姓名最大字符数
#define ID_NATION_CHAR					24		// 国籍字符数
#define ID_BD_CHAR						16		// 出生日期字符数
#define ID_ADDRESS_CHAR					70		// 居住地址字符数
#define ID_TIME_CHAR					19		// 时间字符数
#define MAX_ID_CARD_NUM					20		// 标准中尚未规定，自定义的，可能需要修改
#define MAX_MAC_WIFI_NUM				100		// 最大mac地址的个数，该定义可能需要修改
#define MAX_PG_NUM_RECORD				50		// 最大目标物体个数，该定义可能需要修改

/***********************************************************************************************/
/* 结构体定义																				   */
/***********************************************************************************************/

/* 日期信息 */
typedef struct __DATETIME_INFO
{
	unsigned int			nYear;			// 年
	unsigned int			nMonth;			// 月
	unsigned int			nDay;			// 日
	unsigned int			nHour;			// 时
	unsigned int			nMinute;		// 分
	unsigned int			nSecond;		// 秒
	unsigned int			nMilliSecond;	// 毫秒
}DATETIME_INFO;

/* 解码附加信息 */
typedef struct
{
	LONG			nVideoEncodeType;   // 码流类型
	LONG	        nDataLen;           // 解码数据长度
	char*           pUserData;          // 解码信息,详见DEC_EXT_PARAM_SVAC定义
	LONG	        nReserved[2];
}FRAME_DEC_EXT_INFO;

/* 大华SVAC解码库解码附加信息自定义字段 */
typedef struct
{
	unsigned char type;             // 信息类型
	unsigned char length;           // 信息长度
	unsigned char *pbuf;            // 信息指针
	unsigned char reserved[2];      // 保留
}DEC_EXT_INFO_CUSTOM;

typedef struct
{
	unsigned char subtype;					  // subtype为32,33,34时，表示按照本文档的描述进行解析。同一个subtype的扩展信息不会同时出现两个；当同类信息的扩展信息出现时，后一个扩展信息总是覆盖前一个扩展信息。
	unsigned char codeType;					  // 编码格式，当前仅0在使用，表示使用UTF-8编码
	unsigned char alignType;				  // 对齐格式，0为左对齐，1为右对齐
	unsigned char charSize;					  // 字体大小，用像素表示
	unsigned char charType;					  // 字符格式，0为白底黑边，1为黑底白边，2为白色字体，3为黑色字体
	unsigned short top_pixel;				  // 位置，按像素表示 
	unsigned short left_pixel;				  // 位置，按像素表示 
	unsigned char len;						  // 字符在 OSD_DATA中占用的字节数 
	unsigned char res[3];					  // 3个保留字节 
	unsigned char OSD_DATA[ZXW_OSD_MAX_LEN];  // OSD 字符数据，其长度由 Len 确定。支持
											  // 换行，定义'\n'为换行，'\0'为结束符（同时也受到字符长度的约束）。OSD_DATA的最长
											  // 长度为 243字节
}DEC_EXT_INFO_ZXW_OSD;

typedef struct
{
	unsigned char       m_iChannelID;         			// 车道号
	unsigned char  		m_cPlate[CAR_PLATE_CHARACTERS];	// 车牌
	unsigned char       m_iPlateColor;					// 车牌颜色
	unsigned char       m_iPlateType;         			// 车辆类型
	unsigned char 		m_iCarColor;          			// 车身颜色
	unsigned char   	m_iAlarmType;     				// 报警类型
	unsigned int     	m_iRedBeginTime;    			// 红灯开始时间，单位秒
	unsigned int     	m_iRedEndTime;      			// 红灯结束时间，单位秒
	unsigned char  		m_stCaptureTime[8];  			// 闯红灯录像的绝对时间 年-月-日-星期-时-分-秒-毫秒

}DEC_EXT_INFO_CAR_RECORD;

typedef struct{
	unsigned char    id_number[ID_NUMBER_CHAR]; // 身份证号，ASCII表示， u[8*18]
	unsigned char    reserve;                   // 一个字节长度的保留字符
	unsigned char    name[ID_NAME_CHAR];        // 姓名，GBK编码
	unsigned short   sex;                       // 性别，GBK编码
	unsigned char    nation[ID_NATION_CHAR];    // 国籍，GBK编码
	unsigned char    bD[ID_BD_CHAR];            // 出生日期，采用“2016-12-08”，ASCII表示，未使用字节清零
	unsigned char    address[ID_ADDRESS_CHAR];  // 住址，GBK编码
	unsigned char    time[ID_TIME_CHAR];        // 信息插入时间，采用“2016-12-08 10:52:45”，ASCII表示
}DEC_EXT_INFO_ID_CARD;

typedef struct{
	unsigned char           mac[6];         // mac地址
	unsigned short          range;          // WIFI设置到摄像头的距离，单位：米
}DEC_EXT_INFO_MAC_WIFI;

typedef struct{
	int object_id;                 // 目标物体编号
	int top;                       // 外围矩形左上角纵坐标
	int left;                      // 外围矩形左上角横坐标
	int bottom_diff;               // 外围矩形右下角纵坐标与左上角纵坐标的差值
	int right_diff;                // 外围矩形右下角横坐标与左上角横坐标的差值
	int bIsCrossLine;              // u(1)，是否发生越界告警，1发生；否则0
	int nCrossLineRgn;             // u(5)，目标物体越界线段编号
	int bIsCrossNet;               // u(1)，是否产生入侵告警，1发生；否则0
	int nCrossNetRgn;              // u(3)，目标物体入侵区域编号
	int nIsConverse;               // u(1)，是否产生逆行告警，1发生；否则0
	int nIndexConverse;            // u(2)，目标物体逆行区域编号
}DEC_EXT_OBJECT_INFO;

typedef struct{
	unsigned char   ver0;			// 1级版本
	unsigned char   ver1;			// 2级版本
	int             rate_move_xy;	// 尺度移位系数cs,尺度值最后需左移cs位
	int             bit_width;		// 尺度编码比特数cn
	unsigned int    width;			// 原始图像宽度
	unsigned int    height;			// 原始图像高度
	unsigned int    reserve0;		// 保留字节
	unsigned int    reserve1;
	unsigned char   reserve2;   
	int             num_record;		// 目标物体个数
	DEC_EXT_OBJECT_INFO object_info[MAX_PG_NUM_RECORD]; // 目标信息
}DEC_EXT_INFO_PERIMETER_GUARD;

typedef struct
{
	int flags;                              // 扩展数据类型标记

	int time_year;                          // 绝对时间扩展
	int time_month;
	int time_day;
	int time_hour;
	int time_minute;
	int time_second;
	int time_sec_fractional;
	int time_frame_num;

	int roi_region_num;                             // ROI区域扩展
	int roi_top_left_x[MAX_EXT_ROI_REGION_NUM];     // ROI区域左上角像素x坐标
	int roi_top_left_y[MAX_EXT_ROI_REGION_NUM];     // ROI区域左上角像素y坐标
	int roi_width[MAX_EXT_ROI_REGION_NUM];          // ROI区域宽度
	int roi_height[MAX_EXT_ROI_REGION_NUM];         // ROI区域高度

	int event_region_num;                           // 监控事件扩展
	int event_num[MAX_EXT_EVENT_REGION_NUM];
	int event_region_event_id[MAX_EXT_EVENT_REGION_NUM][16];

	int alert_num;                                  // 监控报警扩展
	int alert_region_id[MAX_EXT_ALERT_NUM];
	int alert_event_id[MAX_EXT_ALERT_NUM];
	int alert_frame_num[MAX_EXT_ALERT_NUM];

	int *auth_buf[2];                               // 认证数据buf, auth_buf[0]是基本层认证数据, auth_buf[1]是增强层认证数据
	int auth_len[2];                                // 认证数据长度, 不存在认证数据时，长度应该设置为 0
	int auth_signature_type[2];
	int auth_hash_hierarchy_flag[2];

	DEC_EXT_INFO_CUSTOM svac_ext_info_custom[MAX_CUSTOM_EXT_COUNT];			// 扩展
	DEC_EXT_INFO_ZXW_OSD svac_ext_info_zxw_osd[ZXW_OSD_TYPE_NUM];			// 存放中星微的OSD信息

	int	car_record_num;	                                                    // 存放车牌数目
	DEC_EXT_INFO_CAR_RECORD svac_ext_info_car_record[MAX_CAR_RECORD_NUM];   // 存放车牌信息

	int id_card_num;                                                        // 存放身份证个数
	DEC_EXT_INFO_ID_CARD    svac_ext_info_id_card[MAX_ID_CARD_NUM];         // 存放身份证信息

	int mac_wifi_num;                                                       // 存放mac信息个数
	DEC_EXT_INFO_MAC_WIFI   svac_ext_info_mac_wifi[MAX_MAC_WIFI_NUM];       // 存放wifi信息

	DEC_EXT_INFO_PERIMETER_GUARD svac_ext_info_perimeter_guard;             // 存放周界预警信息

}DEC_EXT_PARAM_SVAC;

typedef struct 
{
	unsigned char  chExternsion_id;		// OSD信息扩展的标号extenison_id应等于0x12
	unsigned char  chExtension_length;	// 表示extension_length之后本扩展语法元素长度
	unsigned char  chSub_type;			// 表示OSD扩展信息子类型
	unsigned char  chCode_type;			// 表示OSD字符的编码格式，值为0时，表示使用UTF-8	
	unsigned char  chAlign_type;		// 表示OSD字符的对齐格式，0：左对齐。1:右对齐
	unsigned char  chChar_size;			// 表示OSD字符字体大小
	unsigned char  chChar_type;			// OSD字符字符格式。0:白底黑边 1:黑底百变 2:白色 3：黑色 4:自动反色
	unsigned char  chTop_low8;			// top_low8和top_high8组成一个16位无符号整数top，
	unsigned char  chTop_high8;			// 表示OSD字符信息上边界在图像画面中的位置 
	unsigned char  chLeft_low8;			// left_low8和left_high8组成一个16位无符号整数，
	unsigned char  chLeft_high8;		// 表示OSD字符信息左边界在图像画面中的位置
	unsigned char  chLen;				//  表示osd_data占用的字节长度，取值为0~243
	unsigned char  chRes[3];			
	unsigned char  chOsd_data[243];			// 字符数据，长度为len字节
}DEC_EXT_SVAC2_OSD_INFO;

/* 增强支持的功能 */
typedef enum 
{
	IVSEFUNCTYPE_DEHAZE,	    // 去雾
	IVSEFUNCTYPE_DENOISE,		// 去噪
	IVSEFUNCTYPE_WB,			// 偏色校正
	IVSEFUNCTYPE_LOWLIGHT,		// 低照度增强
	IVSEFUNCTYPE_HDR,			// 宽动态
	IVSEFUNCTYPE_NUM			// 支持增强的功能个数
}IVSEFUNCTYPE;

/* ROI数据类型定义 */
typedef struct
{
    int x;          // 左上角x坐标
    int y;          // 左上角y坐标
    int width;      // 区域宽度
    int height;     // 区域高度
}IVSEROI;

/* 视频增强算法输入参数 */
typedef struct
{
    IVSEFUNCTYPE eFuncType;				// 功能选项
    IVSEROI		 cRoi;					// ROI 配置
	int			 nMode;					// 0表示图片模式， 1表示视频模式
    int			 nProcess_param[2];     // 处理参数，范围[1,5]
}IVSEPARAMS;

/***********************************************************************************************/
/* 接口																						   */
/***********************************************************************************************/

/************************************************************************/
//> 文件操作
/************************************************************************/

/**
 * 文件开始、结束时间回调函数。
 *
 * @param[in] nPort		 通道号
 * @param[in] nStartTime 文件开始时间.自1970年1月1日0点0分0秒的秒数
 * @param[in] nEndTime   文件结束时间.自1970年1月1日0点0分0秒的秒数
 * @param[in] pUserData  用户数据
 */
typedef void (CALLBACK* fFileTimeDoneCBFun)(LONG nPort, DWORD nStarTime, DWORD nEndTime, void* pUserData);

/**
 * 设置文件开始、结束时间回调。
 *
 * @param[in] nPort			     通道号
 * @param[in] FileTimeDoneCBFun  回调函数指针,不能为NULL
 * @param[in] pUserData          用户自定义参数
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetFileTimeDoneCallBack(LONG nPort, fFileTimeDoneCBFun FileTimeCBFun, void* pUserData);

/**
 * 按绝对时间查找指定位置之前的关键帧位置。
 *
 * @param[in] nPort		通道号
 * @param[in] t			绝对时间,详见SYSTEMTIME.仅用到年月日时分秒.注：在执行成功后该值存储所返回I帧的时间戳
 * @param[in] framePos  查找到的关键帧的文件位置信息结构指针,详见PFRAME_POS.
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_GetKeyFramePosByAbsTime(LONG nPort, SYSTEMTIME* t, FRAME_POS* framePos);

/**
 * 按绝对时间查找指定位置之后的关键帧位置。
 *
 * @param[in] nPort		通道号
 * @param[in] t			绝对时间,详见SYSTEMTIME.仅用到年月日时分秒.注：在执行成功后该值存储所返回I帧的时间戳
 * @param[in] framePos  查找到的关键帧的文件位置信息结构指针,详见PFRAME_POS.
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_GetNextKeyFramePosByAbsTime(LONG nPort, SYSTEMTIME* t, FRAME_POS* framePos);

/**
 * 按绝对时间设置播放时间。
 *
 * @param[in] nPort		通道号
 * @param[in] pDateTime	绝对时间
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetPlayedAbsTime(LONG nPort, DATETIME_INFO *pDateTime);

/**
 * 按文件偏移设置播放位置。
 *
 * @param[in] nPort		    通道号
 * @param[in] nFileOffset	文件偏移位置
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetPlayPosByFileOffset(LONG nPort, UINT nFileOffset);

/**
 * 设置索引创建进度回调。
 *
 * @param[in] nPort				通道号
 * @param[in] IndexProgressCB	回调函数
 * @param[in] pUser				用户数据
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
typedef void (CALLBACK* fIndexProgressCB)(LONG nPort, float fProgress, void* pUserData);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetFileIndexProgressCallBack(LONG nPort, fIndexProgressCB IndexProgressCB, void* pUser);


/**
 * 获取I帧索引信息。
 *
 * @param[in] nPort		通道号
 * @param[in] pBuffer	索引地址
 * @param[in] pSize		索引大小
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_GetIRefValue(LONG nPort, BYTE *pBuffer, DWORD *pSize);

/************************************************************************/
//> 声音相关
/************************************************************************/

/**
 * 获取音频通道总数。
 *
 * @param[in]  nPort	 通道号
 * @param[out] pChannels 输出参数[0-255]
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_GetAudioChannels(LONG nPort, DWORD* pChannels);
 
/**
 * 选择音频通道。
 *
 * @param[in]  nPort	  通道号
 * @param[in] nChannelID  音频通道从0开始
 * @param[in] bFlag       TRUE打开,FALSE关闭
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_ChooseAudio(LONG nPort, DWORD nChannelID, BOOL bFlag);

/**
 * 获取音频通道打开关闭状态。
 *
 * @param[in]  nPort	   通道号
 * @param[in]  nChannelID  音频通道[0-255]
 * @param[out] bFlag       TRUE打开,FALSE关闭
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_GetAudioChooseState(LONG nPort, DWORD nChannelID, BOOL* bFlag);

/**
 * 控制左右声道音频播放，仅对左右声道音频有效。
 *
 * @param[in]  nPort	   通道号
 * @param[in]  nChnNum     左右通道，0-左通道，1-右通道
 * @param[in] bEnable      使能 TRUE-启用， FALSE-禁用
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_EnableAudioChannel(LONG nPort, DWORD nChnNum, BOOL bEnable);

/************************************************************************/
//> 获取播放或解码信息
/************************************************************************/

/**
 * 获得当前帧率，支持小数形式。
 *
 * @param[in] nPort 通道号
 * @return float 当前帧率
 */
PLAYSDK_API float CALLMETHOD PLAY_GetCurrentFrameRateEx(LONG nPort);

/**
 * 获取最后一帧对应的YUV数据。
 *
 * @param[in] nPort 通道号
 * @param[in] pFrameDecodeInfo YUV数据信息
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_GetLastYUVFrame(LONG nPort, FRAME_DECODE_INFO* pFrameDecodeInfo);

/**
 * 录像回调函数。
 *
 * @param[in] nPort					通道号
 * @param[in] pFrameDecodeInfo      解码后的音视频数据
 * @param[in] pFrameInfo			图像和声音信息,请参见FRAME_INFO结构体
 * @param[in] pDecodeProcessInfo    用于存储解码处理后生成的数据
 * @param[in] pUserData				用户数据
 */
typedef struct 
{
	int nProcessType;			 // 处理类型, 见DECODE_DATA_PROCESS_TYPE枚举类型
	unsigned char *pOutData;     // 经处理后输出数据的地址
	unsigned int nOutDataLen;	 // 经处理后输出数据的长度
	unsigned int nOutDataBufLen; // 经处理后输出数据的buffer长度
}DECODE_DATA_PROCESS_INFO;
typedef void (CALLBACK* fDecodeDataProcessCB)(LONG nPort, FRAME_DECODE_INFO* pFrameDecodeInfo, FRAME_INFO_EX* pFrameInfo, DECODE_DATA_PROCESS_INFO *pDecodeProcessInfo, void* pUserData);

/**
 * 解码后数据回调处理，结果存入相应缓存。
 *
 * @param[in] nPort            通道号
 * @param[in] nProcessType     数据处理类型, 详见DECODE_DATA_PROCESS_TYPE定义
 * @param[in] cbDecDataProcess 解码回调处理函数指针
 * @param[in] pUserData        用户数据
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
typedef enum
{
	NO_PROCESS = 0,				// 无处理
	PCM_MIX_PLAY = 1,			// 音频混音播放
}DECODE_DATA_PROCESS_TYPE;
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDecodeDataProcessCallBack(LONG nPort, int nProcessType, fDecodeDataProcessCB cbDecDataProcess, void* pUserData);

/**
 * 数字签名回调函数。
 *
 * @param[in] nPort		通道号
 * @param[in] nFrameID  帧序号
 * @param[in] bSuccess  校验是否通过
 * @param[in] pUserData	用户数据
 */
typedef void (CALLBACK* fCheckDigitalSignCB)(LONG nPort, int nFrameID, BOOL bSuccess, void* pUserData);

/**
 * 设置数字签名回调。
 *
 * @param[in] nPort            通道号
 * @param[in] pDigitalSignCB   数字签名回调函数
 * @param[in] pUserData        用户数据
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDigitalSignCallBack(LONG nPort, fCheckDigitalSignCB pDigitalSignCB, void* pUserData);

/**
 * 开启解码信息回调，针对SVAC码流中的些监控信息。
 *
 * @param[in] nPort            通道号
 * @param[in] DecInfoCallBack  解码信息回调回调函数
 * @param[in] pUserData        用户数据
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
typedef void (CALLBACK* fMultiFrameDecCallBack)(LONG nPort, LONG nStreamID, char* pData, LONG nLen, 
												FRAME_INFO* stFrameInfo, void* pUserData, LONG nReserved1);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetMultiFrameDecCallBack(LONG nPort, fMultiFrameDecCallBack DecInfoCallBack, void* pUserData);

/**
 * 开启多帧信息回调，针对SVAC码流。
 *
 * @param[in] nPort            通道号
 * @param[in] DecInfoCallBack  多帧信息回调回调函数
 * @param[in] pUserData        用户数据
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
typedef void (CALLBACK* fDecInfoCallBack)(LONG nPort, FRAME_DEC_EXT_INFO* pDecInfo, void* pUserData, LONG nReserved);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDecInfoCallBack(LONG nPort, fDecInfoCallBack DecInfoCallBack, void* pUserData);

/**
 * 设置视频隐私恢复使能。
 *
 * @param[in] nPort            通道号
 * @param[in] bRecover		   TRUE 视频隐私恢复,FALSE 视频隐私遮盖
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetPrivacyRecover(LONG nPort, BOOL bRecover);

/************************************************************************/
//> 图像后处理
/************************************************************************/

/**
 * 开启视频去雾算法功能。
 *
 * @param[in] nPort            通道号
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_StartDeHaze(LONG nPort);

/**
 * 设置视频去雾参数。
 *
 * @param[in] nPort            通道号
 * @param[in] ALightValue	   设定的大气光强的值，范围0-255
 * @param[in] AutoLightOn      代表开启自动寻找大气光强；0-关闭自动，开启手动, 默认为1
 * @param[in] AutoRun          代表一直开启去雾功能，0-自动判断是否雾天并去雾，默认为1
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDehazeParams(LONG nPort, int ALightValue, int AutoLightOn, int AutoRun);

/**
 * 停止视频去雾算法功能。
 *
 * @param[in] nPort            通道号
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_StopDeHaze(LONG nPort);

/**
 * 开启视频增强算法功能。
 *
 * @param[in] nPort            通道号
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_StartIVSE(LONG nPort);

/**
 * 设置视频增强参数，可以多次调用来组合使用多种IVSE库的功能。
 *
 * @param[in] nPort            通道号
 * @param[in] pIVSEParams      IVSEPARAMS结构体参数
 * @param[in] bEnable          对应于IVSEPARAMS中的IVSEFUNCTYPE功能选项，使能开关
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetIVSEParams(LONG nPort, IVSEPARAMS* pIVSEParams, BOOL bEnable);

/**
 * 停止视频增强算法功能。
 *
 * @param[in] nPort            通道号
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_StopIVSE(LONG nPort);

/**
 * 开启图像锐化处理。
 *
 * @param[in] nPort           通道号
 * @param[in] level           处理等级,0-关闭,6-最强,默认等级4
 * @param[in] algMode         算法模式,预留接口,目前只支持0
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_StartEdgeEnhance(LONG nPort, int level, int algMode);

/**
 * 关闭图像锐化处理。
 *
 * @param[in] nPort           通道号
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_StopEdgeEnhance(LONG nPort);

/**
 * 开启视频防抖。
 *
 * @param[in] nPort           通道号
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_StartVideoStable(LONG nPort);

/**
 * 关闭视频防抖。
 *
 * @param[in] nPort           通道号
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_StopVideoStable(LONG nPort);



#define MAX_REGION_NUM	32	// 最大矩形框数目
typedef struct video_rect	// 矩形框
{
	int ulx;	// 左上角点x像素
	int uly;	// 左上角点y像素
	int lrx;	// 右下角点x像素
	int lry;	// 右下角点y像素
} VIDEO_RECT, *PVIDEO_RECT;

typedef enum mosaic_mode	// 马赛克模式
{
	MOSAIC_OFF = 0,			// 停止马赛克处理
	MOSAIC_ADJUST,			// 马赛克位置调整,适用于画面马赛克位置实时调整
	MOSAIC_TRANSFER			// 马赛克转录，适用于码流转录的情况，可以不进行画面渲染
} MOSAIC_MODE;

typedef struct mosaic_region	// 马赛克区域
{
	int			nMosaicType;				// 马赛克类型，定义马赛克模糊等级，输入为正整数,越高越模糊
	int			nRegionNum;					// 马赛克矩形框数目
	VIDEO_RECT	pFaceRects[MAX_REGION_NUM];	// 马赛克矩形框信息
} MOSAIC_REGION, *PMOSAIC_REGION;

/**
 * 开启图像马赛克处理
 *
 * @param[in] nPort           通道号
 * @param[in] fMosaicInfo     马赛克区域信息采集回调，用于获取视频帧马赛克区域
 * @param[in] pUserData		  用户信息 
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
// 马赛克矩形框信息采集接口
typedef void (CALLBACK* fMosaicRegionInfo)(LONG nPort, int nFrameId, MOSAIC_REGION* pFaceRegion, void* pUserData); 
PLAYSDK_API BOOL CALLMETHOD PLAY_StartMosaic(LONG nPort, MOSAIC_MODE mosaicMode, fMosaicRegionInfo fMosaicInfo, void* pUserData);

/**
 * 关闭图像马赛克处理。
 *
 * @param[in] nPort           通道号
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_StopMosaic(LONG nPort);


/************************************************************************/
//> 同步播放
/************************************************************************/

/**
 * 打开同步播放。
 *
 * @return void*，同步播放控制句柄，在调用同步播放控制接口时需要传入该句柄，返回NULL表示失败
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API void* CALLMETHOD PLAY_OpenPlayGroup();

/**
 * 添加一路已经代开的视频至同步播放中。
 *
 * @param[in] hPlayGroup  同步播放句柄，由PLAY_OpenPlayGroup返回
 * @param[in] nPort       要加入同步播放队列的通道号
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_AddToPlayGroup(void* hPlayGroup, LONG nPort);

/**
 * 从同步播放队列中删除指定通道号。
 *
 * @param[in] hPlayGroup  同步播放句柄，由PLAY_OpenPlayGroup返回
 * @param[in] nPort       从同步播放队列中删除的通道号
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_DelFromPlayGroup(void* hPlayGroup, LONG nPort);

/**
 * 从当前时间点正放或倒放。
 *
 * @param[in] hPlayGroup  同步播放句柄，由PLAY_OpenPlayGroup返回
 * @param[in] nDirection  播放方向 0表示正方，1表示倒放
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetPlayGroupDirection(void* hPlayGroup, int nDirection);

/**
 * 设置播放速度。
 *
 * @param[in] hPlayGroup  同步播放句柄，由PLAY_OpenPlayGroup返回
 * @param[in] fSpeed  播放速度，范围[1/64~64.0]，小于1表示慢放，大于1表示正放，当播放速度较快时可能会抽帧播放
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetPlayGroupSpeed(void* hPlayGroup, float fSpeed);

/**
 * 暂停或继续。
 *
 * @param[in] hPlayGroup  同步播放句柄，由PLAY_OpenPlayGroup返回
 * @param[in] bPause TRUE暂停,FLASE恢复
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_PausePlayGroup(void* hPlayGroup, BOOL bPause);

/**
 * 单帧播放。
 *
 * @param[in] hPlayGroup  同步播放句柄，由PLAY_OpenPlayGroup返回
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_StepPlayGroup(void* hPlayGroup);

/**
 * 采用绝对时间进行定位。
 *
 * @param[in] hPlayGroup  同步播放句柄，由PLAY_OpenPlayGroup返回
 * @param[in] pstDateTime 绝对时间
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SeekPlayGroup(void* hPlayGroup, DATETIME_INFO* pstDateTime);

/**
 * 查询当前组中正在播放的时间。
 *
 * @param[in]  hPlayGroup  同步播放句柄，由PLAY_OpenPlayGroup返回
 * @param[out] pDateTime   查询获得的时间
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_QueryGroupPlayingTime(void* hPlayGroup,  DATETIME_INFO *pDateTime);

/**
 * 关闭同步播放控制。
 *
 * @param[in] hPlayGroup  同步播放句柄，由PLAY_OpenPlayGroup返回
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_ClosePlayGroup(void* hPlayGroup);

/**
 * 设置同步播放基准通道。
 *
 * @param[in] hPlayGroup  同步播放句柄，由PLAY_OpenPlayGroup返回
 * @param[in] nPort  同步播放基准通道
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetPlayGroupBaseChannel(void* hPlayGroup, LONG nPort);

/************************************************************************/
//> 鱼眼
/************************************************************************/

/* 鱼球联动 */
typedef struct
{
	int   himg_width;                       // 从相机图像宽
	int   himg_height;                      // 从相机图像高
	int   *zoom_list;						// 球机倍数表
	int   zoom_list_size;					// 球机倍数表档位个数
}MHFPTZ_INITPARAM;

/* 鱼眼矫正参数 */
typedef struct 
{
	int radius;						// 目标鱼眼圆半径——输入为8192坐标系
	int originX;					// 目标鱼眼圆圆心X——输入为8192坐标
	int originY;					// 目标鱼眼圆圆心Y——输入为8192坐标
	FISHEYE_SIZE srcSize;			// 输入鱼眼圆的宽高
	FISHEYE_SIZE dstSize;			// 输出矫正图的宽高
	int winId;						// 目标窗口的id
	FISHEYE_MOUNTMODE mountMode;    // 鱼眼安装模式
	FISHEYE_CALIBRATMODE calibMode; // 矫正模式
	FISHEYE_REGIONPARAM regionParam;// 通过Fisheye_EptzUpdate ，FISHEYE_EPTZ_CMD_GET_CUR_REGION 获得

}FISHRECTIFY_INFO;

/**
 * 鱼球联动功能扩展接口。
 *
 * @param[in] nPort				通道号
 * @param[in] startType			开启类型，见FISHEYE_START_TYPE定义
 * @param[in] funcType			开启功能，见FISHEYE_FUNC_TYPE定义					
 * @param[in] ptzChannelParam	鱼球联动初始化通道参数，startType为0时，ptzChannelParam填NULL
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
typedef enum
{
    FISHEYE_ONLY_RECTIFY = 0,      // 只开启鱼眼校正
    FISHEYE_RECTIFY_FPTZ,          // 同时开启联动和校正
    FISHEYE_ONLY_FPTZ,             // 只开启鱼球联动           
    FISHEYE_RECTIFY_180,           // 180度鱼眼矫正
}FISHEYE_START_TYPE;

typedef enum
{
    FISHEYE_FUNC_NONE = 0,              // 默认不开启
    FISHEYE_FUNC_ONLY_INTELLIGENT,      // 只开启智能帧功能
    FISHEYE_FUNC_ONLY_CATCHPIC,         // 只开启抓图          
    FISHEYE_FUNC_INTELLIGENT_CATCHPIC,  // 开启智能帧和抓图
}FISHEYE_FUNC_TYPE;
PLAYSDK_API BOOL CALLMETHOD PLAY_StartFisheyeEx(LONG nPort, int startType, int funcType, MHFPTZ_INITPARAM* ptzChannelParam);

/**
 * 鱼球联动功能扩展接口，支持一鱼多球。
 *
 * @param[in] nPort				通道号
 * @param[in] startType			开启类型，见FISHEYE_START_TYPE定义
 * @param[in] funcType			开启功能，见FISHEYE_FUNC_TYPE定义								
 * @param[in] ptzChannelParam	鱼球联动初始化通道参数，startType为0时，ptzChannelParam填NULL
 * @param[in] ptzChannelNum	    鱼球联动初始化通道数
 * @param[in] imgMaxOutput		输出图像最大的分辨率
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_StartFisheyeMPTZ(LONG nPort, int startType, int funcType, MHFPTZ_INITPARAM* ptzChannelParam, int ptzChannelNum, FISHEYE_SIZE* pImgMaxOutput);


/**
 * 给定矫正图上坐标，计算出原始鱼眼圆圆上坐标。
 *
 * @param[in]  param		矫正参数，详见FishRectify_Info
 * @param[in]  inrpt		输入点，8192坐标系
 * @param[out] orpt			转换后的坐标
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */	
PLAYSDK_API BOOL CALLMETHOD PLAY_FisheyeTrancFormCoordinate(FISHRECTIFY_INFO *param, FISHEYE_POINT2D* inrpt, FISHEYE_POINT2D *orpt);

/**
 * 给定矫正图上坐标，计算出原始鱼眼圆圆上坐标。
 *
 * @param[in]     param		矫正参数，详见FishRectify_Info
 * @param[in]     rpt1		矫正图上的一个点，8192坐标系
 * @param[in]     rpt2		矫正图上的一个点，8192坐标系
 * @param[in/out] in_num	两点间的点个数
 * @param[out]    fpts		插值后得到的点序列，包括两个端点，8192坐标系
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */		
PLAYSDK_API BOOL CALLMETHOD PLAY_FisheyeTrancFormCurve(FISHRECTIFY_INFO *param, FISHEYE_POINT2D* rpt1,FISHEYE_POINT2D* rpt2,int *in_num, FISHEYE_POINT2D *fpts);

/**
 * 设置透镜张开角度，张开的角度越大，显示的图片越小。
 *
 * @param[in]     nPort		 通道号
 * @param[in]     nRegionNum 显示区域序号,0~(MAX_DISPLAY_WND-1),如果为0,则将设置的区域显示在主窗口中
 * @param[in]     fFovy		 张开的角度大小(0-180)
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */	
PLAYSDK_API BOOL CALLMETHOD PLAY_SetStereoPerspectiveFovy(LONG nPort, DWORD nRegionNum, float fFovy);

/**
 * 设置透镜移动的距离。
 *
 * @param[in]     nPort		 通道号
 * @param[in]     nRegionNum 显示区域序号,0~(MAX_DISPLAY_WND-1),如果为0,则将设置的区域显示在主窗口中
 * @param[in]     enMoveDicret		 移动的方向
 * @param[in]     fDistancefDistance 移动的距离
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
typedef enum
{
	STEREO_EYE_NO_MOVE = -1,                // 没有移动
	STEREO_EYE_MOVE_BACK,                   // 往后移动
	STEREO_EYE_MOVE_RIGHT,                  // 往右移动
	STEREO_EYE_MOVE_TOP,                    // 向上移动
}STEREO_EYE_MOVE_DIRECTION;
PLAYSDK_API BOOL CALLMETHOD PLAY_SetStereoEyeMoveDistance(LONG nPort, DWORD nRegionNum, STEREO_EYE_MOVE_DIRECTION enMoveDicret, float fDistance);

/**
 * 设置物体旋转的角度。
 *
 * @param[in]     nPort		 通道号
 * @param[in]     nRegionNum 显示区域序号,0~(MAX_DISPLAY_WND-1),如果为0,则将设置的区域显示在主窗口中
 * @param[in]     fXOffset	 鼠标在x轴旋转的角度（0-360度）
 * @param[in]     fYOffset   鼠标在y轴旋转的角度（0-360度）
 * @param[in]     fZOffset   鼠标在z轴旋转的角度（0-360度）
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */	
PLAYSDK_API BOOL CALLMETHOD PLAY_SetStereoRotate(LONG nPort, DWORD nRegionNum, float fXOffset, float fYOffset, float fZOffset);

/**
 * 调整摄像机的角度。
 *
 * @param[in]     nPort		 通道号
 * @param[in]     nRegionNum 显示区域序号,0~(MAX_DISPLAY_WND-1),如果为0,则将设置的区域显示在主窗口中
 * @param[in]     fXOffset	 摄像机以自身作为原点，绕Z轴（即摄像机头顶法线）顺时针旋转的角度增量(以度为单位)
 * @param[in]     fYOffset   摄像机以自身作为原点，绕X轴顺时针旋转的角度增量(以度为单位)
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */	
PLAYSDK_API BOOL CALLMETHOD PLAY_SetStereoView(LONG nPort, DWORD nRegionNum, float fXOffset, float fYOffset);

/**
 * 设置观察的模式。
 *
 * @param[in]     nPort		 通道号
 * @param[in]     nRegionNum 显示区域序号,0~(MAX_DISPLAY_WND-1),如果为0,则将设置的区域显示在主窗口中
 * @param[in]     enStereoViewMode	通道号观察的模式，见STEREO_VIEW_MODE
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */	
typedef enum
{
	STEREO_COMMON_VIEW,                     // 普通模式，可以看到整个模型
	STEREO_INNER_VIEW,                      // 内视点模式
}STEREO_VIEW_MODE;
PLAYSDK_API BOOL CALLMETHOD PLAY_SetStereoViewMode(LONG nPort, DWORD nRegionNum, STEREO_VIEW_MODE enStereoViewMode);

/**
 * 设置显示的模式。
 *
 * @param[in]     nPort	   通道号
 * @param[in]     mode     模式，见FISHEYE_CALIBRATMODE
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */	
PLAYSDK_API BOOL CALLMETHOD PLAY_SetCalibratMode(LONG nPort, FISHEYE_CALIBRATMODE mode);

/**
 * 设置文件及路径的编码格式。
 *
 * @param[in] nFileNameEncodeType 文件名编码格式
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 默认ansi编码，如果调用此接口，所有与文件名相关的接口均会按照设置的类型进行操作。
 */
typedef enum
{
	FILE_NAME_ENCODE_ANSI,
    FILE_NAME_ENCODE_UTF8,
}FileNameEncodeType;
PLAYSDK_API BOOL CALLMETHOD PLAY_SetFileNameEncodeType(FileNameEncodeType nFileNameEncodeType);

/************************************************************************/
//> 抓图
/************************************************************************/

/**
 * 获得绝对时间点上面的图片。
 *
 * @param[in] filepath   保存的文件路径
 * @param[in] time		 绝对时间，time填NULL则回调第一帧
 * @param[in] fcbDec     解码回调函数
 * @param[in] pUserData  用户数据
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_GetTimePicture(const char* filepath, struct tm* time, fDecCBFun fcbDec, void* pUserData);

/**
 * 图像数据转为BMP格式。
 *
 * @param[in] pBuf       图像数据指针
 * @param[in] nSize		 图像数据大小
 * @param[in] nWidth     图像宽度
 * @param[in] nHeight    图像高度
 * @param[in] nType      数据类型 T_RGB32,T_UYVY等
 * @param[in] sFileName  要保存的文件名,建议以.BMP作为扩展名
 * @param[in] nBmpType   BMP类型 PIC_BMP_32表示BMP32,PIC_BMP_24表示BMP24
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_ConvertToBmpFileEx(char * pBuf,LONG nSize,LONG nWidth,LONG nHeight,LONG nType, char *sFileName,int nBmpType);

/************************************************************************/
//> 录制或转码功能
/************************************************************************/

/**
 * 设置预录的环境。
 *
 * @param[in] nPort 通道号
 * @param[in] nTime 预录多少时间，单位秒
 * @param[in] tmpDirectory 临时的预录目录
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetupPrepareTime(LONG nPort,int nTime,const char* tmpDirectory);

/**
 * 开始预录。
 *
 * @param[in] nPort 通道号
 * @param[in] pFileName 录像位置
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_StartPrepareRecord(LONG nPort,const char* pFileName);

/**
 * 停止预录。
 *
 * @param[in] nPort 通道号
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_StopPrepareRecord(LONG nPort);

/**
 * 开始变分辨率的AVI转换。
 *
 * @param[in] nPort 通道号
 * @param[in] sFileName 录像存放路径
 * @param[in] lWidth  目的宽
 * @param[in] lHeight 目的高
 * @param[in] uiSegmentSize 分段下载时，设置分块视频大小，不设置分段下载时，置0，大小单位为M
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_StartAVIResizeConvert(LONG nPort, char *sFileName, LONG lWidth, LONG lHeight, unsigned int uiSegmentSize);

/**
 * 停止变分辨率的AVI转换。
 *
 * @param[in] nPort 通道号
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_StopAVIResizeConvert(LONG nPort);

/**
 * 录像回调函数。
 *
 * @param[in] nPort     通道号
 * @param[in] pData     数据指针
 * @param[in] nDataLen  数据长度
 * @param[in] nOffset   从起始数据偏移位置, avi格式会回写,外部需按照此偏移来写文件, -1表示此字段无效
 * @param[in] pUserData 用户数据
 */
typedef void (CALLBACK* fRecordDataCBFun)(LONG nPort, unsigned char* pData, int nDataLen, LONGLONG nOffset, void* pUserData);

/**
 * 开始流数据录像,只对流模式有用,在PLAY_Play之后调用。
 * avi/mp4支持变分辨率转码, 需结合PLAY_ResolutionScale接口使用。
 *
 * @param[in] nPort      通道号
 * @param[in] sFileName  录像文件名,如果文件名中有不存在的文件夹,就创建该文件夹
 * @param[in] idataType  取值DATA_RECORD_TYPE
 * @param[in] fListenter 回调函数
 * @param[in] pUserData  用户数据
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_StartDataRecordEx(LONG nPort, char *sFileName, int idataType, fRecordDataCBFun fListenter, void* pUserData);

/**
 * 分段录像信息回调函数。
 *
 * @param[in] nPort     通道号
 * @param[in] pSegmentFileName     分段文件绝对路径指针
 * @param[in] nFileSize  分段文件长度，单位:字节
 * @param[in] pUserData 用户数据
 */
typedef void (CALLBACK* fSegmentRecordDataCBFun)(LONG nPort, char* pSegmentFileName, ULONGLONG nFileSize, void* pUserData);

/**
 * 设置分段数据转码信息，这个函数在PLAY_StartDataRecordEx前调用有效
 *
 * @param[in] nPort      通道号
 * @param[in] uiSegmentSize 分段下载时，设置分块视频大小，不设置分段下载时，置0，大小单位为M
 * @param[in] fListenter 回调函数
 * @param[in] pUserData  用户数据
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetSegmentRecordData(LONG nPort, unsigned int uiSegmentSize, fSegmentRecordDataCBFun fListenter, void* pUserData);

/************************************************************************/
//> 解码及显示设置
/************************************************************************/

/**
 * 图像缩放，仅支持手机平台。
 *
 * @param[in]  nPort	    通道号
 * @param[in]  scale		缩放比例[1.0, 8.0]
 * @param[out] nRegionNum   显示区域序号
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_Scale(LONG nPort, float scale, DWORD nRegionNum);

/**
 * 图像平移，仅支持手机平台。
 *
 * @param[in]  nPort	    通道号
 * @param[in]  x			x方向平移坐标，绝对值		
 * @param[in]  y            y方向平移坐标，绝对值
 * @param[in]  nRegionNum   显示区域序号
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_Translate(LONG nPort, float x, float y, DWORD nRegionNum);

/**
 * 图像归一化重置平移，缩放操作，仅支持手机平台。
 *
 * @param[in]  nPort	    通道号
 * @param[in]  nRegionNum   显示区域序号
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetIdentity(LONG nPort, DWORD nRegionNum);

/**
 * 获取当前图像缩放值，仅支持手机平台。
 *
 * @param[in]  nPort	    通道号
 * @param[in]  nRegionNum   显示区域序号
 * @return float，当前缩放系数
 */
PLAYSDK_API float CALLMETHOD PLAY_GetScale(LONG nPort, DWORD nRegionNum);

/**
 * 获取当前x轴平移坐标，仅支持手机平台。
 *
 * @param[in]  nPort	    通道号
 * @param[in]  nRegionNum   显示区域序号
 * @return float，当前x轴平移坐标
 */
PLAYSDK_API float CALLMETHOD PLAY_GetTranslateX(LONG nPort, DWORD nRegionNum);

/**
 * 获取当前y轴平移坐标，仅支持手机平台。
 *
 * @param[in]  nPort	    通道号
 * @param[in]  nRegionNum   显示区域序号
 * @return float，当前y轴平移坐标
 */
PLAYSDK_API float CALLMETHOD PLAY_GetTranslateY(LONG nPort, DWORD nRegionNum);

/**
 * 清屏功能，仅支持手机、Mac平台，PLAY_Stop前调用有效。
 *
 * @param[in]  nPort	    通道号
 * @param[in]  red			rgb部分
 * @param[in]  green	    rgb部分
 * @param[in]  blue			rgb部分
 * @param[in]  alpha	    alpha部分
 * @param[in]  nRegionNum   显示区域序号
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_CleanScreen(LONG nPort, float red, float green, float blue, float alpha, DWORD nRegionNum);

/**
 * 选择显示SVAC编码SVC的基本层或增强层。
 *
 * @param[in]  nPort	    通道号
 * @param[in]  nFrameID		要显示的层(0: 基本层，1: 增强层)
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_ChooseFrame(LONG nPort, LONG nFrameID);

/**
 * 实际码流分辨率缩放成目的分辨率渲染。
 *
 * @param[in]  nPort	     通道号
 * @param[in]  nTargetWidth	 目的分辨率宽
 * @param[in]  nTargetHeight 目的分辨率高
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_ResolutionScale(LONG nPort, int nTargetWidth, int nTargetHeight);

/**
 * 用于文件流倒放场景下刷新最后一个GOP。
 *
 * @param[in]  nPort	     通道号
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_Flush(LONG nPort);

/**
 * 设置播放缓冲区最大缓冲帧数。
 *
 * @param[in]  nPort	 通道号
 * @param[in]  nNum	     如果是软解，则缓冲帧数[2,12]，如果是硬解，，则缓冲帧数[2,16]
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDisplayBuf(LONG nPort,DWORD nNum);

/**
 * 设置或增加显示区域,可以做局部放大显示或显示窗口部分区域。
 *
 * @param[in]  nPort	  通道号
 * @param[in]  nRegionNum 显示区域序号,0~(MAX_DISPLAY_WND-1),如果为0,则将设置的区域显示在主窗口中
 * @param[in]  pSrcRect	  视频画面局部显示区域,范围为[0, 视频宽][0, 视频高]
 * @param[in]  pDstRect	  部分窗口显示区域,客户区坐标
 * @param[in]  hDestWnd	  显示窗口句柄
 * @param[in]  bEnable	  打开(设置)或关闭显示区域
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDisplayRegionEx(LONG nPort,DWORD nRegionNum, DISPLAYRECT *pSrcRect, DISPLAYRECT *pDstRect, HWND hDestWnd, BOOL bEnable);

/**
 * 鱼眼矫正回调函数。
 *
 * @param[in] nPort		     通道号
 * @param[in] pBuf           主通道数据指针
 * @param[in] nSize          主通道数据长度
 * @param[in] nWidth	     主通道图像宽
 * @param[in] nHeight	     主通道图像高
 * @param[in] pSecondBuf     辅通道数据指针
 * @param[in] nSecondSize    辅通道数据长度
 * @param[in] nSecondWidth	 辅通道图像宽
 * @param[in] nSecondHeight	 辅通道图像高
 * @param[in] pUserData  用户数据
 */
typedef void (CALLBACK* fDoubleVisibleDecCBFun)(LONG nPort,char * pBuf, int nSize, int nWidth, int nHeight, 
													char* pSecondBuf, int nSecondSize, int nSecondWidth, int nSecondHeight, void* pUserData);
/**
 * 设置鱼眼矫正回调。
 *
 * @param[in] nPort		 通道号
 * @param[in] DataCBFun  回调函数
 * @param[in] pUserData  用户数据
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */												
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDoubleVisibleDecCallBack(LONG nPort, fDoubleVisibleDecCBFun DataCBFun, void* pUserData);

/**
 * 开启拼接算法。
 *
 * @param[in] nPort	 通道号
 * @param[in] nMode  模式，0对应基本模式，1对应1+3模式，2对应1+5模式, 3对应1+1模式（电子放大）
 *					 4对应1P+3, 5对应1P+6, 6对应1+1模式（左右调换）
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */	
PLAYSDK_API BOOL CALLMETHOD PLAY_SplitProc(LONG nPort, int nMode);

/**
 * 拼接算法，更新需要放大的矩形位置。
 *
 * @param[in] nPort	 通道号
 * @param[in] pAreaRect  矩形坐标数组的起始地址
 *			 如果nMode是0，则应为NULL
 *			 如果nMode是1，则该数组的大小应为3
  *			 如果nMode是2，则该数组的大小应为5 
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */	
PLAYSDK_API BOOL CALLMETHOD PLAY_SplitProcUpdate(LONG nPort, DISPLAYRECT* pAreaRect);

/**
 * 初始化第三方解密库。
 *
 * @param[in] nPort	 通道号
 * @param[in] kmcSvrIP    ip地址
 * @param[in] kmcSvrPort  端口
 * @param[in] macAddr     mac地址
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */	
PLAYSDK_API BOOL CALLMETHOD PLAY_InitThirdPartyLibrary(LONG nPort, const char* kmcSvrIP,int kmcSvrPort,const char* macAddr);

/**
 * 设置解码策略,错误码流花屏或跳秒。
 *
 * @param[in] nPort	 通道号
 * @param[in] nStrategyType   
 *				16: 表示解码中遇到frame不连续，提前返回
 *				8 : 表示解码中遇到码流数据不符合协议当成解码错误
 *				0 : 表示解码中遇到码流数据不符合协议继续解码，错误码流会花屏
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */	
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDecodeStrategy(LONG nPort, int nStrategyType);

/**
 * 开启音频滤波。
 *
 * @param[in] nPort	 通道号
 * @param[in] nMode  nMode可以取-1,0,1,2,3,4  
 *				-1:  不进行噪声消除
 *				0:   噪声消除的程度最低，对有用语音信号的损害最小
 *				4:   噪声消除的程度最大,对有用语音信号的损害最大
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */	
PLAYSDK_API BOOL CALLMETHOD PLAY_SetSEnhanceMode(LONG nPort,int nMode);

/**
 * 第三方解密扩展接口。
 *
 * @param[in] nPort	 通道号
 * @param[in] decryptHook  回调函数体 
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */	
enum ThirdDecryptType
{
	DECRYPT_KTJM = 4, // 凯天解密
	DECRYPT_SYJM,	  // 晟元解密
	DECRYPT_HZSD,     // 杭师大算法
	DECRYPT_ZBQL,     // 中标麒麟算法
};

typedef struct 
{ 
	int    type;           // 第三方解密类型,详见ThirdDecryptType
	BOOL (*Init)();		   // 初始化接口,全局初始化一次
	BOOL (*DeInit)();	   // 反初始化接口
	void* (*Open)();	   // 打开解密通道, 返回值不能为空
	BOOL (*Decrypt)(void* handle, unsigned char* inData,  unsigned int inLen, unsigned char* outData, unsigned int* outLen);// 解密, 对返回值有要求(1成功0失败)
	BOOL (*Close)(void* handle); // 关闭解密通道
}ThirdDecryptHook;
PLAYSDK_API BOOL CALLMETHOD PLAY_Register3rdDecryptHook(ThirdDecryptHook* decryptHook);

/**
 * 设置SVAC解密密钥。
 *
 * @param[in] nPort	   通道号
 * @param[in] key      密钥指针 
 * @param[in] key_len  密钥长度
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */	
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDecodeKey(LONG nPort, const unsigned char *key, unsigned int key_len);

/************************************************************************/
//> 私有数据
/************************************************************************/

/* 文件信息帧 */
typedef struct __FILE_INFO_FRAME
{
	unsigned int		nFrameSubType;	  // 帧子类型，动检数据帧、事件帧等
	DATETIME_INFO*		pstDateTimeStart; // 开始时间
	DATETIME_INFO*		pstDateTimeEnd;   // 结束时间
	unsigned char*		pFrameData;		  // 帧数据
	unsigned int		nFrameDataLen;	  // 帧数据长度
} FILE_INFO_FRAME;

typedef struct __FILE_INFO_FRAME_SEARCH
{
#define PLAY_INFO_TYPE_MOTIONDECT     1    // 动检
#define PLAY_INFO_TYPE_EVENT		  2    // 事件
	unsigned int		nFileFrameType;	   // 搜索类型，可以组合，如 PLAYER_INFO_TYPE_MOTIONDECT | PLAYER_INFO_TYPE_EVENT
	DATETIME_INFO		stStartDataTime;   // 开始时间
	DATETIME_INFO		stEndDataTime;     // 结束时间
	DISPLAYRECT			rtDetectedRegion;  // 总区域中的动检检测范围，动检帧时有效，区域矩形为0时，表示全区域搜索
	DISPLAYRECT			rtTotal;		   // 总区域, 动检帧时有效
} FILE_INFO_FRAME_SEARCH;

typedef struct __FILE_INFO_IMAGE
{
	tPicFormats	   imageType;			   // 图片的类型
	unsigned char* pPicBuf;				   // 图片的缓冲指针
	unsigned int   nPicBufLen;			   // 图片的长度
} FILE_INFO_IMAGE;

/**
 * 设置文件信息帧回调函数。
 */
typedef int (CALLBACK* fFileInfoFrameCBFun)(LONG nPort, FILE_INFO_IMAGE* pFileInfoImage, FILE_INFO_FRAME* pFileInfoFrame, void* pUserParam);
PLAYSDK_API BOOL CALLMETHOD	PLAY_SetFileInfoFrameCallback(LONG nPort, fFileInfoFrameCBFun fFileInfoFrame, tPicFormats imageType, void* pUserParam);

/**
 * 设置文件信息帧分析进度回调函数。
 */
typedef int (CALLBACK *fAnalyzePositionCBFun)(LONG nPort, DATETIME_INFO* pstDateTime, void* pUserParam);
PLAYSDK_API BOOL CALLMETHOD	PLAY_SetAnalyzePositionCallback(LONG nPort, fAnalyzePositionCBFun fAnalyzePosition, void* pUserParam);

/**
 * 需要在索引建立完成之后，开始文件信息帧检测，输入搜索条件。
 */
PLAYSDK_API BOOL CALLMETHOD	PLAY_StartFileFrameDetect(LONG nPort, FILE_INFO_FRAME_SEARCH* pFileInfoFrameSearch);

/**
 * 中止搜索。
 */
PLAYSDK_API BOOL CALLMETHOD	PLAY_StopFileFrameDetect(LONG nPort);

/**
 * 多目视频源坐标信息回调函数。
 *
 * @param[in] nPort		 通道号
 * @param[in] pSensor    多目坐标指针, 共mSensor*nSensor大小
 * @param[in] mSensor    m元
 * @param[in] nSensor    n元
 * @param[in] nPicWidth  码流宽
 * @param[in] nPicHeight 码流高
 * @param[in] pUserData  用户数据
 */
typedef struct
{
	short leftTopX;
	short leftTopY;
	short rightBottomX;
	short rightBottomY;
}SensorInfo;
typedef void (CALLBACK* fSensorInfoCallBack)(LONG nPort, SensorInfo* pSensor, int mSensor, int nSensor, int nPicWidth, int nPicHeight, void* pUserData);

/**
 * 设置多目视频源坐标信息回调。
 *
 * @param[in]  nPort	    通道号
 * @param[in]  pCallBack	回调函数
 * @param[in]  pUserData    用户数据
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetMultiSensorCallBack(LONG nPort, fSensorInfoCallBack pCallBack, void* pUserData);

/**
 * osd数据回调函数。
 *
 * @param[in] nPort		 通道号
 * @param[in] pBuf       数据指针
 * @param[in] nSize      数据长度
 * @param[in] pUserData  用户数据
 */
typedef void (CALLBACK* fOSDInfoCallBackFun)(LONG nPort,char * pBuf,int nSize, void* pUserData);

/**
 * 设置osd数据回调。
 *
 * @param[in]  nPort	    通道号
 * @param[in]  OSDInfoFun	回调函数
 * @param[in]  pUserData    用户数据
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetOSDInfoCallBack(LONG nPort, fOSDInfoCallBackFun OSDInfoFun, void* pUserData);

/**
 * 设置osd信息，用于YUV叠加，仅Windows有效。
 *
 * @param[in]  nPort	    通道号
 * @param[in]  pOSDInfo	    osd信息
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
#define OSD_ATTRIBUTE_FLAG_REGION   (1 << 0)
#define OSD_ATTRIBUTE_FLAG_EXTRA    (1 << 1)
#define OSD_ATTRIBUTE_FLAG_TIME	    (1 << 2)
#define MAX_REGION_NUMBER 128
typedef struct{
    unsigned int     attrflag;                    // 使能标记
    unsigned char    region[MAX_REGION_NUMBER];   // 区域信息
    unsigned char    extra[MAX_REGION_NUMBER];    // 附加信息
    SYSTEMTIME       startTime;                   // 起始时间
}YUV_OSD_INFO;
PLAYSDK_API BOOL CALLMETHOD PLAY_SetYUVOSDInfo(LONG nPort, YUV_OSD_INFO* pOSDInfo);

/**
 * 设置osd信息用用平台扩展方法，用于YUV叠加, 需要指定大华字体库
 *
 * @param[in]  nPort	    通道号
 * @param[in]  pOSDInfo	    osd信息
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
typedef struct{
	int	x;							// 旋转点像素x位置
	int	y;							// 旋转点像素y位置
	unsigned int	r;				// osd叠加颜色r，范围0-255
	unsigned int	g;				// osd叠加颜色g，范围0-255
	unsigned int	b;				// osd叠加颜色b，范围0-255
	unsigned int	alpha;			// osd叠加透明度，范围0-255
	char			szOsdData[512];	// osd数据，使用utf-8编码
	unsigned int	fontX;			// 字体宽度, 使用大华字体时无效
	unsigned int	fontY;			// 字体高度, 最大512
	unsigned int	rotateAngle;	// 旋转角度，范围0-359度
	char			reserved[16];	// 保留字段
} OsdDataInfo;

typedef struct{
	bool			bDahuaFont;		// 是否是大华字体
	char			fontPath[256];	// 字体文件位置
	unsigned int	osdCount;		// OSD叠加数量，最多32个
	OsdDataInfo		osdList[32];	// OSD列表
	char			reserved[64];	// 保留字段
}YUV_OSD_INFO_EX;
PLAYSDK_API BOOL CALLMETHOD PLAY_SetYUVOSDInfoEx(LONG nPort, YUV_OSD_INFO_EX* pOSDInfo);

/************************************************************************/
//> 车载硬盘
/************************************************************************/
/**
 * 查询tag信息(Windows32平台)。
 *
 * @param[in] nDiskNo 磁盘号
 * @param[in] pTagInfo 保存查询到的tag信息，由外部分配内存
 * @param[in] nMaxLen TAG_INFO结构的个数
 * @return DWORD，查询到的条目数
 */
typedef struct
{
	unsigned int    firstClusNo;
    USER_TIME       timeStamp; 
    unsigned int    channel;   
    int             state;
    int             duration;
    char            reserved1[12]; 
    char            tagName[160];
    char            userName[32];
    char            channelName[64];
    char            reserved2[128];
    unsigned int    partNo;           	
}TAG_INFO;
PLAYSDK_API DWORD CALLMETHOD PLAY_QueryTagInfo(LONG nDiskNo, TAG_INFO* pTagInfo, DWORD nMaxLen);

typedef struct
{
	char channelTitle[256];			//通道名称，字符串
	char deviceip[36];				//远程设备的IP地址，字符串
	unsigned int    remoteChannel;	//远程通道号，从0开始
	char    reserved[216];			//保留          	
}CHANNEL_INFO;
PLAYSDK_API DWORD CALLMETHOD PLAY_QueryChannelInfo(LONG nDiskNo, CHANNEL_INFO* pChannelInfo);

/************************************************************************/
//> nacl平台特定接口
/************************************************************************/
#ifdef __native_client__

#define FISHEYE_REGION 16
/**
 * ui线程主动调用渲染接口。
 *
 * @param[in]  nPort	 通道号
 * @param[in]  nX        窗口left坐标
 * @param[in]  nY        窗口top坐标
 * @param[in] nWidth     窗口宽
 * @param[in] nHeight    窗口高
 * @param[in] nRegionNum 显示区域序号，默认为0
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */	
PLAYSDK_API BOOL CALLMETHOD PLAY_OutsideRender(LONG nPort, int nX, int nY, int nWidth, int nHeight, unsigned int nRegionNum);

namespace pp
{
	class Instance;
}
/**
 * nacl主线程调用此接口设置句柄地址。
 *
 * @param[in]  pInstance 传入的pp::instance地址 
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */	
PLAYSDK_API BOOL CALLMETHOD PLAY_SetNACLInstance(pp::Instance * pInstance);

#endif //__native_client__

/************************************************************************/
//> 通用设置
/************************************************************************/

typedef enum GetSetType
{
	GRAPH   = 0x100,
	GRAPH_FORWARD_BACK_SWITCH_FRAMESEQ,		// 网络回放正倒放无缝切换点(时间戳)
	GRAPH_IFRAME_COSTTIME_ADJUST_FLAG,		// 纯I帧场景是否自适应调整播放时长,1:调整(帧率*帧间隔),0:不调整(原始帧率播放)
	SOURCE  = 0x200,
	DECODE  = 0x400,
	DECODE_ENGINE = 0x487,//解码方式，如软解，硬解
	RENDER  = 0x800,
	RENDER_STEREO_PERSPECTIVE_FOVY,
	RENDER_STEREO_ROTATE_X,	
	RENDER_STEREO_ROTATE_Y,	
	RENDER_STEREO_ROTATE_Z,	
	RENDER_STEREO_EYE_MOVE_BACK,            // 往前移动
	RENDER_STEREO_EYE_MOVE_RIGHT,           // 往右移动
	RENDER_STEREO_EYE_MOVE_TOP,             // 向上移动
	METHOD  = 0x1000,
	CBMgr   = 0x2000,
	ARENDER = 0x4000,
    RECORDER = 0x8000,
    RECORDER_ENCODE_BITRATE,
}GetSetType;

/**
 * 设置Int32参数。
 *
 * @param[in] nPort	   通道号
 * @param[in] type     类型 
 * @param[in] val      类型对应的值
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */	
PLAYSDK_API BOOL CALLMETHOD PLAY_SetInt32(LONG nPort, GetSetType type, int val);

/**
 * 获取Int32参数。
 *
 * @param[in] nPort	     通道号
 * @param[in] type       类型 
 * @param[out] pval      类型对应的值
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */	
PLAYSDK_API BOOL CALLMETHOD PLAY_GetInt32(LONG nPort, GetSetType type, int* pVal);

/**
 * 获取Double参数。
 *
 * @param[in]  nPort	   通道号
 * @param[in]  nRegionNum  显示区域序号,0~(MAX_DISPLAY_WND-1),如果为0,则将设置的区域显示在主窗口中
 * @param[in]  type        类型 
 * @param[out] pval        类型对应的值
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */	
PLAYSDK_API BOOL CALLMETHOD PLAY_GetDoubleRegion(LONG nPort, DWORD nRegionNum, GetSetType type, double* pVal);

/**
 * 设置对讲是否主动开启扬声器，默认开启，IOS平台下有效
 *
 * @param[in]  bEnable  为TRUE表示打开，FALSE关闭
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */	
PLAYSDK_API BOOL CALLMETHOD PLAY_SetSpeakerAutoEnable(BOOL bEnable);

/**
 * 打开流,已知输入码流封装格式。
 *
 * @param[in] nPort 通道号
 * @param[in] pFileHeadBuf 文件头数据
 * @param[in] nSize 文件头长度
 * @param[in] nBufPoolSize 设置播放器中存放数据流的缓冲区大小。范围是SOURCE_BUF_MIN~SOURCE_BUF_MAX
 * @param[in] nStreamType 码流封装格式,详见STREAM_TYPE
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_OpenStreamEx(LONG nPort,PBYTE pFileHeadBuf,DWORD nSize,DWORD nBufPoolSize, DWORD nStreamType);

typedef enum
{
	PLAY_PARAM_RTP,					// RTP解析
	PLAY_PARAM_RAWAUDIO = 9,		// 裸音频解析(PCM、711等无音频标识数据)
}PLAY_PARAM_TYPE;

typedef struct
{
	unsigned int struct_size;
	unsigned int encode_type;				// 编码类型,详见ENCODE_VIDEO_TYPE定义
	unsigned int payload_type;				// 负载类型
	unsigned int audio_sample_rate;			// 采样率
	unsigned int audio_channels;			// 声道
	unsigned int channel_count;				// 通道数
	unsigned int channel_id;				// 通道ID
	unsigned int discard_flag;				// 丢弃丢帧flag
	unsigned int audio_payload_type;		// 音频载荷类型
	unsigned int audio_encode_type;			// 音频编码类型，详见ENCODE_AUDIO_TYPE
	unsigned int deinter_lace;				// 解交错信息
	unsigned int frame_rate;				// 设置帧率
}PLAY_RTP_PARSER_PARAM;

typedef struct
{
    unsigned int structSize;		// 结构体大小
    unsigned int encodetype;		// 音频编码类型,详见SP_ENCODE_AUDIO_TYPE
    unsigned int sampleRate;		// 采样率
    unsigned short bitsPerSample;	// 采样位数
    unsigned short channels;		// 声道
    unsigned char reserved[8];		// 保留字段
}PLAY_RAWAUDIO_PARSER_PARAM;

/**
 * 设置通用参数,已知输入码流封装格式对应的参数集。
 *
 * @param[in] nParamType 参数类型详见PLAY_PARAM_TYPE
 * @param[in] pParam 类型对应的结构体数据
 * @param[in] nParamLen pParam结构体大小
 * @return BOOL，成功返回TRUE，失败返回FALSE
 * @note 如果返回失败，可以调用PLAY_GetLastErrorEx接口获取错误码。
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetParam(LONG nPort, int nParamType, const void* pParam, unsigned int nParamLen);

/**  
 * 设置翻译文本,在PLAY_RenderPrivateData(LONG nPort, BOOL bTrue, LONG nReserve)接口之后调用
 *
 * @param[in] language 翻译文本字符串
 * @return BOOL，成功返回true，不成功返回false
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetTranslateString(const char* language);

/**
 * 设置开启/关闭正倒放无缝切换。
 *
 * @param[in] nPort	       通道号
 * @param[in] bEnable    开启/关闭
 * @return BOOL，成功返回TRUE，失败返回FALSE
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetSeamlessSwitch(LONG nPort, BOOL bEnable);

/************************************************************************/
//> 无效接口
/************************************************************************/

PLAYSDK_API BOOL CALLMETHOD PLAY_SetPandoraWaterMarkCallBack(LONG nPort, fGetWaterMarkInfoCallbackFunc pFunc, void* pUserData);
PLAYSDK_API BOOL CALLMETHOD PLAY_StartDeNoise(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDeNoiseParams(LONG nPort, int nTemporal);
PLAYSDK_API BOOL CALLMETHOD PLAY_StopDeNoise(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetVideoPerTimer(int iVal);
PLAYSDK_API BOOL CALLMETHOD PLAY_GetVideoPerTimer(int* pVal);
PLAYSDK_API BOOL CALLMETHOD PLAY_InputVideoData(LONG nPort,PBYTE pBuf,DWORD nSize);
PLAYSDK_API BOOL CALLMETHOD PLAY_InputAudioData(LONG nPort,PBYTE pBuf,DWORD nSize);
typedef void (CALLBACK * fVerifyCBFun)(LONG nPort, FRAME_POS * pFilePos, DWORD bIsVideo, void* pUserData);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetVerifyCallBack(LONG nPort, DWORD nBeginTime, DWORD nEndTime, fVerifyCBFun VerifyFun, void* pUserData);
typedef void (CALLBACK * fSourceBufCBFun)(LONG nPort,DWORD nBufSize, void* pUserData,void*pResvered);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetSourceBufCallBack(LONG nPort,
													  DWORD nThreShold,
													  fSourceBufCBFun SourceBufCBFun,
													  void* pUserData,
													  void *pReserved);
PLAYSDK_API BOOL CALLMETHOD PLAY_ResetSourceBufFlag(LONG nPort);
PLAYSDK_API DWORD CALLMETHOD PLAY_GetDisplayBuf(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDisplayType(LONG nPort,LONG nType);
PLAYSDK_API LONG CALLMETHOD PLAY_GetDisplayType(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_RefreshPlayEx(LONG nPort,DWORD nRegionNum);
PLAYSDK_API BOOL CALLMETHOD PLAY_CloseStreamEx(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_AdjustFluency(LONG nPort, int level);
PLAYSDK_API BOOL CALLMETHOD PLAY_SurfaceChange(LONG nPort, HWND hWnd);
PLAYSDK_API BOOL CALLMETHOD PLAY_ViewResolutionChanged(LONG nPort, int nWidth, int nHeight, DWORD nRegionNum);
typedef void (CALLBACK* fMultiFrameCallBack)(LONG nPort, LONG nStreamID, void* pUserData, LONG nReserved);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetMultiFrameCallBack(LONG nPort, fMultiFrameCallBack MultiFrameCallBack, void* pUser);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetRenderMode(LONG nPort, RenderType nMode);
typedef enum
{
	FISHSHOWMODE_WALL_PANORAMA = 0,       
	FISHSHOWMODE_CEIL_PANORAMA,          
	FISHSHOWMODE_CEIL_PANORAMA_TWO,       
	FISHSHOWMODE_FLOOR_PANORAMA,          
	FISHSHOWMODE_FLOOR_PANORAMA_TWO,      
	FISHSHOWMODE_ONE_O_THREE,            
	FISHSHOWMODE_CEIL_ONE_REGION = 10,    
	FISHSHOWMODE_CEIL_FOUR_REGION,        
	FISHSHOWMODE_ORIGINAL,               
	FISHSHOWMODE_WALL_ONE_REGION,         
	FISHSHOWMODE_WALL_FOUR_REGION,       
	FISHSHOWMODE_FLOOR_ONE_REGION,        
	FISHSHOWMODE_FLOOR_FOUR_REGION,       
	FISHSHOWMODE_WALL_ONE_O_THREE,	      
	FISHSHOWMODE_CEIL_ONE_O_THREE,	     
	FISHSHOWMODE_FLOOR_ONE_O_THREE,	     
}FISHSHOWMODES;
typedef enum
{
	FISHEPTZOPT_UPDATE_FOCUS,                   
	FISHEPTZOPT_ZOOM_IN,                        
	FISHEPTZOPT_ZOOM_OUT,                       
	FISHEPTZOPT_MOVE_UP,                       
	FISHEPTZOPT_MOVE_DOWN,                      
	FISHEPTZOPT_MOVE_LEFT,                      
	FISHEPTZOPT_MOVE_RIGHT,                     
	FISHEPTZOPT_AUTO_ROTATE_CLOCKWISE,          
	FISHEPTZOPT_AUTO_ROTATE_COUNTERCLOCKWISE,  
	FISHEPTZOPT_STOP_AUTO_ROTATE,				
	FISHEPTZOPT_GET_POSITION,					
	FISHEPTZOPT_SELECT_REGION_ZOOMIN_ON,       
	FISHEPTZOPT_SELECT_REGION_ZOOMIN_OFF,		
	FISHEPTZOPT_RESTORE_DEFAULT_LOCATION,		
}FISHEPTZOPTS;
PLAYSDK_API BOOL CALLMETHOD PLAY_SetFisheyeParams(LONG nPort, int nX, int nY, int nRadius, int nLensDirection, FISHSHOWMODES mode);
PLAYSDK_API BOOL CALLMETHOD PLAY_FisheyeGetPosition(LONG nPort, int row, int column, int *pX, int *pY);
PLAYSDK_API BOOL CALLMETHOD PLAY_OldFisheyeEptzUpdate(LONG nPort, int *pX, int *pY, int *pHAngle, int *pVAngle, FISHEPTZOPTS ops, int nWinNum,
													  int nZoomStep, int nPtStep, int nRotateStep);
PLAYSDK_API BOOL CALLMETHOD PLAY_FisheyeTrancFormTrackFrame(LONG nPort, void *ptrackframe,int track_frame_size);
PLAYSDK_API BOOL CALLMETHOD PLAY_InitDDraw(HWND hWnd);
PLAYSDK_API int	CALLMETHOD PLAY_GetCaps();
PLAYSDK_API DWORD CALLMETHOD PLAY_GetFileHeadLength();
PLAYSDK_API BOOL CALLMETHOD PLAY_RealeseDDraw();
PLAYSDK_API DWORD CALLMETHOD PLAY_GetDDrawDeviceTotalNums();
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDDrawDevice(LONG nPort,DWORD nDeviceNum);
PLAYSDK_API BOOL CALLMETHOD PLAY_GetDDrawDeviceInfo(DWORD nDeviceNum,LPSTR  lpDriverDescription,DWORD nDespLen,LPSTR lpDriverName ,DWORD nNameLen,LONG *hhMonitor);
PLAYSDK_API int	CALLMETHOD PLAY_GetCapsEx(DWORD nDDrawDeviceNum);
PLAYSDK_API BOOL CALLMETHOD PLAY_ThrowBFrameNum(LONG nPort,DWORD nNum);
PLAYSDK_API BOOL CALLMETHOD PLAY_InitDDrawDevice();
PLAYSDK_API void CALLMETHOD PLAY_ReleaseDDrawDevice();
PLAYSDK_API BOOL CALLMETHOD PLAY_Back(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDDrawDeviceEx(LONG nPort,DWORD nRegionNum,DWORD nDeviceNum);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetOverlayMode(LONG nPort,BOOL bOverlay,COLORREF colorKey);
PLAYSDK_API LONG CALLMETHOD PLAY_GetOverlayMode(LONG nPort);
PLAYSDK_API COLORREF CALLMETHOD PLAY_GetColorKey(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetTimerType(LONG nPort,DWORD nTimerType,DWORD nReserved);
PLAYSDK_API BOOL CALLMETHOD PLAY_GetTimerType(LONG nPort,DWORD *pTimerType,DWORD *pReserved);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetMDRange(LONG nPort,DISPLAYRECT* rc,DWORD nVauleBegin,DWORD nValueEnd,DWORD nType);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetMDThreShold(LONG nPort, DWORD ThreShold);
PLAYSDK_API DWORD CALLMETHOD PLAY_GetMDPosition(LONG nPort, DWORD Direction, DWORD nFrame, DWORD* MDValue);
typedef void (CALLBACK *CutProgressFunc)(DWORD nPort, int iProgress, DWORD dwUser);
PLAYSDK_API BOOL CALLMETHOD PLAY_CutFileSegment(LONG nPort, 
												LONG lBeginTime, 
												LONG lEndTime, 
												CutProgressFunc pFunc, 
												char *sOutFilePath, 
												DWORD dwUser);
PLAYSDK_API BOOL CALLMETHOD PLAY_ChangeRate(LONG nPort, int rate);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDisplayScale(LONG nPort, float fScale, DWORD nRegionNum);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetMemMinimized(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_EnableRecitfy(LONG nPort,BOOL bEnable);

#ifdef	__cplusplus
}
#endif

#endif


