/* --------------------------------- Header --------------------------------- */


/**
 * @file    viewcontext.cpp
 * @brief   View context for view transformations
 */


/* -------------------------------- Includes -------------------------------- */


# include <cmath>

# include "viewcontext.h"


/* ----------------------- Constructors / Destructors ----------------------- */


/**
 * @brief   Creates a view context object
 *
 * @param   *gc     The graphics context to pair with this view context
 *
 * @return  The created view context
 */
ViewContext::ViewContext( GraphicsContext *gc ) :
    gc( gc )
{
    update();
}


/**
 * @brief   View context destructor
 *
 * @param   void
 *
 * @return  void
 */
ViewContext::~ViewContext() = default;


/* ---------------------------- Public Functions ---------------------------- */


/**
 * @brief   Transforms a 2D model point to a 2D device point through the view
 *          context's view transformation matrix
 *
 * @param   &p  The 2D model point to transform
 *
 * @return  The transformed 2D device point
 */
Point2D ViewContext::modelToDevice( const Point2D &p )
{
    return Point2D( transform * p );
}


/**
 * @brief   Transforms a 2D device point to a 2D model point through the view
 *          context's view transformation matrix
 *
 * @param   &p  The 2D device point to transform
 *
 * @return  The transformed 2D model point
 */
Point2D ViewContext::deviceToModel( const Point2D &p )
{
    return Point2D( invTransform * p );
}


/**
 * @brief   Applies a view translation to the transformation matrix
 *
 * @param   x   The magnitude of the translation along the +x axis in pixels
 * @param   y   The magnitude of the translation along the +y axis in pixels
 *
 * @return  void
 */
void ViewContext::translate( double x, double y )
{
    setTranslation( viewTranslationX + x, viewTranslationY + y );
}


/**
 * @brief   Applies a view rotation to the transformation matrix
 *
 * @param   r   The magnitude of the rotation in radians
 *
 * @return  void
 */
void ViewContext::rotate( double r )
{
    setRotation( viewRotation + r );
}


/**
 * @brief   Applies a view scale to the transformation matrix
 *
 * @param   x   The magnitude of the viewScale along the +x axis
 * @param   y   The magnitude of the viewScale along the +y axis
 *
 * @return  void
 */
void ViewContext::scale( double x, double y )
{
    setScale( viewScaleX * x, viewScaleY * y );
}


/**
 * @brief   Sets the translation of the view context's transformation matrix
 *
 * @param   x   The translation along the +x axis in pixels
 * @param   y   The translation along the +y axis in pixels
 *
 * @return  void
 */
void ViewContext::setTranslation( double x, double y )
{
    viewTranslationX = x;
    viewTranslationY = y;
    update();
}


/**
 * @brief   Sets the rotation of the view context's transformation matrix
 *
 * @param   r   The rotation in radians
 *
 * @return  void
 */
void ViewContext::setRotation( double r )
{
    viewRotation = r;
    update();
}


/**
 * @brief   Sets the scale of the view context's transformation matrix
 *
 * @param   x   The scale along the +x axis
 * @param   y   The scale along the +y axis
 *
 * @return  void
 */
void ViewContext::setScale( double x, double y )
{
    viewScaleX = x;
    viewScaleY = y;
    update();
}


/**
 * @brief   Gets the current x-translation of the view context's transformation
 *          matrix in radians
 *
 * @param   void
 *
 * @return  The current x-translation of the view context's transformation
 *          matrix in radians
 */
double ViewContext::getTranslationX()
{
    return viewTranslationX;
}


/**
 * @brief   Gets the current y-translation of the view context's transformation
 *          matrix in radians
 *
 * @param   void
 *
 * @return  The current y-translation of the view context's transformation
 *          matrix in radians
 */
double ViewContext::getTranslationY()
{
    return viewTranslationY;
}


/**
 * @brief   Gets the current rotation of the view context's transformation
 *          matrix in radians
 *
 * @param   void
 *
 * @return  The current rotation of the view context's transformation matrix
 *          in radians
 */
double ViewContext::getRotation()
{
    return viewRotation;
}


/**
 * @brief   Gets the current x-scale of the view context's transformation
 *          matrix in radians
 *
 * @param   void
 *
 * @return  The current x-scale of the view context's transformation
 *          matrix in radians
 */
double ViewContext::getScaleX()
{
    return viewScaleX;
}


/**
 * @brief   Gets the current y-scale of the view context's transformation
 *          matrix in radians
 *
 * @param   void
 *
 * @return  The current y-scale of the view context's transformation
 *          matrix in radians
 */
double ViewContext::getScaleY()
{
    return viewScaleY;
}


