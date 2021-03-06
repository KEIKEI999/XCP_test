/*
 *  TOPPERS ATK2
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 *      Automotive Kernel Version 2
 *
 *  Copyright (C) 2011-2015 by Center for Embedded Computing Systems
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2011-2015 by FUJI SOFT INCORPORATED, JAPAN
 *  Copyright (C) 2011-2013 by Spansion LLC, USA
 *  Copyright (C) 2011-2015 by NEC Communication Systems, Ltd., JAPAN
 *  Copyright (C) 2011-2015 by Panasonic Advanced Technology Development Co., Ltd., JAPAN
 *  Copyright (C) 2011-2014 by Renesas Electronics Corporation, JAPAN
 *  Copyright (C) 2011-2015 by Sunny Giken Inc., JAPAN
 *  Copyright (C) 2011-2015 by TOSHIBA CORPORATION, JAPAN
 *  Copyright (C) 2011-2015 by Witz Corporation
 *  Copyright (C) 2014-2015 by AISIN COMCRUISE Co., Ltd., JAPAN
 *  Copyright (C) 2014-2015 by eSOL Co.,Ltd., JAPAN
 *  Copyright (C) 2014-2015 by SCSK Corporation, JAPAN
 *
 *  上記著作権者は，以下の(1)～(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 *
 *  本ソフトウェアは，AUTOSAR（AUTomotive Open System ARchitecture）仕
 *  様に基づいている．上記の許諾は，AUTOSARの知的財産権を許諾するもので
 *  はない．AUTOSARは，AUTOSAR仕様に基づいたソフトウェアを商用目的で利
 *  用する者に対して，AUTOSARパートナーになることを求めている．
 *
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 *
 *  $Id: Os.h 187 2015-06-25 03:39:04Z t_ishikawa $
 */

/*
 *		ATK2 OSヘッダファイル
 *
 *  ATK2がサポートするシステムサービスの宣言と，必要なデー
 *  タ型，定数，マクロの定義を含むヘッダファイル
 *
 *  アセンブリ言語のソースファイルからこのファイルをインクルードする時
 *  は，TOPPERS_MACRO_ONLYを定義しておく
 *  これにより，マクロ定義以外を除くようになっている
 *
 *  このファイルをインクルードする前にインクルードしておくべきファイル
 *  はない
 */

#ifndef TOPPERS_OS_H
#define TOPPERS_OS_H

#ifdef TOPPERS_TRUSTED
#define TOPPERS_SVC_FUNCCALL
#endif

#if defined(TOPPERS_TRUSTED) && defined(TOPPERS_NON_TRUSTED)
#error "both TOPPERS_TRUSTED and TOPPERS_NON_TRUSTED are defined!"
#endif

/*
 *  共通のデータ型・定数・マクロ
 */
#include "Std_Types.h"
#include "MemMap.h"
#include "Rte_Os_Type.h"

#if !defined(TOPPERS_CFG1_OUT) && !defined(OMIT_INCLUDE_OS_CFG)
//#include "Os_Cfg.h"
#endif

/*
 *  ターゲット依存部
 */
//#include "target_kernel.h"

//#ifndef TOPPERS_MACRO_ONLY
#define	TOPPERS_OMIT_SYSLOG
/*
 *  データ型の定義
 */

/*
 *  オブジェクト番号の型定義
 */
typedef uint8	TaskStateType;                  /* タスク状態 */
typedef uint32	EventMaskType;                  /* イベントマスク */
typedef uint32	TickType;                       /* カウンタ値（ティック）*/
typedef uint32	AppModeType;                    /* アプリケーションモード */
typedef uint8	OSServiceIdType;                /* システムサービスID */
typedef uint8	ScheduleTableStatusType;        /* スケジュールテーブル状態 */
typedef uint8	ProtectionReturnType;           /* プロテクションフックからの返り値 */
typedef uintptr	MemorySizeType;                 /* メモリ領域サイズ */
typedef uint8	ApplicationType;                /* OSアプリケーションID */
typedef uint8	ObjectTypeType;                 /* OSオブジェクト種別 */
typedef uint8	ApplicationStateType;           /* OSアプリケーション状態 */
typedef uint8	AccessType;                     /* メモリ領域アクセス権 */
typedef boolean	ObjectAccessType;               /* OSオブジェクトアクセス権 */
typedef uint8	RestartType;                    /* OSAPリスタート属性 */

