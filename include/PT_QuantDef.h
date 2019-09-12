﻿#ifndef _QuantDef_H_
#define _QuantDef_H_
#include <stdint.h>
#include <string.h>

namespace QuantPlus
{
	/// <summary>
	/// QuantApi
	/// </summary>
	typedef char PT_CodeType[64];

	// 行情环境
	enum PT_QuantMdAppEType
	{
		PT_QuantMdAppEType_Test = 0,            // 测试环境（注：该环境已停止使用！！！）
		PT_QuantMdAppEType_Real,                // 生产环境
	};

	// 交易环境
	enum PT_QuantTdAppEType
	{
		PT_QuantTdAppEType_Real,                // 生产环境
		PT_QuantTdAppEType_Test,                // 测试环境 (注：该环境已停止使用！！！)    
		PT_QuantTdAppEType_Simulation           // 模拟环境
	};

	// 业务服务器类型
	enum PT_Quant_APPServerType
	{
		PT_Quant_APPServerType_RealMdServer = 0,            // 实时行情服务器
		PT_Quant_APPServerType_HisrotyMdServer,             // 历史行情服务器
		PT_Quant_APPServerType_CacheMdServer,               // 实时缓存服务器

		PT_Quant_APPServerType_TDServer = 10,               //  交易服务器
	};

	// 用户角色
	enum PT_QuantUserType
	{
		PT_QuantUserType_Risk = 1,                       //  风控员
		PT_QuantUserType_Trade                           //  交易员
	};

	// 用户信息
	class PT_QuantUserBase
	{
	public:
		int64_t                        nId;
		char               szUserName[128];                 // 用户名
		char               szNickName[128];                 // 用户别名
		int                       nGroupId;                 // 组ID

		PT_QuantUserType   nUserRole;                       // 用户角色

		double          nStampTax;                   //  印花税
		double          nTransferFees;               //  过户费
		double          nCommissions;                //  佣金

		char			szSecurityCode[32];					//验证码

		PT_QuantUserBase()
		{
			nId = 0;
			nUserRole = PT_QuantUserType_Trade;
			memset(szUserName, 0, 128);
			memset(szNickName, 0, 128);
			nGroupId = 0;

			nStampTax = 0;
			nTransferFees = 0;
			nCommissions = 0;

			memset(szSecurityCode, 0, 32);
		}
		virtual ~PT_QuantUserBase()
		{

		}
	};

	class PT_QuantUserCodeControlDetail
	{
	public:
		int64_t           nAccountId;
		int               nVol;
		PT_QuantUserCodeControlDetail()
		{
			nAccountId = 0;
			nVol = 0;
		}
		~PT_QuantUserCodeControlDetail()
		{

		}
	};

	// 券池类
	class PT_QuantUserCodeControl
	{
	public:
		char               szWinCode[64];
		double             nCaptial;                   // 最大可用资金
		int                nLendingAmount;             // 最大可用券

		int                              nDetailNum;   // 可用明细数量
		PT_QuantUserCodeControlDetail*   pDetail;      // 可用数量
		PT_QuantUserCodeControl()
		{
			memset(szWinCode, 0, 64);
			nCaptial = 0;
			nLendingAmount = 0;
			nDetailNum = 0;
			pDetail = NULL;
		}
	};

	class PT_QuantUser : public PT_QuantUserBase
	{
	public:
		bool               ifStopTrade;                     // 是否停机
		int               nStopTradePostion;                // 停机位(亏算资金量)
		double     nStopPercentTradePostion;                // 停机位(亏损比例)

		int                nSinglePositionHoldTime;         // 单笔持仓时间阈值
		int                nSinglePositionLoss;             // 单笔持仓亏损阈值(亏算资金量)
		double      nSinglePercentPositionLoss;             // 单笔持仓亏损阈值(亏损比例)

		int                      nCodeControlNum;       //  可用券数量
		PT_QuantUserCodeControl* pCodeControl;          // （可用券信息）指针偏移

		int                      nDisableCodeNum;
		PT_CodeType*             pDisableCode;

		/////add by long.wang 
		int64_t  	basePoint;							 	 // bp值
		int32_t		forceClosePostion;						 // 强平位
		double 		nPercentForceClosePostion ; 			 // 强平位比例		
		/////
		
		PT_QuantUser()
		{
			ifStopTrade = false;
			nStopTradePostion = 1000000;
			nStopPercentTradePostion = 0.1;

			nSinglePositionHoldTime = 1000000;
			nSinglePositionLoss = 1000000;
			nSinglePercentPositionLoss = 0.1;

			nCodeControlNum = 0;
			pCodeControl = NULL;

			nDisableCodeNum = 0;
			pDisableCode = NULL;

			///// add by long.wang
			basePoint = 0;
			forceClosePostion = 0;
			nPercentForceClosePostion = 0.0;
			/////
		}
		virtual ~PT_QuantUser()
		{
			if(pCodeControl)
			{
				delete[] pCodeControl;
				pCodeControl = NULL;
			}

			if(pDisableCode)
			{
				delete[] pDisableCode;
				pDisableCode = NULL;
			}
		}
	};

