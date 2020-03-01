/**
 *
 * After a brief scan, you calculate the position of each moon (your puzzle input).
 * You just need to simulate their motion so you can avoid them.
 *
 * Each moon has a 3-dimensional position (x, y, and z) and a 3-dimensional velocity.
 * The position of each moon is given in your scan; the x, y, and z velocity of each
 * moon starts at 0.
 *
 * Simulate the motion of the moons in time steps. Within each time step, first update
 * the velocity of every moon by applying gravity. Then, once all moons' velocities
 * have been updated, update the position of every moon by applying velocity. Time
 * progresses by one step once all of the positions are updated.
 *
 * For example, suppose your scan reveals the following positions:
 *
 * <x=-1, y=0, z=2>
 * <x=2, y=-10, z=-7>
 * <x=4, y=-8, z=8>
 * <x=3, y=5, z=-1>
 * Simulating the motion of these moons would produce the following:
 *
 * After 0 steps:
 * pos=<x=-1, y=  0, z= 2>, vel=<x= 0, y= 0, z= 0>
 * pos=<x= 2, y=-10, z=-7>, vel=<x= 0, y= 0, z= 0>
 * pos=<x= 4, y= -8, z= 8>, vel=<x= 0, y= 0, z= 0>
 * pos=<x= 3, y=  5, z=-1>, vel=<x= 0, y= 0, z= 0>
 *
 * After 10 steps:
 * pos=<x= 2, y= 1, z=-3>, vel=<x=-3, y=-2, z= 1>
 * pos=<x= 1, y=-8, z= 0>, vel=<x=-1, y= 1, z= 3>
 * pos=<x= 3, y=-6, z= 1>, vel=<x= 3, y= 2, z=-3>
 * pos=<x= 2, y= 0, z= 4>, vel=<x= 1, y=-1, z=-1>
 * Then, it might help to calculate the total energy in the system. The total energy for a single moon is its potential energy multiplied by its kinetic energy. A moon's potential energy is the sum of the absolute values of its x, y, and z position coordinates. A moon's kinetic energy is the sum of the absolute values of its velocity coordinates. Below, each line shows the calculations for a moon's potential energy (pot), kinetic energy (kin), and total energy:
 *
 * Energy after 10 steps:
 * pot: 2 + 1 + 3 =  6;   kin: 3 + 2 + 1 = 6;   total:  6 * 6 = 36
 * pot: 1 + 8 + 0 =  9;   kin: 1 + 1 + 3 = 5;   total:  9 * 5 = 45
 * pot: 3 + 6 + 1 = 10;   kin: 3 + 2 + 3 = 8;   total: 10 * 8 = 80
 * pot: 2 + 0 + 4 =  6;   kin: 1 + 1 + 1 = 3;   total:  6 * 3 = 18
 * Sum of total energy: 36 + 45 + 80 + 18 = 179
 * In the above example, adding together the total energy for all moons after 10 steps produces the total energy in the system, 179.
 *
 **/

#include <iostream>
#include <vector>


struct mag
{
    ptrdiff_t x = 0;
    ptrdiff_t y = 0;
    ptrdiff_t z = 0;
};
std::ostream& operator<< (std::ostream& os, const mag& m)
{
    return os << "<" << m.x << ", " << m.y << ", " << m.z << ">";
}
class moon
{
public:
    typedef mag pos_type;
    typedef mag vel_type;
    moon() :
        pos_(),
        vel_()
    {}
    moon(const pos_type& pos) :
        pos_(pos),
        vel_()
    {}
    void update_velocity(const moon& other)
    {
        if ( pos_.x < other.pos_.x ) ++vel_.x;
        else if ( pos_.x > other.pos_.x ) --vel_.x;
        if ( pos_.y < other.pos_.y ) ++vel_.y;
        else if ( pos_.y > other.pos_.y ) --vel_.y;
        if ( pos_.z < other.pos_.z ) ++vel_.z;
        else if ( pos_.z > other.pos_.z ) --vel_.z;
    }
    void move()
    {
        pos_.x += vel_.x;
        pos_.y += vel_.y;
        pos_.z += vel_.z;
    }
    size_t energy() const
    {
        return ( std::abs(pos_.x) +
                 std::abs(pos_.y) +
                 std::abs(pos_.z) ) *
               ( std::abs(vel_.x) +
                 std::abs(vel_.y) +
                 std::abs(vel_.z) );
    }
    std::ostream& to_ostream(std::ostream& os) const
    {
        return os << "pos:" << pos_ << ", vel: " << vel_;
    }

private:
    pos_type pos_;
    vel_type vel_;
};
std::ostream& operator<< (std::ostream& os, const moon& m)
{
    return m.to_ostream(os);
}

typedef std::vector<moon> moons_type;
std::ostream& operator<< (std::ostream& os, const moons_type& m)
{
    for ( auto&& moon : m )
    {
        os << moon << "\n";
    }
    return os;
}


int main()
{

    std::vector<std::pair<std::vector<moon::pos_type>, size_t> > data = {
/**
 * <x=-1, y=0, z=2>
 * <x=2, y=-10, z=-7>
 * <x=4, y=-8, z=8>
 * <x=3, y=5, z=-1>
 **/
        { { { -1, 0, 2 },
            { 2, -10, -7 },
            { 4, -8, 8 },
            { 3, 5, -1 } }, 10 },

/**
<x=-8, y=-10, z=0>
<x=5, y=5, z=10>
<x=2, y=-7, z=3>
<x=9, y=-8, z=-3>
**/
        { { { -8, -10, 0 },
            { 5, 5, 10 },
            { 2, -7, 3 },
            { 9, -8, -3 } }, 100 },
/**
<x=-4, y=-14, z=8>
<x=1, y=-8, z=10>
<x=-15, y=2, z=1>
<x=-17, y=-17, z=16>
 **/
        { { { -4, -14, 8 },
            { 1, -8, 10 },
            { -15, 2, 1 },
            { -17, -17, 16 } }, 1000 }
    };

    for ( auto&& datum : data )
    {
        moons_type moons;
        for ( auto&& moon : datum.first )
        {
            moons.emplace_back(moon);
        }

        std::cout << "After Step 0:\n" << moons << "\n";
        const int steps = datum.second;
        for ( int step = 0; step < steps; ++step )
        {
            for ( auto&& moon : moons )
            {
                for ( auto&& other_moon : moons )
                {
                    moon.update_velocity(other_moon);
                }
            }
            for ( auto&& moon : moons )
            {
                moon.move();
            }

        }
        std::cout << "After Step " << steps << ":\n";
        size_t total = 0;
        for ( auto&& moon : moons )
        {
            total += moon.energy();
            std::cout << moon << ", energy: " << moon.energy() << "\n";
        }
        std::cout << "total: " << total << "\n\n";
    }

    return 0;
}