typedef struct {
	TickType	maxallowedvalue;                /* カウンタ指定の最大値 */
	TickType	ticksperbase;                   /* OSでは使用せず，ユーザが自由に使用する値 */
	TickType	mincycle;                       /* サイクル指定の最小値 */
} AlarmBaseType;

/*
 *  最適化するため，依存部再定義できる型
 */
#ifndef OMIT_DATA_TYPE
typedef uint32	TimeType;                       /* 時間 */
typedef uint32	AlarmType;                      /* アラームID */
typedef uint32	ResourceType;                   /* リソースID */
typedef uint32	TaskType;                       /* タスクID */
typedef uint32	ISRType;                        /* ISR ID */
typedef uint32	CounterType;                    /* カウンタID */
typedef uint32	ScheduleTableType;              /* スケジュールテーブルID */
typedef float32	PhysicalTimeType;               /* （ティックから時間に換算用）時間 */
typedef uint32	IocType;                        /* IOC ID */
typedef uint8	SenderIdType;                   /* Sender ID */
typedef uint32	TrustedFunctionIndexType;       /* Trusted Function Index */
#endif /* OMIT_DATA_TYPE */

typedef AlarmBaseType *				AlarmBaseRefType;
typedef TaskType *					TaskRefType;
typedef TaskStateType *				TaskStateRefType;
typedef EventMaskType *				EventMaskRefType;
typedef TickType *					TickRefType;
typedef ScheduleTableStatusType *	ScheduleTableStatusRefType;
typedef ApplicationStateType *		ApplicationStateRefType;
typedef void *						MemoryStartAddressType;             /* メモリ領域先頭 */
typedef void *						TrustedFunctionParameterRefType;    /* Trusted Function Parameter */

/*
 *  保護違反を起こした処理単位の型
 */
typedef uint8 FaultyContextType;

/*
 *  OSオブジェクト宣言用のマクロ
 */
#define DeclareTask(TaskIdentifier)
#define DeclareResource(ResourceIdentifier)
#define DeclareEvent(EventIdentifier)
#define DeclareAlarm(AlarmIdentifier)

/*
 *  メインルーチン定義用のマクロ
 */
#define TASK(TaskName)		void TaskMain ## TaskName(void)
#define ISR(ISRName)		void ISRMain ## ISRName(void)
#ifndef C1ISR
#define C1ISR(ISRName)	void C1ISRMain ## ISRName(void)
#endif /* C1ISR */

#define TRUSTEDFUNCTION(TrustedFunctionName, FunctionIndex, FunctionParams)	\
	StatusType TrustedFunctionName(											\
		TrustedFunctionIndexType FunctionIndex,								\
		TrustedFunctionParameterRefType FunctionParams						\
		)

/*
 *  メモリ領域確保のための型定義
 */
#ifndef TOPPERS_STK_T
#define TOPPERS_STK_T	sintptr
#endif /* TOPPERS_STK_T */
typedef	TOPPERS_STK_T StackType;    /* スタック領域を確保するための型 */

/*
 *  システムサービスパラメータ取得のための定義
 */
typedef union {
	TaskType						tskid;
	TaskRefType						p_tskid;
	TaskStateRefType				p_stat;
	ResourceType					resid;
	EventMaskType					mask;
	EventMaskRefType				p_mask;
	AlarmType						almid;
	AlarmBaseRefType				p_info;
	TickRefType						p_tick;
	TickRefType						p_val;
	TickRefType						p_eval;
	TickType						incr;
	TickType						cycle;
	TickType						start;
	AppModeType						mode;
	CounterType						cntid;
	ScheduleTableType				schtblid;
	TickType						offset;
	ScheduleTableType				schtblid_from;
	ScheduleTableType				schtblid_to;
	ScheduleTableStatusRefType		p_schtblstate;
	StatusType						error;
	ISRType							isrid;
	IocType							iocid;
	SenderIdType					senderid;
	TrustedFunctionIndexType		tfnid;
	TrustedFunctionParameterRefType	tfnpr;
	MemoryStartAddressType			adr;
	MemorySizeType					sz;
	ApplicationType					applid;
	ApplicationStateRefType			p_appstat;
	RestartType						restartoption;
} _ErrorHook_Par;


