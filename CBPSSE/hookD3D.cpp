#include <Windows.h>
//#include <D3DCommon.h>
//#include <dxgi.h>
//#include <d3d11.h>
#include <f4se/GameAPI.h>
#include <f4se/PluginAPI.h>
#include "f4se/GameThreads.h"

#include "log.h"
#include "../detourxs-master/detourxs.h"
#include "f4se_common/Utilities.h"

//#define SAFE_RELEASE(x) if((x)) {x->Release(); x = nullptr;}
//
//
//static IDXGISwapChain* tempSwapChain = nullptr;
//static ID3D11Device* tempDevice = nullptr;
//static ID3D11DeviceContext* tempContext = nullptr;
//
////Real Device Pointers
//static ID3D11Device* g_device = nullptr;
//static ID3D11DeviceContext* g_context = nullptr;
//static IDXGISwapChain* g_swapChain = nullptr;
//
////SwapChain Vtable Adressss
//static DWORD_PTR* swapChainVtable = nullptr;
//static DWORD_PTR* contextVTable = nullptr;
//
//
//DWORD_PTR Hook(DWORD_PTR *VMT, int index, DWORD_PTR ourFunc, DWORD_PTR *oldFunc) {
//	/* We return the original function address for them */
//	DWORD_PTR returnAddy = VMT[index];
//	*oldFunc = returnAddy;
//
//	/* Allow us to edit the spot */
//	DWORD oldProtect;
//	VirtualProtect((LPVOID)(VMT + index), 8, PAGE_EXECUTE_READWRITE, &oldProtect);
//
//	/* Set the address as our function */
//	DWORD_PTR * funcAddy = VMT + index;
//	*funcAddy = ourFunc;
//
//	/* Return it to the original protection */
//	VirtualProtect((LPVOID)(VMT + index), 4, oldProtect, &oldProtect);
//
//	return returnAddy;
//}
//
//typedef void(__stdcall *ClearStateHook) (ID3D11DeviceContext* This);
//static ClearStateHook oClearStateHook = NULL;
//void  __stdcall hookClearState(ID3D11DeviceContext* This)
//{
//	static int foo = 60 * 5;
//	foo++;
//	if (foo > 60 * 5) {
//		foo = 0;
//		//logger.Error("hookClearState\n");
//	}
//
//	//scaleTest();
//
//	return oClearStateHook(This);
//}
//
//typedef HRESULT(__stdcall *D3D11PresentHook) (IDXGISwapChain* This, UINT SyncInterval, UINT Flags);
//static D3D11PresentHook oPresent = NULL;
//
////Present Function
//HRESULT __stdcall hookD3D11Present(IDXGISwapChain* This, UINT SyncInterval, UINT Flags)
//{
//	return oPresent(This, SyncInterval, Flags);
//}
//
//void ReleaseCreatedDevice()
//{
//	SAFE_RELEASE(tempContext);
//	SAFE_RELEASE(tempDevice);
//	SAFE_RELEASE(tempSwapChain);
//}
//
//
//DetourXS clearHookDetour;
//typedef HRESULT(__stdcall *D3D11CreateDeviceAndSwapChainHook) (
//	_In_opt_        IDXGIAdapter         *pAdapter,
//	D3D_DRIVER_TYPE      DriverType,
//	HMODULE              Software,
//	UINT                 Flags,
//	_In_opt_  const D3D_FEATURE_LEVEL    *pFeatureLevels,
//	UINT                 FeatureLevels,
//	UINT                 SDKVersion,
//	_In_opt_  const DXGI_SWAP_CHAIN_DESC *pSwapChainDesc,
//	_Out_opt_       IDXGISwapChain       **ppSwapChain,
//	_Out_opt_       ID3D11Device         **ppDevice,
//	_Out_opt_       D3D_FEATURE_LEVEL    *pFeatureLevel,
//	_Out_opt_       ID3D11DeviceContext  **ppImmediateContext
//	);
//static D3D11CreateDeviceAndSwapChainHook oCreateHook = NULL;
//
//
//
//HRESULT __stdcall D3D11CreateDeviceAndSwapChain2(
//	_In_opt_        IDXGIAdapter         *pAdapter,
//	D3D_DRIVER_TYPE      DriverType,
//	HMODULE              Software,
//	UINT                 Flags,
//	_In_opt_  const D3D_FEATURE_LEVEL    *pFeatureLevels,
//	UINT                 FeatureLevels,
//	UINT                 SDKVersion,
//	_In_opt_  const DXGI_SWAP_CHAIN_DESC *pSwapChainDesc,
//	_Out_opt_       IDXGISwapChain       **ppSwapChain,
//	_Out_opt_       ID3D11Device         **ppDevice,
//	_Out_opt_       D3D_FEATURE_LEVEL    *pFeatureLevel,
//	_Out_opt_       ID3D11DeviceContext  **ppImmediateContext
//) {
//	//logger.Error("Create Device and SwapChain called\n");
//	HRESULT res = oCreateHook(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels
//			, SDKVersion, pSwapChainDesc, ppSwapChain, ppDevice, pFeatureLevel, ppImmediateContext);
//
//	//logger.Error("Hooking ClearState\n");
//	contextVTable = (DWORD_PTR*)*ppImmediateContext;
//	contextVTable = (DWORD_PTR*)contextVTable[0];
//	Hook(contextVTable, 110, (DWORD_PTR)hookClearState, (UINT_PTR *)&oClearStateHook);
//	//logger.Error("ClearState Hooked\n");
//	return res;
//}
//
//
//
//
//DWORD __stdcall HookCreateFn(LPVOID)
//{
//	HWND hWnd = GetForegroundWindow();
//	if (hWnd == nullptr)
//		return false;
//	//logger.Error("hook CreateDevice\n");
//	clearHookDetour.Create((LPVOID)D3D11CreateDeviceAndSwapChain, D3D11CreateDeviceAndSwapChain2, &(LPVOID)oCreateHook);
//	//oCreateHook = (D3D11CreateDeviceAndSwapChainHook)clearHookDetour.GetTrampoline();
//	//logger.Error("Hook Complete\n");
//
//	return 0;
//}
//
//



