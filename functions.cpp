
#include "functions.hpp"
#include <cstring>

void _memset(void* addr, int v, size_t len) {
    DWORD tmp;
    VirtualProtect((void*)addr, len, PAGE_EXECUTE_READWRITE, &tmp);
    memset(addr, v, len);
    VirtualProtect((void*)addr, len, tmp, &tmp);
}

void _memcpy(void* v1, void* v2, size_t len) {
    DWORD tmp;
    VirtualProtect((void*)v1, len, PAGE_EXECUTE_READWRITE, &tmp);
    memcpy(v1, v2, len);
    VirtualProtect((void*)v1, len, tmp, &tmp);
}


void Info_Print( const char *s ) {
	char key[512];
	char value[512];
	char    *o;
	int l;

	if ( *s == '\\' ) {
		s++;
	}
	while ( *s )
	{
		o = key;
		while ( *s && *s != '\\' )
			*o++ = *s++;

		l = o - key;
		if ( l < 20 ) {
			memset( o, ' ', 20 - l );
			key[20] = 0;
		} else {
			*o = 0;
		}
		Com_Printf( "%s", key );

		if ( !*s ) {
			Com_Printf( "MISSING VALUE\n" );
			return;
		}

		o = value;
		s++;
		while ( *s && *s != '\\' )
			*o++ = *s++;
		*o = 0;

		if ( *s ) {
			s++;
		}
		Com_Printf( "%s\n", value );
	}
}


int Cmd_Argc()
{
    return *(int*)0x8D5020;
}

void ClientCommand()
{ 
    call<void*>(0x2001FB60);
}

char* Cvar_VariableString(const char* var_name)
{
	cvar_t* var = Cvar_FindVar(var_name);
	if (!var)
		return (char*)"";
	return var->string;
}
int Cvar_VariableIntegerValue(const char* var_name)
{
	cvar_t* var = Cvar_FindVar(var_name);
	if (!var)
		return 0;
	return var->integer;
}

void __cdecl Com_sprintf(char* dest, int size, const char* fmt, ...)
{
	int ret;
	va_list argptr;

	va_start(argptr, fmt);
	ret = vsnprintf(dest, size, fmt, argptr);
	va_end(argptr);
	if (ret == -1)
	{
		Com_Printf("Com_sprintf: overflow of %i bytes buffer\n", size);
	}
}


int Scr_GetType(int a1)
{
    return call<int, int>(0x47DA20, a1);
}

int Scr_AddInt(int a1)
{
    return call<int, int>(0x47DB60, a1);
}

int Scr_AddBool(BOOL a1)
{
    return call<int, BOOL>(0x47DB40, a1);
}

int Scr_AddString(char* a1)
{
    return call<int, char*>(0x47DCE0, a1);
}

int Scr_AddVector(vec3_t a1)
{
    return call<int, float*>(0x47DDB0, a1);
}

BOOL Scr_GetBool(int index)
{
    return call<BOOL, int>(0x47D050, index);
}

int Scr_GetInt(int index)
{
    return call<int, int>(0x47D100, index);
}

float Scr_GetFloat(int index)
{
    return call<float, int>(0x47D3F0, index);
}

int Scr_GetVector(int index, vec3_t vec)
{
    return call<int, int, float*>(0x47D790, index, vec);
}

char* Scr_GetString(int index)
{
    return call<char*, int>(0x47D530, index);
}

int Scr_GetFunc(int index)
{
    return call<int, int>(0x482D90, index);
}

int Scr_Error(const char *string)
{
    return call<int>(0x200A05AC, string); //game_mp_x86
}

int Scr_AddUndefined()
{
    return call<int>(0x47DBC0); //CODMP
}
 
int Scr_GetNumParam(void)
{
    return call<int>(0x200A0534); //game_mp_x86.dll
}


xfunction_t Scr_GetFunction(const char** v_functionName, qboolean *v_developer)
{
    return call<xfunction_t, const char**, int*>(0x20034C00, v_functionName, v_developer);
}

xmethod_t Scr_GetMethod(const char** v_methodName, qboolean *v_developer)
{
    return call<xmethod_t, const char**, int*>(0x20034D00, v_methodName, v_developer);
}
