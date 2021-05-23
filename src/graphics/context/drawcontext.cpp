/* --------------------------------- Header --------------------------------- */


/**
 * @file    drawcontext.cpp
 * @brief   Context for the active drawing
 */


/* -------------------------------- Includes -------------------------------- */


# include <algorithm>
# include <fstream>
# include <iostream>

# include "drawcontext.h"
# include "line.h"
# include "shape.h"
# include "triangle.h"
# include "polygon.h"


/* ----------------------- Constructors / Destructors ----------------------- */


DrawContext::DrawContext( ViewContext *vc ) :
    vc( vc )
{}


DrawContext::~DrawContext() = default;


/* ---------------------------- Public Functions ---------------------------- */


void DrawContext::paint( GraphicsContext *gc )
{
    // cancel stroke
    strokeCancel( gc );

    // clear the canvas
    gc->clear();

    // update view context
    vc->update();

    // draw crosshair
    if ( draw2DAxis )
    {
        gc->setMode( GraphicsContext::MODE_NORMAL );

        Point2D origin = Point2D( 0, 0 );
        Point2D xAxisVector = Point2D( 0.1, 0 );
        Point2D yAxisVector = Point2D( 0, 0.1 );

        Point2D deviceOrigin = vc->modelToDevice( origin );
        Point2D deviceXAxisVector = vc->modelToDevice( xAxisVector );
        Point2D deviceYAxisVector = vc->modelToDevice( yAxisVector );

        gc->setColor( 0xFF0000 );
        gc->drawLine(
            deviceOrigin.getX(), deviceOrigin.getY(),
            deviceXAxisVector.getX(), deviceXAxisVector.getY()
        );

        gc->setColor( 0x00FF00 );
        gc->drawLine(
            deviceOrigin.getX(), deviceOrigin.getY(),
            deviceYAxisVector.getX(), deviceYAxisVector.getY()
        );
    }

    // redraw shapes
    gc->setMode( GraphicsContext::MODE_NORMAL );
    sc.draw( gc, vc );
}


void DrawContext::keyDown( GraphicsContext *gc, unsigned int keycode )
{
    // std::cout << "Key Down: " << keycode << std::endl;

    switch ( keycode )
    {
        // NUMROW 0: set color random
        case DrawContext::KEY_CODE_0:
        {
            std::cout << "COLOR SET: RANDOM" << std::endl;
            double r = (( double ) ( rand() % 100 )) / 100;
            double g = (( double ) ( rand() % 100 )) / 100;
            double b = (( double ) ( rand() % 100 )) / 100;
            strokeSetColor( gc, Color( r, g, b ));
            break;
        }

        // NUMROW 1: set color black
        case DrawContext::KEY_CODE_1:
            std::cout << "COLOR SET: BLACK" << std::endl;
            strokeSetColor( gc, Color( 0, 0, 0 ));
            break;

        // NUMROW 2: set color gray
        case DrawContext::KEY_CODE_2:
            std::cout << "COLOR SET: GRAY" << std::endl;
            strokeSetColor( gc, Color( 0.4, 0.4, 0.4 ));
            break;

        // NUMROW 3: set color white
        case DrawContext::KEY_CODE_3:
            std::cout << "COLOR SET: WHITE" << std::endl;
            strokeSetColor( gc, Color( 1, 1, 1 ));
            break;

        // NUMROW 4: set color red
        case DrawContext::KEY_CODE_4:
            std::cout << "COLOR SET: RED" << std::endl;
            strokeSetColor( gc, Color( 1, 0, 0 ));
            break;

        // NUMROW 5: set color green
        case DrawContext::KEY_CODE_5:
            std::cout << "COLOR SET: GREEN" << std::endl;
            strokeSetColor( gc, Color( 0.1, 0.9, 0 ));
            break;

        // NUMROW 6: set color blue
        case DrawContext::KEY_CODE_6:
            std::cout << "COLOR SET: BLUE" << std::endl;
            strokeSetColor( gc, Color( 0.1, 0.3, 1 ));
            break;

        // NUMROW 7: set color cyan
        case DrawContext::KEY_CODE_7:
            std::cout << "COLOR SET: CYAN" << std::endl;
            strokeSetColor( gc, Color( 0, 0.8, 1 ));
            break;

        // NUMROW 8: set color magenta
        case DrawContext::KEY_CODE_8:
            std::cout << "COLOR SET: MAGENTA" << std::endl;
            strokeSetColor( gc, Color( 0.9, 0, 0.9 ));
            break;

        // NUMROW 9: set color yellow
        case DrawContext::KEY_CODE_9:
            std::cout << "COLOR SET: YELLOW" << std::endl;
            strokeSetColor( gc, Color( 1, 0.8, 0 ));
            break;

        // A: toggle draw axes
        case DrawContext::KEY_CODE_A:
            draw2DAxis = !draw2DAxis;
            std::cout << "DRAW 2D AXIS: " << ( draw2DAxis ? "ENABLED" : "DISABLED" ) << std::endl;
            paint( gc );
            break;

        // C: clear drawing
        case DrawContext::KEY_CODE_C:
            strokeCancel( gc );
            drawingClear( gc );
            break;

        // O: open drawing
        case DrawContext::KEY_CODE_O:
            drawingOpen( gc );
            break;

        // R: reset view
        case DrawContext::KEY_CODE_R:
            vc->resetView();
            paint( gc );
            break;

        // S: save drawing
        case DrawContext::KEY_CODE_S:
            drawingSave();
            break;

        // X: toggle x-axis snapping
        case DrawContext::KEY_CODE_X:
            snapToX = !snapToX;
            std::cout << "SNAP TO X: " << ( snapToX ? "ENABLED" : "DISABLED" ) << std::endl;
            break;

        // Y: toggle y-axis snapping
        case DrawContext::KEY_CODE_Y:
            snapToY = !snapToY;
            std::cout << "SNAP TO Y: " << ( snapToY ? "ENABLED" : "DISABLED" ) << std::endl;
            break;

        // ENTER: freeze drawing
        case DrawContext::KEY_CODE_ENTER:
            strokeFreeze( gc );
            break;

        // ESCAPE: reset drawing
        case DrawContext::KEY_CODE_ESC:
            strokeCancel( gc );
            break;

        // L-CTRL: toggle loop mode
        case DrawContext::KEY_CODE_LCTRL:
            toggleLoopMode( gc );
            break;

        // R-CTRL: toggle loop mode
        case DrawContext::KEY_CODE_RCTRL:
            toggleLoopMode( gc );
            break;

        default:
            break;
    }

}