	struct PT_BackTestReq
	{
		int64_t nSimAccountId;         // 模拟资金账号


		PT_BackTestReq()
		{
			nSimAccountId = 0;
		}
		virtual ~PT_BackTestReq()
		{

		}
	};

	/// <summary>
	/// 行情结构体
	/// </summary>
#pragma pack(push)
#pragma pack(1)
	typedef int  MD_ReqID;
	typedef char MD_CodeType[32];
	typedef char MD_CodeName[32];
	typedef char MD_ISODateTimeType[21];    //日期和时间类型(格式 yyyy-MM-dd hh:mm:ss)
	typedef char MD_ShortText[128];
	typedef char MD_Text[1024];

	// 服务器类型
	typedef int MD_SrvType;
#define MD_SrvType_none            0x0000   // 未知类型
#define MD_SrvType_history         0x0001   // 历史缓存行情服务器
#define MD_SrvType_cache           0x0002   // 实时缓存行情服务器
#define MD_SrvType_realtime        0x0004   // 实时推送行情服务器

	// 周期类型
	typedef int MD_CycType;
#define MD_CycType_none            0x0000   // 未知类型
#define MD_CycType_second_10       0x0001   // 10秒
#define MD_CycType_minute          0x0002   // 分
#define MD_CycType_minute_5        0x0004   // 5分
#define MD_CycType_minute_15       0x0008   // 15分
#define MD_CycType_minute_30       0x0010   // 30分
#define MD_CycType_hour            0x0020   // 小时
#define MD_CycType_day             0x0040   // 日

	// 订阅类型
	typedef int MD_SubType;
#define MD_SubType_none            0x0000   // 未知类型
#define MD_SubType_market          0x0001   // 个股行情
#define MD_SubType_index           0x0002   // 指数行情
#define MD_SubType_trans           0x0004   // 逐笔成交
#define MD_SubType_order           0x0008   // 逐笔委托
#define MD_SubType_order_queue     0x0010   // 委托队列
#define MD_SubType_future          0x0020   // 期货行情
#define MD_SubType_future_option   0x0040   // 期权行情
#define MD_SubType_kline           0x0080   // K线行情

	struct MD_DATA_CODE
	{
		char    szWindCode[32];         //Wind Code: AG1302.SHF
		char    szMarket[8];            //market code: SHF
		char    szCode[32];             //original code:ag1302
		char    szENName[32];
		char    szCNName[32];           //chinese name: 沪银1302
		int     nType;
	};

	struct MD_DATA_OPTION_CODE
	{
		MD_DATA_CODE basicCode;

		char szContractID[32];          // 期权合约代码
		char szUnderlyingSecurityID[32];// 标的证券代码
		char chCallOrPut;               // 认购认沽C1        认购，则本字段为“C”；若为认沽，则本字段为“P”
		int  nExerciseDate;             // 期权行权日，YYYYMMDD

		//扩充字段
		char chUnderlyingType;          // 标的证券类型C3    0-A股 1-ETF (EBS – ETF， ASH – A 股)
		char chOptionType;              // 欧式美式C1        若为欧式期权，则本字段为“E”；若为美式期权，则本字段为“A”

		char chPriceLimitType;          // 涨跌幅限制类型C1 ‘N’表示有涨跌幅限制类型, ‘R’表示无涨跌幅限制类型
		int  nContractMultiplierUnit;   // 合约单位,         经过除权除息调整后的合约单位, 一定是整数
		int  nExercisePrice;            // 期权行权价,       经过除权除息调整后的期权行权价，右对齐，精确到厘
		int  nStartDate;                // 期权首个交易日,YYYYMMDD
		int  nEndDate;                  // 期权最后交易日/行权日，YYYYMMDD
		int  nExpireDate;               // 期权到期日，YYYYMMDD
	};

	// 备注: 本结构体各字段中的单位为参考单位, 如有异议, 请以市面上常见的行情软件的盘口单位为准
	struct MD_DATA_MARKET
	{
		char            szWindCode[32];         //600001.SH
		char            szCode[32];             //原始Code
		int             nActionDay;             //日期(YYYYMMDD)
		int             nTime;                  //时间(HHMMSSmmm)
		int             nStatus;                //状态
		unsigned int    nPreClose;              //前收盘价=实际价格(单位: 元/股)x10000
		unsigned int    nOpen;                  //开盘价=实际价格(单位: 元/股)x10000
		unsigned int    nHigh;                  //最高价=实际价格(单位: 元/股)x10000
		unsigned int    nLow;                   //最低价=实际价格(单位: 元/股)x10000
		unsigned int    nMatch;                 //最新价=实际价格(单位: 元/股)x10000
		unsigned int    nAskPrice[10];          //申卖价=实际价格(单位: 元/股)x10000
		unsigned int    nAskVol[10];            //申卖量=实际股数(单位: 股)
		unsigned int    nBidPrice[10];          //申买价=实际价格(单位: 元/股)x10000
		unsigned int    nBidVol[10];            //申买量=实际股数(单位: 股)
		unsigned int    nNumTrades;             //成交笔数=实际笔数(单位: 笔)
		int64_t         iVolume;                //成交总量=实际股数(单位: 股)
		int64_t         iTurnover;              //成交总金额=实际金额(单位: 元)
		int64_t         nTotalBidVol;           //委托买入总量=实际股数(单位: 股)
		int64_t         nTotalAskVol;           //委托卖出总量=实际股数(单位: 股)
		unsigned int    nWeightedAvgBidPrice;   //加权平均委买价格=实际价格(单位: 元/股)x10000
		unsigned int    nWeightedAvgAskPrice;   //加权平均委卖价格=实际价格(单位: 元/股)x10000
		int             nIOPV;                  //IOPV净值估值
		int             nYieldToMaturity;       //到期收益率
		unsigned int    nHighLimited;           //涨停价=实际价格(单位: 元/股)x10000
		unsigned int    nLowLimited;            //跌停价=实际价格(单位: 元/股)x10000
	};

