/* --------------------------------- Header --------------------------------- */


/**
 * @file    viewcontext.h
 * @brief   View context for view transformations
 */


/* ------------------------------ Header Guard ------------------------------ */


# ifndef GRAPHICS_CONTEXT_VIEWCONTEXT_H
# define GRAPHICS_CONTEXT_VIEWCONTEXT_H


/* -------------------------------- Includes -------------------------------- */


# include "matrix.h"
# include "point2d.h"
# include "gcontext.h"


/* --------------------------------- Class ---------------------------------- */


class ViewContext
{
    /* =============================== PUBLIC =============================== */

public:

    /* ----------------------------- Attributes ----------------------------- */


    constexpr static const double DEFAULT_VIEW_TRANSLATION_X = 0;
    constexpr static const double DEFAULT_VIEW_TRANSLATION_Y = 0;
    constexpr static const double DEFAULT_VIEW_ROTATION = 0;
    constexpr static const double DEFAULT_VIEW_SCALE_X = 400;
    constexpr static const double DEFAULT_VIEW_SCALE_Y = 400;


    /* --------------------- Constructors / Destructors --------------------- */


    explicit ViewContext( GraphicsContext *gc );
    ~ViewContext();


    /* ------------------------------ Functions ----------------------------- */


    Point2D modelToDevice( const Point2D &p );
    Point2D deviceToModel( const Point2D &p );

    void translate( double x, double y );
    void rotate( double r );
    void scale( double x, double y );

    void setTranslation( double x, double y );
    void setRotation( double r );
    void setScale( double x, double y );

    double getTranslationX();
    double getTranslationY();
    double getRotation();
    double getScaleX();
    double getScaleY();

    void resetTranslation();
    void resetRotation();
    void resetScale();
    void resetView();

    void update();

    std::ostream &out( std::ostream &os ) const;


    /* ============================== PROTECTED ============================= */

protected:

    /* =============================== PRIVATE ============================== */

private:

    /* ----------------------------- Attributes ----------------------------- */


    Matrix<double> transform = Matrix<double>( 3, 3 );
    Matrix<double> invTransform = Matrix<double>( 3, 3 );

    double viewTranslationX = DEFAULT_VIEW_TRANSLATION_X;
    double viewTranslationY = DEFAULT_VIEW_TRANSLATION_Y;
    double viewRotation = DEFAULT_VIEW_ROTATION;
    double viewScaleX = DEFAULT_VIEW_SCALE_X;
    double viewScaleY = DEFAULT_VIEW_SCALE_Y;

    GraphicsContext *gc;


    /* ------------------------------ Functions ----------------------------- */


    Matrix<double> genViewTranslationMatrix() const;
    Matrix<double> genViewRotationMatrix() const;
    Matrix<double> genViewScaleMatrix() const;

    Matrix<double> genInvViewTranslationMatrix() const;
    Matrix<double> genInvViewRotationMatrix() const;
    Matrix<double> genInvViewScaleMatrix() const;

    Matrix<double> genScreenTranslationMatrix() const;
    Matrix<double> genScreenFlipMatrix() const;

    Matrix<double> genInvScreenTranslationMatrix() const;
    Matrix<double> genInvScreenFlipMatrix() const;


    /* ====================================================================== */
};


/* ----------------------- Global Overloaded Operators ---------------------- */


std::ostream &operator<<( std::ostream &os, const ViewContext &vc );


/* --------------------------------- Footer --------------------------------- */


# endif // GRAPHICS_CONTEXT_VIEWCONTEXT_H


/* -------------------------------------------------------------------------- */