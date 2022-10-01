
#include <memory>
#include <iostream>
#include <cstdio>
#include <sstream>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>

#include <png.h>

std::string data = "56,78^56,80^57,81^57,83^58,85^58,89^59,91^59,98^60,100^60,109^61,112^61,138^62,140^62,147^0,65535^151,79^151,81^152,81^152,83^153,85^153,88^154,90^154,101^155,104^155,115^156,117^156,121^157,122^157,125^158,127^158,131^159,133^159,137^160,140^160,150^0,65535^~";
struct coord
{
    int x;
    int y;
};
std::ostream& operator<<(std::ostream& os, coord c)
{
    return os << c.x << "," << c.y;
}
bool operator==(coord lhs, coord rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
coord& operator-=(coord& lhs, coord rhs)
{
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    return lhs;
}
coord operator-(coord lhs, coord rhs)
{
    return lhs -= rhs;
}
coord& operator+=(coord& lhs, coord rhs)
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
}
coord operator+(coord lhs, coord rhs)
{
    return lhs += rhs;
}
const coord end_of_stroke = { 0, 65535 };
struct image_buffer
{
    explicit image_buffer(coord res) :
        resolution(res),
        buf(resolution.x * resolution.y, 0xFF)
    {}
    coord resolution;
    std::vector<unsigned char> buf;
};
typedef std::vector<coord> stroke_type;
std::ostream& operator<<(std::ostream& os, const stroke_type stroke)
{
    std::string sep = "";
    for ( size_t i = 0; i < stroke.size(); ++i )
    {
        os << sep << stroke[i];
        sep = "^";
    }
    return os;
}
typedef std::vector<stroke_type> strokes_type;
std::ostream& operator<< (std::ostream& os, const strokes_type strokes)
{
    std::string sep = "";
    for ( size_t i = 0; i < strokes.size(); ++i )
    {
        os << sep << strokes[i];
        sep = "\n";
    }
    return os;
}

strokes_type line_to_strokes(const std::string& line)
{
    size_t pos = 0;
    strokes_type result;
    bool new_stroke = true;
    while ( pos < line.size() )
    {
        if ( line.at(pos) == '~' )
        {
            return result;
        }
        size_t delim = line.find_first_of("^", pos);
        coord c = { 0, 65535 };
        sscanf(line.data()+pos, "%d,%d", &c.x, &c.y);
        if ( c == end_of_stroke )
        {
            new_stroke = true;
        }
        else
        {
            if ( new_stroke )
            {
                new_stroke = false;
                result.push_back(stroke_type());
            }
            result.back().push_back(c);
        }
        pos = delim;
        if ( pos != std::string::npos ) ++pos; // start of next coord
    }
    return result;
}

strokes_type sig_to_strokes(std::istream& is)
{
    std::string line;
    strokes_type result;
    while ( std::getline(is, line) )
    {
        // newline is a new stroke. because.
        const strokes_type& next_strokes = line_to_strokes(line);
        result.insert(result.end(), next_strokes.begin(), next_strokes.end());
    }
    return result;
}

void draw_pixel(coord c, image_buffer& image)
{
    if ( c.x < 0 || c.x > image.resolution.x ) throw std::runtime_error("x coord out of range");
    if ( c.y < 0 || c.y > image.resolution.y ) throw std::runtime_error("y coord out of range");
    size_t coord_pos = c.y * image.resolution.x + c.x;
    image.buf[coord_pos] = 0x0;
}

void draw_point(coord c, size_t point_size, image_buffer& image)
{
    if ( c.x < 0 || c.x > image.resolution.x ) throw std::runtime_error("x coord out of range");
    if ( c.y < 0 || c.y > image.resolution.y ) throw std::runtime_error("y coord out of range");

    /**
     * need to figure out algo to increase point size.
     * 1 - single pixel, width 1
     * 2 - 4 pixels, width 2
     * 3 - 9 pixels, width 3
     * 4 - 16 pixels, width 4
     * etc
     */
    std::vector<coord> pixels_in_point;
    const int offset = point_size / 2;
    for ( size_t xi = 0; xi < point_size; ++xi )
    {
        for ( size_t yi = 0; yi < point_size; ++yi )
        {
            coord pixel = { int(xi + c.x) - offset, int(yi + c.y) - offset };
            if ( pixel.x < 0 || pixel.x > image.resolution.x ) continue;
            if ( pixel.y < 0 || pixel.y > image.resolution.y ) continue;
            draw_pixel(pixel, image);
        }
    }
}

void draw_line(coord from, coord to, size_t pen_size, image_buffer& image)
{
    // draw all points on the line
    // https://gamedev.stackexchange.com/questions/71299/how-do-you-draw-a-straight-line-between-two-points-in-a-bitmap
    float x = from.x;
    float y = from.y;
    float vec_x = to.x - from.x;
    float vec_y = to.y - from.y;
    const float max = std::max(std::fabs(vec_x), std::fabs(vec_y));
    vec_x /= max;
    vec_y /= max;
    for (float n = 0; n < max; ++n)
    {
        coord draw_at = { static_cast<int>(x), static_cast<int>(y) };
        draw_point(draw_at, pen_size, image);
        x += vec_x;
        y += vec_y;
    }
}

