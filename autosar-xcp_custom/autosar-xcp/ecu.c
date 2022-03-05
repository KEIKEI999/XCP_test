#include "Std_Types.h"
#include <memory.h>
#include <stdio.h>


/*
 * 定数定義
 */
 /* PID制御パラメータ */
#define PID_FACTOR_D	(0.0F)
#define PID_FACTOR_P	(0.25F)
#define PID_FACTOR_I	(0.65F)


/* 上下限 */
#define PID_OUTPUT_MAX	(1.2F)
#define PID_OUTPUT_MIN	(-1.2F)


 /* PID制御管理情報 */
typedef struct {
	/* 開始状況 FALSE = 開始前、TRUE = 開始中 */
	int Start;

	/* 前回車速差 */
	float64 LastDiffSpeedValue;

	/* 前回車速差 */
	float64 LastAdd1Value;

	/* 前回計算結果 */
	float64 LastComputeValue;

} PID_CTRL_BLOCK;

/* 初期化状態, FALSE = 初期化前, TRUE = 初期化済み  */
static int sInit = FALSE;

/* PID制御管理ブロック */
static PID_CTRL_BLOCK sPidManageTbl;

/*
 * 初期化
 */
void PidControl_init(void)
{
	sInit = TRUE;
	memset(&sPidManageTbl, 0, sizeof(sPidManageTbl));
}

/*
 * 開始
 */
int PidControl_start(void)
{
	int Ret;

	Ret = -1;
	if (sInit == TRUE)
	{
		sPidManageTbl.Start = TRUE;
		Ret = 0;
	}
	else
	{
	}

	return Ret;
}

/*
 * 計算の実行
 * @param Auto, 自動制御モード, 1 = 有効, 0 = 無効
 * @param TargetSpeed, 目標角速度[100/256 rad/s]
 * @param InputSpeed, 実角速度[100/256 rad/s]
 * @param extOutput, 外部制御値(Auto=0 時に採用される値)
 * @param pOutput, [out]出力値
 * @param T1Value, 積分単位時間
 * @param TcValue, PID制御の実行周期時間（単位：ミリ秒）
 * @return 処理結果, 1 = 正常終了, -1 = エラー終了
 */
int PidControl_exec(int Auto, float64 TargetSpeed, float64 InputSpeed, float64 extOutput, float64* pOutput, float64 T1Value, float64 TcValue)
{
	int Ret;
	float64  DiffSpeedValue;
	float64  Add1Value;
	float64  T1TcValue;
	float64  TcT1Value;
	float64  OutputValue;

	Ret = -1;
	if ((sInit == TRUE) && (sPidManageTbl.Start == TRUE))
	{
		DiffSpeedValue = TargetSpeed - InputSpeed;

		T1TcValue = T1Value / TcValue;
		TcT1Value = TcValue / T1Value;
		Add1Value = (DiffSpeedValue - sPidManageTbl.LastDiffSpeedValue) * T1TcValue;

		if (Auto == TRUE)
		{
			OutputValue = ((Add1Value - sPidManageTbl.LastAdd1Value) *
				T1TcValue * PID_FACTOR_D +
				(PID_FACTOR_I * DiffSpeedValue + PID_FACTOR_P *
					Add1Value)) * TcT1Value +
				sPidManageTbl.LastComputeValue;
		}
		else
		{
			OutputValue = extOutput;
		}

		/*　出力リミット　*/
		if (OutputValue > PID_OUTPUT_MAX)
		{
			OutputValue = PID_OUTPUT_MAX;
		}
		else if (OutputValue < PID_OUTPUT_MIN)
		{
			OutputValue = PID_OUTPUT_MIN;
		}

		*pOutput = OutputValue;
		sPidManageTbl.LastDiffSpeedValue = DiffSpeedValue;
		sPidManageTbl.LastAdd1Value = Add1Value;
		sPidManageTbl.LastComputeValue = OutputValue;

		Ret = 0;
	}
	else
	{
	}

	return Ret;
}



void ecu_init() 
{
	PidControl_init();
	PidControl_start();
}

extern uint8_t g_XcpDebugMemory[1024];
sint32 *g_pwTarget = (sint32*)&g_XcpDebugMemory[0x200];	// LSB:1/65535.0[rad/s]
sint32 *g_pwInput = (sint32*)&g_XcpDebugMemory[0x204];	// LSB:1/65535.0[rad/s]
sint32 *g_pwOutput = (sint32*)&g_XcpDebugMemory[0x208];

#define NORMALIZE	100.0
#define LSB	(1/65535.0)

#define	T1	0.25
#define dT	0.001
void ecu_t1ms_job()
{
	float64 target = (*g_pwTarget) * LSB / NORMALIZE;
	float64 Input = (*g_pwInput)   * LSB / NORMALIZE;
	float64 Output;
	float64 Output_zi = (*g_pwOutput) * LSB / NORMALIZE;
	/*
	 * 計算の実行
	 * @param Auto, 自動制御モード, 1 = 有効, 0 = 無効
	 * @param TargetSpeed, 目標角速度[100/256 rad/s]
	 * @param InputSpeed, 実角速度[100/256 rad/s]
	 * @param extOutput, 外部制御値(Auto=0 時に採用される値)
	 * @param pOutput, [out]出力値
	 * @param T1Value, 積分単位時間
	 * @param TcValue, PID制御の実行周期時間（単位：ミリ秒）
	 * @return 処理結果, 1 = 正常終了, -1 = エラー終了
	 */
	PidControl_exec(
		1,
		target,
		Input,
		0,
		&Output,
		(float64)T1,
		(float64)dT
	);

	*g_pwOutput = (sint32)(Output * NORMALIZE / LSB);
}

void ecu_t10ms_job()
{

}

void ecu_t100ms_job()
{

}

void ecu_t200ms_job()
{

}