/**
 * @brief   Resets the view translation of the transformation matrix
 *
 * @param   void
 *
 * @return  void
 */
void ViewContext::resetTranslation()
{
    setTranslation( DEFAULT_VIEW_TRANSLATION_X, DEFAULT_VIEW_TRANSLATION_Y );
}


/**
 * @brief   Resets the view rotation of the transformation matrix
 *
 * @param   void
 *
 * @return  void
 */
void ViewContext::resetRotation()
{
    setRotation( DEFAULT_VIEW_ROTATION );
}


/**
 * @brief   Resets the view scale of the transformation matrix
 *
 * @param   void
 *
 * @return  void
 */
void ViewContext::resetScale()
{
    setScale( DEFAULT_VIEW_SCALE_X, DEFAULT_VIEW_SCALE_Y );
}


/**
 * @brief   Resets the view transformation matrix
 *
 * @param   void
 *
 * @return  void
 */
void ViewContext::resetView()
{
    resetTranslation();
    resetRotation();
    resetScale();
}


/**
 * @brief   Updates the view context's transformation matrices
 *
 * @param   void
 *
 * @return  void
 */
void ViewContext::update()
{
    // determine transformation matrix
    transform =
            genScreenTranslationMatrix() *
            genScreenFlipMatrix()        *
            genViewScaleMatrix()         *
            genViewRotationMatrix()      *
            genViewTranslationMatrix();

    // determine inverse transformation matrix
    invTransform =
            genInvViewTranslationMatrix()    *
            genInvViewRotationMatrix()       *
            genInvViewScaleMatrix()          *
            genInvScreenFlipMatrix()         *
            genInvScreenTranslationMatrix();
}


/**
 * @brief   Writes the current transformation matrix to the output stream
 *
 * @param   &os     The output stream to write to
 *
 * @return  The output stream
 */
std::ostream &ViewContext::out( std::ostream &os ) const
{
    transform.out( os );
    return os;
}


/* ---------------------------- Private Functions --------------------------- */


/**
 * @brief   Generates the view translation matrix from internal parameters
 *
 * @param   void
 *
 * @return  The view translation matrix
 */
Matrix<double> ViewContext::genViewTranslationMatrix() const
{
    Matrix<double> viewTranslationMatrix = Matrix<double>( 3, 3 );

    viewTranslationMatrix[0][0] = 1;
    viewTranslationMatrix[1][1] = 1;
    viewTranslationMatrix[2][2] = 1;

    viewTranslationMatrix[0][2] = viewTranslationX;
    viewTranslationMatrix[1][2] = viewTranslationY;

    // std::cout << std::endl << "View Translation: " << std::endl;
    // viewTranslationMatrix.out(std::cout);

    return viewTranslationMatrix;
}


/**
 * @brief   Generates the view rotation matrix from internal parameters
 *
 * @param   void
 *
 * @return  The view rotation matrix
 */
Matrix<double> ViewContext::genViewRotationMatrix() const
{
    Matrix<double> viewRotationMatrix = Matrix<double>( 3, 3 );

    viewRotationMatrix[2][2] = 1;

    viewRotationMatrix[0][0] = cos( viewRotation );
    viewRotationMatrix[0][1] = -sin( viewRotation );
    viewRotationMatrix[1][0] = sin( viewRotation );
    viewRotationMatrix[1][1] = cos( viewRotation );

    // std::cout << std::endl << "View Rotation: " << std::endl;
    // viewRotationMatrix.out(std::cout);

    return viewRotationMatrix;
}


/**
 * @brief   Generates the view scale matrix from internal parameters
 *
 * @param   void
 *
 * @return  The view scale matrix
 */
Matrix<double> ViewContext::genViewScaleMatrix() const
{
    Matrix<double> viewScaleMatrix = Matrix<double>( 3, 3 );

    viewScaleMatrix[0][0] = viewScaleX;
    viewScaleMatrix[1][1] = viewScaleY;
    viewScaleMatrix[2][2] = 1;

    // std::cout << std::endl << "View Scale: " << std::endl;
    // viewScaleMatrix.out(std::cout);

    return viewScaleMatrix;
}


/**
 * @brief   Generates the inverse view translation matrix from internal parameters
 *
 * @param   void
 *
 * @return  The inverse view translation matrix
 */
Matrix<double> ViewContext::genInvViewTranslationMatrix() const
{
    Matrix<double> invViewTranslationMatrix = genViewTranslationMatrix();

    invViewTranslationMatrix[0][2] = -1 * invViewTranslationMatrix[0][2];
    invViewTranslationMatrix[1][2] = -1 * invViewTranslationMatrix[1][2];

    // std::cout << std::endl << "Inverse View Translation: " << std::endl;
    // invViewTranslationMatrix.out(std::cout);

    return invViewTranslationMatrix;
}


