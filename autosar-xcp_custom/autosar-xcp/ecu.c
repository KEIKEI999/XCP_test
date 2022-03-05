#include "Std_Types.h"
#include <memory.h>
#include <stdio.h>


/*
 * �萔��`
 */
 /* PID����p�����[�^ */
#define PID_FACTOR_D	(0.0F)
#define PID_FACTOR_P	(0.25F)
#define PID_FACTOR_I	(0.65F)


/* �㉺�� */
#define PID_OUTPUT_MAX	(1.2F)
#define PID_OUTPUT_MIN	(-1.2F)


 /* PID����Ǘ���� */
typedef struct {
	/* �J�n�� FALSE = �J�n�O�ATRUE = �J�n�� */
	int Start;

	/* �O��ԑ��� */
	float64 LastDiffSpeedValue;

	/* �O��ԑ��� */
	float64 LastAdd1Value;

	/* �O��v�Z���� */
	float64 LastComputeValue;

} PID_CTRL_BLOCK;

/* ���������, FALSE = �������O, TRUE = �������ς�  */
static int sInit = FALSE;

/* PID����Ǘ��u���b�N */
static PID_CTRL_BLOCK sPidManageTbl;

/*
 * ������
 */
void PidControl_init(void)
{
	sInit = TRUE;
	memset(&sPidManageTbl, 0, sizeof(sPidManageTbl));
}

/*
 * �J�n
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
 * �v�Z�̎��s
 * @param Auto, �������䃂�[�h, 1 = �L��, 0 = ����
 * @param TargetSpeed, �ڕW�p���x[100/256 rad/s]
 * @param InputSpeed, ���p���x[100/256 rad/s]
 * @param extOutput, �O������l(Auto=0 ���ɍ̗p�����l)
 * @param pOutput, [out]�o�͒l
 * @param T1Value, �ϕ��P�ʎ���
 * @param TcValue, PID����̎��s�������ԁi�P�ʁF�~���b�j
 * @return ��������, 1 = ����I��, -1 = �G���[�I��
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

		/*�@�o�̓��~�b�g�@*/
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
	 * �v�Z�̎��s
	 * @param Auto, �������䃂�[�h, 1 = �L��, 0 = ����
	 * @param TargetSpeed, �ڕW�p���x[100/256 rad/s]
	 * @param InputSpeed, ���p���x[100/256 rad/s]
	 * @param extOutput, �O������l(Auto=0 ���ɍ̗p�����l)
	 * @param pOutput, [out]�o�͒l
	 * @param T1Value, �ϕ��P�ʎ���
	 * @param TcValue, PID����̎��s�������ԁi�P�ʁF�~���b�j
	 * @return ��������, 1 = ����I��, -1 = �G���[�I��
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

