#include <locale>
#include "utils.hh"
#include <list>
#include <d3d9.h>
#define m_pi 3.14159265358979323846264338327950288419716939937510

namespace structs
{
	uintptr_t _getobjectname;
	uintptr_t free_name;
	uintptr_t bone_matrix;
	float fov_angle;

	struct FMatrix
	{
		float M[4][4];
	};
	static FMatrix* player_matrix = new FMatrix();

	struct Vector2D
	{
		float x, y;
		Vector2D() { x = y = 0.0; }
		Vector2D(float xx, float yy) { x = xx; y = yy; }
	};

	struct Vector3D
	{
		float x, y, z;
		Vector3D() { x = y = z = 0.0; }
		Vector3D(float xx, float yy, float zz) { x = xx; y = yy; z = zz; }
	};

	struct Vector4D
	{
		float x, y, z, w;
		Vector4D() { x = y = z = w = 0.0; }
		Vector4D(float xx, float yy, float zz, float ww) { x = xx; y = yy; z = zz; w = ww; }
	};

	class vector3
	{
	public:
		vector3() : x(0.f), y(0.f), z(0.f)
		{}

		vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
		{}

		vector3(float _v) : x(_v), y(_v), z(_v)
		{}

		~vector3()
		{}

		float x;
		float y;
		float z;

		inline bool zero() const
		{
			return (x > -0.1f && x < 0.1f && y > -0.1f && y < 0.1f && z > -0.1f && z < 0.1f);
		}

		inline float dot(vector3 v)
		{
			return x * v.x + y * v.y + z * v.z;
		}

		inline float distance(vector3 v)
		{
			return float(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
		}

		inline double length() {
			return sqrt(x * x + y * y + z * z);
		}

		vector3 operator+(vector3 v)
		{
			return vector3(x + v.x, y + v.y, z + v.z);
		}

		vector3 operator-(vector3 v)
		{
			return vector3(x - v.x, y - v.y, z - v.z);
		}

		vector3 operator*(float number) const {
			return vector3(x * number, y * number, z * number);
		}

		vector3 operator/(float number) const {
			return vector3(x / number, y / number, z / number);
		}
	};

	class vector2
	{
	public:
		vector2() : x(0.f), y(0.f)
		{}

		vector2(float _x, float _y) : x(_x), y(_y)
		{}

		vector2(float _v) : x(_v), y(_v)
		{}

		~vector2()
		{}

		float x;
		float y;

		inline float distance(vector2 v)
		{
			return sqrtf((powf, (v.x - x), 2.0f) + powf((v.y - y), 2.0f));
		}

		vector2 operator+(vector2 v)
		{
			return vector2(x + v.x, y + v.y);
		}

		vector2 operator-(vector2 v)
		{
			return vector2(x - v.x, y - v.y);
		}

		vector2 operator*(float number) const {
			return vector2(x * number, y * number);
		}

		vector2 operator/(float number) const {
			return vector2(x / number, y / number);
		}
	};


	template<class T>
	struct TArray
	{
		friend struct FString;

	public:
		inline TArray()
		{
			Data = nullptr;
			Count = Max = 0;
		};

		inline int Num() const
		{
			return Count;
		};

		inline T& operator[](int i)
		{
			return Data[i];
		};

		inline const T& operator[](int i) const
		{
			return Data[i];
		};

		inline bool IsValidIndex(int i) const
		{
			return i < Num();
		}

	private:
		T* Data;
		int32_t Count;
		int32_t Max;
	};

	struct FString : private TArray<wchar_t>
	{
		inline FString()
		{
		};

		FString(const wchar_t* other)
		{
			Max = Count = *other ? std::wcslen(other) + 1 : 0;

			if (Count)
			{
				Data = const_cast<wchar_t*>(other);
			}
		};

		inline bool IsValid() const
		{
			return Data != nullptr;
		}

		inline const wchar_t* c_str() const
		{
			return Data;
		}

		std::string ToString() const
		{
			auto length = std::wcslen(Data);

			std::string str(length, '\0');

			std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(Data, Data + length, '?', &str[0]);

			return str;
		}
	};

	class FRotator
	{
	public:
		FRotator() : fPitch(0), fYaw(0), fRoll(0)
		{

		}

		FRotator(float _pitch, float _yaw, float _roll) : fPitch(_pitch), fYaw(_yaw), fRoll(_roll)
		{

		}

		float fPitch;
		float fYaw;
		float fRoll;
	};

	struct FBox
	{
		vector3  Min;
		vector3  Max;
		unsigned char IsValid;
		unsigned char UnknownData00[0x3];
	};

	class FMinimalViewInfo
	{
	public:
		vector3 Location;
		FRotator Rotation;
		float FOV;
		float OrthoWidth;
		float OrthoNearClipPlane;
		float OrthoFarClipPlane;
		float AspectRatio;
	};

	struct FQuat
	{
		float x;
		float y;
		float z;
		float w;
	};