void DrawContext::keyUp( GraphicsContext *gc, unsigned int keycode )
{
    // std::cout << "Key Up: " << keycode << std::endl;
}


void DrawContext::mouseButtonDown( GraphicsContext *gc, unsigned int button, int x, int y )
{

    // Point2D deviceCoords = Point2D( x, y );
    // Point2D modelCoords = vc->deviceToModel( deviceCoords );
    // std::cout << "Mouse Down: " << button << " at " << deviceCoords << " -> " << modelCoords << std::endl;

    if ( button == 1 && !panActive && !rotateActive )
    {
        strokeAddVert( gc, x, y );
    }
    else if ( button == 2 && !panActive && !rotateActive )
    {
        strokeCancel( gc );
        panActive = true;
        lastMousePosition = Point2D( x, y );
    }
    else if ( button == 3 && !panActive && !rotateActive )
    {
        strokeCancel( gc );
        rotateActive = true;
        lastMousePosition = Point2D( x, y );
    }
    else if ( button == 4 && !panActive && !rotateActive )
    {
        vc->scale( 1.05, 1.05 );
        paint( gc );
    }
    else if ( button == 5 && !panActive && !rotateActive )
    {
        vc->scale( 1 / 1.05, 1 / 1.05 );
        paint( gc );
    }
}


void DrawContext::mouseButtonUp( GraphicsContext *gc, unsigned int button, int x, int y )
{
    // std::cout << "Mouse Up: " << button << " at (" << x << ", " << y << ")" << std::endl;

    if ( button == 2 )
    {
        panActive = false;
    }

    else if ( button == 3 )
    {
        Point2D lastMouseVector = lastMousePosition - vc->modelToDevice( Point2D( 0, 0 ) );
        Point2D currentMouseVector = Point2D( x, y ) - vc->modelToDevice( Point2D( 0, 0 ) );
        vc->rotate( currentMouseVector.direction( lastMouseVector ) );
        paint( gc );
        rotateActive = false;
    }
}


