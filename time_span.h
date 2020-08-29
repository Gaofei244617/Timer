#pragma once

#include <chrono>

class TimeCount
{
	using TimePoint = std::chrono::high_resolution_clock::time_point;

private:
	std::chrono::nanoseconds _span;

public:
	TimeCount() :_span(0) {}
	TimeCount(const std::chrono::nanoseconds& span) :_span(span) {}

	inline long long getSeconds()
	{
		return _span.count() / 1000000000;
	}

	inline long long getMilliSeconds()
	{
		return _span.count() / 1000000;
	}

	inline long long getMicroSeconds()
	{
		return _span.count() / 1000;
	}

	inline long long getNanoSeconds()
	{
		return _span.count();
	}

	inline static TimePoint now()
	{
		return std::chrono::high_resolution_clock::now();
	}

	inline static TimeCount span(const TimePoint& tag1, const TimePoint& tag2)
	{
		return TimeCount{ tag2 - tag1 };
	}
};

