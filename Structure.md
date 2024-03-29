# Структура
Структура либы (классы и тд)

## TODO

### v1.0
- [x] actions
- [x] mouse handling (click/scroll/move)
- [x] input handling
- [x] shaders
- [x] sound (https://github.com/raysan5/raudio ?)
- [x] shapenode (рисование)
- [x] changing scenes
- [x] scenes transitions
- [x] scheduler
- [x] filemanager
- [x] animated sprites
- [x] spritesheets

### v1.1
- [ ] joystick support?
- [ ] particles
- [x] ccspritebatchnode
- [ ] rendertexture
- [ ] skew
- [ ] чтото похожее на getWritablePath
- [ ] dds текстуры и другие

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
    ScaleToMonitor = 1 << 10,
    Default = Visible | Decorated | Focused | Resizable | AutoIconify | CenterCursor | FocusOnShow
};
```

## AppManager
Основной менеджер для игры (как CCDirector)  
`friend class WindowManager;`

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

// in points
inline const Sizef& getWinSize() const;

void setCursorVisible(bool visible);
inline bool getCursorVisible() const;

void setCursorLocked(bool locked);
inline bool getCursorLocked() const;

void openURL(const std::string& url);

std::shared_ptr<Scene> getCurrentScene();
void pushScene(std::shared_ptr<Scene> scene);
void replaceScene(std::shared_ptr<Scene> scene);
// -1 => go 1 scene back, 1 => go 1 scene forward etc
void goToScene(int step);

// получить реальный фпс (хз как реализовать пока что)
float getRealFPS();

std::string getClipboardText();
// (без замены существующего, копирует новый)
void setClipboardText(const std::string& text);

Vec2f pointsToPixels(const Vec2f& pointPos);
Vec2f pixelsToPoints(const Vec2f& pixelPos);
```

### Мемберы
```cpp
Sizef m_winSize; // in points
Vec2f m_pointsToPixels; // points to pixels ratio
float m_contentScale;
std::chrono::блаблабла m_startTime;
std::vector<std::shared_ptr<Scene>> m_scenes;
int m_currentScene;
bool m_isRunning;
bool m_isCursorVisible;
bool m_isCursorLocked;
```

## WindowManager
Управление всем, что связано с окном

### Методы
```cpp
static WindowManager* instance();

void createWindow(const Sizei& sizeInPixels, const Sizef& sizeInPoints, const std::string& title, bool fullscreen, WindowFlags windowFlags = WindowFlags::Default);

void setWindowIcon(const std::string& iconPath);

// bool() => возвращает true если окно закрывать, false если не закрывать
void setOnCloseCallback(std::function<bool()> callback);

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

Vec2f getMousePos();
Vec2i getMousePosInPixels();

void setFilesDroppedCallback(std::function<void(std::vector<std::string>)> callback);

// all 3 are for this frame
Vec2f getMouseWheelDelta();
Vec2f getMouseDelta();
Vec2i getMouseDeltaInPixels();
```

### Мемберы
```cpp
Sizei m_winSize; // in pixels
float m_targetFrameTime;
GLFWwindow* m_windowHandle;
std::function<bool()> m_closeCallback;
std::function<void(std::vector<std::string>)> m_filesDroppedCallback;
bool m_isFullscreen;
bool m_isVsync;
```

## Action
`friend class ActionManager;`

```cpp
// https://github.com/ai/easings.net/blob/master/src/easings/easingsFunctions.ts
enum class EasingType {
    Linear,
    EaseInQuad,
    EaseOutQuad,
    EaseInOutQuad,
    EaseInCubic,
    EaseOutCubic,
    EaseInOutCubic,
    EaseInQuart,
    EaseOutQuart,
    EaseInOutQuart,
    EaseInQuint,
    EaseOutQuint,
    EaseInOutQuint,
    EaseInSine,
    EaseOutSine,
    EaseInOutSine,
    EaseInExpo,
    EaseOutExpo,
    EaseInOutExpo,
    EaseInCirc,
    EaseOutCirc,
    EaseInOutCirc,
    EaseInBack,
    EaseOutBack,
    EaseInOutBack,
    EaseInElastic,
    EaseOutElastic,
    EaseInOutElastic,
    EaseInBounce,
    EaseOutBounce,
    EaseInOutBounce
};
```

