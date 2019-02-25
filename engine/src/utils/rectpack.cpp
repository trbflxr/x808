//
// Created by FLXR on 2/25/2019.
//

#include <climits>
#include <cmath>
#include <algorithm>
#include <xe/utils/rectpack.hpp>

namespace xe {

	int32 commonIntervalLength(float i1start, float i1end, float i2start, float i2end) {
		if (i1end < i2start || i2end < i1start) {
			return 0;
		}
		return static_cast<int32>(__min(i1end, i2end) - __max(i1start, i2start));
	}

	RectPack::RectPack() :
			width(0),
			height(0) { }

	RectPack::RectPack(int32 width, int32 height, bool allowFlip) {
		init(width, height, allowFlip);
	}

	void RectPack::init(int32 width, int32 height, bool allowFlip) {
		RectPack::allowFlip = allowFlip;
		RectPack::width = width;
		RectPack::height = height;

		rect n(0, 0, width, height);

		usedRectangles.clear();

		freeRectangles.clear();
		freeRectangles.push_back(n);
	}

	void RectPack::insert(std::vector<vec2> &rects, std::vector<rect> &dst, FreeRectChoice method) {
		dst.clear();

		while (!rects.empty()) {
			int32 bestScore1 = INT_MAX;
			int32 bestScore2 = INT_MAX;
			int32 bestRectIndex = -1;
			rect bestNode;

			for (size_t i = 0; i < rects.size(); ++i) {
				int32 score1;
				int32 score2;
				rect newNode = scoreRect(static_cast<int32>(rects[i].x), static_cast<int32>(rects[i].y),
				                         method, score1, score2);

				if (score1 < bestScore1 || (score1 == bestScore1 && score2 < bestScore2)) {
					bestScore1 = score1;
					bestScore2 = score2;
					bestNode = newNode;
					bestRectIndex = static_cast<int32>(i);
				}
			}

			if (bestRectIndex == -1) {
				return;
			}

			placeRect(bestNode);
			dst.push_back(bestNode);
			rects.erase(rects.begin() + bestRectIndex);
		}
	}

	rect RectPack::insert(int32 width, int32 height, FreeRectChoice method) {
		rect newNode;

		int32 score1 = INT_MAX;
		int32 score2 = INT_MAX;

		switch (method) {
			case FreeRectChoice::BestShortSideFit: {
				findPosBestShortSideFit(width, height, score1, score2);
				break;
			}
			case FreeRectChoice::BottomLeftRule: {
				newNode = findPosBottomLeft(width, height, score1, score2);
				break;
			}
			case FreeRectChoice::ContactPointRule: {
				newNode = findPosContactPoint(width, height, score1);
				break;
			}
			case FreeRectChoice::BestLongSideFit: {
				newNode = findPosBestLongSideFit(width, height, score2, score1);
				break;
			}
			case FreeRectChoice::BestAreaFit: {
				newNode = findPosBestAreaFit(width, height, score1, score2);
				break;
			}
		}

		if (newNode.height == 0) {
			return newNode;
		}

		int32 size = static_cast<int32>(freeRectangles.size());
		for (int32 i = 0; i < size; ++i) {
			if (splitFreeNode(freeRectangles[i], newNode)) {
				freeRectangles.erase(freeRectangles.begin() + i);
				--i;
				--size;
			}
		}

		pruneFreeList();

		usedRectangles.push_back(newNode);
		return newNode;
	}

	void RectPack::placeRect(const rect &node) {
		int32 size = static_cast<int32>(freeRectangles.size());
		for (int32 i = 0; i < size; ++i) {
			if (splitFreeNode(freeRectangles[i], node)) {
				freeRectangles.erase(freeRectangles.begin() + i);
				--i;
				--size;
			}
		}

		pruneFreeList();

		usedRectangles.push_back(node);
	}

	rect RectPack::scoreRect(int32 width, int32 height, FreeRectChoice method, int32 &score1, int32 &score2) const {
		rect newNode;
		score1 = INT_MAX;
		score2 = INT_MAX;

		switch (method) {
			case FreeRectChoice::BestShortSideFit: {
				findPosBestShortSideFit(width, height, score1, score2);
				break;
			}
			case FreeRectChoice::BottomLeftRule: {
				newNode = findPosBottomLeft(width, height, score1, score2);
				break;
			}
			case FreeRectChoice::ContactPointRule: {
				newNode = findPosContactPoint(width, height, score1);
				score1 = -score1;
				break;
			}
			case FreeRectChoice::BestLongSideFit: {
				newNode = findPosBestLongSideFit(width, height, score2, score1);
				break;
			}
			case FreeRectChoice::BestAreaFit: {
				newNode = findPosBestAreaFit(width, height, score1, score2);
				break;
			}
		}

		// can't fit current rect
		if (newNode.height == 0) {
			score1 = INT_MAX;
			score2 = INT_MAX;
		}

		return newNode;
	}

	float RectPack::occupancy() const {
		int32 usedSurfaceArea = 0;
		for (const auto &r : usedRectangles) {
			usedSurfaceArea += static_cast<int32>(r.width * r.height);
		}

		return (float) usedSurfaceArea / (width * height);
	}

