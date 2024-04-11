#include "Stopwatch.h"

#include "Debug.h"

using ms = std::chrono::milliseconds;
using dsec = std::chrono::duration<double>;

void Stopwatch::start()
{
	if (m_HasStarted)
		Debug::printMessage(*this, "Restarting stopwatch!", DebugSeverityLevel::MEDIUM);

	m_Start = CLOCK::now();

	m_HasStarted = true;
}

const double& Stopwatch::stop()
{
	if (!m_HasStarted)
	{
		Debug::printMessage(*this, "The stopwatch wasn't running!", DebugSeverityLevel::MEDIUM);
		return 0.0;
	}

	m_End = CLOCK::now();

	dsec durationInSeconds = m_End - m_Start;

	m_TimeElapsed = durationInSeconds.count();
	m_HasStarted = false;

	return m_TimeElapsed;
}

const double& Stopwatch::lap()
{
	m_End = CLOCK::now();

	dsec durationInSeconds = m_End - m_Start;

	m_TimeElapsed = durationInSeconds.count();

	m_Start = m_End;

	return m_TimeElapsed;
}

const double& Stopwatch::checkpoint()
{
	m_End = CLOCK::now();

	dsec durationInSeconds = m_End - m_Start;

	m_TimeElapsed = durationInSeconds.count();

	return m_TimeElapsed;
}

const bool& Stopwatch::hasStarted() const
{
	return m_HasStarted;
}

const double& Stopwatch::getTimeElapsed() const
{
	return m_TimeElapsed;
}
