//
// Created by FLXR on 7/7/2018.
//

#ifndef X808_ECS_HPP
#define X808_ECS_HPP


#include <map>
#include "ecscomponent.hpp"
#include "ecssystem.hpp"


namespace xe {

	class XE_API ECS {
	public:
		ECS() = default;
		virtual ~ECS();

		///entity methods
		EntityHandle makeEntity(BaseECSComponent **components, const uint *componentIDs, size_t numComponents);
		void removeEntity(EntityHandle handle);

		template<class A>
		EntityHandle makeEntity(A &c0) {
			BaseECSComponent *components[] = {&c0};
			uint componentIDs[] = {A::ID};
			return makeEntity(components, componentIDs, 1);
		}

		template<class A, class B>
		EntityHandle makeEntity(A &c0, B &c1) {
			BaseECSComponent *components[] = {&c0, &c1};
			uint componentIDs[] = {A::ID, B::ID};
			return makeEntity(components, componentIDs, 2);
		}

		template<class A, class B, class C>
		EntityHandle makeEntity(A &c0, B &c1, C &c2) {
			BaseECSComponent *components[] = {&c0, &c1, &c2};
			uint componentIDs[] = {A::ID, B::ID, C::ID};
			return makeEntity(components, componentIDs, 3);
		}

		template<class A, class B, class C, class D>
		EntityHandle makeEntity(A &c0, B &c1, C &c2, D &c3) {
			BaseECSComponent *components[] = {&c0, &c1, &c2, &c3};
			uint componentIDs[] = {A::ID, B::ID, C::ID, D::ID};
			return makeEntity(components, componentIDs, 4);
		}

		template<class A, class B, class C, class D, class E>
		EntityHandle makeEntity(A &c0, B &c1, C &c2, D &c3, E &c4) {
			BaseECSComponent *components[] = {&c0, &c1, &c2, &c3, &c4};
			uint componentIDs[] = {A::ID, B::ID, C::ID, D::ID, E::ID};
			return makeEntity(components, componentIDs, 5);
		}

		template<class A, class B, class C, class D, class E, class F>
		EntityHandle makeEntity(A &c0, B &c1, C &c2, D &c3, E &c4, F &c5) {
			BaseECSComponent *components[] = {&c0, &c1, &c2, &c3, &c4, &c5};
			uint componentIDs[] = {A::ID, B::ID, C::ID, D::ID, E::ID, F::ID};
			return makeEntity(components, componentIDs, 6);
		}

		template<class A, class B, class C, class D, class E, class F, class G>
		EntityHandle makeEntity(A &c0, B &c1, C &c2, D &c3, E &c4, F &c5, G &c6) {
			BaseECSComponent *components[] = {&c0, &c1, &c2, &c3, &c4, &c5, &c6};
			uint componentIDs[] = {A::ID, B::ID, C::ID, D::ID, E::ID, F::ID, G::ID};
			return makeEntity(components, componentIDs, 7);
		}

		template<class A, class B, class C, class D, class E, class F, class G, class H>
		EntityHandle makeEntity(A &c0, B &c1, C &c2, D &c3, E &c4, F &c5, G &c6, H &c7) {
			BaseECSComponent *components[] = {&c0, &c1, &c2, &c3, &c4, &c5, &c6, &c7};
			uint componentIDs[] = {A::ID, B::ID, C::ID, D::ID, E::ID, F::ID, G::ID, H::ID};
			return makeEntity(components, componentIDs, 8);
		}

		template<class A, class B, class C, class D, class E, class F, class G, class H, class I>
		EntityHandle makeEntity(A &c0, B &c1, C &c2, D &c3, E &c4, F &c5, G &c6, H &c7, I &c8) {
			BaseECSComponent *components[] = {&c0, &c1, &c2, &c3, &c4, &c5, &c6, &c7, &c8};
			uint componentIDs[] = {A::ID, B::ID, C::ID, D::ID, E::ID, F::ID, G::ID, H::ID, I::ID};
			return makeEntity(components, componentIDs, 9);
		}

		template<class A, class B, class C, class D, class E, class F, class G, class H, class I, class J>
		EntityHandle makeEntity(A &c0, B &c1, C &c2, D &c3, E &c4, F &c5, G &c6, H &c7, I &c8, J &c9) {
			BaseECSComponent *components[] = {&c0, &c1, &c2, &c3, &c4, &c5, &c6, &c7, &c8, &c9};
			uint componentIDs[] = {A::ID, B::ID, C::ID, D::ID, E::ID, F::ID, G::ID, H::ID, I::ID, J::ID};
			return makeEntity(components, componentIDs, 10);
		}


		///component methods
		template<class Component>
		inline void addComponent(EntityHandle entity, Component *component) {
			addComponentInternal(entity, handleToEntity(entity), Component::ID, component);
		}

		template<class Component>
		bool removeComponent(EntityHandle entity) {
			return removeComponentInternal(entity, Component::ID);
		}

		template<class Component>
		Component *getComponent(EntityHandle entity) {
			return (Component *) getComponentInternal(handleToEntity(entity), components[Component::ID],
			                                          Component::ID);
		}

		///system methods
		void updateSystems(ECSSystemList &systems, float delta);

		NULL_COPY_AND_ASSIGN(ECS);


	private:
		inline std::pair<uint, std::vector<std::pair<uint, uint>>> *handleToRawType(EntityHandle handle) {
			return (std::pair<uint, std::vector<std::pair<uint, uint>>> *) handle;
		}

		inline uint handleToEntityIndex(EntityHandle handle) {
			return handleToRawType(handle)->first;
		}

		inline std::vector<std::pair<uint, uint> > &handleToEntity(EntityHandle handle) {
			return handleToRawType(handle)->second;
		}

		void deleteComponent(uint componentID, uint index);

		bool removeComponentInternal(EntityHandle handle, uint componentID);

		void addComponentInternal(EntityHandle handle,
		                          std::vector<std::pair<uint, uint>> &entity,
		                          uint componentID,
		                          BaseECSComponent *component);

		BaseECSComponent *getComponentInternal(std::vector<std::pair<uint, uint>> &entityComponents,
		                                       std::vector<uint8> &array,
		                                       uint componentID);

		void updateSystemWithMultipleComponents(uint index, ECSSystemList &systems, float delta,
		                                        const std::vector<uint> &componentTypes,
		                                        std::vector<BaseECSComponent *> &componentParam,
		                                        std::vector<std::vector<uint8> *> &componentArrays);

		uint findLeastCommonComponent(const std::vector<uint> &componentTypes,
		                              const std::vector<uint> &componentFlags);


	private:
		std::vector<BaseECSSystem *> systems;
		std::map<uint, std::vector<uint8>> components;
		std::vector<std::pair<uint, std::vector<std::pair<uint, uint>>> *> entities;
	};

}


#endif //X808_ECS_HPP