	// 备注: 本结构体各字段中的单位为参考单位, 如有异议, 请以市面上常见的行情软件的盘口单位为准
	struct MD_DATA_INDEX
	{
		char        szWindCode[32];         //600001.SH
		char        szCode[32];             //原始Code
		int         nActionDay;             //日期(YYYYMMDD)
		int         nTime;                  //时间(HHMMSSmmm)
		int         nOpenIndex;             //今开盘指数=实际价格(单位: 元/股)x10000
		int         nHighIndex;             //最高指数=实际价格(单位: 元/股)x10000
		int         nLowIndex;              //最低指数=实际价格(单位: 元/股)x10000
		int         nLastIndex;             //最新指数=实际价格(单位: 元/股)x10000
		int64_t     iTotalVolume;           //参与计算相应指数的交易数量=实际股数(单位: 股)
		int64_t     iTurnover;              //参与计算相应指数的成交金额=实际金额(单位: 元)
		int         nPreCloseIndex;         //前盘指数=实际价格(单位: 元/股)x10000
	};

	// 备注: 本结构体为通用期货数据结构体, 期货品种不同则交易单位不同, 如有异议, 请以市面上常见的行情软件的盘口单位为准
	struct MD_DATA_FUTURE
	{
		char            szWindCode[32];         //600001.SH
		char            szCode[32];             //原始Code
		int             nActionDay;             //日期(YYYYMMDD)
		int             nTime;                  //时间(HHMMSSmmm)
		int             nStatus;                //状态
		int64_t         iPreOpenInterest;       //昨持仓
		unsigned int    nPreClose;              //昨收盘价=实际价格(单位: 元/吨)x10000
		unsigned int    nPreSettlePrice;        //昨结算=实际价格(单位: 元/吨)x10000
		unsigned int    nOpen;                  //开盘价=实际价格(单位: 元/吨)x10000
		unsigned int    nHigh;                  //最高价=实际价格(单位: 元/吨)x10000
		unsigned int    nLow;                   //最低价=实际价格(单位: 元/吨)x10000
		unsigned int    nMatch;                 //最新价=实际价格(单位: 元/吨)x10000
		int64_t         iVolume;                //成交总量=实际手数(单位: 手)
		int64_t         iTurnover;              //成交总金额=实际金额(单位: 元)
		int64_t         iOpenInterest;          //持仓总量=实际手数(单位: 手)
		unsigned int    nClose;                 //今收盘=实际价格(单位: 元/吨)x10000
		unsigned int    nSettlePrice;           //今结算=实际价格(单位: 元/吨)x10000
		unsigned int    nHighLimited;           //涨停价=实际价格(单位: 元/吨)x10000
		unsigned int    nLowLimited;            //跌停价=实际价格(单位: 元/吨)x10000
		unsigned int    nAskPrice[5];           //申卖价=实际价格(单位: 元/股)x10000
		unsigned int    nAskVol[5];             //申卖量=实际手数(单位: 手)
		unsigned int    nBidPrice[5];           //申买价=实际价格(单位: 元/吨)x10000
		unsigned int    nBidVol[5];             //申买量=实际手数(单位: 手)
	};

	// 备注: 本结构体各字段中的单位为参考单位, 如有异议, 请以市面上常见的行情软件的盘口单位为准
	struct MD_DATA_ORDER_QUEUE
	{
		char    szWindCode[32]; //600001.SH
		char    szCode[32];     //原始Code
		int     nActionDay;     //日期(YYYYMMDD)
		int     nTime;          //时间(HHMMSSmmm)
		int     nSide;          //买卖方向('B':Bid 'A':Ask)
		int     nPrice;         //委托价格=实际价格(单位: 元/手)x10000
		int     nOrders;        //挂单挡位
		int     nABItems;       //委托单数
		int     nABVolume[200]; //委托数量=实际股数(单位: 股)
	};

