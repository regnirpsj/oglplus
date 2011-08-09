/**
 *  .file oglplus/auxiliary/base_range.hpp
 *  .brief Base class for ranges
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_AUX_BASE_RANGE_1107121519_HPP
#define OGLPLUS_AUX_BASE_RANGE_1107121519_HPP

#include <cassert>
#include <iterator>

namespace oglplus {
namespace aux {

template <typename Context, typename Element>
class BaseRange
{
private:
	Context _context;
	GLuint _current, _count;
public:
	BaseRange(Context context, GLuint current, GLuint count)
	 : _context(context)
	 , _current(current)
	 , _count(count)
	{
		assert(current <= count);
	}

	BaseRange(BaseRange&& tmp)
	 : _context(std::move(tmp._context))
	 , _current(tmp._current)
	 , _count(tmp._count)
	{ }

	bool Empty(void) const
	{
		return _current == _count;
	}

	GLuint Size(void) const
	{
		return _count - _current;
	}

	void Next(void)
	{
		assert(!Empty());
		++_current;
	}

	void StepFront(void)
	{
		Next();
	}

	Element Front(void)
	{
		assert(!Empty());
		return Element(_context, _current);
	}
};

template <typename Iterator>
class IterRange
{
private:
	Iterator _pos, _end;
public:
	IterRange(Iterator begin, Iterator end)
	 : _pos(begin)
	 , _end(end)
	{ }

	bool Empty(void) const
	{
		return _pos == _end;
	}

	GLuint Size(void) const
	{
		return _end - _pos;
	}

	void Next(void)
	{
		assert(!Empty());
		++_pos;
	}

	void StepFront(void)
	{
		Next();
	}

	typename std::iterator_traits<Iterator>::reference Front(void)
	{
		assert(!Empty());
		return *_pos;
	}
};

template <typename Element>
class ArrayRange
{
private:
	typedef std::vector<GLuint>::const_iterator iterator;
	iterator _pos;
	iterator _end;
public:
	ArrayRange(iterator i, iterator e)
	 : _pos(i)
	 , _end(e)
	{ }

	bool Empty(void) const
	{
		return _pos == _end;
	}

	GLuint Size(void) const
	{
		return _end - _pos;
	}

	void Next(void)
	{
		assert(!Empty());
		++_pos;
	}

	void StepFront(void)
	{
		Next();
	}

	Element Front(void)
	{
		assert(!Empty());
		return Element(*_pos);
	}
};

} // namespace aux
} // namespace oglplus

#endif // include guard