#pragma once

#include <string>
#include <memory>

namespace algorithms {

class DrawArea {
public:
    using Ptr = std::shared_ptr<DrawArea>;

    DrawArea();

    DrawArea(int width, int height);

    virtual ~DrawArea() = default;

    static void
    setInstance(const Ptr& value);

    static Ptr
    getInstance();

    void
    setTitle(const std::string& value);

    void
    setPosition(int x, int y);

    void
    setInterval(unsigned int value);

    [[nodiscard]] double
    getClipAreaXLeft() const;

    [[nodiscard]] double
    getClipAreaXRight() const;

    [[nodiscard]] double
    getClipAreaYBottom() const;

    [[nodiscard]] double
    getClipAreaYTop() const;

    void
    swapBuffers();

    void
    clear();

    void
    flush();

    void
    postpone(unsigned int delay);

    void
    show(int argc, char* argv[]);

public:
    static void
    drawCircle(double rx, double ry, double radius);

protected:
    virtual void
    init();
    virtual void
    draw();
    virtual void
    reshape(int width, int height);
    virtual void
    refresh(int data);

private:
    static void
    initWrapper();
    static void
    drawWrapper();
    static void
    reshapeWrapper(int width, int height);
    static void
    refreshWrapper(int data);

private:
    static Ptr _instance;

private:
    std::string _title;
    int _width;
    int _height;
    int _positionX;
    int _positionY;
    double _clipAreaXLeft;
    double _clipAreaXRight;
    double _clipAreaYBottom;
    double _clipAreaYTop;
    unsigned int _interval;
};

} // namespace algorithms