/*//OLD METHOD

typedef UINT64 (__cdecl *renderHook) (void* This, UINT64 arg);

renderHook orender = nullptr;

void scaleTest();
UINT64 __cdecl Render(void *This, UINT64 arg)
{
//logger.error("This is called\n");
//logger.error("orender = %016llx\n", orender);
scaleTest();
return orender(This, arg);
//return 0;
}

//RelocPtr <void *> render(0xD69720);
//RelocPtr <void *> main(0x640BC0);

// Address copied out of SKSE
//RelocPtr <void *> ProcessTasks_HookTarget_Enter(0x005B2EF0); //For SSE 1.5.23
//RelocPtr <void *> ProcessTasks_HookTarget_Enter(0x005B34A0);  //For SSE 1.5.39
//RelocPtr <void *> ProcessTasks_HookTarget_Enter(0x005B31E0); //For SSE 1.5.53
RelocPtr <void *> ProcessTasks_HookTarget_Enter(0x005BAB10); //For VR 1.4.15

DetourXS renderDetour;
void DoHook() {
logger.info("Attempting Game Hook\n");
// Useful for finding the addresses
//CreateThread(NULL, 0, HookCreateFn, NULL, 0, NULL);

//renderDetour.Create(render.GetPtr(), Render, &(LPVOID)orender);
renderDetour.Create(ProcessTasks_HookTarget_Enter.GetPtr(), Render, &(LPVOID)orender);
//orender = (renderHook)renderDetour.GetTrampoline();
}

*/

typedef void(*_ProcessEventQueue_Internal) (void* thisPtr);

_ProcessEventQueue_Internal orig_ProcessEventQueue_Internal = nullptr;

void UpdateActors();

void hk_ProcessEventQueue_Internal(void* thisPtr)
{
	orig_ProcessEventQueue_Internal(thisPtr);
	UpdateActors();
}

// RelocPtr <void*> ProcessEventQueue_Internal(0x0211CF80);			//Flat FO4
RelocPtr <void*> ProcessEventQueue_Internal(0x0219DC00);			// FO4VR

DetourXS renderDetour;

void DoHook() {
	//logger.Info("Attempting Game Hook\n");

	renderDetour.Create((LPVOID)ProcessEventQueue_Internal.GetPtr(), hk_ProcessEventQueue_Internal, (LPVOID*)(&orig_ProcessEventQueue_Internal));
}