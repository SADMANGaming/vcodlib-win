
#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include "gsc.hpp"

typedef void ( *xcommand_t )( void );

typedef void (*SV_DirectConnect_f_t)(netadr_t from);
static const SV_DirectConnect_f_t SV_DirectConnect_f = (SV_DirectConnect_f_t)0x00453390;

typedef void (*Info_SetValueForKey_t)(char *s, const char *key, const char *value);
static const Info_SetValueForKey_t Info_SetValueForKey = (Info_SetValueForKey_t)0x0044b300;

typedef void (*Com_Printf_t)(const char *format, ...);
static const Com_Printf_t Com_Printf = (Com_Printf_t)0x4357B0;

typedef gentity_t * (*SV_ClientThink_t)(client_t *cl, usercmd_t *cmd);
static const SV_ClientThink_t SV_ClientThink = (SV_ClientThink_t)0x455270;

typedef char * (*SL_ConvertToString_t)(unsigned int index); //
static const SL_ConvertToString_t SL_ConvertToString = (SL_ConvertToString_t)0x008E6208; //prawy 0x008E6208

typedef void (*Com_DPrintf_t)(const char *format, ...);
static const Com_DPrintf_t Com_DPrintf = (Com_DPrintf_t)0x435820; 

typedef void (*Com_PrintMessage_t)(int channel, const char *message);
static const Com_PrintMessage_t Com_PrintMessage = (Com_PrintMessage_t)0x435820; //prawy 

typedef void (*SV_DropClient_t)(client_t *drop, const char *reason);
static const SV_DropClient_t SV_DropClient = (SV_DropClient_t)0x453D80;

typedef client_t * (*SV_GetPlayerByName_t)(void);
static const SV_GetPlayerByName_t SV_GetPlayerByName = (SV_GetPlayerByName_t)0x451A80;

typedef client_t * (*SV_GetPlayerByNum_t)(void);
static const SV_GetPlayerByNum_t SV_GetPlayerByNum = (SV_GetPlayerByNum_t)0x451BA0;

typedef void (*Cmd_AddCommand_t)(const char* name, xcommand_t cmd);
static const Cmd_AddCommand_t Cmd_AddCommand = (Cmd_AddCommand_t)0x428840;

typedef void (*Cmd_RemoveCommand_t)(const char* name);
static const Cmd_RemoveCommand_t Cmd_RemoveCommand = (Cmd_RemoveCommand_t)0x428990;

typedef cvar_t* (*Cvar_FindVar_t)(const char* n);
static const Cvar_FindVar_t Cvar_FindVar = (Cvar_FindVar_t)0x439280;

typedef cvar_t* (*Cvar_Set_t)(const char *var_name, const char *value);
static const Cvar_Set_t Cvar_Set = (Cvar_Set_t)0x439650;


typedef int (*Cmd_Argv_t)(int a1);
static const Cmd_Argv_t Cmd_Argv = (Cmd_Argv_t)0x004357b0;

//typedef playerState_t * (*SV_GameClientNum_t)(int num);
//static const SV_GameClientNum_t SV_GameClientNum = (SV_GameClientNum_t)0x14073D0;

typedef cvar_t* (*Cvar_Get_t)(const char*, const char*, int);
static const Cvar_Get_t Cvar_Get = (Cvar_Get_t)0x439350;

typedef void(*Com_Error_t)(int, const char*, ...);
static const Com_Error_t Com_Error = (Com_Error_t)0x435AD0;

void Info_Print( const char *s );


extern char **cmd_argv;

static int ( QDECL * syscall )( int arg, ... ) = ( int ( QDECL * )( int, ... ) ) - 1;

template <typename T, typename ... Ts> T call(size_t addr, Ts ... ts);

template <typename T, typename ... Ts>
T call(size_t addr, Ts ... ts) {
    T (*f)(...);
    *(T*)&f = (T)addr;
    return f(ts...);
}

template <typename ... Ts>

int Cmd_Argc();
int Scr_GetNumParam(void);
int Scr_GetPointerType(int);
int Scr_GetType(int);
int Scr_AddInt(int);
int Scr_AddBool(BOOL);
int Scr_AddString(char*);
int Scr_AddVector(vec3_t);
BOOL Scr_GetBool(int);
int Scr_GetInt(int);
float Scr_GetFloat(int);
char* Scr_GetString(int);
int Scr_GetVector(int, vec3_t);
int Scr_GetFunc(int);
int Scr_AddUndefined();
int Scr_Error(const char *string);

xmethod_t Scr_GetMethod(const char** v_methodName, qboolean *v_developer);
xfunction_t Scr_GetFunction(const char** v_functionName, qboolean *v_developer);

void ClientCommand();

void _memset(void* addr, int v, size_t len);
void _memcpy(void* v1, void* v2, size_t len);













/*
void Q_strncpyz(char* dest, const char* src, int destsize)
{
	if (!src)
	{
		Com_Error(ERR_FATAL, "Q_strncpyz: NULL src");
	}
	if (destsize < 1)
	{
		Com_Error(ERR_FATAL, "Q_strncpyz: destsize < 1");
	}

	strncpy_s(dest, destsize, src, destsize - 1);
	dest[destsize - 1] = 0;
}

int Q_stricmpn(const char* s1, const char* s2, int n)
{
	int c1, c2;
	do
	{
		c1 = *s1++;
		c2 = *s2++;

		if (!n--) {
			return 0;       // strings are equal until end point
		}

		if (c1 != c2) {
			if (c1 >= 'a' && c1 <= 'z') {
				c1 -= ('a' - 'A');
			}
			if (c2 >= 'a' && c2 <= 'z') {
				c2 -= ('a' - 'A');
			}
			if (c1 != c2) {
				return c1 < c2 ? -1 : 1;
			}
		}
	} while (c1);

	return 0;       // strings are equal
}

int Q_stricmp(const char* s1, const char* s2)
{
	return (s1 && s2) ? Q_stricmpn(s1, s2, 99999) : -1;
}

char* Q_CleanStr(char* string, bool colors)
{
	char* d;
	char* s;
	int c;

	s = string;
	d = string;
	while ((c = *s) != 0)
	{
		if (Q_IsColorString(s) && !colors)
		{
			s++;
		}
		else if (c >= 0x20 && c <= 0x7E)
		{
			*d++ = c;
		}
		s++;
	}
	*d = '\0';

	return string;
}
*/


#endif