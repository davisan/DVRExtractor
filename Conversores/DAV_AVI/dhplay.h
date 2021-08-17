#ifndef _PLAY_H_
#define _PLAY_H_

#if (defined(WIN32) || defined(WIN64))
	#ifdef play_EXPORTS
		#define PLAYSDK_API __declspec(dllexport)
	#else
		#define PLAYSDK_API __declspec(dllimport)
	#endif
	#define CALLMETHOD __stdcall
	#define CALLBACK   __stdcall
#else
	#define CALLMETHOD
	#define CALLBACK
	#define PLAYSDK_API //extern "C"
#endif

#if defined(WIN32) || defined(WIN64)
#include <windows.h>
#else
#ifdef __OBJC__
#include "objc/objc.h"
#else
#define BOOL        int
#endif
#define BYTE		unsigned char
#define PBYTE		BYTE*
#define LPBYTE		BYTE*
#ifndef LONG
#define LONG		int
#endif
#ifndef DWORD
#define DWORD		unsigned int
#endif
#define WORD		unsigned short
#define COLORREF	DWORD
#define HDC			void*
#define HWND		void*
#define LPSTR		char*
#define UINT		unsigned int
#define TRUE		1
#define FALSE		0
#define ULONGLONG	unsigned long long
#define LONGLONG	long long

