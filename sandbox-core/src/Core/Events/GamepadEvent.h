#pragma once

#ifndef SB_PRECOMPILED_HEADER
#include <sstream>
#endif

#include "Core/Events/Event.h"

namespace sb {

	class GamepadConnectedEvent : public Event {

	public:

		GamepadConnectedEvent(int id)
			: m_ID(id)
		{}

		inline int GetGamepadID() const { return m_ID; }

		std::string ToString() const override {

			std::stringstream ss;
			ss << "GamepadConnected: " << m_ID;
			return ss.str();
		}

		EVENT_CLASS_TYPE(GamepadConnected)
		EVENT_CLASS_CATEGORY(EventCategoryGamepad | EventCategoryInput)

	private:

		int m_ID;
	};

	class GamepadDisconnectedEvent : public Event {

	public:

		GamepadDisconnectedEvent(int id)
			: m_ID(id)
		{}

		inline int GetGamepadID() const { return m_ID; }

		std::string ToString() const override {

			std::stringstream ss;
			ss << "GamepadDisconnected: " << m_ID;
			return ss.str();
		}

		EVENT_CLASS_TYPE(GamepadDisconnected)
		EVENT_CLASS_CATEGORY(EventCategoryGamepad | EventCategoryInput)

	private:

		int m_ID;
	};
}
