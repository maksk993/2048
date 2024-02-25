#include "FlexibleSizes.hpp"

size_t FlexibleSizes::getSize(size_t originalSize, size_t divider) {
	return originalSize / divider;
}