### Методы
```cpp
Action(EasingType easing, float duration);

virtual void update(float dt) {
    if (m_isFinished)
        return;

    m_runTime += dt;
    if (m_runTime >= m_duration) {
        m_isFinished = true;
        m_progress = 1.0f;
        break;
    }

    m_progress = utils::calcEasing(m_easingType, m_runTime / m_duration);
}

inline bool isFinished() const;
inline EasingType getEasingType() const;
inline Node* getNode() const;
inline float getProgress() const;
```

### Мемберы
```cpp
float m_duration; // total action time
float m_runTime; // the time the action has been running
float m_progress; // 0 to 1
Node* m_node;
EasingType m_easingType;
bool m_isFinished;
```

## ActionMoveTo : Action
`friend class ActionManager;`

### Методы
```cpp
ActionMoveTo(EasingType easing, float duration, const Vec2f& startPos, const Vec2f& endPos);

virtual void update(float dt) override {
    Action::update(dt);

    m_node->setPos(utils::lerpValue(m_startPos, m_endPos, m_progress));
}
```

### Мемберы
```cpp
Vec2f m_startPos;
Vec2f m_endPos;
```

## ActionScaleTo : Action
`friend class ActionManager;`

### Методы
```cpp
ActionScaleTo(EasingType easing, float duration, float startScale, float endScale);

virtual void update(float dt) override {
    Action::update(dt);

    m_node->setScale(utils::lerpValue(m_startScale, m_endScale, m_progress));
}
```

### Мемберы
```cpp
float m_startScale;
float m_endScale;
```

## ActionRotateTo : Action
`friend class ActionManager;`

### Методы
```cpp
ActionRotateTo(EasingType easing, float duration, float startRot, float endRot);

virtual void update(float dt) override {
    Action::update(dt);

    m_node->setRotation(utils::lerpValue(m_startRot, m_endRot, m_progress));
}
```

### Мемберы
```cpp
float m_startRot;
float m_endRot;
```

## ActionTintTo : Action
`friend class ActionManager;`

### Методы
```cpp
ActionTintTo(EasingType easing, float duration, const Col4u& startCol, const Col4u& endCol);

virtual void update(float dt) override {
    Action::update(dt);

    auto spr = dynamic_cast<Sprite*>(m_node);

    if (spr)
        spr->setColor(utils::lerpValue(m_startCol, m_endCol, m_progress));
}
```

## template \<typename T> ActionLerp\<T> : Action
`friend class ActionManager;`

### Методы
```cpp
ActionLerp(EasingType easing, float duration, const T& startVal, const T& endVal, std::function<void(T)> callback);

virtual void update(float dt) override {
    Action::update(dt);

    m_callback(utils::lerpValue(m_startVal, m_endVal, m_progress));
}
```

### Мемберы
```cpp
T m_startVal;
T m_endVal;
std::function<void(T)> m_callback;
```

## ActionSequence : Action
`friend class ActionManager;`

### Методы
```cpp
ActionSequence(std::vector<std::shared_ptr<Action>> actions);

virtual void update(float dt) override {
    if (m_currentAction >= m_actions.size())
        break;

    auto curAction = m_action[m_currentAction];
    curAction->update(dt);
    if (curAction->isFinished())
        m_currentAction++;
}
```

### Мемберы
```cpp
std::vector<std::shared_ptr<Action>> m_actions;
int m_currentAction;
```

## ActionManager

### Методы
```cpp
static ActionManager* instance();

void update(float dt);

void addAction(std::shared_ptr<Action> action, Node* node);
void removeAction(std::shared_ptr<Action> action);
```

### Мемберы
```cpp
std::vector<std::shared_ptr<Action>> m_actions;
```

