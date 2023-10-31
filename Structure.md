# Структура
Структура либы (классы и тд)

- [ ] actions
- [ ] mouse handling (click/scroll/move)
- [ ] input handling
- [ ] shaders
- [ ] sound (https://github.com/raysan5/raudio ?)
- [ ] shapenode (рисование)
- [ ] rendertexture
- [ ] changing scenes
- [ ] scenes transitions
- [ ] joystick support?
- [ ] scheduler
- [ ] particles
- [ ] animated sprites
- [ ] filemanager (file? filesystem?)

## WindowFlags
```cpp
enum class WindowFlags {
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
static AppManager* instance();

// то что будет юзер вызывать для первого запуска игры
void run();
// игровой цикл
void update();
void pause();
void resume();
// конец приложения
void end();

// получение времени с момента запуска в секундах
float getTime();

// скейл координат
void setContentScale(float scale);
inline float getContentScale() const;

inline const Sizef& getWinSize() const;
const Sizei& getWinSizeInPixels() const;
```

### Мемберы
```cpp
Sizef m_winSize; // in points
float m_contentScale;
std::chrono::блаблабла m_startTime;
bool m_isRunning;
```

## WindowManager
Управление всем, что связано с окном

### Методы
```cpp
static WindowManager* instance();

void createWindow(const Sizei& sizeInPixels, const Sizef& sizeInPoints, const std::string& title, bool fullscreen, WindowFlags windowFlags = WindowFlags::None);

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

inline const Sizei& getWinSizeInPixels() const;
void setWinSizeInPixels(const Sizei& size);

inline GLFWwindow* getGLFWWindow() const;

// нужно что то еще
```

### Мемберы
```cpp
Sizei m_winSize; // in pixels
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
void setScale(const Vec2f& scale);

inline float getRotation() const;
void setRotation(float degrees);

inline bool getVisible() const;
bool setVisible(bool visible);

inline float getOpacity() const;
void setOpacity(float opacity);

inline int getZOrder() const;
void setZOrder(int zOrder);

inline unsigned int getObjectLimit() const;
void setObjectLimit(unsigned int objectlimit);

inline const Sizef& getBoundingBox() const;
void setBoundingBox(const Sizef& size);

inline const Vec2f& getAnchorPoint() const;
void setAnchorPoint(const Vec2f& anchor);

void setTag(const char* tag);
inline const char* getTag() const;

// обновление нода (каждый кадр)
virtual void update(float dt) = 0;
virtual void draw() = 0;

inline const std::vector<std::shared_ptr<Node>>& getChildren() const;
void addChild(std::shared_ptr<Node> child);
void addChild(std::shared_ptr<Node> child, int zOrder);
// то же что и getChildren()[index]->removeFromParent(), для удобства
void removeChild(int index);
void removeAllChildren();
// удалить нод из родительского
void removeFromParent();
// получить родительский нод
inline Node* getParent() const;
```

### Мемберы
```cpp
Vec2f m_pos; // относительно родителя
Sizef m_boundingBox;
Vec2f m_anchorPoint; // {0.5, 0.5} по умолчанию
Vec2f m_scale;
float m_rotation;
float m_opacity;
unsigned int objectLimit;
int m_zOrder;
const char* m_tag;
std::vector<std::shared_ptr<Node>> m_children;
Node* m_parent;
bool m_visible;
```

## TextureManager

### Методы
```cpp
static TextureManager* instance();

// adds texture if not added previously
std::shared_ptr<Texture> getTexture(const std::string& name);
void addTexture(const std::string& name);

void removeTexture(const std::string& name);
void removeAllTextures();
```

### Мемберы
```cpp
std::unordered_map<std::string, std::shared_ptr<Texture>> m_textures;
```

## Texture
Текстура которую можно загрузить (не спрайт! она не добавляется на экран!)

```cpp
struct TexParams {
    GLuint minFilter; // minification filter
    GLuint magFilter; // magnification filter
    GLuint wrapS;
    GLuint wrapT;
};
```

### Методы
```cpp
// from file
Texture(const std::string& path);
// from memory
Texture(uint8_t* data, unsigned int dataLen);

// in points
Sizef getSize();
inline const Sizei& getSizeInPixels() const;

void setTexParams(const TexParams& params);
```

### Мемберы
```cpp
GLuint m_textureID;
Sizei m_size; // in pixels
```

## Sprite : Node
Спрайт который содержит текстуру, можно добавить на экран

### Методы
```cpp
Sprite(const std::string& path);
Sprite(std::shared_ptr<Texture> texture);

inline Col3u getColor() const;
void setColor(const Col3u& color);

// оверрайдаем draw чтобы отрисовать текстуру
virtual void draw() override;
```

### Мемберы
```cpp
std::shared_ptr<Texture> m_texture;
Col3u m_color; // {0, 0, 0} по умолчанию
```

## FontManager

### Методы
```cpp
static FontManager* instance();

void loadTTF(const std::string& path, const std::string& id);
void loadBitmapFont(const std::string& path, const std::string& id);

const Font& getFont(const std::string& id) const;
```

### Мемберы
```cpp
std::unordered_map<std::string, Font> m_fonts;
```

## Font
```cpp
struct Glyph {
    Rect textureRect;
    int xOffset; // на сколько смещается буква вправо относительно позиции курсора
    int yOffset; // на сколько смещается буква вниз относительно позиции курсора
    int xAdvance; // на сколько смещать курсор вправо после отрисовки буквы
};

struct Font {
    float lineHeight;
    float base;
    std::shared_ptr<Texture> fontAtlas;
    std::unordered_map<unsigned int, Glyph> glyphs;
};
```

### Мемберы


## Label : Node

```cpp
enum class TextAlignmentH : uint8_t {
    Left,
    Center,
    Right
};

enum class TextAlignmentV : uint8_t {
    Top,
    Center,
    Bottom
};
```

### Методы
```cpp
// fontID это то что указывали при загрузке в FontManager
Label(const std::string& text, const std::string& fontID);
Label(const std::string& text, const Font& font);

void setText(const std::string& text);
inline const std::string& getText() const;

inline std::string getFontID() const;
void setFontID(const std::string& fontID);

inline TextAlignmentH getHorizontalAlignment() const;
void setHorizontalAlignment(TextAlignmentH alignment);

inline TextAlignmentV getVerticalAlignment() const;
void setVerticalAlignment(TextAlignmentV alignment);
```

### Мемберы
```cpp
std::string m_text;
std::string m_fontID;
TextAlignmentH m_textAlignmentH;
TextAlignmentV m_textAlignmsntV;
```

## Scheduler

```cpp
struct Timer {
    float interval;
    int timesLeft;
    std::function<void()> callback;
    unsigned int id; // for internal usage
};
```

### Методы
```cpp
static Scheduler* instance();

inline float getTimeScale() const;
void setTimeScale(float ts);

// returns the timer id which can be used to usnchedule it
unsigned int schedule(const Timer& timer);
void unschedule(unsigned int id);
void unscheduleAll();

// internal
void update();
```

### Мемберы
```cpp
float m_timeScale;
unsigned int m_nextTimerID; // 0 by default, += 1 after each created timer
std::vector<Timer> m_timers;
```