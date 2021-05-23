/* --------------------------------- Header --------------------------------- */


/**
 * @file    shape.h
 * @brief   2D shape class
 */


/* ------------------------------ Header Guard ------------------------------ */


# ifndef SHAPE_SHAPE_H
# define SHAPE_SHAPE_H


/* -------------------------------- Includes -------------------------------- */


# include <stdexcept>

# include "color.h"
# include "point2d.h"
# include "viewcontext.h"
# include "gcontext.h"


/* --------------------------------- Class ---------------------------------- */


class ShapeException : public std::runtime_error
{
public:
    explicit ShapeException( const std::string& msg ):
    std::runtime_error( ( std::string( "Shape Exception: " ) + msg ).c_str() )
    {}
};


class Shape
{
    /* =============================== PUBLIC =============================== */

public:

    /* --------------------- Constructors / Destructors --------------------- */


    Shape();
    explicit Shape( const Color &color );
    explicit Shape( const Point2D &origin );
    Shape( const Color &color, const Point2D &origin );
    Shape( const Shape &shape );

    virtual ~Shape();


    /* ------------------------ Overloaded Operators ------------------------ */


    virtual const Point2D &operator[]( unsigned int index ) const = 0;
    virtual Point2D &operator[]( unsigned int index ) = 0;


    /* ------------------------------ Functions ----------------------------- */


    virtual void draw( GraphicsContext *gc, ViewContext *vc ) const = 0;
    virtual Shape *clone() const = 0;

    const Color &getColor() const;
    const Point2D &getOrigin() const;

    void setColor( const Color &color );
    void setOrigin( const Point2D &origin );

    virtual std::ostream &out( std::ostream &os ) const;
    virtual std::istream &in( std::istream &is );


    /* ============================== PROTECTED ============================= */

protected:

    /* ----------------------------- Attributes ----------------------------- */


    Color color;
    Point2D origin;


    /* =============================== PRIVATE ============================== */

private:

    /* ====================================================================== */
};


/* ----------------------- Global Overloaded Operators ---------------------- */


std::ostream &operator<<( std::ostream &os, const Shape &shape );


/* --------------------------------- Footer --------------------------------- */


# endif // SHAPE_SHAPE_H


/* -------------------------------------------------------------------------- */