## Node
Всё, что можно поместить на экран

```cpp
enum class KeyEventType {
    KeyDown,
    KeyUp
};

enum class MouseEventType {
    MouseHold,
    MouseRelease,
    MouseMove,
    MouseEnterArea,
    MouseLeaveArea
};

enum class ModKeys {
    None = 0,
    Shift = 1 << 0,
    Control = 1 << 1,
    Alt = 1 << 2,
    Super = 1 << 3,
    CapsLock = 1 << 4, // if the GLFW_LOCK_KEY_MODS input mode is set.
    NumLock = 1 << 5 // if the GLFW_LOCK_KEY_MODS input mode is set.
};
```

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
Sizef getScaledBoundingBox();

inline const Vec2f& getAnchorPoint() const;
void setAnchorPoint(const Vec2f& anchor);

void setTag(const char* tag);
inline const char* getTag() const;

void runAction(std::shared_ptr<Action> action);

// обновление нода (каждый кадр)
virtual void update(float dt) = 0;
virtual void draw() = 0;

virtual void onKeyEvent(KeyEventType evtType, Key key, ModKeys modKeys) = 0;
virtual void onTextEvent(unsigned int codepoint) = 0;
virtual void onMouseEvent(MouseEventType evtType, const Vec2i& mousePos) = 0;
virtual void onMouseScroll(Vec2f delta) = 0;

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
std::shared_ptr<Texture> addTexture(const std::string& path);

// loads all textures to m_textures;
void loadSpriteSheet(const std::string& path);

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

```cpp
struct BlendFunc {
    GLenum src;
    GLenum dst;
};
```

### Методы
```cpp
Sprite(const std::string& path);
Sprite(std::shared_ptr<Texture> texture);

inline Col3u getColor() const;
void setColor(const Col3u& color);

void setBlendFunc(const BlendFunc& func);
inline const BlendFunc& getBlendFunc() const;

// оверрайдаем draw чтобы отрисовать текстуру
virtual void draw() override;

inline std::shared_ptr<Shader> getShader() const;
void setShader(std::shared_ptr<Shader> shader);
```

### Мемберы
```cpp
std::shared_ptr<Texture> m_texture;
Col3u m_color; // {0, 0, 0} по умолчанию
std::shared_ptr<Shader> m_shader;
BlendFunc m_blendFunc;
```

## Animation

### Методы
```cpp
Animation(float fps, std::vector<Texture*> textures);

void update(float dt);
Texture* getTexture();

void pause();
void play();
```

### Мемберы

```cpp
float m_timeDelay;
std::vector<Texture*> m_textures;
float m_timeRun;
bool m_isPlaying;
```

## AnimationManager

### Методы

```cpp
static AnimationManager* instance();

void addAnim(const std::string& formatStr, float fps, const std::string& id);
void addAnim(std::shared_ptr<Animation> anim);
void removeAnim(const std::string& id);

std::shared_ptr<Animation> getAnim(const std::string& id);
```

### Мемберы

```cpp
std::unordered_map<std::string, std::shared_ptr<Animation>> m_anims;
```

## AnimSprite : Sprite

### Методы
```cpp
AnimSprite();

void runAnim(const std::string& id);
void runAnim(std::shared_ptr<Animation> anim);
// stop any anims, draw a plain texture
void setTexture(std::shared_ptr<Texture> tex);

virtual void update(float dt) override;
virtual void draw() override;
```

### Мемберы

```cpp
std::shared_ptr<Animation> m_curAnim;
bool m_hasAnim;
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
    unsigned int id;
    float timeLeft;
};
```

### Методы
```cpp
static Scheduler* instance();

inline float getTimeScale() const;
void setTimeScale(float ts);

// returns the timer id which can be used to unschedule it
// timesLeft = -1 => infinite repeat
unsigned int schedule(float interval, int timesLeft, std::function<void()> callback);
void unschedule(unsigned int id);
void unscheduleAll();

// internal
void update(float dt);

void setAFKCallback(std::function<void()> callback);
inline float getAFKInterval() const;
void setAFKInterval(float interval);
```

