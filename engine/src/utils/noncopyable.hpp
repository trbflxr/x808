//
// Created by FLXR on 7/15/2018.
//

#ifndef X808_NONCOPYABLE_HPP
#define X808_NONCOPYABLE_HPP

namespace xe {

	struct NonCopyable{
		NonCopyable(NonCopyable &) = delete;
        NonCopyable(NonCopyable &&) = delete;
        NonCopyable &operator=(NonCopyable &) = delete;
        NonCopyable &operator=(NonCopyable &&) = delete;

	protected:
		NonCopyable() = default;
		virtual ~NonCopyable() = default;
	};

}

#endif //X808_NONCOPYABLE_HPP