	// 备注: 本结构体各字段中的单位为参考单位, 如有异议, 请以市面上常见的行情软件的盘口单位为准
	struct MD_DATA_TRANSACTION
	{
		char    szWindCode[32]; //600001.SH
		char    szCode[32];     //原始Code
		int     nActionDay;     //成交日期(YYYYMMDD)
		int     nTime;          //成交时间(HHMMSSmmm)
		int     nIndex;         //成交编号
		int     nPrice;         //成交价格=实际价格(单位: 元/股)x10000
		int     nVolume;        //成交数量=实际股数(单位: 股)
		int     nTurnover;      //成交金额=实际金额(单位: 元)
		int     nBSFlag;        //买卖方向(买：'B', 卖：'A', 不明：' ')
		char    chOrderKind;    //成交类别
		int     nAskOrder;      //叫卖方委托序号
		int     nBidOrder;      //叫买方委托序号
	};

	// 备注: 本结构体各字段中的单位为参考单位, 如有异议, 请以市面上常见的行情软件的盘口单位为准
	struct MD_DATA_ORDER
	{
		char    szWindCode[32]; //600001.SH
		char    szCode[32];     //原始Code
		int     nActionDay;     //委托日期(YYYYMMDD)
		int     nTime;          //委托时间(HHMMSSmmm)
		int     nOrder;         //委托号
		int     nPrice;         //委托价格=实际价格(单位: 元/股)x10000
		int     nVolume;        //委托数量=实际股数(单位: 股)
		char    chOrderKind;    //委托类别
		char    chFunctionCode; //委托代码('B','S','C')
	};

	// 备注: 本结构体各字段中的单位为参考单位, 如有异议, 请以市面上常见的行情软件的盘口单位为准
	struct MD_DATA_KLINE                    //模拟数据请求
	{
		MD_CycType nType;                   //周期类型
		char    szWindCode[32];             //600001.SH
		char    szCode[32];                 //原始Code
		MD_ISODateTimeType szDatetime;      //时间
		int nDate;                          //日期(YYYYMMDD)
		int nTime;                          //时间(HHMMSSmmm)
		double  nOpen;                      //开盘价=实际价格(单位: 元/股)
		double  nHigh;                      //最高价=实际价格(单位: 元/股)
		double  nLow;                       //最低价=实际价格(单位: 元/股)
		double  nClose;                     //今收价=实际价格(单位: 元/股)
		double  nPreClose;                  //昨收价=实际价格(单位: 元/股)
		double  nHighLimit;                 //涨停价=实际价格(单位: 元/股)
		double  nLowLimit;                  //跌停价=实际价格(单位: 元/股)
		int64_t iVolume;                    //成交数量=实际股数(单位: 股)
		int64_t nTurover;                   //成交金额=实际金额(单位: 元)
	};
#pragma pack(pop)
	/// <summary>
	/// 交易结构体
	/// </summary>
	typedef char TD_CodeType[32];
	typedef char TD_CodeName[32];
	typedef char TD_ISODateTimeType[21];    //日期和时间类型(格式 yyyy-MM-dd hh:mm:ss)
	typedef char TD_OrderIdType[64];
	typedef char TD_AccountType[64];
	typedef char TD_PassType[64];
	typedef char TD_Text[128];
	typedef char TD_ClientIdType[128];

	enum TD_TradeType
	{
		TD_TradeType_None,
		TD_TradeType_Sell,      //卖出
		TD_TradeType_Buy        //买入
	};

	enum TD_OffsetType
	{
		TD_OffsetType_None,
		TD_OffsetType_Open,                 //开仓
		TD_OffsetType_Close,                //平仓
	};

	enum TD_OrderStatusType
	{
		TD_OrderStatusType_fail = -10,          ///指令失败
		TD_OrderStatusType_removed,             ///撤单成功
		TD_OrderStatusType_allDealed,           ///全部成交

		TD_OrderStatusType_unAccpet = 0,        ///未接受
		TD_OrderStatusType_accpeted,            ///已接受未受理
		TD_OrderStatusType_queued,              ///正在排队  (已受理状态)
		//      TD_OrderStatusType_toModify,            ///待报改单
		//      TD_OrderStatusType_modifing,            ///已报改单
		//      TD_OrderStatusType_modified,            ///改单受理
		TD_OrderStatusType_toRemove,            ///待报撤单
		TD_OrderStatusType_removing,            ///已报待撤
		TD_OrderStatusType_partRemoved,         ///部分撤单
		TD_OrderStatusType_partDealed,          ///部分成交
	};

	struct TD_OrderDetail
	{
		///委托编号（broker 或交易所的唯一编号）
		TD_OrderIdType  szOrderStreamId;
		///券商资金账户Id
		int             nAccountId;                 //  如需指定资金账号下单，此字段在下单的时候需要填写
		///资金账户别名
		TD_AccountType  szAccountNickName;

		///委托申报量
		int             nOrderVol;                  //  如需指定资金账号下单，此字段在下单的时候需要填写

		///成交均价  * 10000
		int64_t             nDealedPrice;
		///成交量
		int             nDealedVol;

		///撤单数量
		int             nWithDrawnVol;

		///委托时间
		TD_ISODateTimeType  szOrderTime;
		/// 状态
		TD_OrderStatusType  nStatus;
		//备注
		TD_Text             szText;

