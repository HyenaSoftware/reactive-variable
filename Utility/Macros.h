#pragma once
#define WINMAIN int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
#define PROPERTY(GET,SET) __declspec(property(get=GET, put=SET))
#define PROPERTYG(GET) __declspec(property(get=GET))
#define PROPERTYS(SET) __declspec(property(put=SET))

#define SAFE_RELEASE(a)	if((a)!=NULL){(a)->Release();(a)=NULL;}
#define SAFE_DELETE(a)	if((a)!=NULL){delete (a);(a)=NULL;}
#define SAFE_DELETE_ARRAY(a)	if((a)!=NULL){delete[] (a);(a)=NULL;}

#ifdef _DEBUG
#define DBGBREAK {int s=0;}
#else
#define DBGBREAK
#endif

#if !defined(interface) && USE_CUSTOM_INTERFACE_DEFINITION
#define interface struct __declspec(novtable)
#endif

#if !defined(PURE) && USE_CUSTOM_INTERFACE_DEFINITION
#define PURE =0;
#endif

#define IN
#define OUT
#define INOUT

#define NOT !
#define AND &&
#define OR	||
#define XOR !=

#define PAUSE system("pause")

#define FLTCMP(a,b) (abs(a-b) < FLT_EPSILON)
#define FLTEQUAL FLTCMP
#define foreach(I,C) for(auto I=(C).begin(); I!=(C).end(); ++I)
#define cforeach(I,C) for(auto I=(C).cbegin(); I!=(C).cend(); ++I)

#define DEPRECATED(str) __declspec(deprecated(str))

// low-level jump
#define GOTO(v) __asm { jmp dword ptr [v] }
#define SAVELABEL(var,lbl) \
	__asm \
	{ \
		push eax \
		mov eax, [lbl] } \
		mov [var], eax } \
		pop eax \
	}

#define LABEL(a) __asm { a: }

// helper to intellisense
// #define this this

// appear as break-point if assertation failed
#define dbgassert(E) { if(!(E)) { __asm { int 3h } } }

#define D3DXMatrixTranslationV(m,v) D3DXMatrixTranslation(m,v.x,v.y,v.z)
#define D3DXVec3Normalize1(v) D3DXVec3Normalize(v,v)

#define STRING2(x) #x
#define STRING(x) STRING2(x)
#define HERE __FILE__"("STRING(__LINE__)"): "

#define PASTE(n) n

#define randomize() srand((unsigned int)time(NULL))
#define EPSILON FLT_EPSILON
#define INRANGE(v,min,max) (((min)<=(v)) && ((v)<(max)))
#define _PI 3.14159265358979323846
