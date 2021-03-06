#ifndef _YON_PLATFORM_CYONENGINEWIN32_H_
#define _YON_PLATFORM_CYONENGINEWIN32_H_

#include "config.h"

#ifdef YON_COMPILE_WITH_WIN32
////加载Window程序需要的头文件
#include <windows.h>

#include "IYonEngine.h"
#include "SYonEngineParameters.h"
#include "SOGLES1Parameters.h"
#include "COGLES1Driver.h"
#include "CSceneManager.h"

namespace yon{
	namespace platform{
		
		class CYonEngineWin32:public IYonEngine{
		public:
			CYonEngineWin32(const yon::SYonEngineParameters& params);
			~CYonEngineWin32();

			virtual video::IVideoDriver* getVideoDriver(){return  m_videoDriver;}
			virtual scene::ISceneManager* getSceneManager(){return m_sceneManager;}
			virtual bool run();

			//virtual yon::ITimer* getTimer();

			const HWND& getHWND() const{
				return m_hWnd;
			}
		protected:
			virtual void createDriver();
		private:
			//初始化窗口，成功则返回true，失败则返回false
			bool initWindow(const yon::SYonEngineParameters& params);

			//窗口句柄
			//Microsoft Windows 运行环境，通过给应用程序中的每个窗体和控件分配一个句柄（或 hWnd）来标识它们。
			//hWnd 属性用于Windows API调用。许多 Windows 运行环境函数需要活动窗口的 hWnd 作为参数。
			//注意 由于该属性值在程序运行时可以改变，绝对不要将 hWnd 存储在变量中。
			HWND m_hWnd;
			//绑定到外部窗口
			bool m_bExternalWindow;
			//参数结构体
			yon::SYonEngineParameters m_params;

			video::IVideoDriver* m_videoDriver;
			scene::ISceneManager* m_sceneManager;

			bool m_bClose;
		};
	}
}
#endif //YON_COMPILE_WITH_WIN32
#endif //_YON_PLATFORM_CYONENGINEWIN32_H_