/*
 *  メモリ領域確保のためのマクロ
 *
 *  以下のTOPPERS_COUNT_SZとTOPPERS_ROUND_SZの定義は，unitが2の巾乗であ
 *  ることを仮定している．
 */
#ifndef TOPPERS_COUNT_SZ
#define TOPPERS_COUNT_SZ(sz, unit)	(((sz) + (unit) - (1U)) / (unit))
#endif /* TOPPERS_COUNT_SZ */
#ifndef TOPPERS_ROUND_SZ
#define TOPPERS_ROUND_SZ(sz, unit)	(((sz) + (unit) - (1U)) & (~((unit) - (1U))))
#endif /* TOPPERS_ROUND_SZ */

#define COUNT_STK_T(sz)		(TOPPERS_COUNT_SZ((sz), sizeof(StackType)))
#define ROUND_STK_T(sz)		(TOPPERS_ROUND_SZ((sz), sizeof(StackType)))

/*
 *  フックルーチン
 */
#ifdef CFG_USE_SYSTEM_ERRORHOOK
extern void ErrorHook(StatusType Error);
#endif /* CFG_USE_SYSTEM_ERRORHOOK */

#ifdef CFG_USE_PRETASKHOOK
extern void PreTaskHook(void);
#endif /* CFG_USE_PRETASKHOOK */

#ifdef CFG_USE_POSTTASKHOOK
extern void PostTaskHook(void);
#endif /* CFG_USE_POSTTASKHOOK */

#ifdef CFG_USE_SYSTEM_STARTUPHOOK
extern void StartupHook(void);
#endif /* CFG_USE_SYSTEM_STARTUPHOOK */

#ifdef CFG_USE_SYSTEM_SHUTDOWNHOOK
extern void ShutdownHook(StatusType Error);
#endif /* CFG_USE_SYSTEM_SHUTDOWNHOOK */

#ifdef CFG_USE_PROTECTIONHOOK
extern ProtectionReturnType ProtectionHook(StatusType FatalError);
#endif /* CFG_USE_PROTECTIONHOOK */

/*
 *  ライブラリで提供するシステムサービス
 */
extern ObjectAccessType CheckObjectAccess(ApplicationType ApplID, ObjectTypeType ObjectType, ...);
extern ApplicationType CheckObjectOwnership(ObjectTypeType ObjectType, ...);

/*
 *  ファイル名，行番号の参照用の変数
 */
extern const char8	*fatal_file_name;   /* ファイル名 */
extern sint32		fatal_line_num;     /* 行番号 */

//#endif /* TOPPERS_MACRO_ONLY */

/*
 *  システムサービス呼出しのための定義と宣言
 */
//#include "kernel_fncode.h"              /* 機能コードの定義 */
//#include "svc_funccall.h"               /* 関数呼出しによる呼出し */
//#include "target_svc.h"                 /* ソフトウェア割込みによる呼出し */

#if !defined(TOPPERS_CFG1_OUT) && !defined(OMIT_INCLUDE_OS_CFG) && !defined(OMIT_INCLUDE_OS_LCFG)
//#include "Os_Lcfg.h"
#endif

/*
 *  OSのエラーコード
 */
#define E_OS_ACCESS							UINT_C(1)
#define E_OS_CALLEVEL						UINT_C(2)
#define E_OS_ID								UINT_C(3)
#define E_OS_LIMIT							UINT_C(4)
#define E_OS_NOFUNC							UINT_C(5)
#define E_OS_RESOURCE						UINT_C(6)
#define E_OS_STATE							UINT_C(7)
#define E_OS_VALUE							UINT_C(8)
#define E_OS_SERVICEID						UINT_C(9)
#define E_OS_ILLEGAL_ADDRESS				UINT_C(10)
#define E_OS_MISSINGEND						UINT_C(11)
#define E_OS_DISABLEDINT					UINT_C(12)
#define E_OS_STACKFAULT						UINT_C(13)
#define E_OS_PROTECTION_MEMORY				UINT_C(14)
#define E_OS_PROTECTION_TIME_TASK			UINT_C(15)
#define E_OS_PROTECTION_TIME_ISR			UINT_C(16)
#define E_OS_PROTECTION_ARRIVAL_TASK		UINT_C(17)
#define E_OS_PROTECTION_ARRIVAL_ISR			UINT_C(18)
#define E_OS_PROTECTION_LOCKED_RESOURCE		UINT_C(19)
#define E_OS_PROTECTION_LOCKED_OSINT		UINT_C(20)
#define E_OS_PROTECTION_LOCKED_ALLINT		UINT_C(21)
#define E_OS_PROTECTION_EXCEPTION			UINT_C(22)
#define E_OS_PROTECTION_FATAL				UINT_C(23)
#define E_OS_MODE							UINT_C(24)
#define E_OS_SHUTDOWN_FATAL					UINT_C(25)
#define E_OS_PARAM_POINTER					UINT_C(26)
#define E_OS_SYS_ASSERT_FATAL				UINT_C(27)
#define E_OS_STACKINSUFFICIENT				UINT_C(28)