		//手续费
		double              nFee;
		TD_OrderDetail()
		{
			memset(szOrderStreamId, 0, sizeof(TD_OrderIdType));
			nAccountId = 0;
			memset(szAccountNickName, 0, sizeof(TD_AccountType));

			nOrderVol = 0;

			nDealedPrice = 0;
			nDealedVol = 0;

			nWithDrawnVol = 0;
			nStatus = TD_OrderStatusType_unAccpet;
			memset(szOrderTime, 0, sizeof(TD_ISODateTimeType));
			memset(szText, 0, sizeof(TD_Text));

			nFee = 0;
		}
		virtual ~TD_OrderDetail()
		{

		}
	};

	struct TD_Base_Msg
	{
		///请求ID（有客户端API维护的唯一ID）
		int     nReqId;

		int64_t nStrategyId;

		///用户保留字段
		int     nUserInt;
		double  nUserDouble;
		TD_Text szUseStr;

		///用户帐号Id
		int64_t     nUserId;
		///客户端编号
		TD_ClientIdType  szClientId;

		TD_Base_Msg()
		{
			nReqId = 0;
			nStrategyId = 0;

			nUserInt = 0;
			nUserDouble = 0;
			memset(szUseStr, 0, sizeof(TD_Text));

			nUserId = 0;
			memset(szClientId, 0, sizeof(TD_ClientIdType));
		}
		virtual ~TD_Base_Msg()
		{

		}
	};

	// 用户权限
	class TD_QuantUserAuthen : public TD_Base_Msg
	{
	public:
		int64_t                        nId;
		int                         nGroupId;

		bool                        ifStopTrade;                     // 是否停机
		int                        nStopTradePostion;                // 停机位(亏算资金量)
		double              nStopPercentTradePostion;                // 停机位(亏损比例)

		int                         nSinglePositionHoldTime;         // 单笔持仓时间阈值
		int                         nSinglePositionLoss;             // 单笔持仓亏损阈值(亏算资金量)
		double               nSinglePercentPositionLoss;             // 单笔持仓亏损阈值(亏损比例)
		int64_t  		     basePoint;							 	 // bp值
		TD_QuantUserAuthen()
		{
			nId = 0;
			nGroupId = 0;

			ifStopTrade = false;
			nStopTradePostion = 1000000;
			nStopPercentTradePostion = 0.1;

			nSinglePositionHoldTime = 1000000;
			nSinglePositionLoss = 1000000;
			nSinglePercentPositionLoss = 0.1;
			basePoint = 0;
		}
		virtual ~TD_QuantUserAuthen()
		{

		}
	};


	class TD_QuantUserCodeInfoDetail
	{
	public:
		int64_t           nAccountId;
		int               nVol;
		TD_QuantUserCodeInfoDetail()
		{
			nAccountId = 0;
			nVol = 0;
		}
		~TD_QuantUserCodeInfoDetail()
		{

		}
	};

	class TD_QuantUserCodeInfo
	{
	public:
		char               szWinCode[64];
		double             nCaptial;                   // 最大可用资金
		int                nLendingAmount;             // 最大可用券

		int                            nDetailNum;     // 可用明细数量
		TD_QuantUserCodeInfoDetail*    pDetail;        // 可用明细
		TD_QuantUserCodeInfo()
		{
			memset(szWinCode, 0, 64);
			nCaptial = 0;
			nLendingAmount = 0;
			nDetailNum = 0;
			pDetail = NULL;
		}
		~TD_QuantUserCodeInfo()
		{
			if (pDetail)
			{
				delete[] pDetail;
				pDetail = NULL;
			}
		}
	};

	// 用户股票池
	class TD_QuantUserCodePool : public TD_Base_Msg
	{
	public:
		int64_t                        nId;
		int                         nGroupId;

		int                      nCodeControlNum;       //  可用券数量
		TD_QuantUserCodeInfo* pCodeControl;          // （可用券信息）指针偏移

		TD_QuantUserCodePool()
		{
			nId = 0;
			nGroupId = 0;

			nCodeControlNum = 0;
			pCodeControl = NULL;

		}
		~TD_QuantUserCodePool()
		{
			if(pCodeControl)
			{
				delete[] pCodeControl;
				pCodeControl = NULL;
			}
		}
	};

	// 用户股票池
	class TD_QuantUserDisablePublicCode : public TD_Base_Msg
	{
	public:
		int64_t                        nId;
		int                         nGroupId;

		int                      nDisablePublicCodeNum;          //  不可用公用券数量
		TD_CodeType*             pDisablePublicCode;             //  不可用公用券指针

		TD_QuantUserDisablePublicCode()
		{
			nId = 0;
			nGroupId = 0;

			nDisablePublicCodeNum = 0;
			pDisablePublicCode = NULL;

		}
		~TD_QuantUserDisablePublicCode()
		{
			if(pDisablePublicCode)
			{
				delete[] pDisablePublicCode;
				pDisablePublicCode = NULL;
			}
		}
	};

	struct TD_Login
	{
		int64_t nId;
		TD_PassType szPass;
		TD_Text szMachineId;
		TD_Login()
		{
			nId = 0;
			memset(szPass, 0, sizeof(szPass));
			memset(szMachineId, 0, sizeof(szPass));
		}
		virtual ~TD_Login()
		{

		}
	};

