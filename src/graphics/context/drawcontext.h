/* --------------------------------- Header --------------------------------- */


/**
 * @file    drawcontext.h
 * @brief   Context for the active drawing
 */


/* ------------------------------ Header Guard ------------------------------ */


# ifndef GRAPHICS_CONTEXT_DRAWCONTEXT_H
# define GRAPHICS_CONTEXT_DRAWCONTEXT_H


/* -------------------------------- Includes -------------------------------- */


# include <vector>

# include "color.h"
# include "drawbase.h"
# include "point2d.h"
# include "shapecontainer.h"
# include "viewcontext.h"
#include "drawcontext.h"


/* --------------------------------- Class ---------------------------------- */


class DrawContext : public DrawingBase
{
    /* =============================== PUBLIC =============================== */

public:

    /* ----------------------------- Attributes ----------------------------- */


    static constexpr unsigned int KEY_CODE_0 = 48;
    static constexpr unsigned int KEY_CODE_1 = 49;
    static constexpr unsigned int KEY_CODE_2 = 50;
    static constexpr unsigned int KEY_CODE_3 = 51;
    static constexpr unsigned int KEY_CODE_4 = 52;
    static constexpr unsigned int KEY_CODE_5 = 53;
    static constexpr unsigned int KEY_CODE_6 = 54;
    static constexpr unsigned int KEY_CODE_7 = 55;
    static constexpr unsigned int KEY_CODE_8 = 56;
    static constexpr unsigned int KEY_CODE_9 = 57;

    static constexpr unsigned int KEY_CODE_A = 97;
    static constexpr unsigned int KEY_CODE_C = 99;
    static constexpr unsigned int KEY_CODE_O = 111;
    static constexpr unsigned int KEY_CODE_R = 114;
    static constexpr unsigned int KEY_CODE_S = 115;
    static constexpr unsigned int KEY_CODE_X = 120;
    static constexpr unsigned int KEY_CODE_Y = 121;

    static constexpr unsigned int KEY_CODE_ENTER = 65293;
    static constexpr unsigned int KEY_CODE_ESC = 65307;
    static constexpr unsigned int KEY_CODE_SHIFT = 65505;
    static constexpr unsigned int KEY_CODE_LCTRL = 65507;
    static constexpr unsigned int KEY_CODE_RCTRL = 65508;


    /* --------------------- Constructors / Destructors --------------------- */


    explicit DrawContext( ViewContext *vc );
    ~DrawContext() override;


    /* ------------------------------ Functions ----------------------------- */


    void paint( GraphicsContext *gc ) override;
    void keyDown( GraphicsContext *gc, unsigned int keycode ) override;
    void keyUp( GraphicsContext *gc, unsigned int keycode ) override;
    void mouseButtonDown( GraphicsContext *gc, unsigned int button, int x, int y ) override;
    void mouseButtonUp( GraphicsContext *gc, unsigned int button, int x, int y ) override;
    void mouseMove( GraphicsContext *gc, int x, int y ) override;


    /* ============================== PROTECTED ============================= */

protected:

    /* =============================== PRIVATE ============================== */

private:

    /* ----------------------------- Attributes ----------------------------- */


    Color drawColor = Color( 0, 0, 0 );
    Color canvasColor = Color( 1, 1, 1 );

    bool loopMode = false;
    bool snapToX = false;
    bool snapToY = false;

    std::vector<Point2D*> verts;
    ShapeContainer sc = ShapeContainer();

    ViewContext *vc;

    bool draw2DAxis = true;

    bool panActive = false;
    bool rotateActive = false;
    Point2D lastMousePosition = Point2D( 0, 0 );


    /* ------------------------------ Functions ----------------------------- */


    void strokeAddVert( GraphicsContext *gc, int x, int y );
    void strokeFreeze( GraphicsContext *gc );
    void strokeCancel( GraphicsContext *gc );

    void strokeClearVerts();

    void strokeSetColor( GraphicsContext *gc, const Color &color );
    void strokeDrawLines( GraphicsContext *gc );

    void toggleLoopMode( GraphicsContext *gc );

    void drawingOpen( GraphicsContext *gc );
    void drawingSave();
    void drawingClear( GraphicsContext *gc );


    /* ====================================================================== */
};


/* --------------------------------- Footer --------------------------------- */


# endif // GRAPHICS_CONTEXT_DRAWCONTEXT_H


/* -------------------------------------------------------------------------- */