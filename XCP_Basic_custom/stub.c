#include <Windows.h>
#include <stdio.h>

void _timeBeginPeriod(DWORD ms)
{
	timeBeginPeriod(ms);
}


void _Sleep(DWORD ms)
{
	Sleep(ms);
}

unsigned int _timeGetTime()
{
	return timeGetTime();
}

void* _CreateMutex(void* lpMutexAttributes, BOOL bInitialOwner,char* lpName)
{
	return CreateMutex( (LPSECURITY_ATTRIBUTES)lpMutexAttributes, bInitialOwner, lpName);
}

unsigned int _WaitForSigleObject(void* hHandle, unsigned int dwMilliseconds )
{
	return WaitForSingleObject( hHandle,dwMilliseconds);
}

int _ReleaseMutex( void* hMutex )
{
	return ReleaseMutex( hMutex );
}


void (*_pcallback)();

// �^�C���C�x���g�Ƃ��ČĂяo�����R�[���o�b�N�֐�
static void CALLBACK 
callback(unsigned int timerID, unsigned int msg, unsigned int usrParam, unsigned int dw1, unsigned int dw2) 
{
	_pcallback();
}

void setcallback( void (*pcallback)())
{
   unsigned int timer;

   _pcallback = pcallback;
   // �^�C���C�x���g�̊J�n
   timer = timeSetEvent(1, 0, (LPTIMECALLBACK) callback, (DWORD) NULL, TIME_PERIODIC);
   if(timer == 0) { printf("�^�C���C�x���g�̐����Ɏ��s\n"); exit(0); }

}