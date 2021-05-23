/* --------------------------------- Header --------------------------------- */


/**
 * @file    line.cpp
 * @brief   Line shape
 */


/* -------------------------------- Includes -------------------------------- */


# include <sstream>

# include "line.h"
# include "viewcontext.h"


/* ----------------------- Constructors / Destructors ----------------------- */


/**
 * @brief   Creates a black line from two points
 *
 * @param   &start  The starting point of the line
 * @param   &end    The ending point of the line
 *
 * @return  The created line
 */
Line::Line( const Point2D &start, const Point2D &end ):
Line( start, end, Color( 0, 0, 0 ) )
{}


/**
 * @brief   Creates a colored line from two points
 *
 * @param   &start  The starting point of the line
 * @param   &end    The ending point of the line
 * @param   &color  The color of the line
 *
 * @return  The created line
 */
Line::Line( const Point2D &start, const Point2D &end, const Color &color ):
Shape( color, midpoint( start, end ) ),
verts( Vector2<Point2D*>( start.clone(), end.clone() ) )
{}


/**
 * @brief   Creates a line from an existing line
 *
 * @param   &line   The line to create from
 *
 * @return  The created line
 */
Line::Line( const Line &line ):
Shape( line.color, line.origin ), verts( line.verts )
{}


/**
 * @brief   Line destructor
 *
 * @param   void
 *
 * @return  void
 */
Line::~Line()
{
    Point2D::vector2DeepDelete( verts );
}


/* -------------------------- Overloaded Operators -------------------------- */


/**
 * @brief   Assigns a line to this line
 *
 * @param   &line   The line to assign to this line
 *
 * @return  A reference to this line
 */
Line &Line::operator=( const Line &line )
{
    Point2D::vector2DeepDelete( verts );

    this->verts = Point2D::vector2DeepCopy( line.verts );
    this->color = line.color;
    this->origin = line.origin;

    return *this;
}


/**
 * @brief   Gets an immutable reference to the vertex at the specified index
 *
 * @param   index   The index of the vertex
 *
 * @return  An immutable reference to the vertex at the specified index
 */
const Point2D &Line::operator[]( unsigned int index ) const
{
    return *verts[index];
}


/**
 * @brief   Gets a mutable reference to the vertex at the specified index
 *
 * @param   index   The index of the vertex
 *
 * @return  A mutable reference to the vertex at the specified index
 */
Point2D &Line::operator[]( unsigned int index )
{
    return *verts[index];
}


/**
 * @brief   Converts a line to a string and writes it to an output stream
 *
 * @param   &os     The output stream to write to
 * @param   &line   The line to convert
 *
 * @return  The output stream
 */
std::ostream &operator<<( std::ostream &os, const Line &line )
{
    line.out( os );
    return os;
}


/* ---------------------------- Public Functions ---------------------------- */


/**
 * @brief   Draws this line to an graphics context
 *
 * @param   *gc     The graphics context to draw to
 * @param   *vc     The view context to draw with
 *
 * @return  void
 */
void Line::draw( GraphicsContext *gc, ViewContext *vc ) const
{
    // convert from model to device coordinates
    Point2D start = vc->modelToDevice( *verts[0] );
    Point2D end = vc->modelToDevice( *verts[1] );

    // set color
    gc->setColor( color.toX11() );

    // draw line
    gc->drawLine(
        ( int ) start.getX(), ( int ) start.getY(),
        ( int ) end.getX(),   ( int ) end.getY()
    );
}


/**
 * @brief   Clones this line
 *
 * @param   void
 *
 * @return  The cloned copy of this line
 */
Line *Line::clone() const
{
    return new Line( *verts[0], *verts[1], color );
}


/**
 * @brief   Converts this line to a string and flushes it to an output
 *          stream
 *
 * @param   &os     The output stream to write to
 *
 * @return  A reference to the output stream
 */
std::ostream &Line::out( std::ostream &os ) const
{
    Shape::out( os );
    os << "  VERTICES( " << *verts[0] << " " << *verts[1] << " )";
    return os;
}


/**
 * @brief   Extracts a line from an input stream and assigns it to this
 *          line
 *
 * @param   &os     The input stream to extract from
 *
 * @return  A reference to the input stream
 */
std::istream &Line::in( std::istream &is )
{
    // process shape attributes
    Shape::in( is );

    // get description string
    std::string desc;
    std::getline( is, desc );

    // tokenize the description string
    std::vector<std::string> tokens;
    std::stringstream ss = std::stringstream( desc );

    while( ss )
    {
        std::string token;
        ss >> token;
        tokens.push_back( token );
    }

    // validate that the line describes a line
    if ( ( tokens.size() != 21 )  || ( tokens[10] != "VERTICES(" ) ||
         ( tokens[11] != "POINT2D(" ) || ( tokens[15] != "POINT2D(" )  )
    {
        throw ShapeException("Invalid line description.");
    }

    // extract and set the line's vertices
    double startX = std::stod( tokens[ 12 ] );
    double startY = std::stod( tokens[ 13 ] );
    double endX = std::stod( tokens[ 16 ] );
    double endY = std::stod( tokens[ 17 ] );

    Point2D::vector2DeepDelete( verts );
    verts = Vector2<Point2D*>(
        new Point2D( startX, startY),
        new Point2D( endX, endY )
    );

    return is;
}


/* ---------------------------- Private Functions --------------------------- */


/**
 * @brief   Determines the midpoint between two points
 *
 * @param   &a   The first point
 * @param   &b   The second point
 *
 * @return  The midpoint between two points
 */
Point2D Line::midpoint( const Point2D &a, const Point2D &b )
{
    return Point2D( ( a.getX() + b.getX() ) / 2, ( a.getY() + b.getY() ) / 2 );
}


/* -------------------------------------------------------------------------- */