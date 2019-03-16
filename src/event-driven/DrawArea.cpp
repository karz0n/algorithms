#include "DrawArea.hpp"

#include <cmath>

#include <GL/glut.h>

namespace algorithms {

const int DEFAULT_WIDTH = 640;
const int DEFAULT_HEIGHT = 480;
const int DEFAULT_INTERVAL = 30;

DrawArea::Ptr DrawArea::_instance;

DrawArea::DrawArea()
    : DrawArea{DEFAULT_WIDTH, DEFAULT_HEIGHT}
{
}

DrawArea::DrawArea(int width, int height)
    : _width{width}
    , _height{height}
    , _positionX{0}
    , _positionY{0}
    , _clipAreaXLeft{-1.0}
    , _clipAreaXRight{1.0}
    , _clipAreaYBottom{-1.0}
    , _clipAreaYTop{1.0}
    , _interval{DEFAULT_INTERVAL}
{
}

void DrawArea::setInstance(Ptr value)
{
    _instance = value;
}

DrawArea::Ptr DrawArea::getInstance()
{
    return _instance;
}

void DrawArea::setTitle(const std::string& value)
{
    _title = value;
}

void DrawArea::setPostition(int x, int y)
{
    _positionX = x;
    _positionY = y;
}

void DrawArea::setInterval(unsigned int value)
{
    _interval = value;
}

double DrawArea::getClipAreaXLeft() const
{
    return _clipAreaXLeft;
}

double DrawArea::getClipAreaXRight() const
{
    return _clipAreaXRight;
}

double DrawArea::getClipAreaYBottom() const
{
    return _clipAreaYBottom;
}

double DrawArea::getClipAreaYTop() const
{
    return _clipAreaYTop;
}

void DrawArea::swapBuffers()
{
    glutSwapBuffers();
}

void DrawArea::clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void DrawArea::flush()
{
    glFlush();
}

void DrawArea::postpone(unsigned int delay)
{
    glutTimerFunc(delay, refreshWrapper, 0);
}

void DrawArea::show(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow(_title.c_str());
    glutInitWindowSize(_width, _height);
    glutInitWindowPosition(_positionX, _positionY);
    glutReshapeFunc(reshapeWrapper);
    glutDisplayFunc(drawWrapper);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    initWrapper();
    glutMainLoop();
}

void DrawArea::drawCircle(double rx, double ry, double radius)
{
    static constexpr int SEGMENTS_COUNT = 128;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(rx, ry, 0.0);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(0.0f, 0.0f);
    double angle;
    for (int i = 0; i <= SEGMENTS_COUNT; i++) {
        angle = i * 2.0 * M_PI / SEGMENTS_COUNT;
        glVertex2d(std::cos(angle) * radius, std::sin(angle) * radius);
    }
    glEnd();
}

void DrawArea::init()
{
}

void DrawArea::draw()
{
}

void DrawArea::reshape(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (height == 0) {
        height = 1;
    }
    glViewport(0, 0, width, height);

    double aspect = double(width) / double(height);
    if (width >= height) {
        _clipAreaXLeft = -1.0 * aspect;
        _clipAreaXRight = 1.0 * aspect;
        _clipAreaYBottom = -1.0;
        _clipAreaYTop = 1.0;
    }
    else {
        _clipAreaXLeft   = -1.0;
        _clipAreaXRight  = 1.0;
        _clipAreaYBottom = -1.0 / aspect;
        _clipAreaYTop    = 1.0 / aspect;
    }

    gluOrtho2D(_clipAreaXLeft, _clipAreaXRight, _clipAreaYBottom, _clipAreaYTop);
}

void DrawArea::refresh(int)
{
    glutPostRedisplay();
}

void DrawArea::initWrapper()
{
    getInstance()->init();
}

void DrawArea::drawWrapper()
{
    getInstance()->draw();
}

void DrawArea::reshapeWrapper(int width, int height)
{
    getInstance()->reshape(width, height);
}

void DrawArea::refreshWrapper(int data)
{
    getInstance()->refresh(data);
}

} // namespace algorithms
