//
// Created by FLXR on 2/22/2019.
//

#ifndef X808_RAMP_HPP
#define X808_RAMP_HPP


#include <vector>
#include <functional>

namespace xe {

	template<class T>
	class Ramp {
	public:
		explicit Ramp(const std::vector<std::pair<float, T>> &states,
		              const std::function<T(const T &, const T &, float)> &transitionFunction,
		              float duration) :

				duration(duration),
				totalTime(0.0f),
				time(0.0f),
				targetTime(0.0f),
				currentState(0),
				targetState(1),
				transitionFunction(transitionFunction),
				states(states) {

			value = states[currentState].second;

			if (states.size() > 1) {
				targetTime = states[targetState].first * duration;
			}
		}

		void update(float delta) {
			if (states.size() == 1 || totalTime >= duration) return;

			totalTime += delta;

			if (time <= 1.0f) {
				time += delta / targetTime;

				value = transitionFunction(states[currentState].second, states[targetState].second, time);

			} else {
				if (states.size() > targetState + 1) {
					currentState = targetState;
					targetState++;

					targetTime = states[targetState].first * duration - totalTime;
					time = 0.0f;
				}
			}
		}

		inline const T &getValue() const { return value; }

	private:
		float duration;
		float totalTime;

		float time;
		float targetTime;

		T value;

		size_t currentState;
		size_t targetState;

		std::function<T(const T &, const T &, float)> transitionFunction;
		std::vector<std::pair<float, T>> states;
	};

}


#endif //X808_RAMP_HPP
