//
// Created by FLXR on 7/1/2018.
//

#ifndef X808_COMPONENT_HPP
#define X808_COMPONENT_HPP


namespace xe {

	class Entity;

	class Component {
	public:
		inline virtual Entity *getEntity() { return entity; }
		inline virtual const char *getType() const { return nullptr; }

	protected:
		Entity *entity;
	};

}

#endif //X808_COMPONENT_HPP