	static void free_names(__int64 amongus)
	{
		auto function = reinterpret_cast<__int64(__fastcall*)(__int64 sussyfortnite)>(free_name);
		function(amongus);
	}

	static const char* getobjectname(uintptr_t fortnite)
	{
		if (fortnite == 0)
			return ("");
		auto getobjname = reinterpret_cast<FString * (__fastcall*)(int* daindex, FString * string)>(_getobjectname);
		int name_index = *(int*)(fortnite + 0x18);
		FString string;
		getobjname(&name_index, &string);
		if (string.c_str() == 0)
			return ("");
		auto string_result = string.ToString();
		if (string.c_str() != 0)
			free_names((__int64)string.c_str());
		return string_result.c_str();
	}

	static bool get_bone_loc(uintptr_t pawn, int id, vector3* out)
	{
		uintptr_t mesh = *(uintptr_t*)(pawn + offsets::mesh);
		if (!mesh) return false;

		auto get_bone_matrix = ((FMatrix * (__fastcall*)(uintptr_t, FMatrix*, int))(bone_matrix));
		get_bone_matrix(mesh, player_matrix, id);

		out->x = player_matrix->M[3][0];
		out->y = player_matrix->M[3][1];
		out->z = player_matrix->M[3][2];

		return true;
	}

	static bool world_to_screen(vector3 WorldLocation, vector3* out)
	{
		auto WorldToScreen = reinterpret_cast<bool(__fastcall*)(uintptr_t pPlayerController, vector3 vWorldPos, vector3 * vScreenPosOut, char)>(utils::worldtoscreen);
		WorldToScreen((uintptr_t)utils::player_controller, WorldLocation, out, (char)0);
		return true;
	}

	static float get_fov_angle(uintptr_t PlayerCameraManager)
	{
		auto fn = reinterpret_cast<float(*)(UINT64, char*)>(*(ULONG_PTR*)(*(ULONG_PTR*)PlayerCameraManager + 0x6D0));
		return fn((ULONG_PTR)PlayerCameraManager, (char*)0);
	}

	static void client_set_rot(vector3 new_rot, bool reset_ = false)
	{
		auto SetControlRotation_ = (*(void(__fastcall**)(uintptr_t Controller, vector3 NewRotation, bool bResetCamera))(*(uintptr_t*)utils::player_controller + 0x640));
		SetControlRotation_(utils::player_controller, new_rot, reset_);
	}

	static void validate_rot(vector3 new_rot, bool reset_ = false)
	{
		auto SetControlRotation_ = (*(void(__fastcall**)(uintptr_t Controller, vector3 NewRotation, bool bResetCamera))(*(uintptr_t*)utils::player_controller + 0x638));
		SetControlRotation_(utils::player_controller, new_rot, reset_);
	}

	vector3 CamLoc;
	vector3 get_rot(uintptr_t a)
	{
		vector3 RetVector = { 0,0,0 };

		vector3 rootHead;
		get_bone_loc(a, 66, &rootHead);

		if (rootHead.x == 0 && rootHead.y == 0) return vector3(0, 0, 0);

		vector3 VectorPos = rootHead - CamLoc;

		float distance = VectorPos.length();
		RetVector.x = -(((float)acos(VectorPos.z / distance) * (float)(180.0f / m_pi)) - 90.f);
		RetVector.y = (float)atan2(VectorPos.y, VectorPos.x) * (float)(180.0f / m_pi);

		return RetVector;
	}

	double cross_dist(double x1, double y1, double x2, double y2)
	{
		return sqrtf(powf((float)(x1 - x2), (float)2) + powf((float)(y1 - y2), (float)2));
	}

	bool is_in_fov(vector2 screen_pos, float closest_pawn)
	{
		if (settings::draw_circle)
		{
			if (screen_pos.x < ((width / 2) - settings::fov_size)) return false;
			if (screen_pos.x < ((width / 2) + settings::fov_size)) return false;

			if (screen_pos.y < ((height / 2) - settings::fov_size)) return false;
			if (screen_pos.y < ((height / 2) + settings::fov_size)) return false;
		}
		else
		{
			if (screen_pos.distance(vector2(width / 2, height / 2)) > closest_pawn)
				return false;
		}
	}
	
	uintptr_t los;
	static BOOLEAN line_of_sight(PVOID PlayerController, PVOID Actor, vector3* ViewPoint) {

		auto fn = reinterpret_cast<bool(__fastcall*)(PVOID PlayerController, PVOID Actor, vector3 * ViewPoint)>(los);
		return fn(PlayerController, Actor, ViewPoint);
	}
}

namespace cheat_esp
{
	void draw_esp(uintptr_t actor)
	{
		structs::vector3 root, head;
		structs::get_bone_loc(actor, 0, &root);
		structs::world_to_screen(structs::vector3(root.x, root.y, root.z), &root);

		if (settings::draw_distance)
		{

		}
	}
}