### Мемберы
```cpp
float m_timeScale;
unsigned int m_nextTimerID; // 0 by default, += 1 after each created timer
std::vector<Timer> m_timers;
float m_AFKInterval;
std::function<void()> m_AFKCallback;
```

## namespace utils
```cpp
uint32_t ColToInt(const Col3u& col);
uint32_t ColToInt(const Col3f& col);
uint32_t ColToInt(const Col4u& col);
uint32_t ColToInt(const Col4f& col);

Col3u IntToCol3u(uint32_t col);
Col3f IntToCol3f(uint32_t col);
Col4u IntToCol4u(uint32_t col);
Col4f IntToCol4f(uint32_t col);

float calcEasing(EasingType easingType, float x);

template <typename T>
T lerpValue(T start, T end, float t) {
    return start + (end - start) * t;
}
```

## FileManager

### Методы
```cpp
static FileManager* instance();

std::filesystem::path fullPathForFile(const std::string& name);
void addSearchPath(const std::filesystem::path& path);
const std::vector<std::filesystem::path>& getSearchPaths() const;

// Возвращает путь к корню диска, на котором запущено приложение
std::filesystem::path getRootPath();
std::filesystem::path getAppDirectory();
std::filesystem::path getAppPath();
std::filesystem::path getTempPath();
std::filesystem::path getAppFilename();
```

### Мемберы
```cpp
std::vector<std::filesystem::path> m_searchPaths;
```

## ShaderManager

### Методы
```cpp
static ShaderManager* instance();

std::shared_ptr<Shader> getShader(const std::string& id);
void addShader(std::shared_ptr<Shader> shader, const std::string& id);
void removeShader(const std::string& id);
void removeAllShaders();
```

### Мемберы
```cpp
std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaders;
```

## Shader

### Методы
```cpp
~Shader(); // glDeleteShader

bool loadFromFile(const std::string& vertexPath, const std::string& fragmentPath);
bool loadFromString(std::string_view vertexShader, std::string_view fragmentShader);

void link();

void use();

inline GLuint getShaderProgram() const;
inline bool isLinked() const;
```

### Мемберы
```cpp
GLuint m_vertexShader;
GLuint m_fragShader;
GLuint m_shaderProgram;
bool m_isLinked;
```

## Scene : Node

### Мемберы
```cpp
// sets boundingbox to all win size
Scene();
```

## SceneTransition : Scene

```cpp
enum class TransitionType {
    Fade
    // потом другие добавим
};
```

### Методы
```cpp
SceneTransition(std::shared_ptr<Scene> scene, float duration, TransitionType type);

virtual void update(float dt) override;
```

### Мемберы
```cpp
float m_duration;
TransitionType m_type;
```

## InputDispatcher
`friend class WindowManager;`

### Методы
```cpp
static InputDispatcher* instance();

void registerMouseEvents(Node* node);
void registerMouseScrollEvents(Node* node);
void registerKeyEvents(Node* node);
void registerTextEvents(Node* node);

void unregisterMouseEvents(Node* node);
void unregisterMouseScrollEvents(Node* node);
void unregisterKeyEvents(Node* node);
void unregisterTextEvents(Node* node);

private:
// всякие функции для WindowManager которые принимают данные и отправляют их в вектора нодов
```

### Мемберы
```cpp
std::vector<Node*> m_mouseEvents;
std::vector<Node*> m_mouseScrollEvents;
std::vector<Node*> m_keyEvents;
std::vector<Node*> m_textEvents;
```

## AudioManager

```cpp
struct Sample {
    const char* sampleKey;
    uint8_t volume;
    uint8_t balance;
    uint32_t freq;
    uint32_t position;
    uint32_t length;
    uint32_t repeats;
};

struct Channel {
    const char* sampleKey;
    uint8_t volume;
    uint8_t balance;
    uint32_t freq;
    uint32_t position;
    uint32_t length;
    uint32_t repeats;
};
```

