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

// タイムイベントとして呼び出されるコールバック関数
static void CALLBACK 
callback(unsigned int timerID, unsigned int msg, unsigned int usrParam, unsigned int dw1, unsigned int dw2) 
{
	_pcallback();
}

void setcallback( void (*pcallback)())
{
   unsigned int timer;

   _pcallback = pcallback;
   // タイムイベントの開始
   timer = timeSetEvent(1, 0, (LPTIMECALLBACK) callback, (DWORD) NULL, TIME_PERIODIC);
   if(timer == 0) { printf("タイムイベントの生成に失敗\n"); exit(0); }

}