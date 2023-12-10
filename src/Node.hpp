#pragma once
#include <memory>
#include <vector>
#include <glm/mat4x4.hpp>
#include "utils.hpp"
// #include "Action.hpp"

NS_SPECTRUM_BEGIN

class Action;

class Node {
  public:
    Node();

    inline const Vec2f& getPos() const { return m_pos; }
    void setPos(const Vec2f& pos);
    inline float getPosX() const { return m_pos.x; }
    inline float getPosY() const { return m_pos.y; }
    inline void setPosX(float val) {
        m_pos.x = val;
        m_shouldCalcMtx = true;
    }
    inline void setPosY(float val) {
        m_pos.y = val;
        m_shouldCalcMtx = true;
    }

    inline float getScaleX() const { return m_scale.x; }
    inline float getScaleY() const { return m_scale.y; }
    inline const Vec2f& getScale() const { return m_scale; }
    void setScaleX(float scale);
    void setScaleY(float scale);
    void setScale(float scale);
    void setScale(const Vec2f& scale);

    inline float getRotation() const { return m_rotation; }
    void setRotation(float degrees);

    inline bool isVisible() const { return m_visible; }
    inline void setVisible(bool visible) { m_visible = visible; }

    // 0 to 1
    inline float getOpacity() const { return m_opacity; }
    // 0 to 1
    void setOpacity(float opacity);

    inline int getZOrder() const { return m_zOrder; }
    void setZOrder(int zOrder);

    inline unsigned int getObjectLimit() const { return m_objectLimit; }
    inline void setObjectLimit(unsigned int objectlimit) { m_objectLimit = objectlimit; }

    inline const Sizef& getBoundingBox() const { return m_boundingBox; }
    void setBoundingBox(const Sizef& size);
    Sizef getScaledBoundingBox();

    Rectf getRect();

    inline const Vec2f& getAnchorPoint() const { return m_anchorPoint; }
    void setAnchorPoint(const Vec2f& anchor);

    inline void setTag(const char* tag) { m_tag = tag; }
    inline const char* getTag() const { return m_tag; }

    void runAction(std::shared_ptr<Action> action);
    void removeAllActions();

    // обновление нода (каждый кадр)
    virtual void update(float dt);
    virtual void draw() {}

    virtual void onKeyEvent(int key, int scancode, int action, int mods) {};
    virtual void onTextEvent(unsigned int codepoint) {};
    virtual void onMouseEvent(MouseEventType evtType, const Vec2f& mousePos) {};
    virtual void onMouseBtn(int button, bool down, int mods) {};
    virtual void onMouseScroll(const Vec2f& delta) {};

    inline const std::vector<std::shared_ptr<Node>>& getChildren() const { return m_children; }
    void addChild(std::shared_ptr<Node> child);
    void addChild(std::shared_ptr<Node> child, int zOrder);
    // то же что и getChildren()[index]->removeFromParent(), для удобства
    void removeChild(int index);
    void removeAllChildren();
    // удалить нод из родительского
    void removeFromParent();
    // получить родительский нод
    inline Node* getParent() const { return m_parent; }
    void setParent(Node* node);
    std::shared_ptr<Node> getChildByTag(const char* tag) const;
    std::shared_ptr<Node> getChildByIndex(int index) const;

    inline const glm::mat4& getMatrix() const { return m_matrix; }

    inline bool isMouseOver() const { return m_isMouseOver; }
    inline void setMouseOver(bool val) { m_isMouseOver = val; }

    void sortChildren();

  protected:
    Vec2f m_pos; // относительно родителя
    Sizef m_boundingBox;
    Vec2f m_anchorPoint; // {0.5, 0.5} по умолчанию
    Vec2f m_scale;
    float m_rotation;
    float m_opacity;
    unsigned int m_objectLimit;
    int m_zOrder;
    const char* m_tag;
    std::vector<std::shared_ptr<Node>> m_children;
    Node* m_parent;
    glm::mat4 m_matrix;
    bool m_visible;
    bool m_shouldCalcMtx;
    bool m_isMouseOver;
};

NS_SPECTRUM_END