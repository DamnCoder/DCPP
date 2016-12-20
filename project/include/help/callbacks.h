/*
 * callbacks.h
 *
 *  Created on: 25 de jul. de 2016
 *      Author: jorge
 */

#ifndef HELP_CALLBACKS_H_
#define HELP_CALLBACKS_H_

#include <functional>

namespace dc
{
	struct TMouseData
	{
	};
	typedef std::function<void(const TMouseData& mouseData)>	TMouseAction;
	typedef std::function<void(void)> 							TAction;

	struct TActionFunctor
	{
	public:
		TActionFunctor(){}
		TActionFunctor(const TAction& action) : m_action(action) {}
		virtual ~TActionFunctor(){}

	public:
		void operator()()
		{
			m_action();
		}

		const bool operator==(const TActionFunctor& other) const
		{
			return (*this == other);
		}

	private:
		TAction m_action;
	};
}

#endif /* HELP_CALLBACKS_H_ */