	// 下单
	struct TD_ReqOrderInsert : TD_Base_Msg
	{
		///证券合约代码
		TD_CodeType     szContractCode;
		///证券合约名称
		TD_CodeName     szContractName;
		///交易类型 买、卖
		TD_TradeType    nTradeType;
		//开平仓类型
		TD_OffsetType   nOffsetType;
		///委托价  *10000
		int64_t             nOrderPrice;
		///委托量
		int             nOrderVol;
		///  订单分笔数
		int            nOrderNum;
		///  订单明细（指针偏移）
		TD_OrderDetail*    pOrderDetail;                // 如需指定资金账号下单，需要填对应的资金账号id以及下到该资金账号的委托数量

		//是否是风控强平
		int                nCloseR;           // 0正常平仓,1为风控干预平仓,2为服务器风控策略达到强平位平仓
		TD_ReqOrderInsert()
		{

			memset(szContractCode, 0, sizeof(TD_CodeType));
			memset(szContractName, 0, sizeof(TD_CodeName));
			nTradeType = TD_TradeType_None;
			nOffsetType = TD_OffsetType_None;

			nOrderPrice = 0;
			nOrderVol = 0;

			nOrderNum = 0;
			pOrderDetail = NULL;
			nCloseR = 0;
		}

		virtual ~TD_ReqOrderInsert()
		{
			if (pOrderDetail)
			{
				delete[] pOrderDetail;
				pOrderDetail = NULL;
			}
		}
	};

	struct TD_RspOrderInsert : TD_ReqOrderInsert
	{
		/// 订单所属用户UserId
		int64_t         nOrderOwnerId;
		///服务器维护（服务唯一）
		int64_t         nOrderId;

		///提交申报量
		int             nSubmitVol;
		///成交均价  * 10000
		int64_t             nDealedPrice;
		///成交总量
		int             nDealedVol;

		///撤单总量
		int             nTotalWithDrawnVol;

		//废单数量
		int             nInValid;
		/// 状态
		TD_OrderStatusType  nStatus;
		/// 下单时间
		TD_ISODateTimeType  szInsertTime;

		//手续费
		double               nFee;
		TD_RspOrderInsert()
		{
			nOrderOwnerId = 0;
			nOrderId = 0;

			nSubmitVol = 0;
			nDealedPrice = 0;
			nDealedVol = 0;

			nTotalWithDrawnVol = 0;
			nInValid = 0;

			nStatus = TD_OrderStatusType_unAccpet;
			memset(szInsertTime, 0, sizeof(TD_ISODateTimeType));

			nFee = 0;
		}
		virtual ~TD_RspOrderInsert()
		{

		}
	};

	// 撤单
	struct TD_ReqOrderDelete : TD_Base_Msg
	{
		///原始订单服务器唯一Id
		int64_t         nOrderId;
		///委托编号（broker 或交易所的唯一编号）
		TD_OrderIdType  szOrderStreamId;
		TD_ReqOrderDelete()
		{
			nOrderId = 0;
			memset(szOrderStreamId, 0, sizeof(TD_OrderIdType));
		}
		virtual ~TD_ReqOrderDelete()
		{

		}
	};

	///撤销订单响应
	typedef TD_ReqOrderDelete TD_RspOrderDelete;
	//委托查询请求
	struct TD_ReqQryPriority : TD_Base_Msg
	{
		/// 需要查询的用户Id
		int64_t               nQueryUserid;

		TD_ReqQryPriority()
		{
			nQueryUserid = 0;
		}
		virtual ~TD_ReqQryPriority()
		{

		}
	};

	struct TD_Priority
	{
		int          nPriority;
		int64_t      nAccountId;
		TD_Priority()
		{

		}
		virtual ~TD_Priority()
		{

		}
	};
	//委托查询请求
	struct TD_RspQryPriority : TD_Base_Msg
	{
		// 用户id
		int64_t               nQueryUserid;
		///证券合约代码
		TD_CodeType           szContractCode;

		int                   nNum;
		TD_Priority*          pPriority;
		TD_RspQryPriority()
		{
			nQueryUserid = 0;
			memset(szContractCode, 0, sizeof(TD_Priority));
			nNum = 0;
			pPriority = NULL;
		}
		virtual ~TD_RspQryPriority()
		{
			if(pPriority != NULL)
			{
				delete[] pPriority;
				pPriority = NULL;
			}
		}
	};
	typedef TD_RspQryPriority TD_ReqUpdatePriority;
	typedef TD_RspQryPriority TD_RspUpdatePriority;
	//委托查询请求
	struct TD_ReqQryOrder : TD_Base_Msg
	{
		///证券合约代码
		TD_CodeType             szContractCode;
		///起始位置(不填默认从头开始)
		int                     nIndex;
		///数量（不填默认查全部）
		int                     nNum;

		TD_ReqQryOrder()
		{
			memset(szContractCode, 0, sizeof(TD_CodeType));
			nIndex = 0;
			nNum = 0;
		}
		virtual ~TD_ReqQryOrder()
		{

		}
	};