typedef struct _SYSTEMTIME
{
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;
#endif

#ifdef	__cplusplus
extern "C" {
#endif

/***********************************************************************************************/
/* Macro Definition																			   */
/***********************************************************************************************/

#define  FUNC_MAX_PORT					511		// max play channel amount[0,512)

#define MIN_WAVE_COEF					-100	// using by PLAY_AdjustWaveAudio
#define MAX_WAVE_COEF					100		// using by PLAY_AdjustWaveAudio

#define MIN_AUDIO_RECORD_LEN			320		// min audio record length
#define MAX_AUDIO_RECORD_LEN			4096	// max audio record length

#define MAX_DISPLAY_WND					64		// Support max 64 zones in one time

#define BUF_VIDEO_SRC					1		// Video source buffer
#define BUF_AUDIO_SRC					2		// Audio source buffer
#define BUF_VIDEO_RENDER				3		// Video data buffer after decoding
#define BUF_AUDIO_RENDER				4		// Audio data buffer after decoding
#define BUF_VIDEO_ALL					5		// ALL Video data buffer(millisecond)

#define BY_FRAMENUM						1		// In accordance with frame number
#define BY_FRAMETIME					2		// In accordance with time

#define SOURCE_BUF_MAX					1024*100000	// Max original buffer
#define SOURCE_BUF_MIN					1024*1024	// Min original buffer

#define STREAME_REALTIME				0		// The real-time has the highest priority
#define STREAME_FILE					1		// The fluency has the highest priority

#define T_AUDIO16						101		// 16 bit audio type
#define T_AUDIO8						100		// 8 bit audio type

#define T_UYVY							1		// UYVY type, not support	
#define T_IYUV							3		// IYUV(I420) type
#define T_NV12							5		// NV12 type
#define T_RGB32							7		// RGB32 type			
    
#define AVI_MEDIACHANGE_FRAMERATE		1		// change framerate
#define AVI_MEDIACHANGE_RESOLUTION		2		// change resolution	

#define WATERMARK_DATA_TEXT				0		// text watermark	
#define WATERMARK_DATA_JPEG_BMP			1		// jpeg or bmp watermark		
#define WATERMARK_DATA_FRAMEDATA		3		// frame data watermark			

#define	PLAY_NOERROR				0		// No error
#define PLAY_COMMON_ERROR			1		// common error
#define	PLAY_PARA_INVALID			2		// Illegal input parameter
#define PLAY_ORDER_ERROR			3		// Callback sequence is not right
#define	PLAY_PORT_OPEN				4		// port is already open
#define	PLAY_PORT_CLOSE				5		// port is already close
#define	PLAY_PORT_INVALID			6		// Illegal port
#define	PLAY_PORT_EXIST				7		// port is already exist
#define PLAY_OPEN_FILE_ERROR		8		// open file failed
#define PLAY_INTERFACE_NOT_SUPPORT	9		// Interface is not supported
#define PLAY_HWND_INVALID			10		// Illegal hwnd
#define PLAY_PLAY_ERROR				11		// play failed
#define PLAY_SPEED_INVALID			12		// Illegal speed
#define PLAY_NOT_FILE				13		// not file mode
#define PLAY_NOT_STREAM				14		// not stream mode
#define PLAY_NO_FRAME				15		// current is no frame
#define PLAY_INDEX_NOT_COMPLETE		16		// index is not complete
#define PLAY_INDEX_COMPLETE			17		// index is complete
#define PLAY_GET_FILE_SIZE_ERROR	18		// get file size failed
#define PLAY_CREATE_THREAD_FAIL		19		// create thread failed
#define PLAY_CREATE_EVENT_FAIL		20		// create event failed
#define PLAY_SOUND_SHARE_MODE		21		// sound share mode
#define PLAY_INCLUDE_SOUND_SHARE_PORT     22 // sound share port is already include
#define PLAY_NOT_INCLUDE_SOUND_SHARE_PORT 23 // sound share port is not include
#define PLAY_CREATE_DIR_ERROR			  24 // create dir failed
#define PLAY_CREATE_FILE_ERROR			  25 // create file failed

#define PLAY_CONVERT_YUV_ERROR			 26 // convert yuv failed
#define PLAY_CONVERT_JPG_ERROR			 27	// convert jpg failed
#define PLAY_CONVERT_BMP_ERROR			 28	// convert bmp failed
#define PLAY_CONVERT_TIFF_ERROR			 29	// convert tiff failed
#define PLAY_HW_CATCH_ERROR				 30	// Hardware acceleration catch failed
#define PLAY_CREATE_VIDEO_RENDER_ERROR	 31	// create video render failed
#define PLAY_NOT_SUPPORT_REF_VALUE		 32	// file index setting is not supported
#define PLAY_FORMAT_NOT_SUPPORT			 33	// format is not supported
#define PLAY_CREATE_RECORD_ERROR		 34	// create record failed
#define PLAY_OPEN_RECORD_ERROR			 35	// open record failed
#define PLAY_FRAMERATE_ERROR			 36	// frame rate failed
#define PLAY_CREATE_AUDIO_RECORD_ERROR	 37	// create audio record failed
#define PLAY_OPEN_AUDIO_RECORD_ERROR	 38	// open audio record failed
#define	PLAY_AES_ALLOC_ERROR			 39	// aes_alloc failed

#define PLAY_BUF_OVER				     40  // buffer is over
#define PLAY_ALLOC_MEMORY_ERROR		     41  // alloc memory failed
 
/***********************************************************************************************/
/* enum Definition																			   */
/***********************************************************************************************/

typedef enum
{
	RENDER_NOTSET = 0,						// default
	RENDER_GDI,								// GDI
	RENDER_X11 = RENDER_GDI,				// X11, not windows platform
    RENDER_DDRAW,							// ddraw
	RENDER_OPENGL = RENDER_DDRAW,			// opengl, not windows platform
    RENDER_D3D,								// D3D render£¬equeal D3D9
	RENDER_D3D9 = RENDER_D3D,               // D3D9 render
	RENDER_WGL,								// opengl, windows platform
	RENDER_D3D11                            // D3D11 render
}RenderType;

typedef enum
{
	DECODE_NOTSET = 0,        // default
	DECODE_SW,		          // software decode
	DECODE_HW,		          // GPU CopyBack
	DECODE_HW_FAST,           // GPU DirectRender
	DECODE_MSDK,		      // not support
	DECODE_HW_FAST_D3D11,	  // GPU DirectRender via dx11,only windows platform
}DecodeType;

typedef enum __tPicFormats
{
	PicFormat_BMP = 0,						// BMP 32bit
	PicFormat_JPEG,							// JPEG
	PicFormat_JPEG_70,						// 70% JPEG
	PicFormat_JPEG_50,						// 50% JPEG
	PicFormat_JPEG_30,						// 30% JPEG
	PicFormat_JPEG_10,						// 10% JPEG
	PicFormat_BMP24,						// BMP 24bit
	PicFormat_TIFF							// TIFF
} tPicFormats;

typedef enum _CMD_TYPE
{
	PLAY_CMD_GetTime = 1,			// time in stream ,year/month/day
	PLAY_CMD_GetFileRate = 2,		// framerate
	PLAY_CMD_GetMediaInfo = 3,		// media info
	PLAY_CMD_GetRenderNum = 4,		// render frame num(last frame)
	PLAY_CMD_GetRenderTime = 5,		// render time
	PLAY_CMD_GetSrcTime	= 6,		// time in stream,seconds after 1970.7.1
	PLAY_CMD_GetCurRenderNum = 7,   // render frame num(cur frame)
    PLAY_CMD_GetRenderTimeStamp = 8 // render timestamp
} CMD_TYPE_E;

typedef enum
{
	AV_SYNC_VIDEO_MASTER,		  // based in video(no audio and video synchronization)
	AV_SYNC_AUDIO_TIME_STAMP      // based in audio time stamp(no audio and video synchronization)
}AV_SYNC_TYPE;

/***********************************************************************************************/
/* struct Definition																		   */
/***********************************************************************************************/

typedef struct _tagRECT
{
	LONG left;
	LONG top;
	LONG right;
	LONG bottom;
}DISPLAYRECT;


#ifndef _USER_TIME_
#define _USER_TIME_
typedef struct _TIME								
{
	DWORD second	:6;						// 0-59		
	DWORD minute	:6;						// 0-59		
	DWORD hour		:5;						// 0-23		
	DWORD day		:5;						// 1-31		
	DWORD month		:4;						// 1-12		
	DWORD year		:6;						// 2000-2063	
} USER_TIME,*pUSER_TIME;
#endif

#define UUID_MAX_LEN		96
#define MAX_DEV_NAME_LEN	32
typedef struct _FILE_INFO
{
	UINT			channel;				// Channel number
	BYTE			type;					// File type
	BYTE			lock_flag;				// Lock type
	BYTE			video_audio;			// Video or audio
	BYTE			image;					// Image		
	USER_TIME		start_time;				// Start time	
	USER_TIME		end_time;				// End time	
	UINT			file_length;			// File length
	UINT			first_clus_no;			// First cluster number
	UINT			ud_no;					// Userdata number		
	char			part[MAX_DEV_NAME_LEN];	// Partition name
	char			uuid[UUID_MAX_LEN];		// Uuid name
	BYTE		disk_type;		//Disk type, 0:DHFS; 1:XFS
	BYTE		file_type;		//File type:  1: Video; 2: Picture
	BYTE		stream_type;	// Stream type:  1: Main stream; 2:Extra stream1; 3:Extra stream2
	char			name[64];		// XFS disk file name,  sino+"inode number"+".dav"
	UINT			rev[9];					// Reserved
}FILE_INFO,*pFILE_INFO;

typedef struct
{
	LONGLONG		nFilePos;				// Specify the frame offset position in the file
	LONG			nFrameLen;				// Frame length
	LONG			nFrameNum;				// Frame serial number
	LONG			nFrameTime;				// Frame time
	LONG			nErrorFrameNum;			// Error frame number
	SYSTEMTIME*		pErrorTime;				// Error frame time
	LONG			nErrorLostFrameNum;		// Error frame number
	LONG			nErrorFrameSize;		// Error frame size
}FRAME_POS,*PFRAME_POS;

typedef struct
{
	LONG			nWidth;					// Width, unit is pixel, 0 for audio data.
	LONG			nHeight;				// height, 0 for audio data
	LONG			nStamp;					// Time stamp info, unit is ms
	LONG			nType;					// Video frame type,T_AUDIO16,T_RGB32,T_IYUV
	LONG			nFrameRate;				// Video represents frame rate,audio represents sampling rate
}FRAME_INFO;

typedef struct
{
	#define FRAME_TYPE_VIDEO 0				// Video Frame
	#define FRAME_TYPE_AUDIO 1				// Audio Frame
	int				nFrameType;				// Frame Type
	int				nFrameSeq;				// Frame serial number
	int				nStamp;					// Frame time ,MilliSecond
	int				nWidth;					// Width, unit is pixel, 0 for audio data.
	int 			nHeight;				// height, 0 for audio data.
	int				nFrameRate;				// Image frame rate created during encoding
	int				nChannels;				// Audio Channel No.
	int				nBitPerSample;			// Audio Sampling Bit
	int				nSamplesPerSec;			// Audio Sampling Frequency
	int				nRemainData;			// Remain data of internal buffer
	SYSTEMTIME		nDataTime;				// Frame time, year/month.   
	int				nFrameSubType;			//Frame SubType
	int				nReserved[58];			//Reserved
}FRAME_INFO_EX;

typedef struct 
{
	int				nFrameType;				// Frame type, definition as FRAME_INFO_EX nFrameType
	void*			pAudioData;				// Audio data if it is audio frame
	int				nAudioDataLen;			// Audio Data Length
	void*			pVideoData[3];			// as YUV components
	int				nStride[3];				// as spacing among YUV components
	int				nWidth[3];				// as width of YUV components
	int				nHeight[3];				// as height of YUV components
    SYSTEMTIME		nDataTime;              // frame time
	int				nReserved[60];			// Reserved
}FRAME_DECODE_INFO;

typedef struct 
{
	int			lWidth;						// Width	
	int			lHeight;					// Height
	int			lFrameRate;					// Image frame rate
	int			lChannel;					// Audio Channel No.
	int			lBitPerSample;				// Audio Sampling Bit
	int			lSamplesPerSec;				// Audio Sampling Frequency
}MEDIA_INFO;

/***********************************************************************************************/
/* Interface Definition																		   */
/***********************************************************************************************/

/************************************************************************/
//> get version
/************************************************************************/

/**
 * Get PlaySDK Main Version, Sub Version and SVN Version.
 *
 * @return The higher 1 bit represents current main version.2-3 bit represents sub version. others represents SVN version.
 *		For example:return value is 34033722 then you can see: main version is 3, sub version is 40 and SVN version is 33722.
 */
PLAYSDK_API DWORD CALLMETHOD PLAY_GetSdkVersion();

/************************************************************************/
//> error code
/************************************************************************/

/**
 * Get current error code. You can call this function to get error code if you fail to call one function
 *
 * @return Error code
 */
PLAYSDK_API DWORD  CALLMETHOD PLAY_GetLastErrorEx();

/************************************************************************/
//> log off/on
/************************************************************************/

/**
 * log off/on, default is Warn level. Debug level is suggested if need more information.
 * windows platform will generate playsdk.log in the library path, others console output.
 *
 */
typedef enum
{
    LOG_LevelUnknown= 0, // unknown
    LOG_LevelFatal,	     // fatal, when setting this level, (fatal) will output
    LOG_LevelError,	     // error,when setting this level, (fatal,error) will output
    LOG_LevelWarn,	     // warn, when setting this level, (fatal,error,warn) will output
    LOG_LevelInfo,	     // info, when setting this level, (fatal,error,warn,info) will output
    LOG_LevelTrace,	     // Trace, when setting this level, (fatal,error,warn,info,trace) will output
    LOG_LevelDebug	     // Debug, when setting this level, (fatal,error,warn,info,trace,debug) will output
}LOG_LEVEL;
PLAYSDK_API void CALLMETHOD PLAY_SetPrintLogLevel(LOG_LEVEL logLevel);

/************************************************************************/
//> play port
/************************************************************************/

/**
 * Get free port. Range in 101~511
 *
 * @param[out] plPortt Get free Port number
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_GetFreePort(LONG *plPort);

/**
 * Release the port got with PLAY_GetFreePort 
 *
 * @param[in] plPort Port number
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_ReleasePort(LONG lPort);

/************************************************************************/
//> file operation
/************************************************************************/

/**
 * Open file
 *
 * @param[in] nPort Port number
 * @param[in] sFileName File Name
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_OpenFile(LONG nPort,LPSTR sFileName);

/**
 * Close file
 *
 * @param[in] nPort Port number
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_CloseFile(LONG nPort);

/**
 * File End CallBack Function
 *
 * @param[in] nPort Port number
 * @param[in] pUserData Customized Parameter
 */
typedef void (CALLBACK *fFileEndCBFun)(DWORD nPort, void* pUserData);

/**
 * File End CallBack
 *
 * @param[in] nPort Port number
 * @param[out] pFileEndCBFun Callback function pointer
 * @param[in] pUserData Customized Parameter
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetFileEndCallBack(LONG nPort, fFileEndCBFun pFileEndCBFun, void* pUserData);

/************************************************************************/
//> stream operation
/************************************************************************/

/**
 * Set stream play mode. You need to set before playing
 *
 * @param[in] nPort Port number
 * @param[in] nMode STREAME_REALTIME Real-time mode (default);STREAME_FILE File mode.Real-time mode. It is suitable for network real-time mode.The
 *						decoder card will begin decoding right now
 *						File mode. It is suitable for you to input file data as stream
 *						when PLAY_InputData() return FALSE, you need to wait and then input again.
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetStreamOpenMode(LONG nPort,DWORD nMode);

/**
 * Get stream mode type
 *
 * @param[in] nPort Port number
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API LONG CALLMETHOD PLAY_GetStreamOpenMode(LONG nPort);

/**
 * Open stream interface (Just the same as open a file)
 *
 * @param[in] nPort Port number
 * @param[in] pFileHeadBuf It is not available now. Please input NULL
 * @param[in] nSize It is not available now.Please input 0
 * @param[in] nBufPoolSize Set storage data stream buffer size in the play The value ranges is 
 *			[SOURCE_BUF_MIN,SOURCE_BUF_MAX]. Usually it is 900*1024. Please increase the value if the data are not even
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_OpenStream(LONG nPort,PBYTE pFileHeadBuf,DWORD nSize,DWORD nBufPoolSize);

/**
 * Close stream
 *
 * @param[in] nPort Port number
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_CloseStream(LONG nPort);

/**
 * Input the stream data you get from the card. Enable stream and Then call PLAY_Play to input data
 *
 * @param[in] nPort Port number
 * @param[in] pBuf Buffer address
 * @param[in] nSize Buffer size
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_InputData(LONG nPort,PBYTE pBuf,DWORD nSize);

/************************************************************************/
//> sound related
/************************************************************************/

/**
 * Enable audio. There is only 1-ch audio in one time. System auto 
 *		disables previous audio if current audio is enabled. 
 *		Please note audio is disabled by default
 *
 * @param[in] nPort Port number
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_PlaySound(LONG nPort);

/**
 * Disable audio
 * 
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_StopSound();

/**
 * Play audio in share way. Play current channel audio while not disabling audio from other channels
*
 * @param[in] nPort Port number
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
 PLAYSDK_API BOOL CALLMETHOD PLAY_PlaySoundShare(LONG nPort);

/**
 * Disable audio in share way. PLAY_PlaySound and PLAY_StopSound are enable audio in 
 *		exclusive way. Please note, in one progress, all channels are required to use
 *		same way to enable or disable audio
 *
 * @param[in] nPort Port number
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_StopSoundShare(LONG nPort);

/**
 * Set volume.
 * 
 * @param[in] nPort Port number
 * @param[in] nVolume Volume value. The value ranges is [0, 0XFFFF]
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetVolume(LONG nPort,WORD nVolume);

/**
 * To get current volume setup.
 *
 * @param[in] nPort Port number
 * @return WORD,To get current volume value
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API WORD CALLMETHOD PLAY_GetVolume(LONG nPort);

/**
 * Audio sampling data callback function
 *
 * @param[in] pDataBuffer buffer address
 * @param[in] DataLength buffer length 
 * @param[in] pUserData Customized Parameter
 */
typedef void (CALLBACK *pCallFunction)(LPBYTE pDataBuffer, DWORD DataLength, void* pUserData);

/**
 * Enable audio sampling operation.
 *
 * @param[out] pProc Audio sampling data callback pointer
 * @param[in] nBitsPerSample Represent the bit for each sampling
 * @param[in] nSamplesPerSec Sampling rate
 * @param[in] nLength Data buffer length
 * @param[in] encodetype Encode type,see AUDIO_CAPTURE_TYPE.
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
typedef enum
{
	AUDIO_RAW_PCM = 0,		// Raw PCM
	AUDIO_G711A,			// g711a with private head
	AUDIO_G711U,			// g711u with private head
	AUDIO_PCM,				// PCM with private head
} AUDIO_CAPTURE_TYPE;
PLAYSDK_API BOOL CALLMETHOD PLAY_OpenAudioRecord(pCallFunction pProc, LONG nBitsPerSample, LONG nSamplesPerSec, LONG nLength, LONG encodetype, void* pUserData);

/**
 * Disable audio sampling function
 *
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_CloseAudioRecord();

/**
 * speech change function.
 *
 * @param[in] bStart start speech change,1-enable,0-disable, only support Android/IOS
 * @param[in] scEffect speech change effect, range 0-3£¬0-no change£¬1 is for adults to become uncle, 2 for children to be uncle, and 3 for electronic sounds
 * @param[in] scTsm    scale factor,default value 0.0£¬when scTsm sets to 0.0, use scTsm default value fro scEffect value
						when sc_effect=1£¬tsm effective value range 0.80-0.85£¬                                                   
						when sc_effect=2£¬tsm effective value range 0.60-0.65£¬
						when sc_effect=3£¬tsm effective value range 1.40-1.45¡£  
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SpeechChange(BOOL bStart, int scEffect, float scTsm);

/**
 * Set audio record data zoom rate
 *
 * @param[in] fRatio Zoom rate.from 0 to 1=zoom in audio.1=Original audio.Over 1=audio zoom out.
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetAudioRecScaling(float fRatio);

/**
 *Get audio record data zoom rate
 *
 * @param[out] pfRatio zoom rate. From 0 to 1=Zoom in audio.1=Original audio. Over 1=zoom out audio.
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_GetAudioRecScaling(float* pfRatio);

/**
 * Set audio decode zoom rate
 *
 * @param[in] nPort Port number
 * @param[in] fRatio Zoom rate.From 0 to 1=Zoom in audio;1=original audio. Over 1=audio zoom out.
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetAudioRenderScaling(LONG nPort, float fRatio);

/**
 * Get audio decode zoom rate
 *
 * @param[in] nPort Port number
 * @param[out] pfRatio Zoom rate.From 0 to 1=Zoom in audio;1=original audio. Over 1=audio zoom out.
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_GetAudioRenderScaling(LONG nPort, float* pfRatio);

/**
 * Adjust WAVE to adjust volume. The difference between this function and the PLAY_SetVolume is: 
 *			the function is to adjust audio data and only applies to current channel. 
 *			But PLAY_SetVolume is to adjust audio card volume and applies to the whole system.
 *			This function has not realized yet.
 *
 * @param[in] nPort Port number
 * @param[in] nCoefficient Modified parameter.,The value ranges:[MIN_WAVE_COEF, MAX_WAVE_COEF]. 0 stands for no modification.
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_AdjustWaveAudio(LONG nPort,LONG nCoefficient);

/************************************************************************/
//> play control
/************************************************************************/

/**
 * Start play. If it is playing, then return current play status to normal speed
 *
 * @param[in] nPort Port number
 * @param[in] hWnd Play window handle
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_Play(LONG nPort, HWND hWnd);

/**
 * Stop Play
 *
 * @param[in] nPort Port number
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_Stop(LONG nPort);

/**
 * Pause/resume
 *
 * @param[in] nPort Port number
 * @param[in] nPause 1£ºPause£»0£ºResume
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_Pause(LONG nPort,DWORD nPause);

/**
 * Slow play. [1/64, 64]. Each time the speed lowers one level(*0.5). 
 *				call PLAY_Play to resume normal play.
 *
 * @param[in] nPort Port number
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_Slow(LONG nPort);

/**
 * Fast play. [1/64, 64]
 *		Each time the speed upers one level(*2).
 *		You can call PLAY_Play to resume normal playback from current position.
 *
 * @param[in] nPort Port number
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_Fast(LONG nPort);

/**
 * Play frame by frame. Please call PLAY_ Play to resume normal playback
 * 
 * @param[in] nPort Port number
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_OneByOne(LONG nPort);

/**
 * Playback frame by frame. Each callback will return one frame.
 *		You can call this function after creating the file index
 *
 * @param[in] nPort Port number
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_OneByOneBack(LONG nPort);

/**
 * Set video parameter. It becomes active once it is set
 *
 * @param[in] nPort Port number
 * @param[in] nRegionNum Display zone. Please refer to PLAY_SetDisplayRegion. Please set it as o if there is only one display zone (usually it is 0)
 * @param[in] nBrightness Brightness. Default value is 64. The value ranges from 0 to 128
 * @param[in] nContrast Contrastness. Default value is 64. The value ranges from 0 to 128
 * @param[in] nSaturation Saturation.Default value is 64. The value ranges from 0 to 128
 * @param[in] nHue Hue.Default value is 64. The value ranges from 0 to 128
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetColor(LONG nPort, DWORD nRegionNum, int nBrightness, int nContrast, int nSaturation, int nHue);

/**
 * Get the corresponding color value. The parameter is the same as PLAY_SetColor
 *
 * @param[in] nPort Port number
 * @param[in] nRegionNum Display zone. Please refer to PLAY_SetDisplayRegion. Please set it as o if there is only one display zone (usually it is 0)
 * @param[out] pBrightness Brightness. Default value is 64. The value ranges from 0 to 128
 * @param[out] pContrast Contrastness. Default value is 64. The value ranges from 0 to 128.
 * @param[out] pSaturation Saturation.Default value is 64. The value ranges from 0 to 128
 * @param[out] pHue Hue.Default value is 64. The value ranges from 0 to 128
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_GetColor(LONG nPort, DWORD nRegionNum, int *pBrightness, int *pContrast, int *pSaturation, int *pHue);

/**
 * Setting the audio and video playback strategy
 *
 * @param[in] nPort Port number
 * @param[in] nAVSyncType code stream playing datum. 0£ºbased on video £»1£ºbased on the timestamp
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetAVSyncType(LONG nPort,AV_SYNC_TYPE nAVSyncType);

/**
 * Change play speed
 *
 * @param[in] nPort Port number
 * @param[in] fCoff Play Speed,Range[1/64~64.0],less than 1 play slowly£¬greater than 1 play quickly.
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetPlaySpeed(LONG nPort, float fCoff);

/**
 * Set play direction
 *
 * @param[in] nPort Port number
 * @param[in] emDirection Play direction:0,Forward ,1,BackWard
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetPlayDirection(LONG nPort, DWORD emDirection);

/**
 * Set realplay delay time
 *
 * @param[in] nPort Port number
 * @param[in] nDelay(ms) Delay time.
 * @param[in] nThreshold(ms) Threshold time.
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDelayTime(LONG nPort, int nDelay, int nThreshold);

/**
 * set play strategy£¬only for realtime
 *
 * @param[in] nPort Port number
 * @param[in] nStartTime(ms) first start play if internal buffer is greater than nStartTime
 * @param[in] nSlowTime(ms) start play at lower speed if internal buffer is less than nSlowTime
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetPlayMethod(LONG nPort, int nStartTime, int nSlowTime, int nFastTime, int nFailedTime);

/* Real stream data cache mode */
typedef enum
{
	CACHE_MODE_OFF = 0,		// set the real stream data cache mode off
	ADAPTIVE_CACHE,			// adaptive cache mode
	REALTIME_FIRST,			// realtime frist
	FLUENCY_FIRST,			// fluency frist
} CACHE_MODE;

/**
 * set play cache mode, only for realtime streaming
 *
 * @param[in] nPort Port number
 * @param[in] cacheMode Real stream data cache mode
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetCacheMode(LONG nPort, CACHE_MODE cacheMode);

/**
 * set audio play strategy£¬only for Intercom
 *
 * @param[in] nPort Port number
 * @param[in] nClearTime(ms) Buffer clear threshold
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetAudioPlayMethod(LONG nPort, int nClearTime);

/**
 * Setting image flipping, Range in 0~3
 *
 * @param[in] nPort Port number
 * @param[in] nrotateType Flip type,Range[0,3]. 0=no flip;1=Rotate by 90 degrees;2=Rotate by 180 degrees;3=Rotate by 270 degrees. 
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetRotateAngle(LONG nPort , int nrotateType);

/************************************************************************/
//> file position
/************************************************************************/

/**
 * Set relative position of file play pointer (unit :%).
 *
 * @param[in] nPort Port number
 * @param[in] fRelativePos The value ranges is [0, 100%]
 * @return BOOL,TRUE--succeeded FALSE--failed
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetPlayPos(LONG nPort,float fRelativePos);

/**
 * Get the relative position of the file player pointer.
 *
 * @param[in] nPort Port number
 * @return float£¬The value ranges is [0, 100%]
 */
PLAYSDK_API float CALLMETHOD PLAY_GetPlayPos(LONG nPort);

/**
 * Set file play position according to the time. This interface takes a little bit longer 
 * than the PLAY_SetPlayPos. But use time to control progress bar (working with PLAY_GetPlayedTime(Ex))
 * to make the progress bar smoothly
 *
 * @param[in] nPort Port number
 * @param[in] nTime Set the file play position to the specified time. Unit is ms
 * @return BOOL,TRUE--succeeded FALSE--failed
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetPlayedTimeEx(LONG nPort,DWORD nTime);

/**
 * Get file played time. Unit is ms.
 *
 * @param[in] nPort Port number
 * @return DWORD,The file current played time
 */
PLAYSDK_API DWORD CALLMETHOD PLAY_GetPlayedTimeEx(LONG nPort);

/**
 * Get current play frame serial number. PLAY_GetPlayedFrames is the total frame amount. If 
 * the play position is the same, the return values of these two functions shall be very close.
 *
 * @param[in] nPort Port number
 * @return DWORD,Current play frame number
 */
PLAYSDK_API DWORD CALLMETHOD PLAY_GetCurrentFrameNum(LONG nPort);

/**
 * Specify the frame number in current position. Locate the play position according to the 
 * frame number. The function need to be called back after creating the file index.
 *
 * @param[in] nPort Port number
 * @param[in] nFrameNum frame number
 * @return BOOL,TRUE--succeeded FALSE--failed
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetCurrentFrameNum(LONG nPort,DWORD nFrameNum);

/**
 * Get the video frame amount that has been decoded.
 *
 * @param[in] nPort Port number
 * @return DWORD The video frame amount that have been decoded
 */
PLAYSDK_API DWORD CALLMETHOD PLAY_GetPlayedFrames(LONG nPort);

/**
 * Get file played time. Unit is second.
 *
 * @param[in] nPort Port number
 * @return DWORD The file current played time
 */
PLAYSDK_API DWORD CALLMETHOD PLAY_GetPlayedTime(LONG nPort);

/**
 * Get file total time length. Unit is second.
 *
 * @param[in] nPort Port number
 * @return DWORD,Total file time
 */
PLAYSDK_API DWORD CALLMETHOD PLAY_GetFileTime(LONG nPort);

/**
 * Get total frame count.
 *
 * @param[in] nPort Port number
 * @return DWORD,Total frame count
 */
PLAYSDK_API DWORD CALLMETHOD PLAY_GetFileTotalFrames(LONG nPort);

/************************************************************************/
//> file index
/************************************************************************/

/**
 * build index callback fun.
 *
 * @param[in] nPort Port number
 * @param[in] pUserData User data
 */
typedef void(CALLBACK *fFileRefDoneCBFun)(DWORD nPort, void* pUserData);	

/**
 * Set callback function pointer. Callback when establishing callback. To locate quickly 
 * and accurately, system generates a file index when opening a file. This period may take a little 
 * bit long. Its speed is about 40M/s, mainly because reading data from the HDD is slow. The index 
 * establishment is operated in the background. The functions that need to use this index have to 
 * wait until this process ends, while the other interfaces may not be affected
 *
 * @param[in]  nPort Port number
 * @param[out] pFileRefDoneCBFun Callback function pointer
 * @param[in]  pUserData User data
 * @return BOOL,TRUE--succeeded FALSE--failed
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetFileRefCallBack(LONG nPort,
													fFileRefDoneCBFun pFileRefDoneCBFunc,
													void* pUserData);
/**
 * build index callback fun.
 *
 * @param[in] nPort Port number
 * @param[in] bIndexCreated Index creation symbol.TRUE=Index creation succeeded. FALSE=Index creation failed.
 * @param[in] pUserData User data
 */
typedef void (CALLBACK *fFileRefDoneCBFunEx)(DWORD nPort, BOOL bIndexCreated, void* pUserData);

/**
 * Set callback function pointer. Callback when establishing callback. To locate quickly 
 * and accurately, system generates a file index when opening a file. This period may take a little 
 * bit long. Its speed is about 40M/s, mainly because reading data from the HDD is slow. The index 
 * establishment is operated in the background. The functions that need to use this index have to 
 * wait until this process ends, while the other interfaces may not be affected
 *
 * @param[in] nPort Port number
 * @param[out] pFileRefDoneCBFunEx Callback function pointer
 * @param[in] pUserData User data
 * @return BOOL,TRUE--succeeded FALSE--failed
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetFileRefCallBackEx(LONG nPort, fFileRefDoneCBFunEx pFileRefDoneCBFunEx, void* pUserData);

/**
 * Search I frame position before the specified position. The video decode begins from I frame.
 * If the saved file is not from I frame, then the data to the next I frame will be ignored. If you 
 * need to get data from the file, you can better get from I frame. But the end position does not matter
 * since you may lose max 3 frames data.
 *
 * @param[in] nPort Port number
 * @param[in] nValue Current position. It can be time or frame number. Its type is appointed by nType
 * @param[in] nType Specify nValue type
 *	          If nType is BY_FRAMENUM, then nValue means frame number
 *	          If nType is BY_FRAMETIME, then nValue means time and unit is ms
 * @param[in] pFramePosI frame position information struct pointer.
 * @return BOOL,TRUE--succeeded FALSE--failed
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_GetKeyFramePos(LONG nPort,DWORD nValue, DWORD nType, PFRAME_POS pFramePos);

/**
 * Search I frame position after the specified location.
 *
 * @param[in] nPort Port number
 * @param[in] nValue Current position. It can be time or frame number. Its type is appointed by nType.
 * @param[in] nType Specify nValue type.
 *            If nType is BY_FRAMENUM, then nValue means frame number
 *            If nType is BY_FRAMETIME, then nValue means time and unit is ms
 * @param[in] pFramePos I frame position information struct pointer
 * @return BOOL,TRUE--succeeded FALSE--failed
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_GetNextKeyFramePos(LONG nPort,DWORD nValue, DWORD nType, PFRAME_POS pFramePos);

/**
 * To get file index information so that you can use the information directly when you open
 * the same file the next time. You need to create index to get information.
 *
 * @param[in] nPort Port number
 * @param[in] pBuffer Index information
 * @param[in] pSize Input pBuffer size, output index information size.
 *            Note: you can first set pSize=0,pBuffer=NULL, get the buffer size from the return value 
 *            of pSize and then allocate the enough buffer.Then you can callback again.
 * @return BOOL,TRUE--succeeded FALSE--failed
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_GetRefValue(LONG nPort,BYTE *pBuffer, DWORD *pSize);

/**
 * Set file index. If there is file index, you do not need to call callback function 
 * (PLAY_SetFileRefCallBack) and then directly input index information. Please note index 
 * information and its length must be accurate.
 *
 * @param[in] nPort Port number
 * @param[in] pBuffer Index information
 * @param[in] nSize Index information length
 * @return BOOL,TRUE--succeeded FALSE--failed
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetRefValue(LONG nPort,BYTE *pBuffer, DWORD nSize);

/************************************************************************/
//> get play or decode infomation
/************************************************************************/

/**
 * Set callback stream type when decoding.
 *
 * @param[in] nPort Port number
 * @param[in] nTime nStream,1 Video stream;2 Audio stream;3 Composite stream
 * @return BOOL,TRUE--succeeded FALSE--failed
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDecCBStream(LONG nPort,DWORD nStream);

/**
 * decode callback function.
 *
 * @param[in] nPort Port number
 * @param[in] pFrameDecodeInfo Audio and video data after decoding
 * @param[in] pFrameInfo Image and audio information. Please refer to the following information
 * @param[in] pUser User defined parameter
 */
typedef void (CALLBACK* fCBDecode)(LONG nPort, FRAME_DECODE_INFO* pFrameDecodeInfo, FRAME_INFO_EX* pFrameInfo, void* pUser);

/**
 * Set callback function. It is to replace the displayed section in the player. You can control the displayed video.
 * Please call this function before PLAY_Play. This function becomes null when calling PLAY_Stop. 
 * You need to reset when you call PLAY_Play the next time.The decode section does not control speed. 
 * When you return from the callback function, the decoder will decode the next data. Please note before using this function; 
 * you need to fully understand the video display and audio play. Otherwise, do not use this function casually.
 *
 * @param[in] nPort Port number
 * @param[out] cbDec Callback function pointer. It can not be null
 * @param[in] pFrameInfo Image and audio information. Please refer to the following information
 * @return BOOL,TRUE--succeeded FALSE--failed
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDecodeCallBack(LONG nPort, fCBDecode cbDec, void* pUser);

/**
 * Set video data callback. It can be used to snapshot. You can set callback function
 * pointer of DisplayCBFun as null to stop callback. The callback function is valid all the time 
 * once it is set, until the program exits. You can call this function at any time
 *
 * @param[in] nPort Port number
 * @param[in] pBuf Video data buffer
 * @param[in] nSize video data size
 * @param[in] nWidth Image width. Unit is pixel
 * @param[in] nHeight Image height
 * @param[in] nStamp Time mark information. Unit is ms
 * @param[in] nType Data type. T_RGB32, T_UYVY. Please refer to macro definition
 * @param[in] pReserved Reserved
 */
typedef void (CALLBACK* fDisplayCBFun)(LONG nPort,char * pBuf,LONG nSize,LONG nWidth,LONG nHeight,LONG nStamp,LONG nType, void* pReserved);

/**
 * Set video data callback. It can be used to snapshot. You can set callback function
 * pointer of DisplayCBFun as null to stop callback. The callback function is valid all the time 
 * once it is set, until the program exits. You can call this function at any time.
 *
 * @param[in] nPort Port number
 * @param[out] DisplayCBFun Video data callback function. It can be null
 * @param[in] pUserData User-customized parameter
 * @return BOOL,TRUE--succeeded FALSE--failed
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDisplayCallBack(LONG nPort, fDisplayCBFun DisplayCBFun, void* pUserData);

/**
 * Callback wave data after decoding audio frame.
 *
 * @param[in] nPort Port number
 * @param[in] pAudioBuf Wave data buffer
 * @param[in] nSize Wave data length
 * @param[in] nStamp Time mark (ms)
 * @param[in] nType Audio type T_AUDIO16. Sampling rate 8000. single-channel. Each sampling spot is represented by 16-bit
 * @param[in] pUserData User defined data
 */
typedef void (CALLBACK * fAudioCBFun)(LONG nPort, char * pAudioBuf, LONG nSize, LONG nStamp, LONG nType, void* pUserData);

/**
 * Callback wave data after decoding audio frame.
 *
 * @param[in] nPort Port number
 * @param[out] AudioCBFun Audio callback function
 * @param[in] pUserData User defined data
 * @return BOOL,TRUE--succeeded FALSE--failed
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetAudioCallBack(LONG nPort, fAudioCBFun AudioCBFun, void* pUserData);

/**
 * Decoding call, is same almost with PLAY_SetDecCallBackEx, except that decoding call can
 * display video simultaneously, long-time logic processing is not recommended in call function, in order to avoid delay in display.
 *
 * @param[in] nPort Port number
 * @param[out] cbDec, call function indicator, cannot be NULL
 * @param[in] pUser user customized parameter
 * @return BOOL,TRUE--succeeded FALSE--failed
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
typedef fCBDecode fVisibleDecodeCallBackFunc;
PLAYSDK_API BOOL CALLMETHOD PLAY_SetVisibleDecodeCallBack(LONG nPort, fVisibleDecodeCallBackFunc cbDec, void* pUser);

/**
 * decoding callback function.
 *
 * @param[in] nPort channel no
 * @param[in] pBuf A/V data after decoding
 * @param[in] nSize pBuf length of A/V data after decoding
 * @param[in] pFrameInfo image and audio, refer to FRAME_INFO structure
 * @param[in] pUserData User defined data
 * @param[in] nReserved2 reserved parameter
 */
typedef void (CALLBACK* fDecCBFun)(LONG nPort,char * pBuf,LONG nSize,FRAME_INFO * pFrameInfo, void* pUserData, LONG nReserved2);

/**
 * Set decoding call to replace display in player, controlled by user, the function at
 * call before PLAY_Play, when PLAY_Stop, it automatically become invalid. Next time before PLAY_Play,
 * Need to set again, decoding part do not control speed, user shall return from call function, decoder
 * decode next data, only for decoding with no display.
 *
 * @param[in] nPort Port number
 * @param[out] DecCBFun, decoding call function indicator, cannot be NULL. Call function parameter definitions are as follows.
 * @return BOOL,TRUE--succeeded FALSE--failed
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDecCallBack(LONG nPort, fDecCBFun DecCBFun);

/**
 * Set decoding call to replace display in player, controlled by user, the function at
 * call before PLAY_Play, when PLAY_Stop, it automatically become invalid. Next time before PLAY_Play,
 * Need to set again, decoding part do not control speed, user shall return from call function, decoder
 * decode next data, only for decoding with no display.
 *
 * @param[in] nPort Port number
 * @param[out] DecCBFun, decoding call function indicator, cannot be NULL. Call function parameter definitions are as follows.
 * @param[in] pUserData user customized parameter
 * @return BOOL,TRUE--succeeded FALSE--failed
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDecCallBackEx(LONG nPort, fDecCBFun DecCBFun, void* pUserData);

/**
 * Decoding call function.
 *
 * @param[in] nPort Port number
 * @param[in] pBuf A/V data after decoding
 * @param[in] nSize pBuf length of A/V data after decoding
 * @param[in] pFrameInfo image and audio, refer to FRAME_INFO structure
 * @param[in] pUserData user customized parameter
 * @param[in] nReserved1 reserved parameter
 */
typedef void (CALLBACK* fVisibleDecCBFun)(LONG nPort,char * pBuf,LONG nSize,FRAME_INFO * pFrameInfo, void* pUserData, LONG nReserved1);

/**
 * Decoding call, is same almost with PLAY_SetDecCallBackEx, except that decoding call can
 * display video simultaneously, long-time logic processing is not recommended in call function, in order to avoid delay in display.
 *
 * @param[in] nPort Port number
 * @param[out] DecCBFun call function indicator, cannot be NULL
 * @param[in] pUserData user customized parameter
 * @return BOOL,TRUE--succeeded FALSE--failed
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetVisibleDecCallBack(LONG nPort, fVisibleDecCBFun DecCBFun, void* pUserData);

/**
 * watermark data callback.
 *
 * @param[in] buf Watermark data buffer
 * @param[in] key differ Watermark info
 * @param[in] len buffer max length
 * @param[in] reallen buffer actual length
 * @param[in] type 1 no error;2 frame water mark;3 frame data error ;4 frame sequence error;5 frame header error;6 no frame header
 * @param[in] pUserData user data
 * @return int meaningless
 */
typedef int (CALLBACK* fGetWaterMarkInfoCallbackFunc)(char* buf, LONG key, LONG len, LONG reallen, LONG type, void* pUserData);	

/**
 * Set watermark data callback.warning:if setting watermark data callback, decoding and rendering are not allowed.
 *
 * @param[in] nPort Port number
 * @param[out] pFunc Watermark information to get callback function
 * @param[in] pUserData user customized parameter
 * @return BOOL,TRUE--succeeded FALSE--failed
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetWaterMarkCallBack(LONG nPort, fGetWaterMarkInfoCallbackFunc pFunc, void* pUserData);

/**
 * watermark data callback.
 *
 * @param[in] nPort Port number
 * @param[in] buf Watermark data buffer
 * @param[in] lTimeStamp Watermark time stamp
 * @param[in] lInfoType Distinguish different watermarks,There are three types: WATERMARK_DATA_TEXT, WATERMARK_DATA_JPEG_BMP,WATERMARK_DATA_FRAMEDATA
 * @param[in] len Buffer length
 * @param[in] reallen buffer actual length
 * @param[in] lCheckResult 1 no error;2 frame water mark;3 frame data error ;4 frame sequence error;5 frame header error;6 no frame header
 * @param[in] pUserData user data
 */
typedef int (CALLBACK* fGetWaterMarkInfoCallbackFuncEx)(LONG nPort, char* buf, LONG lTimeStamp, LONG lInfoType, LONG len, LONG reallen, LONG lCheckResult, void* pUserData);

/**
 * Set watermark data callback.warning:if setting watermark data callback, decoding and rendering are not allowed.
 *
 * @param[in] nPort Port number
 * @param[out] pFunc Watermark information to get callback function
 * @param[in] pUserData user customized parameter
 * @return BOOL,TRUE--succeeded FALSE--failed
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetWaterMarkCallBackEx(LONG nPort, fGetWaterMarkInfoCallbackFuncEx pFunc, void* pUserData);

/**
 * Callback function to remind you when decoding format changes.
 *
 * @param[in] nPort Port number
 * @param[in] pUserData User data
 */
typedef void (CALLBACK *fEncChangeCBFun)(LONG nPort, void* pUserData);

/**
 * Callback function to remind you when decoding format changes. Use it before opening a file.
 *
 * @param[in]  nPort Port number
 * @param[out] EncChangeCBFun Callback function
 * @param[in]  pUserData User data
 * @return BOOL,TRUE--succeeded FALSE--failed
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetEncTypeChangeCallBack(LONG nPort, fEncChangeCBFun EncChangeCBFun, void* pUserData);

/**
 * Callback function to remind you when decoding format changes.
 *
 * @param[in] nPort Port number
 * @param[in] pUserData User data
 * @param[in] nWidth picture width
 * @param[in] nHeight picture height
 */
typedef void(CALLBACK *fEncChangeCBFunEx)(LONG nPort, void* pUserData,LONG nWidth, LONG nHeight);

/**
 * Callback function to remind you when decoding format changes. Use it before opening a file.
 *
 * @param[in]  nPort Port number
 * @param[out] EncChangeCBFun Callback function
 * @param[in]  pUserData User data
 * @return BOOL,TRUE--succeeded FALSE--failed
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetEncTypeChangeCallBackEx(LONG nPort, fEncChangeCBFunEx EncChangeCBFun, void* pUserData);

/**
 * Information status search function. Now it can search current time and frame rate information.
 *
 * @param[in] nPort Port number
 * @param[in] cmdType Specify status search type in CMD_TYPE_E
 * @param[in] buf Information buffer
 * @param[in] buflen Buffer length
 * @param[out] returnlen Valid data length
 * @return BOOL,TRUE--succeeded FALSE--failed
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_QueryInfo(LONG nPort, int cmdType, char* buf, int buflen, int* returnlen);

/**
 * Get video real-time bit rate.
 *
 * @param[in] nPort Port number
 * @param[out] pBitRate output Parameter,Returns Video bit rate
 * @return BOOL,TRUE--succeeded FALSE--failed
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_GetRealFrameBitRate(LONG nPort, double* pBitRate);


/**
 * get encode frame rate in current bit stream.
 *
 * @param[in] nPort Port number
 * @return DWORD,Frame rate value when encoding current bit stream
 */
PLAYSDK_API DWORD CALLMETHOD PLAY_GetCurrentFrameRate(LONG nPort);

/**
 * Get the original image size from the bit stream and then adjust display window accordingly. 
 * It does not need display card to support zoom function. It is very useful for those display cards 
 * that does not support hardware zoom.
 *
 * @param[in] nPort Port number
 * @param[out] pWidth Width of the original image.
 * @param[out] pHeight Height of the original image.
 * @return BOOL,TRUE--succeeded FALSE--failed
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_GetPictureSize(LONG nPort,LONG *pWidth,LONG *pHeight);

/**
 * Demux Frame Data Callback Fun.
 *
 * @param[in] nPort Port number
 * @param[in] pBuf  Data Buffer
 * @param[in] nSize Data Len
 * @param[in] pMutexInfo Demux Frame Info, DEMUX_INFO
 * @param[in] pMutexInfoEx Demux Frame InfoEx, DemuInfoEx
 * @param[in] pUserData User Data
 */
/* Demux Frame Type */
typedef enum
{
	FRAME_UNKNOWN = 0,			
	FRAME_VIDEO,								// Video
	FRAME_AUDIO,								// Audio
	FRAME_DATA									// Data
}FRAME_TYPE;

/* Demux Frame SubType */
typedef enum
{
	FRAME_SUB_TYPE_DATA_INVALID = 0,			
	FRAME_SUB_TYPE_VIDEO_I_FRAME = 1,			// I Frame
	FRAME_SUB_TYPE_VIDEO_P_FRAME,				// P Frame
	FRAME_SUB_TYPE_VIDEO_B_FRAME,				// B Frame

	FRAME_SUB_TYPE_VIDEO_SMART_I_FRAME = 19,	// smart I Frame
	FRAME_SUB_TYPE_VIDEO_SMART_P_FRAME, 		// smart P Frame
	
	FRAME_SUB_TYPE_DATA_CIPHER_AUXILIARY = 26 	// 
}FRAME_SUB_TYPE;

/* Demux Video Codec */
typedef enum
{
	ENCODE_VIDEO_UNKNOWN = 0,		
	ENCODE_VIDEO_MPEG4,				// MPEG4
	ENCODE_VIDEO_HI_H264,			// H264
	ENCODE_VIDEO_JPEG,				// JPEG
	ENCODE_VIDEO_DH_H264,			// H264
	ENCODE_VIDEO_JPEG2000 = 6,		// JPEG2000
	ENCODE_VIDEO_AVS = 7,			// AVS
	ENCODE_VIDEO_STD_H264 = 8,		// H264
	ENCODE_VIDEO_MPEG2 = 9,			// MPEG2
	ENCODE_VIDEO_VNC = 10,			// VNC
	ENCODE_VIDEO_SVAC = 11,			// SVAC
	ENCODE_VIDEO_DH_H265 = 12		// H265
}ENCODE_VIDEO_TYPE;

/* Demux Audio Codec */
typedef enum 
{
	ENCODE_AUDIO_UNKNOWN = 0,
	ENCODE_AUDIO_PCM = 7,			// PCM8
	ENCODE_AUDIO_G729,				// G729
	ENCODE_AUDIO_IMA,				// IMA
	ENCODE_PCM_MULAW,				// PCM MULAW
	ENCODE_AUDIO_G721,				// G721
	ENCODE_PCM8_VWIS,				// PCM8_VWIS
	ENCODE_MS_ADPCM,				// MS_ADPCM
	ENCODE_AUDIO_G711A,				// G711A
	ENCODE_AUDIO_AMR,				// AMR
	ENCODE_AUDIO_PCM16,				// PCM16
	ENCODE_AUDIO_G711U = 22,		// G711U
	ENCODE_AUDIO_G723 = 25,			// G723
	ENCODE_AUDIO_AAC,				// AAC
	ENCODE_AUDIO_G726_40,           // G726, 40kbps
	ENCODE_AUDIO_G726_32,           // G726, 32kbps
	ENCODE_AUDIO_G726_24,           // G726, 24kbps
	ENCODE_AUDIO_G726_16,           // G726, 16kbps
	ENCODE_AUDIO_MP2,				// mp2
	ENCODE_AUDIO_OGG,				// ogg vorbis
	ENCODE_AUDIO_MP3,				// mp3
	ENCODE_AUDIO_G722_1,		    // G722_1
	ENCODE_AUDIO_OPUS = 38          // OPUS
}ENCODE_AUDIO_TYPE;

/* Stream Type */
typedef enum
{
    STREAM_TYPE_UNKNOWN = 0,        // unknown
    STREAM_TYPE_MPEG4,              // MPEG4
    STREAM_TYPE_DHPT =3,	        // old: DHPT
    STREAM_TYPE_NEW,                // old: NEW
    STREAM_TYPE_HB,                 // old: HB
    STREAM_TYPE_AUDIO,              // audio
    STREAM_TYPE_PS,                 // MPEG-2: PS
    STREAM_TYPE_DHSTD,              // DHSTD
    STREAM_TYPE_ASF,                // ASF
    STREAM_TYPE_3GPP,               // 3GP
    STREAM_TYPE_RAW,	            // RAW
    STREAM_TYPE_TS,                 // MPEG-2: TS
    STREAM_TYPE_SVC,                // SVC
    STREAM_TYPE_AVI,                // AVI
    STREAM_TYPE_MP4,                // MP4
    STREAM_TYPE_CGI,                // CGI
    STREAM_TYPE_WAV,		        // WAV
    STREAM_TYPE_FLV,                // FLV

    STREAM_TYPE_MKV,                // MKV
    STREAM_TYPE_RTP,			    // RTP
    STREAM_TYPE_RAW_MPEG4,	        // MPEG4 RAW
    STREAM_TYPE_RAW_H264,	        // H264 RAW
    STREAM_TYPE_RAW_H265,	        // H265 RAW
    STREAM_TYPE_WMV,			    // WMV
    STREAM_TYPE_RAW_MPEG2,	        // MPEG2 RAW
    STREAM_TYPE_RAW_SVAC,	        // SVAC RAW
    STREAM_TYPE_MOV,
    STREAM_TYPE_VOB,			    // VOB
    STREAM_TYPE_RAW_H263,
    STREAM_TYPE_RM,
    STREAM_TYPE_DHPS,		        // DHPS
    STREAM_TYPE_RAW_AUDIO,
}STREAM_TYPE;

/* Demux extend info*/
typedef struct 
{
	char*	pHead;				// Frame Data
	int		nLen;				// Frame Data Len
	char*	pBody;				// Frame Raw Data
	int		nBodyLen;			// Frame Raw Len

	int		nRet;				// 0:continue 1:no decode, default:0
	BYTE	nEncryptType;		// Encrypt Type, 0:no encrypt 1:AES
    BYTE    nRotateAngle;       // 0:no Rotate 1:90 Rotate 2:180 Rotate	3:270 Rotate
    char    reserved1[2];
    int     nStreamType;        // see STREAM_TYPE
    char	reserved[120];
}DemuInfoEx;

/* Demux Basic info */
typedef struct
{
	int type;			 // see FRAME_TYPE
	int subtype;		 // see FRAME_SUB_TYPE
	int encode;			 // see ENCODE_VIDEO_TYPE, ENCODE_AUDIO_TYPE
	int sequence;		 // Frame sequence
	int width;			 // Frame width
	int height;			 // Frame height
	int rate;			 // Frame rate
	int year;			 // year
	int month;           // month
	int day;             // day
	int hour;            // hour
	int minute;          // minute
	int secode;          // secode
	LONG timestamp;      // timestamp
	int channels;        // audio channels
	int bitspersample;   // audio sample bits
	int samplespersecond;// audio sample frequency
}DEMUX_INFO;

typedef void (CALLBACK* fDemuxDecCBFun)(LONG nPort,char * pBuf,	LONG nSize,void * pMutexInfo,void* pMutexInfoEx, void* pUserData);

/**
 * Set Demux Frame Data Callback.
 *
 * @param[in]  nPort Port number
 * @param[out] DecCBFun CallBack Fun.
 * @param[in]  pUserData User Data
 * @return BOOL,TRUE--succeeded FALSE--failed
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDemuxCallBack(LONG nPort, fDemuxDecCBFun DecCBFun, void* pUserData);

/**
 * H.264 information callback function
 *
 * @param[in] nPort Port number
 * @param[in] pBuf data buffer
 * @param[in] nLen data size
 * @param[in] pUserData User defined parameter
 */
typedef int (CALLBACK *fH264InfoCBFun)(LONG nPort, char* pBuf, LONG nLen, void* pUserData);

/**
 * Set H.264 information callback function
 *
 * @param[in]  nPort Port number
 * @param[out] pH264InfoCBFun H.264 information callback  function
 * @param[in]  nUser User-customized parameter
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_Set264EncodeInfoCallBack(LONG nPort, fH264InfoCBFun pH264InfoCBFun, void* nUser);

/**
 * set AES decrypt key.
 *
 * @param[in] nPort Port number
 * @param[in] szKey key pointer
 * @param[in] nKeylen key len
 * @return BOOL,TRUE--succeeded FALSE--failed
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetSecurityKey(LONG nPort,const char* szKey,DWORD nKeylen);

/*ENCRYPT TYPE*/
typedef enum
{
	ENCRYPT_UNKOWN = 0,
	ENCRYPT_AES,
	ENCRYPT_AES256,
	ENCRYPT_AES256_GDPR2,
	ENCRYPT_SM1_ECB,    
	ENCRYPT_SM1_OFB,                     
	ENCRYPT_SM4_ECB,                   
	ENCRYPT_SM4_OFB,                     
}ENCRYPT_TYPE;

typedef struct
{
	unsigned char x[32];
	unsigned char y[32];
}PUBLICKEY_PARAM;

//DECRYPT PARAM
typedef struct
{
	char* Key;              //AES:key£»AES256(GDPR 1):key£» AES256(GDPR 2)and GM:vkek   			   
	int KeyLen;			
	char* KeyId;       	    //AES:NULL£» AES256(GDPR 1):keyid£» AES256(GDPR 2)and GM:vkekid 		 
	int KeyIdLen;	
	bool bSetPublicKey;            
	PUBLICKEY_PARAM* pPublicKey;   
	char Reserved[19];           
}DECRYPT_PARAM; 
/**
 *  
 *
 * @param[in] nPort 
 * @param[in] nType  
 * @param[in] szKey 
 * @param[in] nKeylen 
 * @return BOOL£¬,TRUE--succeeded FALSE--failed
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetSecurityKeyEx(LONG nPort, ENCRYPT_TYPE nType, DECRYPT_PARAM* key, unsigned int key_len);
/************************************************************************/
//> display
/************************************************************************/

/**
 * Set or add displayed zone. Support partial enlargement.
 *
 * @param[in] nPort nPort,Port number
 * @param[in] nRegionNum nRegionNum,Display zone serial number.0~(MAX_DISPLAY_WND-1). If nRegionNum is 0, it means the main display window
 * @param[in] pSrcRect Partial displayed zone
 * @param[in] hDestWnd Display window handle
 * @param[in] bEnable Open (set) or close displayed zone
 * @return BOOL,TRUE--succeeded FALSE--failed
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDisplayRegion(LONG nPort,DWORD nRegionNum, DISPLAYRECT *pSrcRect, HWND hDestWnd, BOOL bEnable);


/**
 * Refresh to display. If you refresh when player is in pause mode, the window video 
 * disappears. You can call this interface to get the video agaian. It is valid in pause and frame 
 * by frame playback mode. System will return directly in other situations.
 *
 * @param[in] nPort Port number
 * @return BOOL,TRUE--succeeded FALSE--failed
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_RefreshPlay(LONG nPort);

/************************************************************************/
//> buffer
/************************************************************************/

/**
 * Get sourcing buffer remained data in stream play mode.
 *
 * @param[in] nPort Port number
 * @return DWORD,Current sourcing buffer size(byte)
 */
PLAYSDK_API DWORD CALLMETHOD PLAY_GetSourceBufferRemain(LONG nPort);

/**
 * Clear the remained data in sourcing buffer in stream play mode.
 *
 * @param[in] nPort Port number
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_ResetSourceBuffer(LONG nPort);

/**
 * Clear player buffer.
 *
 * @param[in] nPort Port number
 * @param[in] nBufType,Buffer type, Please refer to macro definition macro definition:
 *         	  BUF_VIDEO_SRC 1 
 *	          BUF_AUDIO_SRC 2 
 *            BUF_VIDEO_RENDER 3 
 *	          BUF_AUDIO_RENDER 4
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_ResetBuffer(LONG nPort,DWORD nBufType);

/**
 * To get player buffer size (frame amount or byte). You can use this interface to get the 
 * data in the buffer so that you can estimate the network delaying time.
 *
 * @param[in] nPort Port number
 * @param[in] nBufType,Buffer type, Please refer to macro definition macro definition:
 *         	  BUF_VIDEO_SRC 1 
 *	          BUF_AUDIO_SRC 2 
 *            BUF_VIDEO_RENDER 3 
 *	          BUF_AUDIO_RENDER 4
 *			  BUF_VIDEO_ALL	5  all video buffer(millisecond)
 * @return DWORD,Return different buffer values in accordance with various parameters. Source buffer 
 *  returns byte and other buffer return the frame amount after decoding.
 */
PLAYSDK_API DWORD CALLMETHOD PLAY_GetBufferValue(LONG nPort,DWORD nBufType);

/************************************************************************/
//> vehicular hard disk
/************************************************************************/

/**
 * Initial Disk(Only for Windows32).
 *
 * @return UINT,successful return num of disks, failed return 0.
 */
PLAYSDK_API UINT CALLMETHOD PLAY_InitDisk();

/**
 * Percent CallBack.
 *
 * @param[in] nPort Port number
 * @param[in] nPercent percent, -1 means exception occur.
 * @param[in] pUserData User data
 */
typedef void (CALLBACK *fPercentCallbackFunc)(LONG nPort, int nPercent, void* pUserData);

/**
 * progress callback. you can set begin or end time, if set,you need call PLAY_SetFileRefCallBack interface to take effect, 
 * [0,0] means the whole file, no need to build index,it is used after calling PLAY_OpenFile.
 *
 * @param[in] nPort Port number
 * @param[in] nStartTime start time,seconds from 1970/1/1
 * @param[in] nEndTime end time,seconds from 1970/1/1 
 * @param[out] pFunCallback progress callback fun
 * @param[in] pUserData user data
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetPercentCallBack(LONG nPort, LONG nStartTime, LONG nEndTime, fPercentCallbackFunc pFunCallback, void* pUserData);

typedef enum
{
	FORMAT_ALL_DATA, // all data
	FORMAT_KEY_DATA  // key area data
}FormatType;

/**
 * Format Disk(Only for Windows32)
 *
 * @param[in] disk_no the disk number of partition information
 * @param[in] type format type
 * @return DWORD,Return different buffer values in accordance with various parameters. Sourcing buffer 
 *  returns byte and the buffer return the frame amount after decoding.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_FormatDisk(UINT disk_no, FormatType type);

/**
 * query all files in disk(Only for Windows32).
 *
 * @param[in] channel the channel no of the video that needs to be querying
 * @param[in] start_time start time
 * @param[in] end_time end time
 * @param[in/out] pmax_ret_num input means that the maximum num of files to be query, out means that the file num queried.
 * @param[out] pfile_info the location of the stored video file that is querying.
 * @param[in] type the type of the video of querying
 * @param[in] nDiskIndex disk index
 * @param[in] driver_type drive type
 * @return DWORD,Return different buffer values in accordance with various parameters. Sourcing buffer 
 *  returns byte and the buffer return the frame amount after decoding.
 */
PLAYSDK_API UINT CALLMETHOD PLAY_QueryFileList(UINT nChannel,USER_TIME start_time,USER_TIME end_time,UINT *pmax_ret_num,pFILE_INFO pfile_info,UINT type, BYTE nDiskIndex, UINT driver_type);

/************************************************************************/
//> fish eye
/************************************************************************/

typedef enum
{
	FISHEYEMOUNT_MODE_INVALID = 0,
	FISHEYEMOUNT_MODE_CEIL = 1,						// ceil mode
	FISHEYEMOUNT_MODE_WALL,							// wall mode
	FISHEYEMOUNT_MODE_FLOOR,						// floor mode
	FISHEYEMOUNT_MODE_NUM
}FISHEYE_MOUNTMODE;

typedef enum
{
	FISHEYECALIBRATE_MODE_INVALID = 0,
	FISHEYECALIBRATE_MODE_OFF = 1,								// stop fish-eye algorithm
	FISHEYECALIBRATE_MODE_ORIGINAL,								// original
	FISHEYECALIBRATE_MODE_PANORAMA,								// 1p
	FISHEYECALIBRATE_MODE_PANORAMA_PLUS_ONE_EPTZ,				// 1p+1
	FISHEYECALIBRATE_MODE_DOUBLE_PANORAMA,						// 2p
	FISHEYECALIBRATE_MODE_ORIGINAL_PLUS_DOUBLE_PANORAMA,		// 1+2p
	FISHEYECALIBRATE_MODE_ORIGINAL_PLUS_THREE_EPTZ_REGION,		// 1+3
	FISHEYECALIBRATE_MODE_PANORAMA_PLUS_THREE_EPTZ_REGION,		// 1p+3
	FISHEYECALIBRATE_MODE_ORIGINAL_PLUS_TWO_EPTZ_REGION,		// 1+2	
	FISHEYECALIBRATE_MODE_ORIGINAL_PLUS_FOUR_EPTZ_REGION,		// 1+4
	FISHEYECALIBRATE_MODE_PANORAMA_PLUS_FOUR_EPTZ_REGION,		// 1p+4
	FISHEYECALIBRATE_MODE_PANORAMA_PLUS_SIX_EPTZ_REGION,		// 1p+6
	FISHEYECALIBRATE_MODE_ORIGINAL_PLUS_EIGHT_EPTZ_REGION,		// 1+8
	FISHEYECALIBRATE_MODE_PANORAMA_PLUS_EIGHT_EPTZ_REGION,		// 1p+8
	FISHEYECALIBRATE_MODE_TWO_EPTZ_REGION_WITH_ORIGINAL,		// 1F+2	
	FISHEYECALIBRATE_MODE_FOUR_EPTZ_REGION_WITH_ORIGINAL,		// 1F+4	
	FISHEYECALIBRATE_MODE_DOUBLE_PANORAMA_WITH_ORIGINAL,		// 1F+2p
	FISHEYECALIBRATE_MODE_FOUR_EPTZ_REGION_WITH_PANORAMA,		// 1p(F)+4

	FISHEYECALIBRATE_MODE_TWO_EPTZ_REGION,		                // 2 eptz region
	FISHEYECALIBRATE_MODE_SINGLE,								// single region
	FISHEYECALIBRATE_MODE_FOUR_EPTZ_REGION,						// 4 eptz region
	FISHEYECALIBRATE_MODE_USER_DEFINED,				    		// user defined
	FISHEYECALIBRATE_MODE_PHONE,								// mobile
	FISHEYECALIBRATE_MODE_ORIGINAL_PLUS_ONE_EPTZ_REGION,		// 1+1
	FISHEYECALIBRATE_MODE_ONE_EPTZ_REGION,						// 1 eptz region
	FISHEYECALIBRATE_MODE_SEMI_SPHERE,							// VR
	FISHEYECALIBRATE_MODE_CYLINDER,								// VR
	FISHEYECALIBRATE_MODE_LITTLE_PLANET,						// VR
	FISHEYECALIBRATE_MODE_DOUBLE_SPHERE,						// VR
	FISHEYECALIBRATE_MODE_DOUBLE_CYLINDER,						// VR
	FISHEYECALIBRATE_MODE_DOUBLE_360,							// VR

	FISHEYECALIBRATE_MODE_NUM
}FISHEYE_CALIBRATMODE;

typedef enum
{
	FISHEYEEPTZ_CMD_INVALID = 0,	
	FISHEYEEPTZ_CMD_ZOOM_IN = 1,						// zoom in
	FISHEYEEPTZ_CMD_ZOOM_OUT,							// zoom out
	FISHEYEEPTZ_CMD_UP,									// up
	FISHEYEEPTZ_CMD_DOWN,								// down
	FISHEYEEPTZ_CMD_LEFT,								// left
	FISHEYEEPTZ_CMD_RIGHT,								// right
	FISHEYEEPTZ_CMD_ROTATE_CLOCKWISE_AUTO,				// auto clockwise
	FISHEYEEPTZ_CMD_ROTATE_ANTICLOCKWISE_AUTO,			// auto anti-clockwise
	FISHEYEEPTZ_CMD_STOP,								// stop
	FISHEYEEPTZ_CMD_SHOW_REGION,						// show region
	FISHEYEEPTZ_CMD_EXIT_SHOW_REGION,					// exit show region
	FISHEYEEPTZ_CMD_DEFAULT,						    // restore
	FISHEYEEPTZ_CMD_ORIGIN_ROTATE,						// rotate

	FISHEYEEPTZ_CMD_SET_CUR_REGION = 0x20,             
	FISHEYEEPTZ_CMD_GET_CUR_REGION,                   
	FISHEYEEPTZ_CMD_IS_IN_PANORAMA_REGION,           
	FISHEYEEPTZ_CMD_TAP_VIEW,							
	FISHEYEEPTZ_CMD_SET_FOCUS,	 				       
	FISHEYEEPTZ_CMD_GET_FOCUS,							

	FISHEYEEPTZ_CMD_PTZ_CALI,							
	FISHEYEEPTZ_CMD_GET_PTZ_RLT,	
    FISHEYEEPTZ_CMD_SET_CUR_REGION_PTZ,                 
    FISHEYEEPTZ_CMD_GET_FOCUS_8192,                     
	FISHEYEEPTZ_CMD_NUM
}FISHEYE_EPTZCMD;

typedef enum
{
	FISHEYE_SETPARAM,
	FISHEYE_GETPARAM

}FISHEYE_OPERATETYPE;

typedef enum
{
	IPCTYPE_200WN				= 0,	
	IPCTYPE_130WN				= 1,
	IPCTYPE_D1WN				= 2,
	IPCTYPE_100WN				= 3,
	IPCTYPE_FE					= 4,	

	SPCTYPE_D6501				= 100,	
	HSPCTYPE_D6A2030E			= 101,	
	HSPCTYPE_D65A2030E			= 102
}CAM_TYPE;

typedef enum
{
	LENTYPE_NORM				= 0,	
	LENTYPE_Lens0361 			= 1,	
	LENTYPE_Lens2880			= 2,	
	LENTYPE_Lens0362 			= 3,	
	LENTYPE_Lens0401 			= 4,	

	LENTYPE_TEST1				= 100	
}LEN_TYPE;

typedef struct
{
	int w;
	int h;
}FISHEYE_SIZE;

typedef struct
{
	short x;
	short y;
}FISHEYE_POINT2D;

typedef struct
{
	FISHEYE_MOUNTMODE     subMountMode;			   
	FISHEYE_CALIBRATMODE  subCalibrateMode;	      
	FISHEYE_SIZE          imgOutput;               
	FISHEYE_POINT2D       upperLeft;               
	int					  reserved[3];				
}FISHEYE_SUBMODE;

typedef struct
{
	FISHEYE_SIZE          mainShowSize;		        
	FISHEYE_SIZE          floatMainShowSize;		
	FISHEYE_SIZE          imgOutput;                
	FISHEYE_SUBMODE*	  subMode;                  
	int		              subModeNum;              
	int                   outputSizeRatio;		   
	int                   reserved[1];				
}FISHEYE_OUTPUTFORMAT;

typedef struct
{
	int x;
	int y;
	int hAngle;
	int vAngle;
	int available;
	int reserved[3];
}FISHEYE_REGIONPARAM;

typedef struct
{
	FISHEYE_REGIONPARAM   regionParam[9];
	int              circularOffset;
	int              panoramaOffset;
	int              useRegionParam;           
	int              reserved[1];
}FISHEYE_MODEINITPARAM;

typedef struct
{	
	int zoom_type;							
	int hcam_wax;		
	int hcam_way;	
	int hcam_wmul;							
	int cfg_type;							

	int prm_re;								
	int prm_mul;							
	int prm_dx;								
	int prm_dy;								
	int prm_cw;								
	int prm_ch;								

	LEN_TYPE mlen_type;						
	CAM_TYPE mcam_type;						
	CAM_TYPE hcam_type;		

	int himg_width;                       
	int himg_height;                        
	int prm_fax;                           

	int mcam_fc;							
	int mcam_cw;							
	int mcam_ch;							
	int cam_height;                         
	int prm_ma;								

	int prm_hw;								// CMOS Width
	int prm_hh;								// CMOS height
	int prm_fo;							
	int prm_ca;								
	int prm_mmul;							
}MHFPTZ_CONFIGPARAM;

typedef struct
{
	FISHEYE_SIZE     mainStreamSize;		   
	int              originX;					
	int              originY;					
	int              radius;					
	int              lensDirection;		       
	FISHEYE_MOUNTMODE     mainMountMode;		
	FISHEYE_CALIBRATMODE  mainCalibrateMode;	
	FISHEYE_MODEINITPARAM modeInitParam;       
	FISHEYE_OUTPUTFORMAT *outputFormat;        
	MHFPTZ_CONFIGPARAM   *configParam;          // default NULL
	int              enableAutoContrast;        // default 0
	int              alphaHistogram;            // default 0
	int              alphaGray;                 // default 0
	FISHEYE_SIZE     captureSize;		        // default 0
	int              mhfptzIndex;               // ptz seqence 0,1,2...
	int              reserved[1];				// reserved
}FISHEYE_OPTPARAM;

typedef struct
{
	FISHEYE_EPTZCMD   ePtzCmd;			
	int          winId;				   						
	int          arg1;
	int          arg2;
	int          arg3;
	int          arg4;
	int          arg5;
	int          arg6;
	int          reserved0[6];			  
	void*        pParam;                   
	void*        pResult;
	void*        pArg;   

	int          reserved1[7];			  
}FISHEYE_EPTZPARAM;

/**
 * start fish-eye correction algorithm.
 *
 * @param[in] nPort Port number
 * @return BOOL,TRUE--succeeded FALSE--failed
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_StartFisheye(LONG nPort);

/**
 * set or get fish-eye params.
 *
 * @param[in] nPort Port number
 * @param[in] operatetype set or get operate type
 * @param[in/out] pOptParam fish-eye params
 * @return BOOL,TRUE--succeeded FALSE--failed
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_OptFisheyeParams(LONG nPort, FISHEYE_OPERATETYPE operatetype, FISHEYE_OPTPARAM* pOptParam);

/**
 * enable or disable the second fish-eye window in floating mode.
 *
 * @param[in] nPort Port number
 * @param[in] hDestWnd handle of display window
 * @param[in] pOptParam fish-eye params
 * @param[in] bEnable TRUE means enable, FALSE means disable
 * @return BOOL,TRUE--succeeded FALSE--failed
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_FisheyeSecondRegion(LONG nPort, HWND hDestWnd, FISHEYE_OPTPARAM* pOptParam, BOOL bEnable);

/**
 * start EPTZ for scaling or moving.
 *
 * @param[in] nPort Port number
 * @param[in/out] pEptzParam EPTZ params
 * @param[in] bSecondRegion TRUE means operate target is the second window in floating mode, default is FALSE
 * @return BOOL,TRUE--succeeded FALSE--failed
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_FisheyeEptzUpdate(LONG nPort, FISHEYE_EPTZPARAM* pEptzParam, BOOL bSecondRegion);

/**
 * stop fish-eye correction algorithm.
 *
 * @param[in] nPort Port number
 * @return BOOL,TRUE--succeeded FALSE--failed
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_StopFisheye(LONG nPort);

/**
 * fish-eye information callback.
 *
 * @param[in] nPort Port number
 * @param[in] byCorrectMode correction mode
 * @param[in] wRadius radius
 * @param[in] wCircleX x-coordinate
 * @param[in] wCircleY y-coordinate
 * @param[in] widthRatio ratio of width
 * @param[in] heightRatio ratio of heigth
 * @param[in] gain gain
 * @param[in] denoiseLevel denoise level
 * @param[in] InstallStyle install style
 * @param[in] pUserData custom data
 */
typedef void (CALLBACK* fFishEyeInfoFun)( 
	LONG nPort,
	BYTE byCorrectMode,
	WORD wRadius,
	WORD wCircleX,
	WORD wCircleY,
	UINT widthRatio,
	UINT heightRatio,
	BYTE gain,
	BYTE denoiseLevel,
	BYTE installStyle,
	void* pUserData );

/**
 * set fish-eye information callback.
 *
 * @param[in] nPort Port number
 * @param[out] pFishEyeInfoFun callback function, can not be set to NULL.
 * @param[in] pUserData custom data
 * @return BOOL,TRUE--succeeded FALSE--failed
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetFishEyeInfoCallBack(LONG nPort, fFishEyeInfoFun pFishEyeInfoFun, void* pUserData);

/************************************************************************/
//> catch pic
/************************************************************************/

/*
 * bmp snapshot. write picture data to specified file. PLAY_SetDisplayCallBack Call this function
 * when decoding video data and then you can process the video data (such as snapshot). Keep calling
 * this callback function if there is continue decoding data. But LAY_CatchPic snapshot one image 
 * at one time and it can realize snapshot in pause or frame by frame play mode. If you want to snapshot
 * (one time for one image), please call PLAY_CatchPic. You can call PLAY_SetDisplayCallBack to get
 * video data in a period of time.
 *
 * @param[in] nPort Port number
 * @param[in] sFileName File name
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_CatchPic(LONG nPort,char* sFileName);

/*
 * Snapshot. Picture format could be specified as bmp or jpeg. 
 * write picture data to specified file. PLAY_SetDisplayCallBack Call this function
 * when decoding video data and then you can process the video data (such as snapshot). Keep calling
 * this callback function if there is continue decoding data. But LAY_CatchPic snapshot one image 
 * at one time and it can realize snapshot in pause or frame by frame play mode. If you want to snapshot
 * (one time for one image), please call PLAY_CatchPic. You can call PLAY_SetDisplayCallBack to get
 * video data in a period of time.
 *
 * @param[in] nPort Port number
 * @param[in] sFileName File name
 * @param[in] ePicfomat Picture format type refer to tPicFomats
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_CatchPicEx(LONG nPort,char* sFileName,tPicFormats ePicfomat);

/*
 * Save the snapshot image as BMP file.This switch will occupy CPU resources. Do not call this function if you do not need to save image
 *
 * @param[in] pBuf Image data buffer
 * @param[in] nSize Image data size
 * @param[in] nWidth Image width. Unit is pixel
 * @param[in] nHeight Image height
 * @param[in] nType Data type. T_RGB32, T_UYVY. Please refer to macro definition
 * @param[in] sFileName File name. The file extension name is BMP
 * @return BOOL,TRUE--succeeded  FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_ConvertToBmpFile(char * pBuf,LONG nSize,LONG nWidth,LONG nHeight,LONG nType, char *sFileName);

/*
 * Convert YUV image data to jpeg format.
 *
 * @param[in] pYUVBuf Image data buffer
 * @param[in] nWidth Image width
 * @param[in] nHeight Image height
 * @param[in] YUVtype YUV data type. T_YV12,T_UYVY, ex.
 * @param[in] quality Compress quality, (0, 100]
 * @param[in] sFileName File name.
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_ConvertToJpegFile(char *pYUVBuf, LONG nWidth, LONG nHeight, int YUVtype, int quality, char *sFileName);

/*
 * Snapshot. Return BMP picture data buffer.
 *
 * @param[in] nPort Port number
 * @param[in] pBmpBuf Picture buffer. Allocate by user, suggest size:
 *			sizeof(BITMAPFILEHEADER) +
 *			sizeof(BITMAPINFOHEADER) + w * h * 4
 *			where w is picture width, h is picture height
 * @param[in] dwBufSize Buffer size
 * @param[out] pBmpSize BMP picture data size
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_GetPicBMP(LONG nPort, PBYTE pBmpBuf, DWORD dwBufSize, DWORD* pBmpSize);

/*
 * snapshot BMP image
 *
 * @param[in] nPort Port number
 * @param[in] pBmpBuf   buffer address to store BMP data, allocated by user, must be greater than bmp image size,
 *			Recommended size :size of(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+w*h*4,
 *			w and h are image width and height.
 * @param[in] dwBufSize buffer area size
 * @param[out] pBmpSize image size of actual bmp
 * @param[in] nWidth designated bmp width
 * @param[in] nHeight designated bmp height
 * @param[in] nRgbType designated RGB format 0£ºRGB32;1£ºRGB24;
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_GetPicBMPEx(LONG nPort, PBYTE pBmpBuf, DWORD dwBufSize, DWORD* pBmpSize, LONG nWidth, LONG nHeight, int nRgbType);

/*
 * Snapshot. Return JPEG picture data buffer.
 *
 * @param[in] nPort Port number
 * @param[in] pJpegBuf Picture buffer. Allocate by user, suggest size:
 *			w * h * 3/2
 *			where w is picture width, h is picture height
 * @param[in] dwBufSize Buffer size.
 * @param[out] pJpegSize JPEG picture data size.
 * @param[in] quality Quality of the jpeg compression, value is (0, 100]
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_GetPicJPEG(LONG nPort, PBYTE pJpegBuf, DWORD dwBufSize, DWORD* pJpegSize, int quality);

/*
 * Snapshot. Return TIFF picture data buffer.
 *
 * @param[in] nPort Port number
 * @param[in] pTiffBuf buffer address to store TIFF data, allocated by user, must be greater than TIFF image size,
 *			suggest size:w*h*3+1024,
 *			where w is picture width, h is picture height.
 * @param[in] dwBufSize Buffer size
 * @param[out] pTiffSize TIFF picture data size.
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_GetPicTIFF(LONG nPort, PBYTE pTiffBuf, DWORD dwBufSize, DWORD* pTiffSize);

/*
 * Snap. Can set format, height and width.
 *
 * @param[in] nPort Port number
 * @param[in] sFileName file name
 * @param[in] lTargetWidth picture width
 * @param[in] lTargetHeight picture height
 * @param[in] ePicfomat picture type,refer to tPicFomats
  * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_CatchResizePic(LONG nPort, char* sFileName, LONG lTargetWidth, LONG lTargetHeight, tPicFormats ePicfomat);

/************************************************************************/
//> draw callback
/************************************************************************/

/*
 * Drawing Callback function
 * 
 * @param[in] nPort Port number
 * @param[in] hDc OffScreen, You can operate it just as operate the displayed window DC
 * @param[in] pUserData Customized Parameter
 */
typedef void (CALLBACK* fDrawCBFun)(LONG nPort,HDC hDc, void* pUserData);

/*
 * Register one callback function to get current surface device context. You can draw 
 * (write) in the DC just as you do in client zone DC of the window. But this DC is not the client 
 * zone DC of the window, it is the DC of Off-Screen in DirectDraw. Please note: This interface is 
 * null if you use overlay surface. You can draw in the window. It will be displayed if it is not
 * a transparent color.
 *
 * @param[in] nPort Port number
 * @param[out] DrawFun Callback function handle
 * @param[in] pUserData Customized Parameter
  * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_RigisterDrawFun(LONG nPort, fDrawCBFun DrawCBFun, void* pUserData); 

/*
 *Drawing Callback function
 * 
 * @param[in] nPort Port number
 * @param[in] nReginNum Display zone serial number
 *			0~(MAX_DISPLAY_WND-1).
 *			If nRegionNum is 0, it means refresh the main display window
 * @param[in] hDc OffScreen, You can operate it just as operate the displayed window DC
 * @param[in] pUserData Customized Parameter
 */
typedef void (CALLBACK* fDrawCBFunEx)(LONG nPort,LONG nReginNum,HDC hDc, void* pUserData);

/*
 * Register one callback function to get current surface device context. You can draw 
 * (write) in the DC just as you do in client zone DC of the window. But this DC is not the client 
 * zone DC of the window, it is the DC of Off-Screen in DirectDraw. Please note: This interface is 
 * null if you use overlay surface. You can draw in the window. It will be displayed if it is not 
 * a transparent color.
 *
 * @param[in] nPort Port number
 * @param[in] nReginNum Display zone serial number
 *			0~(MAX_DISPLAY_WND-1).
 *			If nRegionNum is 0, it means refresh the main display window
 * @param[out] DrawFunEx Callback function handle
 * @param[in] pUserData Customized Parameter
  * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_RigisterDrawFunEx(LONG nPort, LONG nReginNum, fDrawCBFunEx DrawFunEx, void* pUserData);

/************************************************************************/
//> record or convertor
/************************************************************************/

/*
 * Start pre record.
 *
 * @param[in] nPort Port number
 * @param[in] sFileName File position
  * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_StartPrepareRecord(LONG nPort,const char* pFileName);

/*
 * Stop pre record.
 *
 * @param[in] nPort Port number
  * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_StopPrepareRecord(LONG nPort);

/*
 * Begin record stream data. It applies to stream mode only. Call it after PLAY_Play.
 *
 * @param[in] nPort Port number
 * @param[in] sFileName Record file name. If there is no existing folder in the name, then create a new folder
 * @param[in] idataType see DATA_RECORD_TYPE
  * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
typedef enum
{
    DATA_RECORD_ORIGINAL = 0,     // Raw video stream
    DATA_RECORD_AVI,              // AVI
    DATA_RECORD_ASF,              // ASF   
    DATA_RECORD_ORIGINAL_SEGMENT, // Segment Raw video stream
    DATA_RECORD_RESIZE_AVI,       // Resolution Changed AVI, target width and height is needed. use PLAY_ResolutionScale.
    DATA_RECORD_MP4,              // MP4 
    DATA_RECORD_RESIZE_MP4,       // Resolution Changed MP4, target width and height is needed. use PLAY_ResolutionScale.
    DATA_RECORD_MP4_NOSEEK,       // No Seek MP4    
    DATA_RECORD_RESIZE_MP4_NOSEEK,// Resolution Changed No Seek MP4, target width and height is needed. use PLAY_ResolutionScale.
    DATA_RECORD_TS,
    DATA_RECORD_PS,               // PS
    DATA_RECORD_RESIZE_DAV,
	DATA_RECORD_DAV,
	DATA_RECORD_AAC,              // AAC(Raw Audio)
	DATA_RECORD_WAV,              // WAV(Raw Audio)

	// if need to add enumeration, add beore it
	DATA_RECORD_COUNT			  // record type count 
}DATA_RECORD_TYPE;
PLAYSDK_API BOOL CALLMETHOD PLAY_StartDataRecord(LONG nPort, char *sFileName, int idataType);

/*
 * Save native stream, the interface need to be used in conjunction with PLAY_StartDataRecord or PLAY_StartDataRecordEx.
 *
 * @param[in] nPort Port number
 * @param[in] pBuf Stream Buffer
 * @param[in] nSize Buffer Size
  * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_WriteData(LONG nPort, PBYTE pBuf,DWORD nSize);

/*
 * Stop recording stream data.
 *
 * @param[in] nPort Port number
  * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_StopDataRecord(LONG nPort);

/*
 * Callback function AVIConvertCallback.
 *
 * @param[in] nPort Port number
 * @param[in] lMediaChangeType AVI_MEDIACHANGE_FRAMERATE means frame change;AVI_MEDIACHANGE_FRAMERATE means resolution change. 
 * @param[in] pUserData Customized Parameter
 * @param[out] pIsNewFile TRUE=segment conversion;FALSE= only one file conversion;Default FALSE.
 * @param[out] sNewFileName new file name if segment conversion.
  * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
typedef void (CALLBACK* fAVIConvertCallback)(LONG nPort, LONG lMediaChangeType, void* pUserData, BOOL *pIsNewFile, char *sNewFileName);

/*
 * Begin AVI conversion and set AVI switch call status. 
 *
 * @param[in] nPort Port number
 * @param[in] sFileName File Name
 * @param[out] pAVIFunc Callback function
 * @param[in] pUserData Customized Parameter
  * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_StartAVIConvert(LONG nPort, char *sFileName, fAVIConvertCallback pAVIFunc, void* pUserData);

/*
 * stop converting avi.
 *
 * @param[in] nPort Port number
  * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_StopAVIConvert(LONG nPort);

/************************************************************************/
//> decode or render settings
/************************************************************************/

/*
 * Set Decode&Render Engine(Windows Platform), Must be Called before PLAY_Play.
 *
 * @param[in] nPort Port number
 * @param[in] decodeType Decode Engine£¨only for H264,hevc)
 * @param[in] renderType Render Engine
  * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetEngine(LONG nPort,DecodeType decodeType,RenderType renderType);

/*
 * Set video quality. When it is in high quality the video is vivid, but the CPU comsuption 
 * is high. When system is in multiple-channel play mode, you can set a little bit lower quality so
 * as to lower CPU comsuption. When you want to see one window in large zone, you can set it to high
 * quality to get excellent video effect.
 *
 * @param[in] nPort Port number
 * @param[in] bHighQuality The video quality is the best when it is 1.The video quality is the lowest when it is o (default value.)
  * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetPicQuality(LONG nPort,BOOL bHighQuality);

/*
 * Get current video quality.
 *
 * @param[in] nPort Port number
 * @param[out] bHighQuality TRUE high quality,FALSE low quality.
  * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_GetPictureQuality(LONG nPort,BOOL *bHighQuality);

/*
 * Vertical synchronize method, support offscreen mode only
 * Called after PLAY_Play. When displaying dynamic images, this method may be useful.
 *
 * @param[in] nPort Port number
 * @param[in] bEnable TRUE Enable vertical synchronize;FALSE Diable vertical synchronize.
  * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_VerticalSyncEnable(LONG nPort, BOOL bEnable);

/*
 * Whether to enable high definition image internal adjustment strategy. This strategy is enabled in the quick release of 4 times or more, 
 * only play I frames, each frame play is not enabled
 *
 * @param[in] nPort Port number
 * @param[in] bEnable see PLAY_STRATEGE_E
  * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
typedef enum _PLAY_STRATEGE
{
	PLAY_THROW_FRAME_NO = 0,						// no drop frame
	PLAY_THROW_FRAME_FLAG_HIGHT = 1,				// drop frame if resolution>1080p&&speed>=4,or 720p=<resolution<=1080p&&speed>=8, or resolution<720p&&speed>=16
	PLAY_THROW_FRAME_FLAG_ALL = 2,					// forced drop frame
	PLAY_THROW_FRAME_FLAG_ADAPTION = 3,				// adaptive drop frame
	PLAY_THROW_FRAME_FLAG_ADAPTION_LOW_CPU = 4,		// adaptive drop frame,low cpu usage mode
} PLAY_STRATEGE_E;
PLAYSDK_API BOOL CALLMETHOD PLAY_EnableLargePicAdjustment(LONG nPort, int bEnable);

/*
 * Setting the number of decode threads
 *
 * @param[in] nPort Port number
 * @param[in] nNum Thread number
  * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDecodeThreadNum(LONG nPort, DWORD nNum);

/*
 * Setting the decoding strategy
 *
 * @param[in] nPort Port number
 * @param[in] nStrategyType 16:It indicates that the frame discontinuous in decoding is returned in advance.
 *               8: In the representation of decoding, the stream protocol does not conform to the protocol as a decoding error
 *               0: It is indicated that when the stream protocol does not conform to the protocol in decoding, the decoding will continue, 
 *                  and the error stream will Blurred the screen.
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDecodeStrategy(LONG nPort, int nStrategyType);

/*
 * Anti sawtooth enabled switch, only windows
 *
 * @param[in] nPort Port number
 * @param[in] bEnable True:Open anti aliasing , False:turn off anti aliasing
  * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_AntiAliasEnable(LONG nPort, BOOL bEnable);

/************************************************************************/
//> private data
/************************************************************************/

/*
 * Display private data such as rule box, rule box alarm, mobile detection, etc.
 *
 * @param[in] nPort Port number
 * @param[in] bTrue TRUE:open FALSE:close
 * @param[in] nReserve Retention parameter
  * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_RenderPrivateData(LONG nPort, BOOL bTrue, LONG nReserve);

//IVS TYPE
typedef enum
{
	IVSDRAWER_TRACK = 1,						//track
	IVSDRAWER_ALARM,							//Event alarm
	IVSDRAWER_RULE,								//rule
	IVSDRAWER_TRACKEX2 = 14,					//trackEx2
	IVSDRAWER_DATA_WITH_LARGE_AMOUNT = 25		//large amount (include CrowdDistri heatmap)
}IVSDRAWER_TYPE;
/*
 * Set Ivs Display Enable
 *
 * @param[in] nPort Port number
 * @param[in] nIvsType
 * @param[in] bEnable
 * @return BOOL,TRUE--succeeded FALSE--failed
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetIvsEnable( LONG nPort, int nIvsType, BOOL bEnable);

/*
 * Data Frame CallBack.
 *
 * @param[in] nPort Port number
 * @param[in] pBuf Raw data with head
 * @param[in] nSize Buffer Size
 * @param[in] pUserData  Customized Parameter
  * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
typedef void (CALLBACK* fDataCBFun)(LONG nPort,char * pBuf,LONG nSize, void* pUserData);

/*
 * Data Frame CallBack,callback  the original data which has head, and the outer layer is parsed by itself
 *
 * @param[in] nPort Port number
 * @param[out] pDataCBFun CallBack Function
 * @param[in] pUserData Customized Parameter
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDataCallBack(LONG nPort, fDataCBFun pDataCBFun, void* pUserData);

/*
 * IVS Decode CallBack Function
 *
 * @param[in] pIVSBuf Auxiliary frame data(json or data after intelligent frame parsing)
 * @param[in] nIVSType Auxiliary frame data type, see IVS_TYPE.
 *			nIVSType==IVSINFOTYPE_RAWDATA, pIVSBuf means json data;
 *			nIVSType==IVSINFOTYPE_TRACK, single IVS object is SP_IVS_OBJ_EX struct;
 *			nIVSType==IVSINFOTYPE_TRACK_EX_B0, single IVS object is SP_IVS_COMMON_OBJ struct;
 * @param[in] nIVSBufLen Auxiliary frame data length
 *			  nIVSType==IVSINFOTYPE_RAWDATA, nIVSBufLen means the length of json data;
 *			  nIVSType==IVSINFOTYPE_TRACK, nIVSBufLen means nums of IVS Object * sizeof(SP_IVS_OBJ_EX);
 *			  nIVSType==IVSINFOTYPE_TRACK_EX_B0, nIVSBufLen means nums of IVS Object * sizeof(SP_IVS_COMMON_OBJ);
 * @param[in] nFrameSeq Auxiliary frame ID
 * @param[in] pReserved Retention parameters
 * @param[in] pUserData Customized Parameter
 */
/* IVS Type */
typedef enum _IVS_TYPE
{
	IVSINFOTYPE_PRESETPOS			= 1,						
	IVSINFOTYPE_MOTINTRKS			= 2,				
	IVSINFOTYPE_MOTINTRKS_EX		= 3,			
	IVSINFOTYPE_LIGHT				= 4,			
	IVSINFOTYPE_RAWDATA				= 5,   // jason
	IVSINFOTYPE_TRACK				= 6,   // intelligent analysis information 
	IVSINFOTYPE_TRACK_EX_B0			= 7,   // intelligent structured data information
	IVSINFOTYPE_MOTIONFRAME			= 9,	
	IVSINFOTYPE_VIDEO_CONCENTRATION = 10,
	IVSINFOTYPE_OVERLAY_PIC			= 11,
	IVSINFOTYPE_OSD_INFO			= 12,  
	IVSINFOTYPE_GPS_INFO			= 13,  // GPS
	IVSINFOTYPE_TAGGING_INFO		= 14,  
	IVSINFOTYPE_TRACK_A1			= 15,  
	IVSINFOTYPE_DATA_WITH_LARGE_AMOUNT = 16,
    IVSINFOTYPE_TRACK_A1_EX         = 17,
	IVSINFOTYPE_DATA_WITH_WATER_LEVEL_MONITOR = 18, //waterlevel detection
	IVSINFOTYPE_INTELFLOW			= 19,			// intelligent flow
	IVSINFOTYPE_DATA_WITH_SOUND_DECIBEL = 20,	//sound decibel(0x18)
	IVSINFOTYPE_DATA_WITH_SMART_MOTION = 21,	//smart motion(0x19)
	IVSINFOTYPE_DHOP_SMART			= 22,		//DHOP(0x14)
}IVS_TYPE;

/* IVSINFOTYPE_OVERLAY_PIC struct */
typedef struct 
{
	unsigned char nOverLayPicPurpose;	
	unsigned char nOverLayPicAction;	
	unsigned char nOverLayPicCodeFormat;
}OVERLAY_PIC_INFO;

/* IVSINFOTYPE_OSD_INFO struct */
typedef struct 
{
	unsigned short nOsdTopLeftCornercoordinateX; 
	unsigned short nOsdTopLeftCornercoordinateY; 
	unsigned char  nOsdWordSize;				 
	unsigned char  nOsdWordAlignment;
	unsigned char  reverse[6];
	unsigned int   nOsdRgbaValue;
}OSD_DATA_INFO;

typedef void (CALLMETHOD *fIVSInfoCallbackFunc)(char* pIVSBuf, LONG nIVSType, LONG nIVSBufLen, LONG nFrameSeq, void* pReserved, void* pUserData);

/*
 * IVS information acquisition function
 *
 * @param[in] nPort Port number
 * @param[out] pFunc CallBack Function
 * @param[in] pUserData Customized Parameter
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetIVSCallBack(LONG nPort, fIVSInfoCallbackFunc pFunc, void* pUserData);

/*
 * GPS information acquisition CallBack Function
 *
 * @param[in] pBuf Auxiliary frame data
 * @param[in] nLen Auxiliary frame data length 
 * @param[in] pUserData Customized Parameter
 * @return int,Meaningless
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
typedef int (CALLBACK *fGPSInfoCallbackFunc)(char* pBuf, LONG nLen, void* pUserData);

/*
 * GPS information acquisition function
 *
 * @param[in] nPort Port number
 * @param[out] pFunc CallBack Function  
 * @param[in] pUserData Customized Parameter
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetGPSCallBack(LONG nPort, fGPSInfoCallbackFunc pFunc, void* pUserData);

/* Statistics information type */
typedef enum _STATISTIC_TYPE
{
	TYPE_UNUSE			= 0,							// Unuse type
	INPUT_DATA_INTERVAL,						// Input stream data interval, parameter 1 means time interval, paramete 2 means data length
	PRASE_VIDEO_INTERVAL,					// Video frame resolution interval, parameter 1 means time interval£¬parameter  means frame number
	VIDEO_PTS_INTERVAL,						// Video frame pts interval, parameter 1 means time interval, parameter  means frame number
	DECODE_VIDEO_TIME,						// Video frame decoding time consuming, parameter 1 means interface time consuming, parameter  means frame number
	PLAY_VIDEO_INTERVAL,						// Video frame playing interval, parameter 1 means time interval, parameter  means frame number
	RENDER_VIDEO_TIME,						// Video frame rendering time consuming, parameter 1 means interface time consuming
	VIDEO_DECODE_ERROR = 1000,		// Video decoding error, parameter 1 lack of meaning, parameter  means frame number
}STATISTIC_TYPE;

/* Statistics information structure */
typedef struct statistic_info
{
	LONG			nPort;							// Port number
	LONG			nStatisticType;			// Statistic type
	LONGLONG		nParam1;			// Parameter1
	LONGLONG		nParam2;			// Parameter2
	char			szReserved[16];				// Reserved	 parameter
} STATISTIC_INFO, *PSTATISTIC_INFO;

/*
 * Decode And Play Statistics information callback
 *
 * @param[in] pStatisticData Statistics data
 * @param[in] pUserData User defined parameter
 * @return int lack of meaning
 */
typedef int (CALLBACK *fStatisticCallbackFunc)(PSTATISTIC_INFO pStatisticData, void* pUserData);

/*
 * Statistics information callback function
 *
 * @param[in]  nPort Port number
 * @param[out] pFunc callback  function  
 * @param[in]  pUserData User-customized parameter
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetStatisticCallBack(LONG nPort, fStatisticCallbackFunc pFunc, void* pUserData);

/*
 * Set image display proportion
 *
 * @param[in] nPort Port number
 * @param[in] nWidthProportion  Width, image display proportion
 * @param[in] nHeightProportion Height, image display proportion	
 * @return BOOL,TRUE--succeeded FALSE--failed.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetViewProportion(LONG nPort, int nWidthProportion, int nHeightProportion);

/************************************************************************/
//> not recommend
/************************************************************************/

/**
 * Get current error code. please use PLAY_GetLastErrorEx.
 *
 * @return Error code
 */
PLAYSDK_API DWORD CALLMETHOD PLAY_GetLastError(LONG nPort);

/*
 * Open the file and automatically assign the channel number
 *
 * @param[in] sFileName File Name
 * @return DWORD,Fail to return 0, otherwise return to the channel number
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API DWORD CALLMETHOD PLAY_CreateFile(LPSTR sFileName);

/*
 * Close the playback file and release the automatic channel number
 *
 * @param[in] nPort Port number
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_DestroyFile(LONG nPort);

/*
 * Open the stream interface and automatically assign the channel number
 *
 * @param[in] nBufPoolSize The buffer size range for setting up the data stream in the player is [SOURCE_BUF_MIN,SOURCE_BUF_MAX].
 * @return DWORD,Fail to return 0, otherwise return to the channel number
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API DWORD CALLMETHOD PLAY_CreateStream(DWORD nBufPoolSize);

/*
 * Close the data stream interface and release the automatically allocated channel number
 *
 * @param[in] nPort Port number
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_DestroyStream(LONG nPort);

/*
 * Repeat with PLAY_OneByOneBack, use PLAY_OneByOneBack.
 *
 * @param[in] nPort Port number
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_BackOne(LONG nPort);

/*
 * Setting the resolution change notification message.
 *
 * @param[in] nPort Port number
 * @param[in] hWnd A message sent window
 * @param[in] nMsg User input message, when the encoding format changes , the user receives this message in the hWnd window
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetEncChangeMsg(LONG nPort,HWND hWnd,UINT nMsg);

/*
 * Set the message to be sent at the end of the file.
 *
 * @param[in] nPort Port number
 * @param[in] hWnd A message sent window
 * @param[in] nMsg User input message, when the encoding format changes , the user receives this message in the hWnd window
 * @return BOOL,TRUE--succeeded FALSE--failed.
 * @note if failed,you can get the error code by calling PLAY_GetLastErrorEx.
 */
PLAYSDK_API BOOL CALLMETHOD PLAY_SetFileEndMsg(LONG nPort,HWND hWnd,UINT nMsg);

#ifdef __cplusplus
}
#endif

#endif