/**
 * @brief   Generates the inverse view rotation matrix from internal parameters
 *
 * @param   void
 *
 * @return  The inverse view rotation matrix
 */
Matrix<double> ViewContext::genInvViewRotationMatrix() const
{
    Matrix<double> invViewRotationMatrix = genViewRotationMatrix();

    invViewRotationMatrix = ~invViewRotationMatrix;

    // std::cout << std::endl << "Inverse View Rotation: " << std::endl;
    // invViewRotationMatrix.out(std::cout);

    return invViewRotationMatrix;
}


/**
 * @brief   Generates the inverse view scale matrix from internal parameters
 *
 * @param   void
 *
 * @return  The inverse view scale matrix
 */
Matrix<double> ViewContext::genInvViewScaleMatrix() const
{
    Matrix<double> invViewScaleMatrix = genViewScaleMatrix();

    invViewScaleMatrix[0][0] = 1 / invViewScaleMatrix[0][0];
    invViewScaleMatrix[1][1] = 1 / invViewScaleMatrix[1][1];

    // std::cout << std::endl << "Inverse View Scale: " << std::endl;
    // invViewScaleMatrix.out(std::cout);

    return invViewScaleMatrix;
}


/**
 * @brief   Generates the screen translation matrix from internal parameters
 *
 * @param   void
 *
 * @return  The screen translation matrix
 */
Matrix<double> ViewContext::genScreenTranslationMatrix() const
{
    Matrix<double> screenTranslationMatrix = Matrix<double>( 3, 3 );

    screenTranslationMatrix[0][0] = 1;
    screenTranslationMatrix[1][1] = 1;
    screenTranslationMatrix[2][2] = 1;

    screenTranslationMatrix[0][2] = ( ( double ) gc->getWindowWidth() ) / 2;
    screenTranslationMatrix[1][2] = ( ( double ) gc->getWindowHeight() ) / 2;

    // std::cout << std::endl << "Screen Translation: " << std::endl;
    // screenTranslationMatrix.out( std::cout);

    return screenTranslationMatrix;
}


/**
 * @brief   Generates the screen flip matrix from internal parameters
 *
 * @param   void
 *
 * @return  The screen flip matrix
 */
Matrix<double> ViewContext::genScreenFlipMatrix() const
{
    Matrix<double> screenFlipMatrix = Matrix<double>( 3, 3 );

    screenFlipMatrix[0][0] = 1;
    screenFlipMatrix[1][1] = -1;
    screenFlipMatrix[2][2] = 1;

    // std::cout << std::endl << "Screen Flip: " << std::endl;
    // screenFlipMatrix.out( std::cout);

    return screenFlipMatrix;
}


/**
 * @brief   Generates the inverse screen translation matrix from internal parameters
 *
 * @param   void
 *
 * @return  The inverse screen translation matrix
 */
Matrix<double> ViewContext::genInvScreenTranslationMatrix() const
{
    Matrix<double> invScreenTranslationMatrix = genScreenTranslationMatrix();

    invScreenTranslationMatrix[0][2] = -1 * invScreenTranslationMatrix[0][2];
    invScreenTranslationMatrix[1][2] = -1 * invScreenTranslationMatrix[1][2];

    // std::cout << std::endl << "Inverse Screen Translation: " << std::endl;
    // invScreenTranslationMatrix.out( std::cout);

    return invScreenTranslationMatrix;
}


/**
 * @brief   Generates the inverse screen flip matrix from internal parameters
 *
 * @param   void
 *
 * @return  The inverse screen flip matrix
 */
Matrix<double> ViewContext::genInvScreenFlipMatrix() const
{
    Matrix<double> invScreenFlipMatrix = genScreenFlipMatrix();

    invScreenFlipMatrix[0][0] = 1 / invScreenFlipMatrix[0][0];
    invScreenFlipMatrix[1][1] = 1 / invScreenFlipMatrix[1][1];

    // std::cout << std::endl << "Inverse Screen Flip: " << std::endl;
    // invScreenFlipMatrix.out( std::cout);

    return invScreenFlipMatrix;
}


/* -------------------------- Overloaded Operators -------------------------- */


/**
 * @brief   Writes a view context's transformation matrix to the output stream
 *
 * @param   &os     The output stream to write to
 * @param   &vc     The view context to write
 *
 * @return  The output stream
 */
std::ostream &operator<<( std::ostream &os, const ViewContext &vc )
{
    vc.out( os );
    return os;
}


/* -------------------------------------------------------------------------- */