#include "scene/component/Collider.h"

#include <physics/Collision.h>

namespace engine::Component {

    void Collider::init(BaseGameObject* gor, Transform* t, PointerArrayList<Collider>* cg) {
        go_reference = gor;
        transform = t;
        collision_group = cg;
        group_index = collision_group->size();
        collision_group->push_back(this);

        aabbs = new PointerArrayList<AABB>();
        points = new PointerArrayList<Point>();

        prev_collisions = new PointerArrayList<BaseGameObject>();
        current_collisions = new PointerArrayList<CollisionResult>();
    }

    void Collider::shutdown() {
        for (unsigned int i = 0; i < aabbs->size(); i++) {
            delete (*aabbs)[i];
        }
        aabbs->clear();
        delete aabbs;

        for (unsigned int i = 0; i < points->size(); i++) {
            delete (*points)[i];
        }
        points->clear();
        delete points;
    }

    void Collider::update() {
        if (type == Type::DYNAMIC) {
            // updating the game object's transform position
            velocity += acceleration;
            transform->move(velocity);

            // updating aabb and point positions
            Vec2 t_pos = transform->getPosition();
            for (unsigned int i = 0; i < aabbs->size(); i++) {
                AABB* aabb = (*aabbs)[i];
                aabb->min_x = t_pos.x + aabb->x_offset - aabb->half_width;
                aabb->max_x = t_pos.x + aabb->x_offset + aabb->half_width;
                aabb->min_y = t_pos.y + aabb->y_offset - aabb->half_height;
                aabb->max_y = t_pos.y + aabb->y_offset + aabb->half_height;
            }
            for (unsigned int i = 0; i < points->size(); i++) {
                Point* point = (*points)[i];
                point->x = t_pos.x + point->x_offset;
                point->y = t_pos.y + point->y_offset;
            }
        }
    }

    void Collider::setType(Type t) {
        if (set_type) { std::cerr << "Attempting to change collider type more than once" << std::endl; }

        type = t;
        set_type = true;
    }

    void Collider::addBoxCollider(const Vec2& offset, const Vec2& dimensions) {
        Vec2 half_d = dimensions / 2.0f;
        aabbs->push_back(new AABB{
            offset.x,
            offset.y,
            half_d.x,
            half_d.y,
            transform->getPosition().x + offset.x - half_d.x,
            transform->getPosition().x + offset.x + half_d.x,
            transform->getPosition().y + offset.y - half_d.y,
            transform->getPosition().y + offset.y + half_d.y
        });
    }

    void Collider::addPointCollider(const Vec2& offset) {
        points->push_back(new Point { 
            offset.x,
            offset.y,
            transform->getPosition().x + offset.x,
            transform->getPosition().y + offset.y
        });
    }

}
