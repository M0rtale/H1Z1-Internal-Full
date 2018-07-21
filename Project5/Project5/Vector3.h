/**
 * Rainbow Six: Siege SDK
 * Copyright (C) 2017 RangeMachine
 */

#pragma once

#include <cmath>

namespace Engine
{
	class Vector3
	{
		public:
			float x;
			float y;
			float z;

			Vector3();
			Vector3(float x, float y, float z);

			Vector3 operator+(const Vector3& vector) const;
			Vector3 operator-(const Vector3& vector) const;
			Vector3 operator-() const;
			Vector3 operator*(float number) const;
			Vector3 operator/(float number) const;

			Vector3& operator+=(const Vector3& vector);
			Vector3& operator-=(const Vector3& vector);
			Vector3& operator*=(float number);
			Vector3& operator/=(float number);

			bool operator==(const Vector3& vector) const;
			bool operator!=(const Vector3& vector) const;

			inline float Dot(const Vector3& vector)
			{
				return x * vector.x + y * vector.y + z * vector.z;
			}

			inline float Distance(const Vector3& vector)
			{
				return sqrt(
					(x - vector.x) * (x - vector.x) +
					(y - vector.y) * (y - vector.y) +
					(z - vector.z) * (z - vector.z));
			}

			inline float Length()
			{
				return sqrt(
					x * x +
					y * y +
					z * z);
			}
	};

	inline bool Vector3::operator==(const Vector3& vector) const
	{
		return x == vector.x && y == vector.y && z == vector.z;
	}

	inline bool Vector3::operator!=(const Vector3& vector) const
	{
		return x != vector.x || y != vector.y || z != vector.z;
	}

	inline Vector3 Vector3::operator+(const Vector3& vector) const
	{
		return Vector3(x + vector.x, y + vector.y, z + vector.z);
	}

	inline Vector3 Vector3::operator-(const Vector3& vector) const
	{
		return Vector3(x - vector.x, y - vector.y, z - vector.z);
	}

	inline Vector3 Vector3::operator-() const
	{
		return Vector3(-x, -y, -z);
	}

	inline Vector3 Vector3::operator*(float number) const
	{
		return Vector3(x * number, y * number, z * number);
	}

	inline Vector3 Vector3::operator/(float number) const
	{
		return Vector3(x / number, y / number, z / number);
	}
}