	//成交查询请求
	struct TD_ReqQryMatch : TD_Base_Msg
	{
		///证券合约代码
		TD_CodeType     szContractCode;
		///起始位置(不填默认从头开始)
		int             nIndex;
		///数量（不填默认查全部）
		int             nNum;

		TD_ReqQryMatch()
		{
			memset(szContractCode, 0, sizeof(TD_CodeType));
			nIndex = 0;
			nNum = 0;
		}
		virtual ~TD_ReqQryMatch()
		{

		}
	};

	///持仓查询请求
	struct TD_ReqQryPosition : TD_Base_Msg
	{
		/// 证券合约代码
		TD_CodeType     szContractCode;
		TD_ReqQryPosition()
		{
			memset(szContractCode, 0, sizeof(TD_CodeType));
		}
		virtual ~TD_ReqQryPosition()
		{

		}
	};

	///持仓查询回调
	struct TD_RspQryPosition : TD_Base_Msg
	{
		///  证券合约代码
		TD_CodeType     szContractCode;
		///  持仓总量
		int     nPosition;
		///  持仓均价 * 10000
		double      nPrice;
		///  浮盈
		double  nProfit;
		///  已结算的盈利
		double nSelltleProfit;
		TD_RspQryPosition()
		{
			memset(szContractCode, 0, sizeof(TD_CodeType));
			nPosition = 0;
			nPrice = 0;
			nProfit = 0;
			nSelltleProfit = 0;
		}
		virtual ~TD_RspQryPosition()
		{

		}
	};

	///最大可委托量查询请求
	struct TD_ReqQryMaxEntrustCount : TD_Base_Msg
	{
		/// 股票代码
		TD_CodeType szContractCode;
		TD_ReqQryMaxEntrustCount()
		{
			memset(szContractCode, 0, sizeof(TD_CodeType));
		}
		virtual ~TD_ReqQryMaxEntrustCount()
		{

		}
	};

	///资金账号最大可委托量查询请求
	struct TD_ReqQryAccountMaxEntrustCount : TD_Base_Msg
	{
		/// 股票代码
		TD_CodeType szContractCode;
		/// 资金账号
		int         nAccountId;

		TD_ReqQryAccountMaxEntrustCount()
		{
			memset(szContractCode, 0, sizeof(TD_CodeType));
			nAccountId = 0;
		}
		virtual ~TD_ReqQryAccountMaxEntrustCount()
		{

		}
	};

	///  可委托数量
	struct StockMaxEntrustCount
	{
		///  股票代码
		TD_CodeType szContractCode;
		///  最大可买资金量
		double nMaxBuyCaptial;
		///  最大可卖
		int nMaxSellVol;
		StockMaxEntrustCount()
		{
			memset(szContractCode, 0, sizeof(TD_CodeType));
			nMaxBuyCaptial = 0;
			nMaxSellVol = 0;
		}
		virtual ~StockMaxEntrustCount()
		{

		}
	};

	///  查询最大可委托数量回调
	struct TD_RspQryMaxEntrustCount : public TD_Base_Msg
	{
		StockMaxEntrustCount pStockMaxEntrustCount;
		TD_RspQryMaxEntrustCount()
		{

		}
		virtual ~TD_RspQryMaxEntrustCount()
		{

		}
	};
	///  资金账号信息初始值回调
	struct TD_RspQryInitAccountMaxEntrustCount : TD_Base_Msg
	{
		///  资金账号
		int nAccountId;
		///  资金账户别名
		TD_AccountType  szAccountNickName;
		///  可用股票数
		int nNum;
		///  指针偏移
		StockMaxEntrustCount* pStockMaxEntrustCount;
		///  资金通道是否可用
		bool bStatus;
		///  资金通道权限
		bool bPermission;
		///  资金账号层面可用资金
		int nAvailableCaptial;

		TD_RspQryInitAccountMaxEntrustCount()
		{
			memset(szAccountNickName, 0, sizeof(TD_AccountType));
			nAccountId = 0;
			nNum = 0;
			pStockMaxEntrustCount = NULL;
			bStatus = 0;
			nAvailableCaptial = 0;
			bPermission = true;
		}
		virtual ~TD_RspQryInitAccountMaxEntrustCount()
		{
			if (pStockMaxEntrustCount)
			{
				delete[] pStockMaxEntrustCount;
			}
		}
	};
	struct StockAccountMaxEntrustCount
	{
		///  证券合约代码
		TD_CodeType     szContractCode;
		///  持仓总量
		int     nTotalPosition;
		///  可卖量
		int     nAvailablePosition;
		///  资金账号层面当日初始持仓
		int     nLastPosition;

		StockAccountMaxEntrustCount()
		{
			memset(szContractCode, 0, sizeof(TD_CodeType));
			nTotalPosition = 0;
			nAvailablePosition = 0;
			nLastPosition = 0;
		}
		virtual ~StockAccountMaxEntrustCount()
		{

		}
	};