void draw_stroke(const stroke_type& stroke, size_t pen_size, image_buffer& image)
{
    if ( stroke.size() == 1 )
    {
        draw_point(stroke[0], pen_size, image);
    }
    else
    {
        for ( size_t i = 1; i < stroke.size(); ++i )
        {
            draw_line(stroke[i-1], stroke[i], pen_size, image);
        }
    }
}

void draw_strokes(const strokes_type& strokes, size_t pen_size, image_buffer& image)
{
    for ( size_t i = 0; i < strokes.size(); ++i )
    {
        draw_stroke(strokes[i], pen_size, image);
    }
}

coord strokes_dimensions(const strokes_type& strokes)
{
    coord dimensions = { 0, 0 };
    for ( auto&& stroke : strokes )
    {
        for ( auto&& coord : stroke )
        {
            if ( coord.x > dimensions.x ) dimensions.x = coord.x;
            if ( coord.y > dimensions.y ) dimensions.y = coord.y;
        }
    }
    return dimensions;
}

void strokes_to_png(const strokes_type& strokes)
{
    //determine this later
    const coord boundary_size = { 20, 20 };
    const coord resolution = strokes_dimensions(strokes) + boundary_size;
    const size_t resolution_x = resolution.x;
    const size_t resolution_y = resolution.y;
    png_structp png_ptr;
    png_infop info_ptr;

    // was debugging:
    //FILE* fp = std::fopen("./my.png", "wb");
    //if (fp == NULL) throw std::runtime_error("fopen(\"./my.png\", \"wb\") returned NULL");
    //std::unique_ptr<FILE, int(*)(FILE*)> filecloser(fp, &std::fclose);

    /* Create and initialize the png_struct with the desired error handler
     * functions.  If you want to use the default stderr and longjump method,
     * you can supply NULL for the last three parameters.  We also check that
     * the library version is compatible with the one used at compile time,
     * in case we are using dynamically linked libraries.  REQUIRED.
     */
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png_ptr == NULL)
    {
        throw std::runtime_error("png_create_write_struct returned NULL");
    }

    /* Allocate/initialize the image information data.  REQUIRED. */
    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL)
    {
        png_destroy_write_struct(&png_ptr,  NULL);
        throw std::runtime_error("png_create_info_struct returned NULL");
    }

    /* Set up error handling.  REQUIRED if you aren't supplying your own
     * error handling functions in the png_create_write_struct() call.
     */
    if (setjmp(png_jmpbuf(png_ptr)))
    {
        /* If we get here, we had a problem writing the file. */
        png_destroy_write_struct(&png_ptr, &info_ptr);
        throw std::runtime_error("setjump(png_jmpbuf(png_ptr)) returned non-zero");
    }

    //png_init_io(png_ptr, fp); // debug
    png_init_io(png_ptr, ::stdout);

    /* Set the image information here.  Width and height are up to 2^31,
     * bit_depth is one of 1, 2, 4, 8 or 16, but valid values also depend on
     * the color_type selected.  color_type is one of PNG_COLOR_TYPE_GRAY,
     * PNG_COLOR_TYPE_GRAY_ALPHA, PNG_COLOR_TYPE_PALETTE, PNG_COLOR_TYPE_RGB,
     * or PNG_COLOR_TYPE_RGB_ALPHA.  interlace is either PNG_INTERLACE_NONE or
     * PNG_INTERLACE_ADAM7, and the compression_type and filter_type MUST
     * currently be PNG_COMPRESSION_TYPE_BASE and PNG_FILTER_TYPE_BASE.
     * REQUIRED.
     */
    png_set_IHDR(png_ptr, info_ptr, resolution_x, resolution_y, 8,
        PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    // write the header info
    png_write_info(png_ptr, info_ptr);

    /* In this example, "image" is a one-dimensional array of bytes. */
    /* Guard against integer overflow. */
    if (resolution_y > PNG_SIZE_MAX / resolution_x)
    {
        png_error(png_ptr, "Image data buffer would be too large");
    }

    //png_byte image[resolution_y * resolution_x];
    // fill white
    //std::memset(image, 0xFF, sizeof(image)/sizeof(image[0]));

    struct image_buffer image(resolution);
    // draw the signature
    const size_t pen_size = 2;
    draw_strokes(strokes, pen_size, image);


    png_bytep row_pointers[resolution_y];

    if (resolution_y > PNG_UINT_32_MAX / (sizeof (png_bytep)))
    {
        png_error(png_ptr, "Image is too tall to process in memory");
    }

    /* Set up pointers into your "image" byte array. */
    for ( size_t i = 0; i < resolution_y; ++i)
    {
        row_pointers[i] = image.buf.data() + i * resolution_x;
    }

    png_write_image(png_ptr, row_pointers);
    png_write_end(png_ptr, info_ptr);

    /* Clean up after the write, and free any allocated memory. */
    png_destroy_write_struct(&png_ptr, &info_ptr);
}

int main()
{
    strokes_type strokes = sig_to_strokes(std::cin);
    //std::stringstream ss(data);
    //strokes_type strokes = sig_to_strokes(ss);
    //std::cout << "signature:\n" << strokes << std::endl;
    strokes_to_png(strokes);
    return 0;
}
