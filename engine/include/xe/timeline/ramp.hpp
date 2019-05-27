//
// Created by FLXR on 2/22/2019.
//

#ifndef X808_RAMP_HPP
#define X808_RAMP_HPP


#include <vector>
#include <tuple>
#include <functional>
#include <xe/utils/random.hpp>
#include <xe/utils/assert.hpp>

namespace xe {

  template<typename T>
  class Ramp {
  public:
    explicit Ramp(const std::vector<std::tuple<float, T, T>> &states,
                  const std::function<T(const T &, const T &, float)> &transitionFunction) :
        hasChange(true),
        hasStates(states.size() > 1),
        duration(0.0f),
        transitionFunction(transitionFunction),
        states(states) {

      XE_ASSERT(!states.empty(), "Must have at least one state!");
    }

    explicit Ramp(const std::vector<std::pair<float, T>> &states,
                  const std::function<T(const T &, const T &, float)> &transitionFunction) :
        hasChange(false),
        hasStates(states.size() > 1),
        duration(0.0f),
        transitionFunction(transitionFunction) {

      XE_ASSERT(!states.empty(), "Must have at least one state!");

      for (const auto &s : states) {
        Ramp::states.emplace_back(s.first, s.second, s.second);
      }
    }

    inline const std::vector<std::tuple<float, T, T>> &getStates() const { return states; }

    inline void setStates(const std::vector<std::tuple<float, T, T>> &states) {
      hasStates = states.size() > 1;

      Ramp::states = states;

      XE_ASSERT(!states.empty(), "Must have at least one state!");
    }

    void reset(float duration) {
      Ramp::duration = duration;
      time = 0.0f;
      totalTime = 0.0f;
      targetTime = 0.0f;
      index = 0;

      if (hasChange) {
        const T cv = std::get<1>(states[index]);
        const T cc = std::get<2>(states[index]);

        value = random::next<T>(cv - cc, cv + cc);
        currentValue = value;

        if (states.size() > 1) {
          targetTime = std::get<0>(states[index + 1]) * duration;

          const T tv = std::get<1>(states[index + 1]);
          const T tc = std::get<2>(states[index + 1]);

          targetValue = random::next<T>(tv - tc, tv + tc);
        }
      } else {
        value = std::get<1>(states[index]);
        currentValue = value;

        if (states.size() > 1) {
          targetTime = std::get<0>(states[index + 1]) * duration;
          targetValue = std::get<1>(states[index + 1]);
        }
      }
    }

    bool fixedUpdate(float delta) {
      if (!hasStates || states.size() == 1 || totalTime >= duration) return false;

      totalTime += delta;

      if (time <= 1.0f) {
        time += delta / targetTime;

        value = transitionFunction(currentValue, targetValue, time);

      } else {
        if (states.size() > index + 2) {
          index++;

          targetTime = std::get<0>(states[index + 1]) * duration - totalTime;
          time = 0.0f;

          currentValue = targetValue;
          if (hasChange) {
            const T tv = std::get<1>(states[index + 1]);
            const T tc = std::get<2>(states[index + 1]);

            targetValue = random::next<T>(tv - tc, tv + tc);
          } else {
            targetValue = std::get<1>(states[index + 1]);
          }
        }
      }

      return true;
    }

    inline const T &getValue() const { return value; }

    inline bool isHasChange() const { return hasChange; }
    inline void setHasChange(bool hasChange) { Ramp::hasChange = hasChange; }

    static T lerp(const T &s, const T &e, float t);
    static T lerpc1(const T &s, const T &e, float t);

  private:
    bool hasChange;
    bool hasStates;

    float duration;
    float totalTime;

    float time;
    float targetTime;

    T value;

    T currentValue;
    T targetValue;

    size_t index;

    std::function<T(const T &, const T &, float)> transitionFunction;
    std::vector<std::tuple<float, T, T>> states;
  };

}


#endif //X808_RAMP_HPP
