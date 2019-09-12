﻿#ifndef _PT_StrategyApi_H_
#define _PT_StrategyApi_H_

#ifdef WIN32
#ifdef PT_QUANTAPI_EXPORTS
#define PT_QUANTAPI_EXTERN  _declspec(dllexport)
#else
#define PT_QUANTAPI_EXTERN//  _declspec(dllimport)
#pragma comment(lib, "PT_QuantApi.lib")
#endif
#endif /* WIN32 */

#include "PT_QuantBaseErr.h"
#include "PT_QuantDef.h"

namespace QuantPlus
{
	class PT_QuantSpi
	{
	public:
		PT_QuantSpi() {}
		virtual ~PT_QuantSpi() {}
	public:
		///@brief 通知连接
		///@param nSrvType 业务服务器类型 参考QuantPlus::PT_Quant_APPServerType
		///@return 无
		///@note 在业务服务器连通时主动通知
		virtual void OnConnect(int nSrvType) = 0;
		///@brief 通知断开
		///@param nSrvType 业务服务器类型 参考QuantPlus::PT_Quant_APPServerType
		///@return 无
		///@note 在业务服务器断开时主动通知
		virtual void OnDisconnect(int nSrvType) = 0;
		///@brief 通知用户信息
		///@param  pInfo 用户信息
		///@return 无
		///@note 登录成功之后返回的用户信息
		virtual void onRtnUserInfo(const PT_QuantUserBase* pInfo) {};
        ///@brief 通知用户登录警告信息
        ///@param  nLoginWarnType 参考PT_QuantBaseErr.h中LoginWarnType
        ///@return 无
        ///@note 登录警告时推送
        virtual void onRtnLoginWarn(int nLoginWarnType) {};
	public://非业务级别指令回调
		///查询用户信息回调
		///@param    pUserInfo              回调信息指针
		///@param    isEnd                  是否是最后一条
		///@return   无
		///@remark   reqQueryAllUser接口的回复
		virtual void onRspQueryAllUser(const PT_QuantUser* pUserInfo, bool isEnd) {};
		///查询用户信息回调
		///@param    pPublicCode              公用券信息
		///@param    nNum                     公用券数量
		///@return   无
		///@remark   reqQueryAllUser接口的回复
		virtual void onRspPublicCode(const PT_QuantUserCodeControl* pPublicCode, int nNum) {};
		///修改用户信息回调
		///@param    TD_QuantUserAuthen                修改后的信息
		///@param    error                    操作是否成功，非0代表失败，错误码参考TQuantErrorType::EQuantErrorType
		///@return   无
		///@remark   reqUpdateUserAuthen接口的回复
		virtual void onRspUpdateUserAuthen(const TD_QuantUserAuthen* rsp, int error) {};
		///修改用户券池回调
		///@param    TD_QuantUserCodePool              修改后的信息
		///@param    error                    操作是否成功，非0代表失败，错误码参考TQuantErrorType::EQuantErrorType
		///@return   无
		///@remark   reqUpdateUserCodePool接口的回复
		virtual void onRspUpdateUserCodePool(const TD_QuantUserCodePool* rsp, int error) {};
		///修改用户可用券回调
		///@Param    pUserDisablePublicCode        需要修改的用户可用券
		///@param    error                    操作是否成功，非0代表失败，错误码参考TQuantErrorType::EQuantErrorType
		///@return   无
		///@remark   reqDisablePublicCode接口回调
		virtual void onRspDisablePublicCode(const TD_QuantUserDisablePublicCode* pUserDisablePublicCode, int error) {};
		///修改账户优先级回调
		///@Param    rsp              修改请求信息
		///@param    error            修改是否成功，非0代表失败，错误码参考TQuantErrorType::EQuantErrorType
		///@return   无
		///@remark   reqUpdateAccountPriority接口回调
		virtual void onRspUpdateAccountPriority(const TD_RspUpdatePriority* rsp, int error) {};
		///查询账户优先级回调
		///@Param    rsp              优先级信息
		///@param    error            查询是否成功，非0代表失败，错误码参考TQuantErrorType::EQuantErrorType
		///@param    isEnd            是否是最后一条
		///@return   无
		///@remark   reqQueryAccountPriority接口回调
		virtual void onRspQueryAccountPriority(const TD_RspQryPriority* rsp, int error, bool isEnd) {};
		///盘中修改资金账户操作权限
		///@Param    rsp        修改信息
		///@Param    error      是否成功
		///@return   返回不为0，请求失败，错误码参考TQuantErrorType::EQuantErrorType
		///@remark   采用非阻塞模式
		virtual void onRspUpdateAccountPermissions(const TD_RspUpdateAccountPermission* rsp, int error) {};
	public: //交易业务逻辑回调
		///下单回调
		///@param    rsp              下单回调信息
		///@param    error            下单是否成功，非0代表失败，错误码参考TQuantErrorType::EQuantErrorType
		///@return   无
		///@remark   reqOrderInsert接口的回复
		virtual void onRspOrderInsert(const TD_RspOrderInsert *rsp, int error) {};
		///撤单回调
		///@param    rsp              撤单回调信息
		///@param    error            撤单是否成功，非0代表失败，错误码参考TQuantErrorType::EQuantErrorType
		///@return   无
		///@remark   reqOrderDelete接口的回复
		virtual void onRspOrderDelete(const TD_RspOrderDelete *rsp, int error) {};