/* AUTOSAR仕様R4.0.3との互換性考慮 */
#define OS_E_PARAM_POINTER					E_OS_PARAM_POINTER

#define ERRCODE_NUM							UINT_C(28) /* エラーコード数 */
/*
 *  IOCのエラーコード
 */
#define IOC_E_OK			UINT_C(0)
#define IOC_E_NOK			UINT_C(1)
#define IOC_E_LIMIT			UINT_C(130)
#define IOC_E_LOST_DATA		UINT_C(64)
#define IOC_E_NO_DATA		UINT_C(131)

/*
 *  その他の定数値
 */
#define UINT32_INVALID		UINT_C(0xffffffff)
#define UINT8_INVALID		UINT_C(0xff)

#define SUSPENDED			((TaskStateType) 0) /* 休止状態 */
#define RUNNING				((TaskStateType) 1) /* 実行状態 */
#define READY				((TaskStateType) 2) /* 実行可能状態 */
#define WAITING				((TaskStateType) 3) /* 待ち状態 */

/*
 *  最適化するため，依存部での再定義が必要
 */
#ifndef OMIT_DATA_TYPE
#define INVALID_TASK			((TaskType) UINT32_INVALID)
#define INVALID_ISR				((ISRType) UINT32_INVALID)
#endif /* OMIT_DATA_TYPE */
#define INVALID_APPMODETYPE		((AppModeType) UINT32_INVALID)
#define INVALID_OSAPPLICATION	((ApplicationType) UINT8_INVALID)

/*
 *  スケジュールテーブルのステータス定義
 */
#define SCHEDULETABLE_STOPPED					((ScheduleTableStatusType) 0x01)
#define SCHEDULETABLE_NEXT						((ScheduleTableStatusType) 0x02)
#define SCHEDULETABLE_WAITING					((ScheduleTableStatusType) 0x04)
#define SCHEDULETABLE_RUNNING					((ScheduleTableStatusType) 0x08)
#define SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS	((ScheduleTableStatusType) 0x10)

/*
 *  OSアプリケーションの状態
 */
#define APPLICATION_ACCESSIBLE	((ApplicationStateType) 0)  /* 利用可能状態 */
#define APPLICATION_RESTARTING	((ApplicationStateType) 1)  /* 再起動状態 */
#define APPLICATION_TERMINATED	((ApplicationStateType) 2)  /* アプリケーション終了状態 */

/*
 *  アクセス情報
 */
#define ACCESS		(TRUE)
#define NO_ACCESS	(FALSE)

/*
 *  システムサービスID
 */
