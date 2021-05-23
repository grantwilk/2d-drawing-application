/* --------------------------------- Header --------------------------------- */


/**
 * @file    main.cpp
 * @brief   Application Entry Point
 */


/* -------------------------------- Includes -------------------------------- */


# include "drawcontext.h"
# include "viewcontext.h"
# include "x11context.h"

using namespace std;


/* ------------------------------- Functions -------------------------------- */


int main()
{
    /* ---------------- Create Graphics and Drawing Context ----------------- */


    GraphicsContext *gc = new X11Context( 800, 800, X11Context::WHITE );
    ViewContext *vc = new ViewContext( gc );
    DrawContext *dc = new DrawContext( vc );

    /* ---------------------------- Print Header ---------------------------- */

    cout << endl;
    cout << "/* ====== Grant's Spectacular 2D Art Designer ====== */" << endl;
    cout << endl;
    cout << endl;
    cout << "  DRAW CONTROLS:" << endl;
    cout << "  LMB   - Start Stroke / Continue Stroke" << endl;
    cout << "  ENTER - Confirm Stroke" << endl;
    cout << "  ESC   - Cancel Stroke" << endl;
    cout << "  X     - Toggle Snap To X" << endl;
    cout << "  Y     - Toggle Snap To Y" << endl;
    cout << "  CTRL  - Toggle Loop Mode" << endl;
    cout << "  C     - Clear Canvas" << endl;
    cout << endl;
    cout << "  COLOR CONTROLS:" << endl;
    cout << "  1 - Black     6 - Blue" << endl;
    cout << "  2 - Gray      7 - Cyan" << endl;
    cout << "  3 - White     8 - Magenta" << endl;
    cout << "  4 - Red       9 - Yellow" << endl;
    cout << "  5 - Green     0 - Random" << endl;
    cout << endl;
    cout << "  VIEW CONTROLS:" << endl;
    cout << "  MMB    - Pan" << endl;
    cout << "  RMB    - Rotate" << endl;
    cout << "  SCROLL - Zoom" << endl;
    cout << "  A      - Toggle 2D Axes" << endl;
    cout << "  R      - Reset View" << endl;
    cout << endl;
    cout << "  FILE CONTROLS:" << endl;
    cout << "  O - Open File" << endl;
    cout << "  S - Save File" << endl;
    cout << endl;
    cout << endl;
    cout << "/* ------------------------------------------------- */" << endl;
    cout << endl;


    /* --------------------------- Enter Run Loop --------------------------- */


    gc->runLoop( dc );


    /* ---------------------- Delete Graphics Context ----------------------- */


    delete dc;
    delete vc;
    delete gc;


    /* ---------------------------------------------------------------------- */
}