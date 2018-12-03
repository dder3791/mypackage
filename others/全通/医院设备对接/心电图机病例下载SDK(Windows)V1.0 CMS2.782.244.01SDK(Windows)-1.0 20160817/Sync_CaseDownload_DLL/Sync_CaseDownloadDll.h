#ifndef _SYNC_CASEDOWNLOAD_DLL
#define _SYNC_CASEDOWNLOAD_DLL

//#include <winioctl.h>

enum DownloadMessage
{
	CASEDOWNLOAD = 0,	// 0  已下载新病例
	ERROR_OPEN,			// 1  端口打开失败
	ERROR_VSN,			// 2  获取设备版本号失败
	ERROR_DEV,			// 3  获取设备标识失败
	ERROR_CASES,		// 4  获取病例数失败
	ERROR_NOCASE,		// 5  未检测到新病例
	ERROR_INFO,			// 6  获取病例信息失败
	ERROR_DATA,			// 7  获取病例数据失败
	ERROR_DELETE,		// 8  删除病例失败
	ERROR_SPACE,		// 9  磁盘空间不足
	ERROR_END,			// 10 中止下载
	DOWNLOADING			// 11 正在下载
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//函数功能：向外部传递线程信息
//使用规则：可通过emDLM参数值获得下载过程的信息，做出正确的处理
//输入参数：emDLM 下载过程向外部传输的信息
//			nPercent 下载病例进度（百分比），此参数只在emDLM为DOWNLOADING时有效
//输出参数：无
//返回值：无
typedef void (__stdcall *fcbDownloadMessage)(DownloadMessage emDLM, int nPercent);// 向外部传递线程信息

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//函数功能：开启下载线程，循环下载心电图机中的病例，下载成功后删除病例
//使用规则：先使用CheckPort函数检查nCommNum端口是否正确。如果已经开启了下载线程，再调用此函数则会中止已开启的线程，开启新的线程。
//输入参数：nCommNum：串口编号；
//			nInterval：下载间隔，单位ms
//			funcDLM：获取线程信息回调函数
//输出参数：无
//返回值：成功返回1，失败返回0
int StartDownloadCase(int nCommNum, int nInterval, char *pPath, fcbDownloadMessage funcDLM);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//函数功能：中止下载线程
//使用规则：使用此函数随时中止下载线程。
//输入参数：无
//输出参数：无
//返回值：无
void StopDownloadCase();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//函数功能：检测端口是否已经连接了正确的设备
//使用规则：在下载病例之前，如果需要检测端口，可以调用本函数。
//输入参数：nCommNum：串口编号；
//输出参数：无
//返回值：如果设备连接正确，返回1，否则返回0
int CheckPort(int nCommNum);

#endif