void DrawContext::mouseMove( GraphicsContext *gc, int x, int y )
{
    // std::cout << "Mouse Move: (" << x << ", " << y << ")" << std::endl;

    // draw handler
    if ( !verts.empty() )
    {
        // get rubberbanding vert and most recently frozen vert
        Point2D *startVert = verts[0];
        Point2D *frozenVert = verts[verts.size() - 2];
        Point2D *rbVert = verts[verts.size() - 1];

        // erase old lines
        gc->drawLine(
            frozenVert->getX(), frozenVert->getY(),
            rbVert->getX(), rbVert->getY()
        );

        if (( verts.size() > 2 ) && loopMode )
        {
            gc->drawLine(
                startVert->getX(), startVert->getY(),
                rbVert->getX(), rbVert->getY()
            );
        }

        // adjust mouse coordinates for snapping
        if ( snapToX ) y = frozenVert->getY();
        if ( snapToY ) x = frozenVert->getX();

        // update rubberbanding vert
        rbVert->setX( x );
        rbVert->setY( y );

        // draw new line
        gc->drawLine(
            frozenVert->getX(), frozenVert->getY(),
            rbVert->getX(), rbVert->getY()
        );

        if (( verts.size() > 2 ) && loopMode )
        {
            gc->drawLine(
                startVert->getX(), startVert->getY(),
                rbVert->getX(), rbVert->getY()
            );
        }
    }

    // pan handler
    else if ( panActive )
    {
        Point2D currentMousePosition = Point2D( x, y );
        Point2D mouseDeltaModel = vc->deviceToModel( currentMousePosition ) - vc->deviceToModel( lastMousePosition );

        vc->translate( mouseDeltaModel.getX(), mouseDeltaModel.getY() );
        lastMousePosition = currentMousePosition;
        paint( gc );
    }

    // rotate handler
    else if ( rotateActive )
    {
        Point2D lastMouseVector = vc->deviceToModel( lastMousePosition ) - Point2D( 0, 0 );
        Point2D currentMouseVector = vc->deviceToModel( Point2D( x, y ) ) - Point2D( 0, 0 );

        double currentRotation = vc->getRotation();
        double deltaRotation = lastMouseVector.direction( currentMouseVector );

        vc->rotate( deltaRotation );
        paint( gc );
        vc->setRotation( currentRotation );
    }
}


/* ---------------------------- Private Functions --------------------------- */


/**
 * @brief   Adds a vertex to a stroke
 *
 * @param   *gc     The graphics context to draw the stroke to
 * @param   x       The x-coordinate of the vertex
 * @param   y       The y-coordinate of the vertex
 *
 * @return  void
 */
void DrawContext::strokeAddVert( GraphicsContext *gc, int x, int y )
{
    if ( verts.empty())
    {
        // set draw color and draw mode
        gc->setColor( drawColor.toX11() ^ Color( 1, 1, 1 ).toX11());
        gc->setMode( GraphicsContext::MODE_XOR );

        // add new verts
        verts.push_back( new Point2D( x, y ) );
        verts.push_back( new Point2D( x, y ) );

        // draw initial line
        Point2D *startVert = verts[0];
        Point2D *rbVert = verts[verts.size() - 1];
        gc->drawLine(
            startVert->getX(), startVert->getY(),
            rbVert->getX(), rbVert->getY()
        );
    }
    else
    {
        // adjust mouse coordinates for snapping
        Point2D * frozenVert = verts[verts.size() - 2];
        if ( snapToX ) y = frozenVert->getY();
        if ( snapToY ) x = frozenVert->getX();

        // freeze rubberbanding vert
        verts[verts.size() - 1]->setX( x );
        verts[verts.size() - 1]->setY( y );

        // add new rubberbanding vert
        verts.push_back( new Point2D( x, y ));

        // draw initial loop line
        if (( verts.size() == 3 ) & loopMode )
        {
            Point2D *startVert = verts[0];
            Point2D *rbVert = verts[verts.size() - 1];
            gc->drawLine(
                startVert->getX(), startVert->getY(),
                rbVert->getX(), rbVert->getY()
            );
        }
    }
}


/**
 * @brief   Freezes a stroke and converts it to a shape
 *
 * @param   *gc     The graphics context to draw the stroke to
 *
 * @return  void
 */
void DrawContext::strokeFreeze( GraphicsContext *gc )
{
    if ( !verts.empty())
    {
        // clear the rubberbanding lines
        strokeDrawLines( gc );

        // set draw mode to normal
        gc->setMode( GraphicsContext::MODE_NORMAL );

        // convert verts to model coordinates
        for ( unsigned int i = 0; i < verts.size(); i++ )
        {
            *verts[i] = vc->deviceToModel( *verts[i] );
        }

        // define and add shapes to container
        if ( !loopMode )
        {
            for ( unsigned int i = 0; i < ( verts.size() - 2 ); i++ )
            {
                Line line = Line( *verts[i], *verts[i + 1], drawColor );
                line.draw( gc, vc );
                sc.add( line );
            }
        }
        else if ( verts.size() == 3 )
        {
            Line line = Line( *verts[0], *verts[1], drawColor );
            line.draw( gc, vc );
            sc.add( line );
        }
        else if ( verts.size() == 4 )
        {
            Triangle triangle = Triangle( *verts[0], *verts[1], *verts[2], drawColor );
            triangle.draw( gc, vc );
            sc.add( triangle );
        }
        else
        {
            verts.erase( verts.begin() + ( verts.size() - 1 ));
            Polygon polygon = Polygon( verts, drawColor );
            polygon.draw( gc, vc );
            sc.add( polygon );
        }

        // clear verts
        strokeClearVerts();
    }
}


/**
 * @brief   Cancels a stroke
 *
 * @param   *gc     The graphics context to draw the stroke to
 *
 * @return  void
 */
