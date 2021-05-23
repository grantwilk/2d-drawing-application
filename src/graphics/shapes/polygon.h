/* --------------------------------- Header --------------------------------- */


/**
 * @file    polygon.h
 * @brief   2D polygon shape class
 */


/* ------------------------------ Header Guard ------------------------------ */


# ifndef SHAPE_POLYGON_H
# define SHAPE_POLYGON_H


/* -------------------------------- Includes -------------------------------- */


# include "point2d.h"
# include "shape.h"


/* --------------------------------- Class ---------------------------------- */


class Polygon : public Shape
{
    /* =============================== PUBLIC =============================== */

public:

    /* --------------------- Constructors / Destructors --------------------- */


    explicit Polygon( const std::vector<Point2D*> &verts );
    Polygon( const std::vector<Point2D*> &verts, const Color &color );
    Polygon( const Polygon &polygon );

    ~Polygon() override;


    /* ------------------------ Overloaded Operators ------------------------ */


    Polygon &operator=( const Polygon &polygon );

    const Point2D &operator[]( unsigned int index ) const override;
    Point2D &operator[]( unsigned int index ) override;


    /* ------------------------------ Functions ----------------------------- */


    void draw( GraphicsContext *gc, ViewContext *vc ) const override;
    Polygon *clone() const override;

    std::ostream &out( std::ostream &os ) const override;
    std::istream &in( std::istream &is ) override;


    /* =============================== PRIVATE ============================== */

private:

    /* ----------------------------- Attributes ----------------------------- */


    std::vector<Point2D*> verts;


    /* ------------------------------ Functions ----------------------------- */


    static Point2D midpoint( const std::vector<Point2D*> &verts );


    /* ====================================================================== */
};


/* ----------------------- Global Overloaded Operators ---------------------- */


std::ostream &operator<<( std::ostream &os, const Polygon &polygon );


/* --------------------------------- Footer --------------------------------- */


# endif // SHAPE_POLYGON_H


/* -------------------------------------------------------------------------- */