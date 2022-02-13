#include "Ghost.h"

Direction GetOpposite(Direction dir)
{
    switch (dir)
    {
    case Direction::Up:
        return Direction::Down;
    
    case Direction::Left:
        return Direction::Right;

    case Direction::Down:
        return Direction::Up;

    case Direction::Right:
        return Direction::Left;
    }
    return dir;
}

Ghost::Ghost(sf::Color _color) :
    direction(Direction::Stop), mode(GhostsMode::Scatter), currentImageG(0),
    color(_color), setMode(GhostsMode::Scatter), preMode(GhostsMode::Scatter)
{
    sprite.setTexture(*Resources::ghostTexture);
    sprite.setScale(CharacterScale, CharacterScale);
    sprite.setTextureRect(sf::IntRect(15, 0, 15, 15));
}

void Ghost::Frightened()
{
    if (EdgeCheck())
        return;
    int opposite = static_cast<int>(GetOpposite(direction));
    std::vector<int> vec;
    vec.reserve(3);
    for (int i = 0; i < 4; ++i)
    {
        if (i != opposite)
        {
            const int* temp = Tiles[i];
            if (Map::Objects[tile.y + temp[1]][tile.x + temp[0]].object != MapObjects::Wall)
                vec.push_back(i);
        }
    }
    Direction dir = static_cast<Direction>(vec[rand() % vec.size()]);
    Center(dir);
    direction = dir;
    const int* temp = Tiles[static_cast<int>(dir)];
    preTile = tile + sf::Vector2i(temp[0], temp[1]);
}

void Ghost::Chase(sf::Vector2i target)
{
    if (EdgeCheck())
        return;
    Direction opposite = GetOpposite(direction);
    // The first is the linear distance, the second is the direction.
    std::vector<std::pair<int, int>> vec;
    vec.reserve(3);
    for (int i = 0; i < 4; ++i)
    {
        if (static_cast<Direction>(i) == opposite)
            continue;
        const int* ptr = Tiles[i];
        if (Map::Objects[tile.y + ptr[1]][tile.x + ptr[0]].object == MapObjects::Wall)
            continue;
        int v1 = target.y - tile.y - ptr[1];
        int v2 = target.x - tile.x - ptr[0];
        vec.push_back({ v1 * v1 + v2 * v2, i });
    }
    std::sort(vec.begin(), vec.end());
    Direction dir = static_cast<Direction>(vec.front().second);
    Center(dir);
    direction = dir;
    const int* temp = Tiles[static_cast<int>(dir)];
    preTile = tile + sf::Vector2i(temp[0], temp[1]);
}

void Ghost::Center(Direction newDir)
{
    sf::Vector2f vt = sprite.getPosition();
    if ((newDir == Direction::Up || newDir == Direction::Down)
        && (direction == Direction::Left || direction == Direction::Right))
    {
        vt.x = Map::Objects[tile.y][tile.x].sprite.getPosition().x + Padding;
    }
    if ((newDir == Direction::Left || newDir == Direction::Right)
        && (direction == Direction::Up || direction == Direction::Down))
    {
        vt.y = Map::Objects[tile.y][tile.x].sprite.getPosition().y + Padding;
    }
    sprite.setPosition(vt);
}

bool Ghost::EdgeCheck()
{
    const int* temp = Tiles[static_cast<int>(direction)];
    if (11 < tile.x && tile.x < 16 && (tile.y == 11 || tile.y == 23 ) && mode != GhostsMode::Eaten
        && (direction == Direction::Left || direction == Direction::Right))
    {
        preTile.x = tile.x + temp[0];
        return true;
    }
    if (tile.x >= 27 && direction == Direction::Right)
    {
        if (tile.x > 27)
        {
            sprite.setPosition(-CharacterScale * 15, sprite.getPosition().y);
            preTile.x = 1;
        }
        else
            preTile.x = 28;
        return true;
    }
    if (tile.x <= 0 && direction == Direction::Left)
    {
        if (tile.x < 0)
        {
            sprite.setPosition((27 * MapObjectScale  + CharacterScale) * 15, sprite.getPosition().y);
            preTile.x = 26;
        }
        else
            preTile.x = -1;
        return true;
    }
    sf::Vector2f vec = sprite.getPosition();
    vec.x -= tile.x * 15 * MapObjectScale;
    vec.y -= tile.y * 15 * MapObjectScale;
    if (!(0 <= vec.y && vec.y <= 2 * Padding && 0 <= vec.x && vec.x <= 2 * Padding))
        return true;
    return false;
}