		///查询委托回调
		///@param    rsp              委托详细信息
		///@param    error            查询是否成功，非0代表失败，错误码参考TQuantErrorType::EQuantErrorType
		///@param    isEnd            是否是最后一条
		///@return   无
		///@remark   reqQryOrder接口的回复，该接口有可能会重复触发直到最后一条IsEnd为True rsp为空的消息
		virtual void onRspQryOrder(const TD_RspQryOrder *rsp, int error, bool isEnd) {};
		///查询成交明细
		///@param    rsp              成交详细信息
		///@param    error            查询是否成功，非0代表失败，错误码参考TQuantErrorType::EQuantErrorType
		///@param    isEnd            是否是最后一条
		///@return   无
		///@remark   reqQryMatch接口的回复，该接口有可能会重复触发直到最后一条IsEnd为True rsp为空的消息
		virtual void onRspQryMatch(const TD_RspQryMatch *rsp, int error, bool isEnd) {};
		///查询持仓回调
		///@param    rsp              持仓详细信息
		///@param    error            查询是否成功，非0代表失败，错误码参考TQuantErrorType::EQuantErrorType
		///@param    isEnd            是否是最后一条
		///@return   无
		///@remark   reqQryPosition接口的回复，该接口有可能会重复触发直到最后一条IsEnd为True rsp为空的消息
		virtual void onRspQryPosition(const TD_RspQryPosition *rsp, int error, bool isEnd) {};
		///查询最大可委托量回调
		///@param    rsp              可委托量详细信息
		///@param    error            查询是否成功，非0代表失败，错误码参考TQuantErrorType::EQuantErrorType
		///@param    isEnd            是否是最后一条
		///@return   无
		///@remark   reqQryMaxEntrustCount接口的回复，该接口有可能会重复触发直到最后一条IsEnd为True rsp为空的消息
		virtual void onRspQryMaxEntrustCount(const TD_RspQryMaxEntrustCount* rsp, int error, bool isEnd) {};
		///查询资金帐号信息初始值回调
		///@param    rsp              可委托量详细信息
		///@param    error            查询是否成功，非0代表失败，错误码参考TQuantErrorType::EQuantErrorType
		///@param    isEnd            是否是最后一条
		///@return   无
		///@remark   reqQryAccountInitMaxEntrustCount接口的回复，该接口有可能会重复触发直到最后一条IsEnd为True rsp为空的消息
		virtual void onRspQryAccountInitMaxEntrustCount(const TD_RspQryInitAccountMaxEntrustCount* rsp, int error, bool isEnd) {};
		///查询资金帐号当前信息回调
		///@param    rsp              可委托量详细信息
		///@param    error            查询是否成功，非0代表失败，错误码参考TQuantErrorType::EQuantErrorType
		///@param    isEnd            是否是最后一条
		///@return   无
		///@remark   reqQryAccountMaxEntrustCount接口的回复，该接口有可能会重复触发直到最后一条IsEnd为True rsp为空的消息
		virtual void onRspQryAccountMaxEntrustCount(const TD_RspQryAccountMaxEntrustCount* rsp, int error, bool isEnd) {};

