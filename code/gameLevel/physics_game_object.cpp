#include "physics_game_object.h"

#include <QTimer>

#include "enums/file_keys_enum.h"
#include "enums/sprites_names_enum.h"

/*!
 * \brief PhysicsGameObject::PhysicsGameObject
 * Constructor
 * \param file file with the object's data
 */
PhysicsGameObject::PhysicsGameObject(file::FileManager file) : SimpleGameObject()
{
    using namespace file;
    _level_file = file;
    _main_link = "../" + file.GetStringValue(FileKeys::MainLink);
    SetAllSprites();
    if (_simple_sprites.size() != 0)
    {
        setPixmap(_simple_sprites[cur_sprite]);
        int width = file.GetByWidthRatio(FileKeys::Width);
        SetSize(abs(width), file.GetByHeightRatio(FileKeys::Height));
        if (width < 0)
            CheckRepresentation(false);
        _speed = abs(width)/8;
    }
    setPos(file.GetByWidthRatio(FileKeys::X),
           file.GetByHeightRatio(FileKeys::Y));
    setZValue(file.GetRealValue(FileKeys::ZValue));

    _health = file.GetRealValue(FileKeys::Health);

}

PhysicsGameObject::~PhysicsGameObject()
{
    for (int  i = 0; i < _arrows.size(); i++)
    {
        _arrows[i]->deleteLater();
    }
    _arrows.clear();

}

void PhysicsGameObject::SetAllSprites()
{
    using namespace file;
    using namespace sprites;

    FileManager file(_main_link + "/sprites.txt");

    _sprites_count = file.GetRealValue(GetSpriteName(SpritesNames::Count));
    cur_sprite = 0;
    for (int i = 1; i <= _sprites_count; i++)
    {
        _simple_sprites.push_back("../" + file.GetStringValue(GetSpriteName(SpritesNames::Simple) + QString::number(i)));
    }

    shoot_sprite ="../" + file.GetStringValue(GetSpriteName(SpritesNames::Shoot));
    jump_sprite = "../" + file.GetStringValue(GetSpriteName(SpritesNames::Jump));
    strike_sprite = "../" + file.GetStringValue(GetSpriteName(SpritesNames::Strike));

}

void PhysicsGameObject::NextSimpleSprite()
{
    if (cur_sprite >= _sprites_count - 1 || cur_sprite < 0)
        cur_sprite = 0;
    SetPixmap(_simple_sprites[cur_sprite++]);
}

/*!
 * \brief PhysicsGameObject::CheckColliderForGround
 * \return true if \param ground is appropriate ground
 * false otherwise
 */
bool PhysicsGameObject::IsAppropriateGround(QGraphicsItem * ground)
{
    if (y() + _height >= ground->y() && y() + _height/2 <= ground->y()
            && (GetRightX() - _width/2 <= ground->x() + ground->boundingRect().width()
            && GetLeftX() + _width/2 >= ground->x()))
    {
        setY(ground->y() - _height);
        while (!collidesWithItem(ground) && y() + _height < ground->y())
            moveBy(0, 1);

        isGround = true;
        return true;
    }

    return false;
}

void PhysicsGameObject::PrevSimpleSprite()
{
    if (cur_sprite < 0)
        cur_sprite = _sprites_count - 1;
    else if (cur_sprite > _sprites_count - 1)
        cur_sprite = _sprites_count - 1;
    SetPixmap(_simple_sprites[cur_sprite--]);
}

void PhysicsGameObject::SwitchOnSword()
{
    WeaponWasChange(false);
    cur_sprite = 0;
    SetPixmap(_simple_sprites[cur_sprite]);
}

void PhysicsGameObject::SwitchOnBow()
{
    WeaponWasChange(true);
    SetPixmap(shoot_sprite);
}

void PhysicsGameObject::RightMove()
{
    MoveBy(_speed, 0);
}

void PhysicsGameObject::LeftMove()
{
    MoveBy(-_speed, 0);
}

void PhysicsGameObject::CheckItemCollision(QGraphicsItem *collider)
{
    bool left_collision = false;
    bool right_collision = false;
    int collider_x2 =  collider->x() + collider->boundingRect().width();

    if (right_representation)
    {
        int x2 = GetRightX();
        if (x2 > collider->x() && x() < collider->x())
        {
            if (collider->y() > y() + _height/2)
            {
                moveBy(1, 0);
                while (collidesWithItem(collider))
                {
                    moveBy(0, -1);
                }
            }
            else
            {
                setX(collider->x() - _width);
                while (!collidesWithItem(collider))
                {
                    moveBy(1, 0);
                }
                moveBy(-1, 0);
                right_collision = true;
            }
        }
        else if (x2 - _width/2 > collider_x2 && x() < collider_x2)
        {
            setX(collider_x2);
            while (!collidesWithItem(collider))
            {
                moveBy(-1, 0);
            }
        }
    }
    else
    {
        int x1 = GetLeftX();
        if (x1 < collider_x2 && x() > collider_x2)
        {
            if (collider->y() > y() + _height/2)
            {
                moveBy(-1, 0);
                while (collidesWithItem(collider))
                {
                    moveBy(0, -1);
                }
            }
            else
            {
                setX(collider_x2 + _width);
                while (!collidesWithItem(collider))
                {
                    moveBy(-1, 0);
                }
                moveBy(1, 0);
                left_collision = true;
            }
        }
        else if (x1 + _width/2 < collider->x() && x() > collider->x())
        {
            setX(collider->x());
            while (!collidesWithItem(collider))
            {
                moveBy(1, 0);
            }
            moveBy(-1, 0);
        }
    }
    _right_collision = right_collision;
    _left_collision = left_collision;

}

