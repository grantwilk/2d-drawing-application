/* --------------------------------- Header --------------------------------- */


/**
 * @file    shape.cpp
 * @brief   
 */


/* -------------------------------- Includes -------------------------------- */


# include <sstream>
# include "shape.h"


/* ------------------------ Constructors / Destructors ---------------------- */


/**
 * @brief   Creates a black shape object with an origin at (0, 0)
 *
 * @param   void
 *
 * @return  The created shape
 */
Shape::Shape():
color( Color( 0, 0, 0 ) ), origin( Point2D( 0, 0 ) )
{}


/**
 * @brief   Creates a shape object with the specified color and an origin at
 *          (0, 0)
 *
 * @param   &color      The color of the shape
 *
 * @return  The created shape
 */
Shape::Shape( const Color &color ):
color( color ),
origin( Point2D( 0, 0 ) )
{}


/**
 * @brief   Creates a black shape object with an origin at the specified
 *          coordinates
 *
 * @param   &origin     The origin of the shape
 *
 * @return  The created shape
 */
Shape::Shape( const Point2D &origin ):
color( Color( 0, 0, 0 ) ), origin( origin )
{}


/**
 * @brief   Creates a shape with the specified color and an origin at the
 *          specified coordinates
 *
 * @param   &color      The color of the shape
 * @param   &origin     The origin of the shape
 *
 * @return  The created shape
 */
Shape::Shape( const Color &color, const Point2D &origin ):
color( color ), origin( origin )
{}


/**
 * @brief   Creates a shape from an existing shape
 *
 * @param   &shape  The shape to create from
 *
 * @return  The created shape
 */
Shape::Shape( const Shape &shape ):
color( shape.color ), origin( shape.origin )
{}


/**
* @brief   Shape destructor
*
* @param   void
*
* @return  void
*/
Shape::~Shape() = default;


/* -------------------------- Overloaded Operators -------------------------- */


/**
 * @brief   Converts a shape to a string and writes it to an output stream
 *
 * @param   &os         The output stream to write to
 * @param   &shape      The shape to convert
 *
 * @return  The output stream
 */
std::ostream &operator<<( std::ostream &os, const Shape &shape )
{
    shape.out( os );
    return os;
}


/* ---------------------------- Public Functions ---------------------------- */


/**
 * @brief   Gets the color of this shape
 *
 * @param   void
 *
 * @return  A reference to the color of this shape
 */
const Color &Shape::getColor() const
{
    return color;
}


/**
 * @brief   Gets the origin of this shape
 *
 * @param   void
 *
 * @return  A reference to the origin point of this shape
 */
const Point2D &Shape::getOrigin() const
{
    return origin;
}


/**
 * @brief   Sets the color of this shape
 *
 * @param   &color      The shape's color
 *
 * @return  void
 */
void Shape::setColor( const Color &color )
{
    this->color = color;
}


/**
 * @brief   Sets the origin of this shape
 *
 * @param   &origin     The shape's origin point
 *
 * @return  void
 */
void Shape::setOrigin( const Point2D &origin )
{
    this->origin = origin;
}


/**
 * @brief   Converts this shape to a string and flushes it to an output
 *          stream
 *
 * @param   &os     The output stream to write to
 *
 * @return  A reference to the output stream
 */
std::ostream &Shape::out( std::ostream &os ) const
{
    os << "SHAPE  COLOR( " << color[0] << " " << color[1] << " " << color[2] <<
       " )  ORIGIN( " << origin[0] << " " << origin[1] << " )";
    return os;
}


/**
 * @brief   Extracts a shape from an input stream and assigns it to this
 *          shape (NOTE: Does not advance the input stream)
 *
 * @param   &os     The input stream to extract from
 *
 * @return  A reference to the input stream
 */
std::istream &Shape::in( std::istream &is )
{
    // get description string and seek back
    std::string desc;
    std::streampos pos = is.tellg();
    std::getline( is, desc );
    is.seekg( pos, std::ios_base::beg );

    // tokenize the description string
    std::vector<std::string> tokens;
    std::stringstream ss = std::stringstream( desc );

    while( ss )
    {
        std::string token;
        ss >> token;
        tokens.push_back( token );
    }

    // validate that the line describes a shape
    if ( ( tokens.size() < 10 )     || ( tokens[0]  != "SHAPE" )  ||
         ( tokens[1]  != "COLOR(" ) || ( tokens[6]  != "ORIGIN(" ) )
    {
        throw ShapeException("Invalid shape description.");
    }

    // extract and set the line's color channels
    double colorRed = std::stod( tokens[2] );
    double colorGreen = std::stod( tokens[3] );
    double colorBlue = std::stod( tokens[4] );
    color = Color( colorRed, colorGreen, colorBlue );

    // extract and set the line's origin
    double originX = std::stod( tokens[7] );
    double originY = std::stod( tokens[8] );
    origin = Point2D( originX, originY );

    return is;
}


/* -------------------------------------------------------------------------- */