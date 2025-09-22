#ifndef SIMPLEX_H
#define SIMPLEX_H

#include <array>
#include "Vector3.h"

struct Simplex
{
private:

	std::array<Vector3, 4> m_Points;
	unsigned m_size;

public:

	Simplex() : m_Points({ 0, 0, 0, 0 }), m_size(0) { }

	Simplex& operator=(std::initializer_list<Vector3> list)
	{
		for (auto v = list.begin(); v != list.end(); v++)
		{
			m_Points[std::distance(list.begin(), v)] = *v;
		}
		m_size = list.size();

		return *this;
	}

	void push_front(Vector3 point)
	{
		m_Points = { point, m_Points[0], m_Points[1], m_Points[2] };
		m_size = min(m_size + 1, 4u);
	}

	Vector3& operator[](unsigned int i) { return m_Points[i]; }
	unsigned size() const { return m_size; }

	auto begin() const { return m_Points.begin(); }
	auto end() const { return m_Points.end() - (4 - m_size); }
};

#endif
