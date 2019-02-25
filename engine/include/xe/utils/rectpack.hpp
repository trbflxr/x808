//
// Created by FLXR on 2/25/2019.
//

#ifndef X808_RECTPACK_HPP
#define X808_RECTPACK_HPP


#include <vector>
#include <xe/common.hpp>
#include <xe/xeint.hpp>
#include <xe/math/rect.hpp>

namespace xe {

	enum class FreeRectChoice {
		BestShortSideFit,
		BestLongSideFit,
		BestAreaFit,
		BottomLeftRule,
		ContactPointRule
	};

	class XE_API RectPack {
	public:
		explicit RectPack();
		explicit RectPack(int32 width, int32 height, bool allowFlip = true);

		void init(int32 width, int32 height, bool allowFlip = true);

		void insert( std::vector<vec2> &rects, std::vector<rect> &dst, FreeRectChoice method);
		rect insert(int32 width, int32 height, FreeRectChoice method);

		float occupancy() const;

	private:
		rect scoreRect(int32 width, int32 height, FreeRectChoice method, int32 &score1, int32 &score2) const;

		void placeRect(const rect &node);

		int32 contactPointScoreNode(int32 x, int32 y, int32 width, int32 height) const;

		rect findPosBottomLeft(int32 width, int32 height, int32 &bestY, int32 &bestX) const;
		rect findPosBestShortSideFit(int32 width, int32 height, int32 &bestShortSideFit, int32 &bestLongSideFit) const;
		rect findPosBestLongSideFit(int32 width, int32 height, int32 &bestShortSideFit, int32 &bestLongSideFit) const;
		rect findPosBestAreaFit(int32 width, int32 height, int32 &bestAreaFit, int32 &bestShortSideFit) const;
		rect findPosContactPoint(int32 width, int32 height, int32 &contactScore) const;

		bool splitFreeNode(const rect &freeNode, const rect &usedNode);

		void pruneFreeList();

	private:
		int32 width;
		int32 height;

		bool allowFlip;

		std::vector<rect> usedRectangles;
		std::vector<rect> freeRectangles;
	};

}


#endif //X808_RECTPACK_HPP