#define OSServiceId_GetApplicationID			((OSServiceIdType) 0x00)
#define OSServiceId_GetISRID					((OSServiceIdType) 0x01)
#define OSServiceId_CallTrustedFunction			((OSServiceIdType) 0x02)
#define OSServiceId_CheckISRMemoryAccess		((OSServiceIdType) 0x03)
#define OSServiceId_CheckTaskMemoryAccess		((OSServiceIdType) 0x04)
#define OSServiceId_StartScheduleTableRel		((OSServiceIdType) 0x07)
#define OSServiceId_StartScheduleTableAbs		((OSServiceIdType) 0x08)
#define OSServiceId_StopScheduleTable			((OSServiceIdType) 0x09)
#define OSServiceId_NextScheduleTable			((OSServiceIdType) 0x0a)
#define OSServiceId_GetScheduleTableStatus		((OSServiceIdType) 0x0e)
#define OSServiceId_IncrementCounter			((OSServiceIdType) 0x0f)
#define OSServiceId_GetCounterValue				((OSServiceIdType) 0x10)
#define OSServiceId_GetElapsedValue				((OSServiceIdType) 0x11)
#define OSServiceId_TerminateApplication		((OSServiceIdType) 0x12)
#define OSServiceId_AllowAccess					((OSServiceIdType) 0x13)
#define OSServiceId_GetApplicationState			((OSServiceIdType) 0x14)
#define IOCServiceId_IOC_Send					((OSServiceIdType) 0x1e)
#define IOCServiceId_IOC_Write					((OSServiceIdType) 0x1f)
#define IOCServiceId_IOC_SendGroup				((OSServiceIdType) 0x20)
#define IOCServiceId_IOC_WriteGroup				((OSServiceIdType) 0x21)
#define IOCServiceId_IOC_Receive				((OSServiceIdType) 0x22)
#define IOCServiceId_IOC_Read					((OSServiceIdType) 0x23)
#define IOCServiceId_IOC_ReceiveGroup			((OSServiceIdType) 0x24)
#define IOCServiceId_IOC_ReadGroup				((OSServiceIdType) 0x25)
#define IOCServiceId_IOC_EmptyQueue				((OSServiceIdType) 0x26)

#define OSServiceId_EnableInterruptSource		((OSServiceIdType) 0xa0)
#define OSServiceId_DisableInterruptSource		((OSServiceIdType) 0xa1)
#define OSServiceId_CheckTaskAccess				((OSServiceIdType) 0xa2)
#define OSServiceId_CheckISRAccess				((OSServiceIdType) 0xa3)
#define OSServiceId_CheckAlarmAccess			((OSServiceIdType) 0xa4)
#define OSServiceId_CheckResourceAccess			((OSServiceIdType) 0xa5)
#define OSServiceId_CheckCounterAccess			((OSServiceIdType) 0xa6)
#define OSServiceId_CheckScheduleTableAccess	((OSServiceIdType) 0xa7)
#define OSServiceId_CheckTaskOwnership			((OSServiceIdType) 0xa9)
#define OSServiceId_CheckISROwnership			((OSServiceIdType) 0xaa)
#define OSServiceId_CheckAlarmOwnership			((OSServiceIdType) 0xab)
#define OSServiceId_CheckCounterOwnership		((OSServiceIdType) 0xac)
#define OSServiceId_CheckScheduleTableOwnership	((OSServiceIdType) 0xad)
#define OSServiceId_TaskMissingEnd				((OSServiceIdType) 0xaf)
#define OSServiceId_ISRMissingEnd				((OSServiceIdType) 0xb0)
#define OSServiceId_HookMissingEnd				((OSServiceIdType) 0xb1)

#define OSServiceId_ActivateTask				((OSServiceIdType) 0xe0)
#define OSServiceId_TerminateTask				((OSServiceIdType) 0xe1)
#define OSServiceId_ChainTask					((OSServiceIdType) 0xe2)
#define OSServiceId_Schedule					((OSServiceIdType) 0xe3)
#define OSServiceId_GetTaskID					((OSServiceIdType) 0xe4)
#define OSServiceId_GetTaskState				((OSServiceIdType) 0xe5)
#define OSServiceId_EnableAllInterrupts			((OSServiceIdType) 0xe6)
#define OSServiceId_DisableAllInterrupts		((OSServiceIdType) 0xe7)
#define OSServiceId_ResumeAllInterrupts			((OSServiceIdType) 0xe8)
#define OSServiceId_SuspendAllInterrupts		((OSServiceIdType) 0xe9)
#define OSServiceId_ResumeOSInterrupts			((OSServiceIdType) 0xea)
#define OSServiceId_SuspendOSInterrupts			((OSServiceIdType) 0xeb)
#define OSServiceId_GetResource					((OSServiceIdType) 0xec)
#define OSServiceId_ReleaseResource				((OSServiceIdType) 0xed)
#define OSServiceId_SetEvent					((OSServiceIdType) 0xee)
#define OSServiceId_ClearEvent					((OSServiceIdType) 0xef)
#define OSServiceId_GetEvent					((OSServiceIdType) 0xf0)
#define OSServiceId_WaitEvent					((OSServiceIdType) 0xf1)
#define OSServiceId_GetAlarmBase				((OSServiceIdType) 0xf2)
#define OSServiceId_GetAlarm					((OSServiceIdType) 0xf3)
#define OSServiceId_SetRelAlarm					((OSServiceIdType) 0xf4)
#define OSServiceId_SetAbsAlarm					((OSServiceIdType) 0xf5)
#define OSServiceId_CancelAlarm					((OSServiceIdType) 0xf6)
#define OSServiceId_GetActiveApplicationMode	((OSServiceIdType) 0xf7)
#define OSServiceId_StartOS						((OSServiceIdType) 0xf8)
#define OSServiceId_ShutdownOS					((OSServiceIdType) 0xf9)

