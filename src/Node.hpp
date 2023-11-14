#pragma once
#include <memory>
#include <vector>
#include "utils.hpp"

NS_SPECTRUM_BEGIN

class Action;

class Node {
  public:
    Node();

    inline const Vec2f& getPos() const { return m_pos; }
    void setPos(const Vec2f& pos);

    inline float getScaleX() const { return m_scale.x; }
    inline float getScaleY() const { return m_scale.y; }
    void setScaleX(float scale);
    void setScaleY(float scale);
    void setScale(float scale);
    void setScale(const Vec2f& scale);

    inline float getRotation() const { return m_rotation; }
    void setRotation(float degrees);

    inline bool getVisible() const { return m_visible; }
    void setVisible(bool visible);

    inline float getOpacity() const { return m_opacity; }
    void setOpacity(float opacity);

    inline int getZOrder() const { return m_zOrder; }
    void setZOrder(int zOrder);

    inline unsigned int getObjectLimit() const { return m_objectLimit; }
    void setObjectLimit(unsigned int objectlimit);

    inline const Sizef& getBoundingBox() const { return m_boundingBox; }
    void setBoundingBox(const Sizef& size);
    Sizef getScaledBoundingBox();

    inline const Vec2f& getAnchorPoint() const { return m_anchorPoint; }
    void setAnchorPoint(const Vec2f& anchor);

    void setTag(const char* tag);
    inline const char* getTag() const { return m_tag; }

    void runAction(std::shared_ptr<Action> action);

    // обновление нода (каждый кадр)
    virtual void update(float dt) {};
    virtual void draw();

    virtual void onKeyEvent(KeyEventType evtType, int key, ModKeys modKeys) {};
    virtual void onTextEvent(unsigned int codepoint) {};
    virtual void onMouseEvent(MouseEventType evtType, const Vec2i& mousePos) {};
    virtual void onMouseScroll(Vec2f delta) {};

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

    void setShouldSortChildren(bool val);

  protected:
    void sortChildren();

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
    bool m_visible;
    bool m_shouldSortChildren;
};

NS_SPECTRUM_END