/*!
 * \brief PhysicsGameObject::MoveBy
 * Moves object with animation
 * \param x move by x
 * \param y move by y
 */
void PhysicsGameObject::MoveBy(qreal x, qreal y)
{
    MoveBySimple(x, y);
    (x >= 0) ? NextSimpleSprite() : PrevSimpleSprite();
}

/*!
 * \brief PhysicsGameObject::MoveBySimple
 * Moves object without animation
 * \param x move by x
 * \param y move by y
 */
void PhysicsGameObject::MoveBySimple(qreal x, qreal y)
{
    if (x != 0)
        CheckRepresentation(x > 0);
    isGround = false;
    WeaponWasChange(false);
    moveBy(x, y);
    LocationWasChanged();
}

void PhysicsGameObject::Shoot(qreal target_x, qreal target_y)
{
    CheckRepresentation(target_x >= pos().x());

    if (_arrows.size() > 3)
        return;

    bool areWrongCoordinates = (target_x >= pos().x()
                                && target_x <= pos().x() + boundingRect().width() + 100);
    if (areWrongCoordinates)
        return;

    areWrongCoordinates = (target_x < pos().x()
                                    && target_x >= pos().x() - boundingRect().width() - 100);
    if (areWrongCoordinates)
        return;

    int start_x = right_representation ? GetRightX() : GetLeftX();

    arrow::Arrow *arrow = new arrow::Arrow(file::FileManager("../src/assets/arrows/arrow_simple.txt"),
                            start_x, y() + GetHeight()/4, target_x, target_y);

    _arrows.push_back(arrow);
    NewArrowWasCreated(arrow);
}

int PhysicsGameObject::GetHealth()
{
    return _health;
}

int PhysicsGameObject::GetArrowsAmount()
{
    return _arrows.size();
}

void PhysicsGameObject::SetHealth(int value)
{
    _health = value;
}

QVector<arrow::Arrow *> PhysicsGameObject::GetArrows()
{
    return _arrows;
}

void PhysicsGameObject::RemoveArrow(int idx)
{
     _arrows[idx]->deleteLater();
    _arrows.remove(idx);
}

/**
 * @brief PhysicsGameObject::CheckRepresentation
 * @param condition bool condition for right representation
 *          true if must be right reprasintation false otherwise
 */
void PhysicsGameObject::CheckRepresentation(bool condition)
{
    if (!condition && right_representation)
    {
        setTransform(QTransform::fromScale(-1, 1));
        moveBy(_width, 0);
        right_representation = false;
    }
    else if (condition && !right_representation)
    {
        setTransform(QTransform::fromScale(1, 1));
        moveBy(-_width, 0);
        right_representation = true;
    }
}

/*!
 * \brief PhysicsGameObject::GetLeftX
 * \return right x coordinate of the object's texture
 */
qreal PhysicsGameObject::GetLeftX() const
{
    if (right_representation)
        return x();
    else
        return x() - _width;
}

/*!
 * \brief PhysicsGameObject::GetRightX
 * \return left x coordinate of the object's texture
 */
qreal PhysicsGameObject::GetRightX() const
{
    if (right_representation)
        return x() + _width;
    else
        return x();
}

/*!
 * \brief PhysicsGameObject::Jump
 * is called for jump of the object
 * \param x jump offset
 */
void PhysicsGameObject::Jump(qreal x)
{
    if (isGround)
    {
        isJumping = true;

        if (x != 0)
            MoveBy(x, -_jump_height);
        else
            MoveBySimple(0, -_jump_height);

        QTimer::singleShot(120, this, [=](){
            isJumping = false;
        });
    }
    else
    {
        MoveBy(x, 0);
    }
}

void PhysicsGameObject::Strike()
{
    SetPixmap(strike_sprite,
              _width, _height);
    QTimer::singleShot(200, this, [&](){
        cur_sprite = 0;
        SetPixmap(_simple_sprites[cur_sprite]);
    });
}

void PhysicsGameObject::FallObject()
{
    MoveBySimple(0, 10);
}