#define OSServiceId_INVALID						((OSServiceIdType) 0xff)  /* 無効なシステムサービスID */

/*
 *  保護違反を起こした処理単位の定義
 */
#define FC_INVALID			UINT_C(0x00)        /* 保護違反を起こした処理単位が特定できない */
#define FC_TASK				UINT_C(0x01)        /* 保護違反を起こした処理単位がタスク */
#define FC_C2ISR			UINT_C(0x02)        /* 保護違反を起こした処理単位がC2ISR */
#define FC_SYSTEM_HOOK		UINT_C(0x03)        /* 保護違反を起こした処理単位がシステム定義のフック */
#define FC_OSAP_HOOK		UINT_C(0x04)        /* 保護違反を起こした処理単位がOSAP固有のフック */
#define FC_TRUSTED_FUNC		UINT_C(0x05)        /* 保護違反を起こした処理単位が信頼関数 */

/*
 *  システムサービスパラメータ取得のための定義
 */
#ifndef TOPPERS_MACRO_ONLY

/*
 *  エラーフックOFF時，サービスID取得とパラメータ取得もOFFになる
 */
#ifdef CFG_USE_ERRORHOOK

#ifdef CFG_USE_GETSERVICEID
extern OSServiceIdType	_errorhook_svcid;
#endif /* CFG_USE_GETSERVICEID */

#ifdef CFG_USE_PARAMETERACCESS
extern _ErrorHook_Par	errorhook_par1;
extern _ErrorHook_Par	errorhook_par2;
extern _ErrorHook_Par	errorhook_par3;
#endif /* CFG_USE_PARAMETERACCESS */

#endif /* CFG_USE_ERRORHOOK */

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  エラーフックOFF時，サービスID取得とパラメータ取得もOFFになる
 */
#ifdef CFG_USE_ERRORHOOK

/*
 *  マクロの定義
 */
#ifdef CFG_USE_GETSERVICEID
#define OSErrorGetServiceId()				(_errorhook_svcid)
#endif /* CFG_USE_GETSERVICEID */

/*
 *  エラーを引き起こしたシステムサービスID
 */
