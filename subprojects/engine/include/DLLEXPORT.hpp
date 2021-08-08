#pragma once

#ifdef DLLDIR_EX
   #define DLLEXPORT  __declspec(dllexport)   // export DLL information 
#else
   #define DLLEXPORT  __declspec(dllimport)   // import DLL information
#endif