	///  资金账号最大可委托量回调
	struct TD_RspQryAccountMaxEntrustCount : TD_Base_Msg
	{
		///  资金账号
		int nAccountId;
		///  资金账户别名
		TD_AccountType  szAccountNickName;
		///  可用股票数
		int nNum;
		///  指针偏移
		StockAccountMaxEntrustCount* pStockMaxEntrustCount;
		///  资金通道是否可用
		bool bStatus;
		///  资金通道权限
		bool bPermission;
		///  资金账号层面可用资金
		int nAvailableCaptial;
		//   资金账号层面当日初始资金
		int nTotalCaptial;

		TD_RspQryAccountMaxEntrustCount()
		{
			memset(szAccountNickName, 0, sizeof(TD_AccountType));
			nAccountId = 0;
			nNum = 0;
			pStockMaxEntrustCount = NULL;
			bStatus = 0;
			nAvailableCaptial = 0;
			nTotalCaptial = 0;
			bPermission = true;
		}
		virtual ~TD_RspQryAccountMaxEntrustCount()
		{
			if(pStockMaxEntrustCount)
			{
				delete[] pStockMaxEntrustCount;
			}
		}
	};

	///订单状态变化通知
	typedef TD_RspOrderInsert TD_RtnOrderStatusChangeNotice;

	///成交回调通知
	struct TD_RtnOrderMatchNotice : TD_Base_Msg
	{
		/// 委托编号
		int64_t             nOrderId;
		///委托编号（broker 或交易所的唯一编号）
		TD_OrderIdType      szOrderStreamId;
		///系统编号
		int64_t             nMatchStreamId;
		///成交价 * 10000
		double              nMatchPrice;
		///成交量
		int                 nMatchVol;
		/// 股票代码
		TD_CodeType         szContractCode;
		///证券合约名称
		TD_CodeName     szContractName;
		/// 成交时间
		TD_ISODateTimeType  szMatchTime;
		///交易类型 买、卖
		TD_TradeType    nTradeType;
		///券商资金账户Id
		int             nAccountId;
		///资金账户别名
		TD_AccountType  szAccountNickName;


		TD_RtnOrderMatchNotice()
		{
			nOrderId = 0;
			nMatchStreamId = 0;
			nMatchPrice = 0;
			nMatchVol = 0;
			nTradeType = TD_TradeType_None;

			memset(szContractCode, 0, sizeof(TD_CodeType));
			memset(szMatchTime, 0, sizeof(TD_ISODateTimeType));
			memset(szOrderStreamId, 0, sizeof(TD_OrderIdType));
			memset(szContractName, 0, sizeof(szContractName));
			nAccountId = 0;
			memset(szAccountNickName, 0, sizeof(TD_AccountType));
		}
		virtual ~TD_RtnOrderMatchNotice()
		{

		}
	};

	///委托查询响应
	struct TD_RspQryOrder : public TD_RtnOrderStatusChangeNotice
	{
		int            nIndex;
		TD_RspQryOrder()
		{
			nIndex = 0;
		}
		~TD_RspQryOrder()
		{

		}
	};
	///成交查询响应
	struct TD_RspQryMatch : public TD_RtnOrderMatchNotice
	{
		int nIndex;
		TD_RspQryMatch()
		{
			nIndex = 0;
		}
		~TD_RspQryMatch()
		{

		}
	};
	///订单状态
	typedef TD_RtnOrderStatusChangeNotice TD_OrderStatus;
	///盈利推送参数
	typedef TD_RspQryPosition TD_RtnProfit;

	class TD_SimulationReservation
	{
	public:
		char               szWinCode[64];
		int                nLendingAmount;             // 底仓数量
		double             nPrice;                     // 底仓均价
	public:
		TD_SimulationReservation()
		{
			memset(szWinCode, 0, 64);
			nLendingAmount = 0;
			nPrice = 0;
		}
		virtual ~TD_SimulationReservation()
		{

		}
	};
	// 模拟资金账号信息
	class TD_SimulationAccount
	{
	public:
		int64_t               nSimAccountId;
		char                  szNickName[64];
		char                  szText[128];

		double                      nTotalAmount;
		int                         nReservationNum;   // 底仓股票数量
		TD_SimulationReservation*   pReservationCode;  // 底仓股票代码

	public:
		TD_SimulationAccount()
		{
			nSimAccountId = 0;
			memset(szNickName, 0, 64);
			memset(szText, 0, 128);

			nTotalAmount = 0;
			nReservationNum = 0;
			pReservationCode = NULL;
		}
		virtual ~TD_SimulationAccount()
		{
			if(pReservationCode != NULL)
			{
				delete[] pReservationCode;
				pReservationCode = NULL;
			}
		}
	};

	class TD_ReqUpdateAccountPermission : public TD_Base_Msg
	{
	public:
		int       nAccounid;
		bool      bEnable;
		TD_ReqUpdateAccountPermission()
		{
			nAccounid = 0;
			bEnable = 0;
		}
		~TD_ReqUpdateAccountPermission()
		{

		}
	};

	typedef TD_ReqUpdateAccountPermission TD_RspUpdateAccountPermission;
}



#endif//_QuantDef_H_