void DrawContext::strokeCancel( GraphicsContext *gc )
{
    strokeDrawLines( gc );
    strokeClearVerts();
    gc->setMode( GraphicsContext::MODE_NORMAL );
}


/**
 * @brief   Clears the vertices from a stroke
 *
 * @param   void
 *
 * @return  void
 */
void DrawContext::strokeClearVerts()
{
    if ( !verts.empty())
    {
        // clear verts
        std::for_each(
            verts.begin(), verts.end(), []( Point2D *p )
            {
                delete p;
            }
        );
        verts.clear();
    }
}


/**
 * @brief   Sets the color of a stroke
 *
 * @param   *gc     The graphics context to draw the stroke to
 * @param   &color  The color of the stroke
 *
 * @return  void
 */
void DrawContext::strokeSetColor( GraphicsContext *gc, const Color &color )
{
    strokeDrawLines( gc );
    gc->setColor( color.toX11() ^ canvasColor.toX11());
    drawColor = color;
    strokeDrawLines( gc );
}


/**
 * @brief   Draws the lines of a stroke
 *
 * @param   *gc     The graphics context to draw the stroke to
 *
 * @return  void
 */
void DrawContext::strokeDrawLines( GraphicsContext *gc )
{
    if ( !verts.empty())
    {
        // draw all XOR lines
        for ( unsigned int i = 0; i < verts.size() - 1; i++ )
        {
            Point2D *curVert = verts[i];
            Point2D *nextVert = verts[i + 1];
            gc->drawLine(
                curVert->getX(), curVert->getY(),
                nextVert->getX(), nextVert->getY()
            );
        }

        // draw loop lines
        if (( verts.size() > 2 ) && loopMode )
        {
            Point2D *startVert = verts[0];
            Point2D *rbVert = verts[verts.size() - 1];
            gc->drawLine(
                startVert->getX(), startVert->getY(),
                rbVert->getX(), rbVert->getY()
            );
        }
    }
}


/**
 * @brief   Toggles loop mode
 *
 * @param   *gc     The graphics context to draw the stroke to
 *
 * @return  void
 */
void DrawContext::toggleLoopMode( GraphicsContext *gc )
{
    loopMode = !loopMode;

    if ( verts.size() > 2 )
    {
        Point2D *startVert = verts[0];
        Point2D *rbVert = verts[verts.size() - 1];
        gc->drawLine(
            startVert->getX(), startVert->getY(),
            rbVert->getX(), rbVert->getY()
        );
    }

    std::cout << "LOOP MODE: ";
    std::cout << ( loopMode ? "ENABLED" : "DISABLED" ) << std::endl;
}


/**
 * @brief   Clears the canvas and opens a new drawing from file
 *
 * @param   *gc     The graphics context to draw to
 *
 * @return  void
 */
void DrawContext::drawingOpen( GraphicsContext *gc )
{
    strokeCancel( gc );

    std::cout << "OPEN FILE: ";

    std::string fileName;
    std::cin >> fileName;

    std::ifstream filein( fileName.c_str());

    if ( !filein )
    {
        std::cerr << "ERROR: Invalid file name or location!" << std::endl;
    }
    else
    {
        drawingClear( gc );
        sc.in( filein );
        sc.draw( gc, vc );
        filein.close();
        std::cout << "FILE OPENED!" << std::endl;
    }

    vc->resetView();
    paint( gc );
}


/**
 * @brief   Saves the current drawing to a file
 *
 * @param   void
 *
 * @return  void
 */
void DrawContext::drawingSave()
{
    std::cout << "SAVE FILE: ";

    std::string fileName;
    std::cin >> fileName;

    std::ofstream fileout( fileName.c_str());

    if ( !fileout )
    {
        std::cerr << "ERROR: Invalid file name or location!" << std::endl;
    }
    else
    {
        fileout << sc;
        fileout.close();
        std::cout << "FILE SAVED!" << std::endl;
    }
}


/**
 * @brief   Clears the drawing canvas
 *
 * @param   *gc     The graphics context to clear
 *
 * @return  void
 */
void DrawContext::drawingClear( GraphicsContext *gc )
{
    std::string input;

    do
    {
        std::cout << "ARE YOU SURE YOU WANT TO CLEAR THE CANVAS? (Y/N): ";
        std::cin >> input;
        std::transform( input.begin(), input.end(), input.begin(), ::toupper);;
    } while ( input != "Y" && input != "N" );

    if ( input == "Y" )
    {
        strokeCancel( gc );
        sc.erase();
        vc->resetView();
        paint( gc );
        std::cout << "CANVAS CLEARED" << std::endl;
    }
    else
    {
        std::cout << "CLEAR CANCELLED" << std::endl;
    }

}


/* -------------------------------------------------------------------------- */