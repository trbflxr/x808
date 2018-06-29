//
// Created by FLXR on 6/29/2018.
//

#ifndef X808_TIMESTEP_HPP
#define X808_TIMESTEP_HPP


namespace xe {

	struct TimeStep {
	public:
		inline explicit TimeStep(float initialTime) :
				timeStep(0.0f), lastTime(initialTime) { }

		inline void update(float currentTime) {
			timeStep = currentTime - lastTime;
			lastTime = currentTime;
		}

		inline float getMillis() const { return timeStep; }
		inline float getSeconds() const { return timeStep * 0.001f; }

	private:
		float timeStep;
		float lastTime;
	};

}

#endif //X808_TIMESTEP_HPP
