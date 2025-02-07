#include "Ball.hpp"
#include <cmath>

Ball::Ball() = default;

Ball::Ball(double radius, Color color) {
    this->radius = radius;
    this->color = color;
}
    
/**
 * Задает скорость объекта
 * @param velocity новое значение скорости
 */
void Ball::setVelocity(const Velocity& velocity) {
    this->velocity = velocity;
}

/*
 * @return скорость объекта
 */
Velocity Ball::getVelocity() const {
    return this->velocity;
}

/**
 * @brief Выполняет отрисовку объекта
 * @details объект Ball абстрагирован от конкретного
 * способа отображения пикселей на экране. Он "знаком"
 * лишь с интерфейсом, который предоставляет Painter
 * Рисование выполняется путем вызова painter.draw(...)
 * @param painter контекст отрисовки
 */
void Ball::draw(Painter& painter) const {
    painter.draw(Ball::getCenter(), Ball::getRadius(), Color::Color());
}

/**
 * Задает координаты центра объекта
 * @param center новый центр объекта
 */
void Ball::setCenter(const Point& center) {
    this->center = center;
}


/**
 * @return центр объекта
 */
Point Ball::getCenter() const {
    return this->center;
}

/**
 * @brief Возвращает радиус объекта
 * @details обратите внимание, что метод setRadius()
 * не требуется
 */
double Ball::getRadius() const {
    return this->radius;
}

/**
 * @brief Возвращает массу объекта
 * @details В нашем приложении считаем, что все шары
 * состоят из одинакового материала с фиксированной
 * плотностью. В этом случае масса в условных единицах
 * эквивалентна объему: PI * radius^3 * 4. / 3.
 */
double Ball::getMass() const {
    return M_PI * std::powf(getRadius(), 3) * 4. / 3;
}

void Ball::setCollidable(const bool& isCollidable){
    this->isCollidable = isCollidable;
}


bool Ball::getCollidable() const{
    return this->isCollidable;
}