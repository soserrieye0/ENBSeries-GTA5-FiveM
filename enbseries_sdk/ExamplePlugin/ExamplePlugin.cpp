//Example dll plugin for ENBSeries
//author: Boris Vorontsov
//Library is linked in DllMain calls, but it's bad practice because ENBSeries may not be available yet
#include <windows.h>
#include <psapi.h>
#pragma comment(lib, "psapi.lib")
#include "..\enbseries.h"

//for checking compatibility with sdk
#define EXAMPLE_VERSION		1000

char	ENBDllName1[]="d3d11.dll"; //wrapper version
char	ENBDllName2[]="enbseries.dll"; //injector version
//char	ENBDllName3[]="d3d9.dll";


_ENBGetSDKVersion			enbGetSDKVersion=NULL;
_ENBGetVersion				enbGetVersion=NULL;
_ENBGetGameIdentifier		enbGetGameIdentifier=NULL;
_ENBSetCallbackFunction		enbSetCallbackFunction=NULL;
_ENBGetParameter			enbGetParameter=NULL;
_ENBSetParameter			enbSetParameter=NULL;
void WINAPI					CallbackFunction(ENBCallbackType calltype);



BOOL	IsLoaded=FALSE; //if successfully attached to ENBSeries

BOOL	OldState_UseEffect=FALSE;
float	OldState_CC_Gamma=1.0f;

void	LinkFunctions();

