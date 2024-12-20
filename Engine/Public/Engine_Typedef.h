#pragma once

namespace Engine
{
	typedef unsigned char				_ubyte;
	typedef signed char					_byte;

	typedef unsigned short				_ushort;
	typedef signed short				_short;

	typedef unsigned int				_uint;
	typedef signed int					_int;

	typedef unsigned long				_ulong;
	typedef signed long					_long;

	typedef unsigned long long			_ulonglong;
	typedef signed long long			_longlong;

	typedef float						_float;
	typedef double						_double;

	typedef bool						_bool;

	typedef wchar_t						_tchar;
	typedef char						_char;

	typedef D3DXVECTOR2					_float2;
	typedef D3DXVECTOR3					_float3;
	typedef D3DXVECTOR4					_float4;

	typedef D3DXMATRIX					_float4x4;

	typedef POINT						_point;

	typedef struct tagInt32
	{
		tagInt32(unsigned int _ix, unsigned int _iy, unsigned int _iz)
			: ix(_ix)
			, iy(_iy)
			, iz(_iz) {	}

		unsigned int ix, iy, iz;
	} _uint3;


	

	
}
