#include "gsc.hpp"
#include <iostream>
#include <cstdlib> // For exit
#include <string>
#include <signal.h>

cvar_t *com_sv_running;
cvar_t *sv_maxclients;

int game_mp;
gentity_t* g_entities;



void custom_SV_Init()
{
    Cvar_Get("vcodlib", "1", CVAR_SERVERINFO);
    Cvar_Get("jump_height", "39.0", CVAR_ARCHIVE | CVAR_SERVERINFO);
    com_sv_running = Cvar_FindVar("sv_running");
    sv_maxclients = Cvar_FindVar("sv_maxclients");
}

void moyai()
{
    Com_Printf("workin?\n");
    Com_DPrintf(":c\n");
}



void addCommands()
{
    Cmd_AddCommand("moyai", moyai);
}





void *custom_Sys_LoadDll( const char *name, char *fqpath, int( **entryPoint ) ( int, ... ), int ( *systemcalls )( int, ... ) )
{

    void *l = call<void*, const char*, char*, int(**)(int,...)>(0x4633A0, name, fqpath, entryPoint, systemcalls);

    game_mp = (int)GetModuleHandle("game_mp_x86.dll");
    Com_Printf("[game_mp: %02x]\n", game_mp);
    _memset((void*)0x20018D7A, 0x90, 5);

    gentity_t* g_entities = (gentity_t*)0x2016f220;

    return l;
}



void vcodlib()
{
    
    char vc[3];
    memcpy(&vc, (void*)0x5A60D0, 3);


    cracking_hook_call(0x460399, (int)custom_Sys_LoadDll);



    custom_SV_Init();

    _memset((void*)0x452FB3, 0x90, 2);


    addCommands();


//    if(GetModuleHandle("game_mp_x86.dll") != NULL)
//    {
//        ScriptInitiating();

        //Jump_Check_2();
//    }


    //008930f0 - cmd_Argv

    DWORD old;
    VirtualProtect((void*)0x469BEE, 6, PAGE_EXECUTE_READWRITE, &old);
    *(BYTE*)0x469BEE = 0xe8;
    cracking_hook_call(0x469BEE, (int)Scr_GetCustomFunction);
    *(BYTE*)(0x469BEE + 5) = 0x90;
    VirtualProtect((void*)0x469BEE, 6, old, &old);


    VirtualProtect((void*)0x469E8E, 6, PAGE_EXECUTE_READWRITE, &old);
    *(BYTE*)0x469E8E = 0xe8;
    cracking_hook_call(0x469E8E, (int)Scr_GetCustomMethod);
    *(BYTE*)(0x469E8E + 5) = 0x90;
    VirtualProtect((void*)0x469E8E, 6, old, &old);

    Com_Printf("VCODLIB_SV: PLUGIN LOADED\n");
    Com_Printf("VCODLIB_SV: https://cod1.rf.gd/\n");
    Com_DPrintf("VCODLIB_SV: Developer mode\n");
}


DWORD old;
DWORD WINAPI tExtend(LPVOID);
DWORD g_threadID;
HMODULE g_hModule;


BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
        vcodlib();
    }
	break;

	case DLL_PROCESS_DETACH:
	{
        Com_Printf("VCODLIB_SV: PLUGIN UNLOADED\n");
	}
	break;

	}
	return TRUE;
}