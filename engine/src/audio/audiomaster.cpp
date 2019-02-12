//
// Created by FLXR on 2/12/2019.
//

#include <al/al.h>
#include <audio/alcommon.hpp>
#include <xe/utils/logger.hpp>
#include <xe/audio/audiomaster.hpp>

namespace xe {

	int32 distanceModelToAl(DistanceModel model) {
		switch (model) {
			case DistanceModel::Inverse: return AL_INVERSE_DISTANCE;
			case DistanceModel::InverseClamped: return AL_INVERSE_DISTANCE_CLAMPED;
			case DistanceModel::Linear: return AL_LINEAR_DISTANCE;
			case DistanceModel::LinearClamped: return AL_LINEAR_DISTANCE_CLAMPED;
			case DistanceModel::Exponent: return AL_EXPONENT_DISTANCE;
			case DistanceModel::ExponentClamped: return AL_EXPONENT_DISTANCE_CLAMPED;
			default: return 0;
		}
		return 0;
	}

	void AudioMaster::setDistanceModel(DistanceModel model) {
		alCall(alDistanceModel(distanceModelToAl(model)));
	}

}