		///订单状态改变推送
		///@param    notice              定单状态信息
		///@return   无
		///@remark   该接口在订单状态改变时被调用
		virtual void onRtnOrderStatusChangeNotice(const TD_RtnOrderStatusChangeNotice *notice) {};
		///成交明细推送
		///@param    notice              成交明细信息
		///@return   无
		///@remark   该接口在订单发生成交时被调用，推送成交明细
		virtual void onRtnOrderMatchNotice(const TD_RtnOrderMatchNotice *notice) {};
		///持仓浮盈推送
		///@param    notice              持仓浮盈信息
		///@return   无
		///@remark   该接口频率与Tick数据同步，推送持仓的的浮盈信息
		virtual void onRtnProfit(const TD_RtnProfit *notice) {};
		///用户权限信息推送
		///@param    notice              用户权限信息
		///@return   无
		///@remark   当用户权限信息被修改时推送；登陆时也会推送一次
		virtual void onRtnUserAuthen(const TD_QuantUserAuthen* notice) {};
		///最大可委托量推送
		///@param    notice              用户权限信息
		///@return   无
		///@remark   当用户可委托量被改变时推送
		virtual void onRtnMaxEntrustCount(const TD_RspQryMaxEntrustCount* notice) {};
		///修改用户券池推送
		///@param    notice              券池信息
		///@return   无
		///@remark   用户券池被修改之后推送股票可买可卖初始值
		virtual void onRtnUpdateUserCodePool(const TD_QuantUserCodePool* notice) {};
		///模拟资金账号推送
		///@param    notice              模拟资金账号信息
		///@return   无
		///@remark   创建模拟交易环境，登陆时阻塞进行推送所有可用模拟账号信息
		virtual void onRtnSimulationAccount(const TD_SimulationAccount* notice) {};
	public://行情业务逻辑回调
		///@brief 响应请求交易日列表
		///@param[in] nReqID 消息请求序号
		///@param[in] pWindCode 指定的股票代码列表
		///@param[in] nWindCodeNum 指定的股票代码数量
		///@param[in] szBeginDay 指定的起始日期
		///@param[in] szEndDay 指定的结束日期
		///@param[in] nErrNo 响应失败的错误码
		///@param[in] szErrMsg 响应失败的错误描述
		///@return 无
		virtual void OnRspTradingDay(MD_ReqID nReqID, const MD_CodeType *pWindCode, long nWindCodeNum, MD_ISODateTimeType szBeginDay, MD_ISODateTimeType szEndDay, int nErrNo, const char *szErrMsg) {};
		///@brief 响应请求停牌日列表
		///@param[in] nReqID 消息请求序号
		///@param[in] pWindCode 指定的股票代码表
		///@param[in] nWindCodeNum 指定的股票代码数量
		///@param[in] szBeginDay 指定的起始日期
		///@param[in] szEndDay 指定的结束日期
		///@param[in] nErrNo 响应失败的错误码
		///@param[in] szErrMsg 响应失败的错误描述
		///@return 无
		///@note 该信号会在请求停牌日列表后主动通知
		virtual void OnRspHaltingDay(MD_ReqID nReqID, const MD_CodeType *pWindCode, long nWindCodeNum, MD_ISODateTimeType szBeginDay, MD_ISODateTimeType szEndDay, int nErrNo, const char *szErrMsg) {};
		///@brief 响应请求订阅行情
		///@param[in] nReqID 消息请求序号
		///@param[in] nSubType 指定的订阅类型
		///@param[in] nCycType 指定的K线周期类型(如果nSubType未包含K线订阅类型, 请将该参数置为0)
		///@param[in] pSubWindCode 指定的股票代码表
		///@param[in] nSubWindCodeNum 指定的股票代码数量
		///@param[in] szBeginTime 指定的起始时间
		///@param[in] szEndTime 指定的结束时间
		///@param[in] nErrNo 响应失败的错误码
		///@param[in] szErrMsg 响应失败的错误描述
		///@return 无
		///@note 该信号会在请求订阅行情后主动通知
		virtual void OnRspSubQuote(MD_ReqID nReqID, MD_SubType nSubType, MD_CycType nCycType, const MD_CodeType *pSubWindCode, long nSubWindCodeNum, MD_ISODateTimeType szBeginTime, MD_ISODateTimeType szEndTime, int nErrNo, const char *szErrMsg) {};
		///@brief 通知交易代码表
		///@param[in] pWindCode 指定的股票代码表
		///@param[in] nWindCodeNum 指定的股票代码数量
		///@param[in] pOptionCode 指定的期权代码表
		///@param[in] nOptionCodeNum 指定的期权代码数量
		///@return 无
		virtual void OnRtnTradingCode(const MD_DATA_CODE *pWindCode, long nWindCodeNum, const MD_DATA_OPTION_CODE *pOptionCode, long nOptionCodeNum) {};
		///@brief 通知交易日列表
		///@param[in] nReqID 消息请求序号
		///@param[in] szWindCode 指定的股票的代码(该指针若为nullptr, 则表示整个市场的交易日列表)
		///@param[in] pDay 交易日列表
		///@param[in] nDayNum 交易日个数
		///@return 无
		///@note 该信号会在请求交易日列表后主动通知
		virtual void OnRtnTradingDay(MD_ReqID nReqID, const char *szWindCode, const MD_ISODateTimeType *pDay, long nDayNum) {};
		///@brief 通知停牌日列表
		///@param[in] nReqID 消息请求序号
		///@param[in] szWindCode 指定股票的代码
		///@param[in] pDay 交易日列表
		///@param[in] nDayNum 交易日个数
		///@return 无
		///@note 该信号会在请求停牌日列表后主动通知
		virtual void OnRtnHaltingDay(MD_ReqID nReqID, const char *szWindCode, const MD_ISODateTimeType *pDay, long nDayNum) {};
		///@brief 通知个股行情
		///@param[in] nReqID 消息请求序号
		///@param[in] pMarket 个股的行情数据地址
		///@return 无
		///@note 该信号会在请求历史逐笔行情或订阅实时逐笔行情后主动通知
		virtual void OnRtnMarket(MD_ReqID nReqID, MD_DATA_MARKET *pMarket) {};
		///@brief 通知K线行情
		///@param[in] nReqID 消息请求序号
		///@param[in] pKLine K线行情数据地址
		///@return 无
		///@note 该信号会在请求历史K线行情或订阅实时K线行情后主动通知
		virtual void OnRtnKLine(MD_ReqID nReqID, MD_DATA_KLINE *pKLine) {};
		///@brief 通知指数行情
		///@param[in] nReqID 消息请求序号
		///@param[in] pIndex 指数行情数据地址
		///@return 无
		///@note 该信号会在请求历史逐笔行情或订阅实时逐笔行情后主动通知
		virtual void OnRtnIndex(MD_ReqID nReqID, MD_DATA_INDEX *pIndex) {};
		///@brief 通知逐笔成交
		///@param[in] nReqID 消息请求序号
		///@param[in] pTrans 逐笔成交数据地址
		///@return 无
		///@note 该信号会在请求历史逐笔行情或订阅实时逐笔行情后主动通知
		virtual void OnRtnTransaction(MD_ReqID nReqID, MD_DATA_TRANSACTION *pTrans) {};
		///@brief 通知委托队列
		///@param[in] nReqID 消息请求序号
		///@param[in] pQueue 委托队列数据地址
		///@return 无
		///@note 该信号会在请求历史逐笔行情或订阅实时逐笔行情后主动通知
		virtual void OnRtnOrderQueue(MD_ReqID nReqID, MD_DATA_ORDER_QUEUE *pQueue) {};
		///@brief 通知逐笔委托
		///@param[in] nReqID 消息请求序号
		///@param[in] pOrder 逐笔委托数据地址
		///@return 无
		///@note 该信号会在请求历史逐笔行情或订阅实时逐笔行情后主动通知
		virtual void OnRtnOrder(MD_ReqID nReqID, MD_DATA_ORDER *pOrder) {};
		///@brief 通知期货行情
		///@param[in] nReqID 消息请求序号
		///@param[in] pFuture 期货行情数据地址
		///@return 无
		///@note 该信号会在请求历史逐笔行情或订阅实时逐笔行情后主动通知
		virtual void OnRtnFuture(MD_ReqID nReqID, MD_DATA_FUTURE *pFuture) {};
		///@brief 通知期权行情
		///@param[in] nReqID 消息请求序号
		///@param[in] pOption 期权行情数据地址
		///@return 无
		///@note 该信号会在请求历史逐笔行情或订阅实时逐笔行情后主动通知
		virtual void OnRtnFutureOption(MD_ReqID nReqID, MD_DATA_FUTURE *pOption) {};
		///@brief 通知开市消息
		///@param[in] nReqID 消息请求序号
		///@param[in] pDate 开市日期地址
		///@return 无
		///@note 该信号会在请求历史行情或订阅实时行情后主动通知
		virtual void OnRtnDayBegin(MD_ReqID nReqID, MD_ISODateTimeType pDate) {};
		///@brief 通知闭市消息
		///@param[in] nReqID 消息请求序号
		///@param[in] pDate 闭市日期地址
		///@return 无
		///@note 该信号会在请求历史行情或订阅实时行情后主动通知
		virtual void OnRtnDayEnd(MD_ReqID nReqID, MD_ISODateTimeType pDate) {};
		///@brief 通知实效性消息
		///@param[in] nReqID
		///@return 无
		///@note 该信号只在请求实时行情时出现, 用于表示之后的数据为实时推送行情数据
		virtual void OnRtnTimeless(MD_ReqID nReqID) {};
	};

#ifdef WIN32
	class PT_QUANTAPI_EXTERN PT_QuantApi
#else
	class PT_QuantApi
#endif
	{
	public:
		PT_QuantApi();
		virtual ~PT_QuantApi();
	public:
		///获取API版本
		///@param    无
		///@return   API版本
		///@remark   静态函数
		static char* getVersion();
		///创建实例
		///@param    spi                  回调指针
		///@param    bEnableLog           是否开启日志
		///@param    nTdType              交易环境
		///@param    nMdType              行情环境
		///@return   TradeDataApi类型的对象实例
		///@remark   默认连接上选择的环境
		static PT_QuantApi* createApi(PT_QuantSpi* spi, bool bEnableLog, PT_QuantTdAppEType nTdType, PT_QuantMdAppEType nMdType);
		///创建实例
		///@param    spi                  回调指针
		///@param    bEnableLog           是否开启日志
		///@param    nTdType              交易环境
		///@param    bTdConnect           是否激活交易环境
		///@param    nMdType              行情环境
		///@param    bMdConnect           是否激活行情环境
		///@return   TradeDataApi类型的对象实例
		///@remark   静态函数
		static PT_QuantApi* createApi(PT_QuantSpi* spi, bool bEnableLog, PT_QuantTdAppEType nTdType, bool bTdConnect, PT_QuantMdAppEType nMdType, bool bMdConnect, bool bIfSyn);
		/// ///删除实例
		///@param    api                  需要删除的对象实例
		///@return   无
		///@remark   静态函数
		static void deleteApi(PT_QuantApi* api);
		/// 初始化
		///@param    无
		///@return   无
		///@remark   静态函数
		static void Init();
		///解析错误码
		///@Param    nErrCode             代码号
		///@Param    szErrmsg             错误码
		///@Param    len                  szErrmsg内存长度
		///@remark:  静态函数，使用此接口前需调用Init()才能获取完整的错误码解析，否则只能解析系统级别错误
		static void GetErrMsg(int nErrCode, char* szErrmsg, int len);
		///设置回测限制模板
		///@param    req                  // 设置的回测限制
		///@return   返回不为0，请求失败，错误码参考TQuantErrorType::EQuantErrorType
		///@remark   采用阻塞模式,仅在回测时有用
		virtual int SetNewBackTest(PT_BackTestReq* req) = 0;
		///登录认证获取权限
		///@Param    szUseName            登录帐号
		///@Param    szPasswd             登录密码
		///@return   返回0登录成功,非0登录失败，错误码参考TQuantErrorType::EQuantErrorType
		///@remark:  采用阻塞模式
		virtual int Login(char* szUseName, char* szPasswd) = 0;
		///获取股票代码表
		///@return   返回不为0，请求失败，错误码参考TQuantErrorType::EQuantErrorType
		///@remark:  采用阻塞模式
		virtual int GetCode() = 0;
		///同步执行函数
		///@remark:  同步模式中启用，调用该函数的线程作为回调线程
		//virtual void Run() = 0;
		static void Run();
		///退出同步执行
		///@remark:  强行退出同步执行
		//virtual void BreakExec() = 0;
		static void BreakExec();
	public:// 非业务级别接口
		///获取所有用户信息
		///@return   返回不为0，请求失败，错误码参考TQuantErrorType::EQuantErrorType
		///@remark:  采用阻塞模式
		//  virtual int reqQueryAllUser() = 0;
		///修改用户权限
		///@Param    req                  请求指令
		///@return   返回不为0，请求失败，错误码参考TQuantErrorType::EQuantErrorType
		///@remark   采用非阻塞模式，修改方式为覆盖修改
		//  virtual int reqUpdateUserAuthen(TD_QuantUserAuthen* pUserAuthen) = 0;
		///修改用户可用券
		///@Param    req                  请求指令
		///@return   返回不为0，请求失败，错误码参考TQuantErrorType::EQuantErrorType
		///@remark   采用非阻塞模式，修改方式为增量修改,当Id为-1000的时候修改的是公用券
		//  virtual int reqUpdateUserCodePool(TD_QuantUserCodePool* pUserCodePool) =0;
		///修改用户可用券
		///@Param    pUserDisablePublicCode        需要修改的用户可用券
		///@return   返回不为0，请求失败，错误码参考TQuantErrorType::EQuantErrorType
		///@remark   采用非阻塞模式，修改方式为增量修改
		//  virtual int reqDisablePublicCode(TD_QuantUserDisablePublicCode* pUserDisablePublicCode) = 0;
		///修改账户优先级
		///@Param    req          修改请求信息
		///@return   返回不为0，请求失败，错误码参考TQuantErrorType::EQuantErrorType
		///@remark   采用非阻塞模式,修改为覆盖修改
		//  virtual int reqUpdateAccountPriority(TD_ReqUpdatePriority* req) = 0;
		///查询账户优先级
		///@Param    req          查询请求信息
		///@return   返回不为0，请求失败，错误码参考TQuantErrorType::EQuantErrorType
		///@remark   采用非阻塞模式，nUserId为0，默认为查询全部
		//  virtual int reqQueryAccountPriority(TD_ReqQryPriority* req) = 0;
		///盘中修改资金账户操作权限
		///@Param    req          禁用信息
		///@return   返回不为0，请求失败，错误码参考TQuantErrorType::EQuantErrorType
		///@remark   采用非阻塞模式
		//  virtual int reqUpdateAccountPermissions(TD_ReqUpdateAccountPermission* req) = 0;
	public:///交易业务接口
		///下单
		///@Param    req                  下单请求信息
		///@return   返回不为0，发送失败，错误码参考TQuantErrorType::EQuantErrorType
		///@remark   采用非阻塞模式
		virtual int reqOrderInsert(TD_ReqOrderInsert* req) = 0;
		///撤单
		///@Param    req                  撤单请求信息
		///@return   返回不为0，发送失败，错误码参考TQuantErrorType::EQuantErrorType
		///@remark   采用非阻塞模式
		virtual int reqOrderDelete(TD_ReqOrderDelete* req) = 0;
		///查询委托
		///@Param    req                  查询请求信息
		///@return   返回不为0，发送失败，错误码参考TQuantErrorType::EQuantErrorType
		///@remark   采用非阻塞模式
		virtual int reqQryOrder(TD_ReqQryOrder* req) = 0;
		///查询成交明细
		///@Param    req                  查询请求信息
		///@return   返回不为0，发送失败，错误码参考TQuantErrorType::EQuantErrorType
		///@remark   采用非阻塞模式
		virtual int reqQryMatch(TD_ReqQryMatch* req) = 0;
		///查询持仓
		///@Param    req                  查询请求信息
		///@return   返回不为0，发送失败，错误码参考TQuantErrorType::EQuantErrorType
		///@remark   采用非阻塞模式
		virtual int reqQryPosition(TD_ReqQryPosition* req) = 0;
		///订阅最大可委托量
		///@Param    req                  查询请求信息
		///@return   返回不为0，发送失败，错误码参考TQuantErrorType::EQuantErrorType
		///@remark   采用非阻塞模式
		virtual int reqQryMaxEntrustCount(TD_ReqQryMaxEntrustCount* req) = 0;
		///查询资金帐号信息初始值
		///@Param    req                  查询请求信息
		///@return   返回不为0，发送失败，错误码参考TQuantErrorType::EQuantErrorType
		///@remark   采用非阻塞模式
		virtual int reqQryAccountInitMaxEntrustCount(TD_ReqQryAccountMaxEntrustCount* req) = 0;
		///查询资金帐号当前信息
		///@Param    req                  查询请求信息
		///@return   返回不为0，发送失败，错误码参考TQuantErrorType::EQuantErrorType
		///@remark   采用非阻塞模式
		virtual int reqQryAccountMaxEntrustCount(TD_ReqQryAccountMaxEntrustCount* req) = 0;
		///订阅最大可委托量推送
		///@return   返回不为0，发送失败，错误码参考TQuantErrorType::EQuantErrorType
		///@remark   采用非阻塞模式
		virtual int reqSubscribeMaxEntrustCount() = 0;

	public:
		///@brief 请求交易日列表
		///@param[in] nReqID 消息请求序号
		///@param[in] pWindCode 指定的股票代码列表
		///@param[in] nWindCodeNum 指定的股票代码数量
		///@param[in] szBeginDay 指定的起始日期
		///@param[in] szEndDay 指定的结束日期
		///@return 无
		///@note 如果调用者为pWindCode插入的是动态内存, 由调用者负责释放, 本接口内部不作释放处理
		virtual int ReqTradingDay(MD_ReqID nReqID, const MD_CodeType *pWindCode, long nWindCodeNum, const MD_ISODateTimeType szBeginDay, const MD_ISODateTimeType szEndDay) = 0;
		///@brief 请求停牌日列表
		///@param[in] nReqID 消息请求序号
		///@param[in] pWindCode 指定的股票代码列表
		///@param[in] nWindCodeNum 指定的股票代码数量
		///@param[in] szBeginDay 指定的起始日期
		///@param[in] szEndDay 指定的结束日期
		///@return 无
		///@note 如果调用者为pWindCode插入的是动态内存, 由调用者负责释放, 本接口内部不作释放处理
		virtual int ReqHaltingDay(MD_ReqID nReqID, const MD_CodeType *pWindCode, long nWindCodeNum, const MD_ISODateTimeType szBeginDay, const MD_ISODateTimeType szEndDay) = 0;
		///@brief 请求订阅行情
		///@param[in] nReqID 消息请求序号
		///@param[in] nSubType 订阅行情类型
		/// 常见的订阅行情类型:
		/// -# 0x0000-未知类型(不订阅任何订阅行情)
		/// -# 0x0001-个股行情
		/// -# 0x0002-指数行情
		/// -# 0x0004-逐笔成交
		/// -# 0x0008-逐笔委托
		/// -# 0x0010-委托队列
		/// -# 0x0020-期货行情
		/// -# 0x0040-期权行情
		/// -# 0x0080-K线行情
		///@param[in] nCycType K线周期类型
		/// 常见的K线周期类型:
		/// -# 0x0000-未知类型(不订阅任何K线行情)
		/// -# 0x0001-10秒K线
		/// -# 0x0002-1分钟K线
		/// -# 0x0004-5分钟K线
		/// -# 0x0008-15分钟K线
		/// -# 0x0010-30分钟K线
		/// -# 0x0020-1小时K线
		/// -# 0x0040-1日K线
		///@param[in] pSubWindCode 指定的股票代码列表
		///@param[in] nSubWindCodeNum 指定的股票代码数量
		///@param[in] szBeginTime 指定的起始时间
		///@param[in] szEndTime 指定的结束时间
		///@return 返回不为0，请求失败，错误码参考TQuantErrorType::EQuantErrorType
		///@note 如果调用者为pSubWindCode插入的是动态内存, 由调用者负责释放, 本接口内部不作释放处理
		virtual int ReqSubQuote(MD_ReqID nReqID, MD_SubType nSubType, MD_CycType nCycType, const MD_CodeType *pSubWindCode, long nSubWindCodeNum, const MD_ISODateTimeType szBeginTime, const MD_ISODateTimeType szEndTime) = 0;
	};
}
#endif//_PT_StrategyApi_H_