	int32 RectPack::contactPointScoreNode(int32 x, int32 y, int32 width, int32 height) const {
		int32 score = 0;

		if (x == 0 || x + width == width) {
			score += height;
		}
		if (y == 0 || y + height == height) {
			score += width;
		}

		for (const auto &r : usedRectangles) {
			if (r.x == x + width || r.x + r.width == x) {
				score += commonIntervalLength(r.y, r.y + r.height, y, y + height);
			}
			if (r.y == y + height || r.y + r.height == y) {
				score += commonIntervalLength(r.x, r.x + r.width, x, x + width);
			}
		}
		return score;
	}

	bool RectPack::splitFreeNode(const rect &freeNode, const rect &usedNode) {
		if (usedNode.x >= freeNode.x + freeNode.width || usedNode.x + usedNode.width <= freeNode.x ||
		    usedNode.y >= freeNode.y + freeNode.height || usedNode.y + usedNode.height <= freeNode.y)
			return false;

		if (usedNode.x < freeNode.x + freeNode.width && usedNode.x + usedNode.width > freeNode.x) {
			if (usedNode.y > freeNode.y && usedNode.y < freeNode.y + freeNode.height) {
				rect newNode = freeNode;
				newNode.height = usedNode.y - newNode.y;
				freeRectangles.push_back(newNode);
			}

			if (usedNode.y + usedNode.height < freeNode.y + freeNode.height) {
				rect newNode = freeNode;
				newNode.y = usedNode.y + usedNode.height;
				newNode.height = freeNode.y + freeNode.height - (usedNode.y + usedNode.height);
				freeRectangles.push_back(newNode);
			}
		}

		if (usedNode.y < freeNode.y + freeNode.height && usedNode.y + usedNode.height > freeNode.y) {
			if (usedNode.x > freeNode.x && usedNode.x < freeNode.x + freeNode.width) {
				rect newNode = freeNode;
				newNode.width = usedNode.x - newNode.x;
				freeRectangles.push_back(newNode);
			}

			if (usedNode.x + usedNode.width < freeNode.x + freeNode.width) {
				rect newNode = freeNode;
				newNode.x = usedNode.x + usedNode.width;
				newNode.width = freeNode.x + freeNode.width - (usedNode.x + usedNode.width);
				freeRectangles.push_back(newNode);
			}
		}

		return true;
	}

	void RectPack::pruneFreeList() {
		for (size_t i = 0; i < freeRectangles.size(); ++i) {
			for (size_t j = i + 1; j < freeRectangles.size(); ++j) {
				if (freeRectangles[i].contains(freeRectangles[j])) {
					freeRectangles.erase(freeRectangles.begin() + i);
					--i;
					break;
				}
				if (freeRectangles[j].contains(freeRectangles[i])) {
					freeRectangles.erase(freeRectangles.begin() + j);
					--j;
				}
			}
		}
	}

	rect RectPack::findPosBottomLeft(int32 width, int32 height, int32 &bestY, int32 &bestX) const {
		rect bestNode;

		bestY = INT_MAX;
		bestX = INT_MAX;

		for (const auto &r : freeRectangles) {
			if (r.width >= width && r.height >= height) {
				int32 topSideY = static_cast<int32>(r.y + height);
				if (topSideY < bestY || (topSideY == bestY && r.x < bestX)) {
					bestNode.x = r.x;
					bestNode.y = r.y;
					bestNode.width = width;
					bestNode.height = height;
					bestY = topSideY;
					bestX = static_cast<int32>(r.x);
				}
			}
			if (allowFlip && r.width >= height && r.height >= width) {
				int32 topSideY = static_cast<int32>(r.y + width);
				if (topSideY < bestY || (topSideY == bestY && r.x < bestX)) {
					bestNode.x = r.x;
					bestNode.y = r.y;
					bestNode.width = height;
					bestNode.height = width;
					bestY = topSideY;
					bestX = static_cast<int32>(r.x);
				}
			}
		}
		return bestNode;
	}

	rect RectPack::findPosBestShortSideFit(int32 width, int32 height,
	                                       int32 &bestShortSideFit, int32 &bestLongSideFit) const {

		rect bestNode;

		bestShortSideFit = INT_MAX;
		bestLongSideFit = INT_MAX;

		for (const auto &r : freeRectangles) {
			if (r.width >= width && r.height >= height) {
				int32 leftoverH = static_cast<int32>(fabsf(r.width - width));
				int32 leftoverV = static_cast<int32>(fabsf(r.height - height));
				int32 shortSideFit = __min(leftoverH, leftoverV);
				int32 longSideFit = __max(leftoverH, leftoverV);

				if (shortSideFit < bestShortSideFit ||
				    (shortSideFit == bestShortSideFit && longSideFit < bestLongSideFit)) {
					bestNode.x = r.x;
					bestNode.y = r.y;
					bestNode.width = width;
					bestNode.height = height;
					bestShortSideFit = shortSideFit;
					bestLongSideFit = longSideFit;
				}
			}

			if (allowFlip && r.width >= height && r.height >= width) {
				int32 flippedLeftoverH = static_cast<int32>(fabsf(r.width - height));
				int32 flippedLeftoverV = static_cast<int32>(fabsf(r.height - width));
				int32 flippedShortSideFit = __min(flippedLeftoverH, flippedLeftoverV);
				int32 flippedLongSideFit = __max(flippedLeftoverH, flippedLeftoverV);

				if (flippedShortSideFit < bestShortSideFit ||
				    (flippedShortSideFit == bestShortSideFit && flippedLongSideFit < bestLongSideFit)) {
					bestNode.x = r.x;
					bestNode.y = r.y;
					bestNode.width = height;
					bestNode.height = width;
					bestShortSideFit = flippedShortSideFit;
					bestLongSideFit = flippedLongSideFit;
				}
			}
		}

		return bestNode;
	}