### Методы
```cpp
static AudioManager* instance();

void playSample(const std::string& sample, uint32_t repeats);
void playSample(const std::string& sample, uint8_t channel, uint32_t repeats);
void playSampleFile(const std::string& samplePath, uint8_t channel, uint32_t repeats);

void preloadSampleFile(const std::string& samplePath);
void unloadSampleFile(const std::string& sample);

void pauseSample(const std::string& sample);
void pauseChannel(uint8_t channel);
void pauseAllChannels();

void resumeSample(const std::string& sample);
void resumeChannel(uint8_t channel);
void resumeAllChannels();

void stopSample(const std::string& sample);
void stopChannel(uint8_t channel);
void stopAllChannels();

void setGeneralVolume(float volume);
void setSampleVolume(const std::string& sample, float volume);
void setChannelVolume(uint8_t channel, float volume);

float getGeneralVolume();
float getSampleVolume(const std::string& sample);
float getChannelVolume(uint8_t channel);

void setGeneralBalance(float balance);
void setSampleBalance(const std::string& sample, float balance);
void setChannelBalance(uint8_t channel, float balance);

float getGeneralBalance();
float getSampleBalance(const std::string& sample);
float getChannelBalance(uint8_t channel);

void setSamplePosition(const std::string& sample, float seconds);
void setChannelPosition(uint8_t channel, float seconds);

float getSamplePosition(const std::string& sample);
float getChannelPosition(uint8_t channel);

float getSampleLength(const std::string& sample);
float getChannelLength(uint8_t channel);

void setSampleFrequency(const std::string& sample, uint32_t freq);
void setChannelFrequency(uint8_t channel, uint32_t freq);

float getSampleFrequency(const std::string& sample);
float getChannelFrequency(uint8_t channel);

void lockChannel(uint8_t channel);
void unlockChannel(uint8_t channel);
```

### Мемберы
```cpp
std::array<Channel, 48> m_channels;
std::vector<Sample> m_loadedSamples;
float m_generalVolume;
float m_generalBalance;
```

## ShapeNode : Node

### Методы
```cpp
virtual void draw() override;

void setDrawCallback(std::function<void()> callback);

void setColor(const Col4u& col);

void drawCircle(const Vec2f& pos, float radius);
void drawEllipse(const Vec2f& pos, float radiusX, float radiusY);
void drawRect(const Rectf& rect);
void drawLine(const Vec2f& start, const Vec2f& end, float width);
void drawLines(const std::vector<Vec2f>& points, float width);
void drawPolygon(const std::vector<Vec2f>& points);
```

### Мемберы
```cpp
Col4u m_col;
std::function<void()> m_drawCallback;
```

## ShapeNodeEx : Node

```cpp
enum class ShapeType : uint8_t {
    Ellipse,
    Polygon,
    Line
};

enum class FillType : uint8_t {
    SolidColor,
    Gradient,
    Texture
};
```

### Методы
```cpp
virtual void draw() override;

void setShape(ShapeType shape);
void setFill(FillType fill);

void setLineColor(Col4u color);
void setLineWidth(float width);

void setGradientStartCol(Col4u color);
void setGradientEndCol(Col4u color);
// all is from 0 to 1
void setGradientPositions(Vec2f start, Vec2f end);

void setTexture(std::shared_ptr<Texture> texture);

void setPolygonPoints(std::vector<Vec2f> points);

// for circle x = y
void setEllipseRadius(float x, float y);
```

### Мемберы
```cpp
ShapeType m_shapeType;
FillType m_fillType;

Vec2f m_ellipseRadius;

std::shared_ptr<Texture> m_texture;

float m_lineWidth;
Col4u m_lineCol;

Col4u m_gradientStartCol;
Col4u m_gradientEndCol;
Vec2f m_gradientStartPos;
Vec2f m_gradientEndPos;

std::vector<Vec2f> m_polygonPoints;
```