#ifdef CFG_USE_PARAMETERACCESS
#define OSError_StartOS_Mode()									(errorhook_par1.mode)
#define OSError_ActivateTask_TaskID()							(errorhook_par1.tskid)
#define OSError_ChainTask_TaskID()								(errorhook_par1.tskid)
#define OSError_GetTaskID_TaskID()								(errorhook_par1.p_tskid)
#define OSError_GetTaskState_TaskID()							(errorhook_par1.tskid)
#define OSError_GetTaskState_State()							(errorhook_par2.p_stat)
#define OSError_GetResource_ResID()								(errorhook_par1.resid)
#define OSError_ReleaseResource_ResID()							(errorhook_par1.resid)
#define OSError_SetEvent_TaskID()								(errorhook_par1.tskid)
#define OSError_SetEvent_Mask()									(errorhook_par2.mask)
#define OSError_ClearEvent_Mask()								(errorhook_par1.mask)
#define OSError_GetEvent_TaskID()								(errorhook_par1.tskid)
#define OSError_GetEvent_Event()								(errorhook_par2.p_mask)
#define OSError_WaitEvent_Mask()								(errorhook_par1.mask)
#define OSError_GetAlarmBase_AlarmID()							(errorhook_par1.almid)
#define OSError_GetAlarmBase_Info()								(errorhook_par2.p_info)
#define OSError_GetAlarm_AlarmID()								(errorhook_par1.almid)
#define OSError_GetAlarm_Tick()									(errorhook_par2.p_tick)
#define OSError_SetRelAlarm_AlarmID()							(errorhook_par1.almid)
#define OSError_SetRelAlarm_increment()							(errorhook_par2.incr)
#define OSError_SetRelAlarm_cycle()								(errorhook_par3.cycle)
#define OSError_SetAbsAlarm_AlarmID()							(errorhook_par1.almid)
#define OSError_SetAbsAlarm_start()								(errorhook_par2.start)
#define OSError_SetAbsAlarm_cycle()								(errorhook_par3.cycle)
#define OSError_CancelAlarm_AlarmID()							(errorhook_par1.almid)
#define OSError_IncrementCounter_CounterID()					(errorhook_par1.cntid)
#define OSError_GetCounterValue_CounterID()						(errorhook_par1.cntid)
#define OSError_GetCounterValue_Value()							(errorhook_par2.p_val)
#define OSError_GetElapsedValue_CounterID()						(errorhook_par1.cntid)
#define OSError_GetElapsedValue_Value()							(errorhook_par2.p_val)
#define OSError_GetElapsedValue_ElapsedValue()					(errorhook_par3.p_eval)
#define OSError_StartScheduleTableRel_ScheduleTableID()			(errorhook_par1.schtblid)
#define OSError_StartScheduleTableRel_Offset()					(errorhook_par2.offset)
#define OSError_StartScheduleTableAbs_ScheduleTableID()			(errorhook_par1.schtblid)
#define OSError_StartScheduleTableAbs_Start()					(errorhook_par2.start)
#define OSError_StopScheduleTable_ScheduleTableID()				(errorhook_par1.schtblid)
#define OSError_NextScheduleTable_ScheduleTableID_From()		(errorhook_par1.schtblid_from)
#define OSError_NextScheduleTable_ScheduleTableID_To()			(errorhook_par2.schtblid_to)
#define OSError_GetScheduleTableStatus_ScheduleTableID()		(errorhook_par1.schtblid)
#define OSError_GetScheduleTableStatus_ScheduleStatus()			(errorhook_par2.p_schtblstate)
#define OSError_ShutdownOS_Error()								(errorhook_par1.error)
#define OSError_DisableInterruptSource_DisableISR()				(errorhook_par1.isrid)
#define OSError_EnableInterruptSource_EnableISR()				(errorhook_par1.isrid)
#define OSError_GetApplicationState_Application()				(errorhook_par1.applid)
#define OSError_GetApplicationState_Value()						(errorhook_par2.p_appstat)
#define OSError_CallTrustedFunction_FunctionIndex()				(errorhook_par1.tfnid)
#define OSError_CallTrustedFunction_FunctionParams()			(errorhook_par2.tfnpr)
#define OSError_CheckISRMemoryAccess_ISRID()					(errorhook_par1.isrid)
#define OSError_CheckISRMemoryAccess_Address()					(errorhook_par2.adr)
#define OSError_CheckISRMemoryAccess_Size()						(errorhook_par3.sz)
#define OSError_CheckTaskMemoryAccess_TaskID()					(errorhook_par1.tskid)
#define OSError_CheckTaskMemoryAccess_Address()					(errorhook_par2.adr)
#define OSError_CheckTaskMemoryAccess_Size()					(errorhook_par3.sz)
#define OSError_CheckTaskAccess_ApplID()						(errorhook_par1.applid)
#define OSError_CheckTaskAccess_TaskID()						(errorhook_par2.tskid)
#define OSError_CheckISRAccess_ApplID()							(errorhook_par1.applid)
#define OSError_CheckISRAccess_ISRID()							(errorhook_par2.isrid)
#define OSError_CheckAlarmAccess_ApplID()						(errorhook_par1.applid)
#define OSError_CheckAlarmAccess_AlarmID()						(errorhook_par2.almid)
#define OSError_CheckResourceAccess_ApplID()					(errorhook_par1.applid)
#define OSError_CheckResourceAccess_ResID()						(errorhook_par2.resid)
#define OSError_CheckCounterAccess_ApplID()						(errorhook_par1.applid)
#define OSError_CheckCounterAccess_CounterID()					(errorhook_par2.cntid)
#define OSError_CheckScheduleTableAccess_ApplID()				(errorhook_par1.applid)
#define OSError_CheckScheduleTableAccess_ScheduleTableID()		(errorhook_par2.schtblid)
#define OSError_CheckTaskOwnership_TaskID()						(errorhook_par1.tskid)
#define OSError_CheckISROwnership_ISRID()						(errorhook_par1.isrid)
#define OSError_CheckAlarmOwnership_AlarmID()					(errorhook_par1.almid)
#define OSError_CheckCounterOwnership_CounterID()				(errorhook_par1.cntid)
#define OSError_CheckScheduleTableOwnership_ScheduleTableID()	(errorhook_par1.schtblid)
#define OSError_IocSend_IocId()									(errorhook_par1.iocid)
#define OSError_IocSend_SenderId()								(errorhook_par2.senderid)
#define OSError_IocWrite_IocId()								(errorhook_par1.iocid)
#define OSError_IocWrite_SenderId()								(errorhook_par2.senderid)
#define OSError_IocReceive_IocId()								(errorhook_par1.iocid)
#define OSError_IocRead_IocId()									(errorhook_par1.iocid)
#define OSError_IocEmptyQueue_IocId()							(errorhook_par1.iocid)
#define OSError_TerminateApplication_Application()				(errorhook_par1.applid)
#define OSError_TerminateApplication_RestartOption()			(errorhook_par2.restartoption)

