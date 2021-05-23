/* --------------------------------- Header --------------------------------- */


/**
 * @file    line.h
 * @brief   2D line shape class
 */


/* ------------------------------ Header Guard ------------------------------ */


# ifndef SHAPE_LINE_H
# define SHAPE_LINE_H


/* -------------------------------- Includes -------------------------------- */


# include "point2d.h"
# include "shape.h"


/* --------------------------------- Class ---------------------------------- */


class Line : public Shape
{
    /* =============================== PUBLIC =============================== */

public:

    /* --------------------- Constructors / Destructors --------------------- */


    Line( const Point2D &start, const Point2D &end );
    Line( const Point2D &start, const Point2D &end, const Color &color );
    Line( const Line &line );

    ~Line() override;


    /* ------------------------ Overloaded Operators ------------------------ */


    Line &operator=( const Line &line );

    const Point2D &operator[]( unsigned int index ) const override;
    Point2D &operator[]( unsigned int index ) override;


    /* ------------------------------ Functions ----------------------------- */


    void draw( GraphicsContext *gc, ViewContext *vc ) const override;
    Line *clone() const override;

    std::ostream &out( std::ostream &os ) const override;
    std::istream &in( std::istream &is ) override;


    /* =============================== PRIVATE ============================== */

private:

    /* ----------------------------- Attributes ----------------------------- */


    Vector2<Point2D*> verts;


    /* ------------------------------ Functions ----------------------------- */


    static Point2D midpoint( const Point2D &a, const Point2D &b );


    /* ====================================================================== */
};


/* ----------------------- Global Overloaded Operators ---------------------- */


std::ostream &operator<<( std::ostream &os, const Line &line );


/* --------------------------------- Footer --------------------------------- */


# endif // SHAPE_LINE_H


/* -------------------------------------------------------------------------- */