void Ghost::SetTextureRect(int offset, int num, float dt)
{
    int shift = offset;
    switch (direction)
    {
    case Direction::Left:
        break;
    case Direction::Right:
        shift += num * 15;
        break;
    case Direction::Down:
        shift += 2 * num * 15;
        break;
    case Direction::Up:
        shift += 3 * num * 15;
        break;
    }
    currentImageG += AnimationRate * dt;
    int temp = static_cast<int>(currentImageG);
    if (temp >= num)
    {
        currentImageG -= num;
        temp -= num;
    }
    sprite.setTextureRect(sf::IntRect(shift + temp * 15, 0, 15, 15));
}

void Ghost::Reverse()
{
    Direction opposite = GetOpposite(direction);
    const int* temp = Tiles[static_cast<int>(opposite)];
    sf::Vector2i vec = tile + sf::Vector2i(temp[0], temp[1]);
    if (Map::Objects[vec.y][vec.x].object != MapObjects::Wall)
    {
        direction = opposite;
        preTile = tile + sf::Vector2i(temp[0], temp[1]);
    }
}

void Ghost::Eaten()
{
    Chase(sf::Vector2i(12, 13));
}

void Ghost::SetPosition(sf::Vector2f ghostInitialPosition)
{
    tile.x = (ghostInitialPosition.x) / (MapObjectScale * 15);
    tile.y = (ghostInitialPosition.y) / (MapObjectScale * 15);
    preTile = tile;
    direction = Direction::Stop;
    mode = setMode = GhostsMode::Scatter;
    sprite.setColor(color);
    sprite.setPosition(ghostInitialPosition);
}

void Ghost::Move(float dt)
{
    bool flag = true;
    if (mode == setMode || setMode == GhostsMode::Eaten)
    {
        flag = false;
        mode = setMode;
        if (tile == preTile)
        {
            if (10 < tile.x && tile.x < 17 && 11 < tile.y && tile.y < 17)
                Chase(GetOut());
            else
            {
                switch (mode)
                {
                case GhostsMode::Frightened:
                    Frightened();
                    break;
                case GhostsMode::Eaten:
                    Eaten();
                    break;
                default:
                    Chase(GetTarget());
                }
            }
        }
    }
    if (mode == GhostsMode::Eaten && tile.y == 12 && tile.x == 13)
    {
        direction = Direction::Down;
        SetMode(preMode);
        flag = true;
    }
    if (flag)
    {
        if (!(10 < tile.x && tile.x < 17 && 12 < tile.y && tile.y < 17))
            Reverse();
        mode = setMode;
    }
    const float* vector = DirectionOffset[static_cast<int>(direction)];
    sprite.move(vector[0] * dt, vector[1] * dt);
    sf::Vector2f vec = sprite.getPosition();
    tile.x = vec.x / (MapObjectScale * 15);
    tile.y = vec.y / (MapObjectScale * 15);
}

void Ghost::Animate(float dt)
{
    switch (mode)
    {
    case GhostsMode::Chase:
    case GhostsMode::Scatter:
        SetTextureRect(0, 2, dt);
        break;
    case GhostsMode::Eaten:
        SetTextureRect(120, 1, dt);
        break;
    case GhostsMode::Frightened:
        currentImageG += AnimationRate * dt;
        int temp = static_cast<int>(currentImageG);
        if (temp >= 2)
        {
            currentImageG -= 2;
            temp -= 2;
        }
        sprite.setTextureRect(sf::IntRect(180 + temp * 15, 0, 15, 15));
        break;
    }
}

void Ghost::SetMode(GhostsMode _mode)
{
    switch (_mode)
    {
    case GhostsMode::Chase:
    case GhostsMode::Scatter:
        sprite.setColor(color);
        break;
    case GhostsMode::Frightened:
        if (mode != GhostsMode::Eaten && mode != GhostsMode::Frightened)
            preMode = mode;
        sprite.setColor(sf::Color::White);
        break;
    case GhostsMode::Eaten:
        sprite.setColor(sf::Color::White);
        break;
    }
    setMode = _mode;
}


void Ghost::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

GhostsMode Ghost::GetMode() const
{
	return mode;
}

Direction Ghost::PacmanDirection = Direction::Right;
sf::Vector2i Ghost::PacmanTile = sf::Vector2i();