#endif /* CFG_USE_PARAMETERACCESS */

#endif /* CFG_USE_ERRORHOOK */

/*
 *  プロテクションフック関係のマクロ
 */
#define PRO_IGNORE					UINT_C(0x00)
#define PRO_SHUTDOWN				UINT_C(0x01)
#define PRO_TERMINATETASKISR		UINT_C(0x02)
#define PRO_TERMINATEAPPL			UINT_C(0x03)
#define PRO_TERMINATEAPPL_RESTART	UINT_C(0x04)

/*
 *  OSAP終了/再起動関係のマクロ
 */
#define NO_RESTART					UINT_C(0x00)
#define RESTART						UINT_C(0x01)

/*
 *  メモリアクセス権限チェックのためのマクロ
 */

/*
 *  メモリ領域 権限
 */

#define AP_NoAccess		UINT_C(0x0)
#define AP_Executable	UINT_C(0x1)
#define AP_Readable		UINT_C(0x2)
#define AP_Writable		UINT_C(0x4)
#define AP_StackSpace	UINT_C(0x8)

/*
 *  アクセスチェックマクロ
 */
#define OSMEMORY_IS_READABLE(AccessType)	((AccessType) & AP_Readable)
#define OSMEMORY_IS_WRITEABLE(AccessType)	((AccessType) & AP_Writable)
#define OSMEMORY_IS_EXECUTABLE(AccessType)	((AccessType) & AP_Executable)
#define OSMEMORY_IS_STACKSPACE(AccessType)	((AccessType) & AP_StackSpace)

/*
 *   オブジェクトタイプ
 */
#define OBJECT_TASK				UINT_C(0x01)
#define OBJECT_ISR				UINT_C(0x02)
#define OBJECT_ALARM			UINT_C(0x03)
#define OBJECT_RESOURCE			UINT_C(0x04)
#define OBJECT_COUNTER			UINT_C(0x05)
#define OBJECT_SCHEDULETABLE	UINT_C(0x06)

/*
 *  バージョン情報
 */
#define OS_SW_MAJOR_VERSION				UINT_C(1)   /* サプライヤーバージョン */
#define OS_SW_MINOR_VERSION				UINT_C(3)
#define OS_SW_PATCH_VERSION				UINT_C(2)

#define OS_AR_RELEASE_MAJOR_VERSION		UINT_C(4)   /* AUTOSARリリースバージョン */
#define OS_AR_RELEASE_MINOR_VERSION		UINT_C(0)
#define OS_AR_RELEASE_REVISION_VERSION	UINT_C(3)

#define TKERNEL_NAME	"TOPPERS/ATK2-SC3"  /* カーネル名称（独自仕様） */

#endif /* TOPPERS_OS_H */
