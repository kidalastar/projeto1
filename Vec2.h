/******************************************************************************************
*	Chili DirectX Framework Version 14.03.22											  *
*	Vec2.h																				  *
*	Copyright 2014 PlanetChili.net <http://www.planetchili.net>							  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#pragma once

#include "ChiliMath.h"
#include <memory>
#include <vector>

template <typename T>
class _Vec2
{
public:
	inline			_Vec2() {}
	inline			_Vec2( T x,T y )
		:
	x( x ),
	y( y )
	{}
	inline			_Vec2( const _Vec2& vect )
		:
	_Vec2( vect.x,vect.y )
	{}
	template <typename T2>
	inline			operator _Vec2< T2 >() const
	{
		return { (T2)x,(T2)y };
	}
	inline T		LenSq() const
	{
		return *this * *this;
	}
	inline T		Len() const
	{
		return sqrt( LenSq() );
	}
	inline _Vec2&	Normalize()
	{
		const T length = Len();
		x /= length;
		y /= length;
		return *this;
	}
	inline _Vec2&	CW90()
	{
		T temp = y;
		y = -x;
		x = temp;
		return *this;
	}
	inline _Vec2&	CCW90()
	{		
		T temp = y;
		y = x;
		x = -temp;
		return *this;
	}
	inline _Vec2&	Swap( _Vec2& vect )
	{
		const _Vec2 temp = vect;
		vect = *this;
		*this = temp;
		return *this;
	}
	inline _Vec2	operator-() const
	{
		return _Vec2( -x,-y );
	}
	inline _Vec2&	operator=( const _Vec2 &rhs )
	{
		this->x = rhs.x;
		this->y = rhs.y;
		return *this;
	}
	inline _Vec2&	operator+=( const _Vec2 &rhs )
	{
		this->x += rhs.x;
		this->y += rhs.y;
		return *this;
	}
	inline _Vec2&	operator-=( const _Vec2 &rhs )
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		return *this;
	}
	//DOT PRODUCT de 2 pontos retorna a distancias entre os mesmos.
	inline T		operator*( const _Vec2 &rhs ) const
	{
		return this->x * rhs.x + this->y * rhs.y;
	}	
	inline _Vec2	operator+( const _Vec2 &rhs ) const
	{
		return _Vec2( *this ) += rhs;
	}
	inline _Vec2	operator-( const _Vec2 &rhs ) const
	{
		return _Vec2( *this ) -= rhs;
	}
	inline _Vec2&	operator*=( const T &rhs )
	{
		this->x *= rhs;
		this->y *= rhs;
		return *this;
	}
	inline _Vec2	operator*( const T &rhs ) const
	{
		return _Vec2( *this ) *= rhs;
	}
	inline _Vec2&	operator/=( const T &rhs )
	{
		this->x /= rhs;
		this->y /= rhs;
		return *this;
	}
	inline _Vec2	operator/( const T &rhs ) const
	{
		return _Vec2( *this ) /= rhs;
	}
	inline T		CrossWith( const _Vec2 &rhs ) const
	{
		return x * rhs.y - y * rhs.x;
	}
	inline _Vec2	ClosestPtOnLine( const _Vec2 &lnpt1,const _Vec2 &lnpt2 ) const
	{
		_Vec2 p1 = lnpt1;
		_Vec2 p2 = lnpt2;
		_Vec2 pointOnLine;
		if( abs( p1.x - p2.x ) > 0.0f )
		{
			if( p1.x > p2.x )
			{
				p1.Swap( p2 );
			}
			const T m = (p2.y - p1.y) / (p2.x - p1.x);
			const T b = p1.y - m * p1.x;

			if( abs( m ) > 0.0f )
			{
				T n = -1.0f / m;
				T c = this->y - this->x * n;
				pointOnLine.x = (b - c) / (n - m);
				pointOnLine.y = m * pointOnLine.x + b;
			}
			else
			{
				pointOnLine.x = this->x;
				pointOnLine.y = p1.y;
			}
		}
		else
		{
			pointOnLine.x = p1.x;
			pointOnLine.y = this->y;
		}
		return pointOnLine;
	}
	inline bool		IsInsideRect( const _Vec2 &p1,const _Vec2 & p2 ) const
	{
		const T medianX = (p1.x + p2.x) / 2.0f;
		const T medianY = (p1.y + p2.y) / 2.0f;
		return abs( medianX - x ) <= abs( medianX - p1.x ) &&
			abs( medianY - y) <= abs( medianY - p1.y );
	}
	inline bool		operator==( const _Vec2 &rhs ) const
	{
		return x == rhs.x && y == rhs.y;
	}
	inline bool		operator!=(const _Vec2 &rhs) const
	{
		return !(*this == rhs);
	}
	inline _Vec2	MidpointWith( const _Vec2& p2 ) const
	{
		return _Vec2( (x + p2.x) / 2.0f,(y + p2.y) / 2.0f );
	}
	inline int sgn(T valor) const
	{
		// Equivalente a  (x < 0 ?  -1 : 1)
		return (T)(((T)0.0 <= valor) - (valor < (T)0.0));
	}
	//make work for T
	inline _Vec2  Rotation(const float angle) const
	{
		_Vec2<float> result;
		const float cosine = cosf(angle);
		const float sine =   sinf(angle);
		result.x = x * cosine - y * sine;
		result.y = x * sine + y * cosine;
		return result;
	}
	inline std::vector< _Vec2<T>> CalculateIntersecctionPoints(_Vec2<T> pos, _Vec2<T> p1, _Vec2<T> p2,float r)
	{
		std::vector<_Vec2<T>> points;
		const _Vec2<T>  d = p2 - p1;
		const float dr2 = d.LenSq();
		const float D = (p1 - pos).CrossWith(p2 - pos);
		const float discriminant = sq(r) * dr2 - sq(D);

		if (discriminant >= (T)0.0)
		{
			//calculate points of intersection
			const float sqrtDisc = sq(discriminant);
			const float lhsx = D * d.y;
			const float rhsx = sgn(d.y) * d.x * sqrtDisc;
			const float lhsy = -D * d.x;
			const float rhsy = abs(d.y)*sqrtDisc;
			points.push_back(_Vec2<T>{(lhsx + rhsx) / dr2, (lhsy + rhsy) / dr2}+pos);
			if (discriminant > (T)0.0)
			{
				points.push_back(_Vec2<T>{(lhsx + rhsx) / dr2, (lhsy + rhsy) / dr2}+pos);
			}
		}
		return  points;
	}
	
public:
	T x;
	T y;
};

typedef _Vec2< float > Vec2;
typedef _Vec2< double > Ved2;