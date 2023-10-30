# Структура
Структура либы (классы и тд)

## WindowFlags
```cpp
enum WindowFlags {
    // no flags
    None = 0,
    // whether the windowed mode window will be resizable by the user
    Resizable = 1 << 0,
    // whether the windowed mode window will be initially visible
    Visible = 1 << 1,
    // whether the windowed mode window will have window decorations such as a border, a close widget, etc.
    Decorated = 1 << 2,
    // whether the windowed mode window will be given input focus when created
    Focused = 1 << 3,
    // whether the full screen window will automatically iconify and restore the previous video mode on input focus loss
    AutoIconify = 1 << 4,
    // whether the windowed mode window will be floating above other regular windows, also called topmost or always-on-top.
    Floating = 1 << 5,
    // whether the windowed mode window will be maximized when created
    Maximized = 1 << 6,
    // whether the cursor should be centered over newly created full screen windows
    CenterCursor = 1 << 7,
    // whether the window framebuffer will be transparent. If enabled and supported by the system, the window framebuffer alpha channel will be used to combine the framebuffer with the background. This does not affect window decorations.
    TransparentFramebuffer = 1 << 8,
    // whether the window will be given input focus when glfwShowWindow is called
    FocusOnShow = 1 << 9,
    // whether the window content area should be resized based on the monitor content scale of any monitor it is placed on
    ScaleToMonitor = 1 << 10
};
```

## AppManager
Основной менеджер для игры (как CCDirector)

### Методы
```cpp
// получение инстанса класса (как sharedState в кокосе)
std::shared_ptr<AppManager> instance();

// то что будет юзер вызывать для первого запуска игры
void run();
// игровой цикл
void update();
void pause();
void resume();

// получение времени с момента запуска в секундах
float getTime();

// скейл координат
void setContentScale(float scale);
inline float getContentScale() const;

inline const Vec2f& getWinSize() const;
const Vec2i& getWinSizeInPixels() const;
```

### Мемберы
```cpp
Vec2f m_winSize; // in points
float m_contentScale;
std::chrono::блаблабла m_startTime;
bool m_isRunning;
```

## WindowManager
Управление всем, что связано с окном

### Методы
```cpp
static std::shared_ptr<WindowManager> instance();

void createWindow(const Vec2i& sizeInPixels, const Vec2f& sizeInPoints, const std::string& title, bool fullscreen, WindowFlags windowFlags = WindowFlags::None);

void setWindowIcon(const std::string& iconPath);

// bool() => возвращает true если окно закрывать, false если не закрывать
void setOnCloseCallback(std::function<bool()>);

void setFullscreen(bool fullscreen);
inline bool getFullscreen() const;

void setVsync(bool vsync);
inline bool getVsync() const;

// frameTime = 1.0 / fps;
void setTargetFrameTime(float frameTime);
inline float getTargetFrameTime() const;

inline const Vec2i& getWinSizeInPixels() const;
void setWinSizeInPixels(const Vec2i& size);

inline GLFWwindow* getGLFWWindow() const;

// нужно что то еще
```

### Мемберы
```cpp
Vec2i m_winSize; // in pixels
float m_targetFrameTime;
GLFWwindow* m_windowHandle;
bool m_isFullscreen;
bool m_isVsync;
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

inline bool getVisible() const;
bool setVisible(bool visible);

inline float getOpacity() const;
void setOpacity(float opacity);

inline Col4b getRGBCoefficient() const;
void setRGBCoefficient(const Col4b& color);

inline int getZOrder() const;
void setZOrder(int zOrder);

inline const Vec2f& getBoundingBox() const;
void setBoundingBox(const Vec2f& size);

inline const Vec2f& getAnchorPoint() const;
void setAnchorPoint(const Vec2f& anchor);

// обновление нода (каждый кадр)
virtual void update(float dt) = 0;
virtual void draw() = 0;

inline std::vector<std::shared_ptr<Node>> getChildren() const;
void addChild(std::shared_ptr<Node>);
void addChild(std::shared_ptr<Node>, int zOrder);
// то же что и getChildren()[index]->removeFromParent(), для удобства
void removeChild(int index);
void removeAllChildren();
// удалить нод из родительского
void removeFromParent();
// получить родительский нод
inline std::shared_ptr<Node> getParent() const;
```

### Мемберы
```cpp
Vec2f m_pos; // относительно родителя
Vec2f m_boundingBox;
Vec2f m_anchorPoint; // {0.5, 0.5} по умолчанию
Col3b m_rgbCoef; // {255, 255, 255} по умолчанию
float m_scaleX;
float m_scaleY;
float m_rotation;
float m_opacity;
int m_zOrder;
bool m_visible;
std::vector<std::shared_ptr<Node>> m_children;
std::shared_ptr<Node> m_parent;
```

## Texture
Текстура которую можно загрузить (не спрайт! она не добавляется на экран!)

### Методы
```cpp
// from file
Texture(const std::string& path);
// from memory
Texture(uint8_t* data, unsigned int dataLen);
```

### Мемберы
```cpp
GLuint m_textureID;
```

## Sprite : Node
Спрайт который содержит текстуру, можно добавить на экран

### Методы
```cpp
Sprite(const std::string& path);
Sprite(const Texture& texture);

inline Color4b getBackgroundColor() const;
void setBackgroundColor(const Color4b& color);

// оверрайдаем draw чтобы отрисовать текстуру
virtual void draw() override;
```

### Мемберы
```cpp
Texture m_texture; // может сделать sharedptr хз
Col4b m_backgroundColor; // {0, 0, 0, 0} по умолчанию
```

## FontManager
Менеджер шрифтов

### Методы
```cpp
static std::shared_ptr<FontManager> instance();

void loadTTF(const std::string& path);
```

## Label : Node
Текст

### Методы
```cpp
// fontID
Label(const std::string& text, const std::string& fontID);
```