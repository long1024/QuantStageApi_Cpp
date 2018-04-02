#ifndef __PT_QUANT_BASE_ERR_H__
#define __PT_QUANT_BASE_ERR_H__

#ifndef PT_QUANTBASEAPI_NAMESPACE
#define PT_QUANTBASEAPI_NAMESPACE
#define PT_QUANTBASEAPI_NAMESPACE_BEGIN    namespace PT_QuantPlatform {
#define PT_QUANTBASEAPI_NAMESPACE_END      }
#define USE_PT_QUANTBASEAPI_NAMESPACE      using namespace PT_QuantPlatform;
#endif /* PT_QUANTBASEAPI_NAMESPACE */

#include <stdint.h>

PT_QUANTBASEAPI_NAMESPACE_BEGIN

/* 量化交易接口公共错误码 */
typedef long TQuantErrorType;
typedef enum
{
	/* 默认错误 */
	/* 通信层面错误: (-100) - (-1) */

	EQuantErrorType_None = 0,                    /* 执行正常, 没有错误 */

	/* quantplus系统平台错误: 1-99 */
	EQuantErrorType_NotConnect = 1,              /* 网络尚未连通 */
	EQuantErrorType_ParamInvalid = 2,            /* 指定参数无效 */
	EQuantErrorType_LimitFunction = 3,           /* 指定功能受限 */
	EQuantErrorType_HttpServerConnectError,      /* http服务器连接失败*/
	EQuantErrorType_HttpRequestError,            /* http请求失败 */
	EQuantErrorType_ParseError,                  /* 通信包解析失败 */
	EQuantErrorType_SerializeError,              /* 通信包打包失败 */
	EQuantErrorType_NoTavailableFuction,         //暂不支持此函数
	EQuantErrorType_Logout,                      //未登录
	EQuantErrorType_AppServerDisconnect,         //业务服务器已断开


	/* 行情错误: 100-199 */

	/* 交易错误: 200-299 */
	EQuantErrorType_TooHighFrequency = 200,             //指令太频繁
	EQuantErrorType_OrderNotFound,                      //无此订单
	EQuantErrorType_NotTradingTime,                     //非交易时间
	EQuantErrorType_OverHighOrLow,                      //超过涨跌停价
	EQuantErrorType_InvalidVol,                         //非法委托量
	EQuantErrorType_Cannotselfdeal,                     //无法自成交
	EQuantErrorType_CannotWithDrawn,                    //无法撤单(订单已经处于终结状态)
	EQuantErrorType_NotEnoughLendingAmoutOrCaptial,     //没有足够的券或钱
	EQuantErrorType_StopTrade,                          //停机
	EQuantErrorType_NoSuchTradeType,                    //无此交易类型
	EQuantErrorType_RiskCantTrade,                      //风控无法开仓交易
	EQuantErrorType_StrategyRiskCantWithDrawn,          //策略强平无法撤单
	EQuantErrorType_WithoutthisAuthority,               //无此权限
	EQuantErrorType_InvalidCode,                        //非法证券代码
	EQuantErrorType_NoPisitionToClose,                  //无仓可以平

	// QuantApi: 600-800
	EQuantErrorType_MDNotConnect = 600,               // 尚未连接行情服务器
	EQuantErrorType_TDNotConnect,                     // 尚未连接交易服务器
	EQuantErrorType_MDNotAvaliable,                   // 无法正常使用行情
	EQuantErrorType_TDNotAvaliable,                   // 无法正常使用交易

} EQuantErrorType;

PT_QUANTBASEAPI_NAMESPACE_END

#endif /* __PT_QUANT_BASE_ERR_H__ */