void	SaveParameters();
void	RestoreParameters();
void	ExecuteSomething();

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
BOOL WINAPI	DllMain(HINSTANCE hinstDLL, DWORD fdwReason, void *lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hinstDLL);

		//attach functions to ENBSeries
		if (IsLoaded==FALSE)
		{
			LinkFunctions();
		}

		return TRUE;
	}

	if (fdwReason == DLL_PROCESS_DETACH)
	{
		return TRUE;
	}
    return FALSE;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Get ENBSeries dll and attach all function to it
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void	LinkFunctions()
{
	IsLoaded=FALSE;

	DWORD	cb=1000*sizeof(HMODULE);
	DWORD	cbNeeded=0;
	HMODULE	enbmodule=NULL;
	HMODULE	hmodules[1000];
	HANDLE	hproc=GetCurrentProcess();
	for (long i=0; i<1000; i++) hmodules[i]=NULL;
	//find proper library by existance of exported function, because several with the same name may exist
	if (EnumProcessModules(hproc, hmodules, cb, &cbNeeded))
	{
		long	count=cbNeeded/sizeof(HMODULE);
		for (long i=0; i<count; i++)
		{
			if (hmodules[i]==NULL) break;
			void	*func=(void*)GetProcAddress(hmodules[i], "ENBGetSDKVersion");
			if (func)
			{
				enbmodule=hmodules[i];
				break;
			}
		}
	}

	if (!enbmodule) return;

	//actually link functions
	enbGetSDKVersion=(_ENBGetSDKVersion)GetProcAddress(enbmodule, "ENBGetSDKVersion");
	enbGetVersion=(_ENBGetVersion)GetProcAddress(enbmodule, "ENBGetVersion");
	enbGetGameIdentifier=(_ENBGetGameIdentifier)GetProcAddress(enbmodule, "ENBGetGameIdentifier");
	enbSetCallbackFunction=(_ENBSetCallbackFunction)GetProcAddress(enbmodule, "ENBSetCallbackFunction");
	enbGetParameter=(_ENBGetParameter)GetProcAddress(enbmodule, "ENBGetParameter");
	enbSetParameter=(_ENBSetParameter)GetProcAddress(enbmodule, "ENBSetParameter");

	//check if all functions are linked
	if (
		   (!enbGetSDKVersion)
		|| (!enbGetVersion)
		|| (!enbGetGameIdentifier)
		|| (!enbSetCallbackFunction)
		|| (!enbGetParameter)
		|| (!enbSetParameter)
		)
	{
		return;
	}

	long	sdkversion=enbGetSDKVersion();
	//check compatibility, for example 1025 is guaranteed compatible with 1000..1999 (though new functions may exist)
	if ((sdkversion/1000) != (EXAMPLE_VERSION/1000))
	{
		return;
	}

	//assign callback
	enbSetCallbackFunction(CallbackFunction);

	//set flag that everything initialized properly
	IsLoaded=TRUE;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Called by ENBSeries. Please do not read or set parameters outside of it
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void WINAPI	CallbackFunction(ENBCallbackType calltype)
{
	if (IsLoaded==FALSE) return;

	if (calltype == ENBCallback_PostLoad)
	{
		//TODO you need to save original values to restore them later
		SaveParameters();
	}

	if (calltype == ENBCallback_PreSave)
	{
		//TODO you need to restore original values, if modified by ENBSetParameter function (otherwise this plugin changes will be saved to configs)
		RestoreParameters();
	}

	//in this example just ignore everything, except end frame callback
	if (calltype == ENBCallback_EndFrame)
	{
		//TODO your code here for processing parameters
		ExecuteSomething();
	}

}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Warning! Any values set here will be saved if pressing "Save Config" button of the mod
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
DWORD	callcounter=0;
void	ExecuteSomething()
{
	if (IsLoaded==FALSE) return;

	//do whatever you want here with config or shader parameters of ENBSeries
	BOOL	res;
	ENBParameter	param;

	//just count frames and toggle mod on/off ever 20 frames
	callcounter++;
	if (callcounter>=20) callcounter=0;
	if (callcounter==0)
	{
		BOOL	bvalue=FALSE;
		//read parameter
		res=enbGetParameter("enbseries.ini", "GLOBAL", "UseEffect", &param);
		if (res==FALSE)
		{
			//this means some of arguments are invalid, parameter not exist, parameter hidden
		} else
		{
			bvalue=FALSE;
			if (param.Type==ENBParam_BOOL) memcpy(&bvalue, param.Data, 4);//param.Size
			if (bvalue==FALSE) bvalue=TRUE; else bvalue=FALSE;
		}

		//set parameter
		param.Type=ENBParam_BOOL;
		param.Size=ENBParameterTypeToSize(param.Type);
		memcpy(param.Data, &bvalue, param.Size);
		res=enbSetParameter("enbseries.ini", "GLOBAL", "UseEffect", &param);
		if (res==FALSE)
		{
			//this means some of arguments are invalid, parameter not exist, parameter hidden, parameter read only. Also fails if not executed inside callback
		}
	}

	//modify shader variable, filename must be NULL to access it and category is file name upper case (like in shader editor window)
	float	fvalue=1.0f;
	param.Type=ENBParam_FLOAT;
	param.Size=ENBParameterTypeToSize(param.Type);
	memcpy(param.Data, &fvalue, param.Size);
	res=enbSetParameter(NULL, "ENBEFFECT.FX", "CC: Gamma", &param);
	if (res==FALSE)
	{
		//this means some of arguments are invalid, parameter not exist, parameter hidden, parameter read only. Also fails if not executed inside callback
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//save parameters before modifying them
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void	SaveParameters()
{
	if (IsLoaded==FALSE) return;

	BOOL	res;
	ENBParameter	param;

	//set parameter
	res=enbGetParameter("enbseries.ini", "GLOBAL", "UseEffect", &param);
	if ((res==TRUE) && (param.Type==ENBParam_BOOL)) memcpy(&OldState_UseEffect, param.Data, param.Size);

	res=enbGetParameter(NULL, "ENBEFFECT.FX", "CC: Gamma", &param);
	if ((res==TRUE) && (param.Type==ENBParam_FLOAT)) memcpy(&OldState_CC_Gamma, param.Data, param.Size);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//restore previously saved parameters
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void	RestoreParameters()
{
	if (IsLoaded==FALSE) return;

	BOOL	res;
	ENBParameter	param;

	//set parameter
	param.Type=ENBParam_BOOL;
	param.Size=ENBParameterTypeToSize(param.Type);
	memcpy(param.Data, &OldState_UseEffect, param.Size);
	res=enbSetParameter("enbseries.ini", "GLOBAL", "UseEffect", &param);

	param.Type=ENBParam_FLOAT;
	param.Size=ENBParameterTypeToSize(param.Type);
	memcpy(param.Data, &OldState_CC_Gamma, param.Size);
	res=enbSetParameter(NULL, "ENBEFFECT.FX", "CC: Gamma", &param);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++