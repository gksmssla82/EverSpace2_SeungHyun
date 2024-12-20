#pragma once

namespace Engine
{
	template<typename T>
	void Safe_Delete(T& Temp)
	{
		if (Temp)
		{
			delete Temp;
			Temp = nullptr;
		}
	}

	template<typename T>
	void Safe_Release(T& Temp)
	{
		if (Temp)
		{
 			Temp->Free();
			Temp = nullptr;
		}
	}

	//template<typename T>
	//unsigned long Safe_Release(T& Temp)
	//{
	//	unsigned long dwRefCnt = 0;

	//	if (Temp)
	//	{
	//		dwRefCnt = Temp->Release();

	//		if(0 == dwRefCnt)
	//			Temp = nullptr;
	//	}

	//	return dwRefCnt;
	//}

	//template<typename T>
	//unsigned long Safe_AddRef(T& Temp)
	//{
	//	unsigned long dwRefCnt = 0;

	//	if (Temp)	
	//		dwRefCnt = Temp->AddRef();		

	//	return dwRefCnt;
	//}


	template<typename T>
	void Safe_Delete_Array(T& Temp)
	{
		if (Temp)
		{
			delete[] Temp;
			Temp = nullptr;
		}
	}

}