	rect RectPack::findPosBestLongSideFit(int32 width, int32 height,
	                                      int32 &bestShortSideFit, int32 &bestLongSideFit) const {

		rect bestNode;

		bestShortSideFit = INT_MAX;
		bestLongSideFit = INT_MAX;

		for (const auto &r : freeRectangles) {
			if (r.width >= width && r.height >= height) {
				int32 leftoverH = static_cast<int32>(fabsf(r.width - width));
				int32 leftoverV = static_cast<int32>(fabsf(r.height - height));
				int32 shortSideFit = __min(leftoverH, leftoverV);
				int32 longSideFit = __max(leftoverH, leftoverV);

				if (longSideFit < bestLongSideFit ||
				    (longSideFit == bestLongSideFit && shortSideFit < bestShortSideFit)) {
					bestNode.x = r.x;
					bestNode.y = r.y;
					bestNode.width = width;
					bestNode.height = height;
					bestShortSideFit = shortSideFit;
					bestLongSideFit = longSideFit;
				}
			}

			if (allowFlip && r.width >= height && r.height >= width) {
				int32 leftoverH = static_cast<int32>(fabsf(r.width - height));
				int32 leftoverV = static_cast<int32>(fabsf(r.height - width));
				int32 shortSideFit = __min(leftoverH, leftoverV);
				int32 longSideFit = __max(leftoverH, leftoverV);

				if (longSideFit < bestLongSideFit ||
				    (longSideFit == bestLongSideFit && shortSideFit < bestShortSideFit)) {
					bestNode.x = r.x;
					bestNode.y = r.y;
					bestNode.width = height;
					bestNode.height = width;
					bestShortSideFit = shortSideFit;
					bestLongSideFit = longSideFit;
				}
			}
		}

		return bestNode;
	}

	rect RectPack::findPosBestAreaFit(int32 width, int32 height, int32 &bestAreaFit, int32 &bestShortSideFit) const {
		rect bestNode;

		bestAreaFit = INT_MAX;
		bestShortSideFit = INT_MAX;

		for (const auto &r : freeRectangles) {
			int32 areaFit = static_cast<int32>(r.width * r.height - width * height);

			if (r.width >= width && r.height >= height) {
				int32 leftoverH = static_cast<int32>(fabsf(r.width - width));
				int32 leftoverV = static_cast<int32>(fabsf(r.height - height));
				int32 shortSideFit = __min(leftoverH, leftoverV);

				if (areaFit < bestAreaFit || (areaFit == bestAreaFit && shortSideFit < bestShortSideFit)) {
					bestNode.x = r.x;
					bestNode.y = r.y;
					bestNode.width = width;
					bestNode.height = height;
					bestShortSideFit = shortSideFit;
					bestAreaFit = areaFit;
				}
			}

			if (allowFlip && r.width >= height && r.height >= width) {
				int32 leftoverH = static_cast<int32>(fabsf(r.width - height));
				int32 leftoverV = static_cast<int32>(fabsf(r.height - width));
				int32 shortSideFit = __min(leftoverH, leftoverV);

				if (areaFit < bestAreaFit || (areaFit == bestAreaFit && shortSideFit < bestShortSideFit)) {
					bestNode.x = r.x;
					bestNode.y = r.y;
					bestNode.width = height;
					bestNode.height = width;
					bestShortSideFit = shortSideFit;
					bestAreaFit = areaFit;
				}
			}
		}

		return bestNode;
	}

	rect RectPack::findPosContactPoint(int32 width, int32 height, int32 &contactScore) const {
		rect bestNode;

		contactScore = -1;

		for (const auto &r : freeRectangles) {
			if (r.width >= width && r.height >= height) {
				int32 score = contactPointScoreNode(static_cast<int32>(r.x), static_cast<int32>(r.y), width, height);
				if (score > contactScore) {
					bestNode.x = r.x;
					bestNode.y = r.y;
					bestNode.width = width;
					bestNode.height = height;
					contactScore = score;
				}
			}
			if (r.width >= height && r.height >= width) {
				int32 score = contactPointScoreNode(static_cast<int32>(r.x), static_cast<int32>(r.y), height, width);
				if (score > contactScore) {
					bestNode.x = r.x;
					bestNode.y = r.y;
					bestNode.width = height;
					bestNode.height = width;
					contactScore = score;
				}
			}
		}

		return bestNode;
	}

}
