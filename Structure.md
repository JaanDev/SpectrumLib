# Структура
Структура либы (классы и тд)

## AppManager
Основной менеджер для игры (как CCDirector)

### Методы
```cpp
// получение инстанса класса (как sharedState в кокосе)
std::shared_ptr<AppManager> instance();
// то что будет юзер вызывать для первого запуска игры
void run();
void pause();
void resume();
void setFPS(float fps);
void setVsync(bool vsync);
// скейл координат
void setContentScale(float scale);
inline const Vec2f& getWinSize() const;
inline const Vec2i& getWinSizeInPixels() const;
// управление всем что связано с окном вот тут
std::shared_ptr<Window> getWindow();
```

## Node
Всё, что можно поместить на экран

### Методы
```cpp
inline const Vec2f& getPos() const;
void setPos(const Vec2f& pos);

inline float getScaleX() const;
inline float getScaleY() const;
void setScaleX(float scale);
void setScaleY(float scale);
void setScale(float scale);

inline float getRotation() const;
void setRotation(float degrees);

inline float getOpacity() const;
void setOpacity(float opacity);

inline std::vector<std::shared_ptr<Node>> getChildren() const;
void addChild(std::shared_ptr<Node>);
void addChild(std::shared_ptr<Node>, int zOrder);
// то же что и getChildren()[index]->removeFromParent(), для удобства
void removeChild(int index);
// удалить нод из родительского
void removeFromParent();
// получить родительский нод
inline std::shared_ptr<Node> getParent() const;
```

### Мемберы
```cpp
Vec2f m_pos; // относительно родителя
float m_scaleX;
float m_scaleY;
float m_rotation;
float m_opacity;
std::vector<std::shared_ptr<Node>> m_children;
std::shared_ptr<Node> m_parent;
```