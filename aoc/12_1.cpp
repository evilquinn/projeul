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
#include <array>
#include <vector>
#include <numeric>


typedef std::array<ptrdiff_t, 3> mag_type;
static const int x = 0;
static const int y = 1;
static const int z = 2;

std::ostream& operator<< (std::ostream& os, const mag_type& m)
{
    return os << "<" << m[x] << ", " << m[y] << ", " << m[z] << ">";
}
bool operator== (const mag_type& lhs, const mag_type& rhs)
{
    return lhs[x] == rhs[x] && lhs[y] == rhs[y] && lhs[z] == rhs[z];
}
mag_type& operator+= (mag_type& lhs, const mag_type& rhs)
{
    lhs[x] += rhs[x];
    lhs[y] += rhs[y];
    lhs[z] += rhs[z];
    return lhs;
}
mag_type operator+ (mag_type lhs, const mag_type& rhs)
{
    return lhs += rhs;
}
class moon
{
public:
    typedef mag_type pos_type;
    typedef mag_type vel_type;
    moon() :
        pos_(),
        vel_()
    {}
    moon(const pos_type& pos) :
        pos_(pos),
        vel_()
    {}
    void update_velocity(moon& other)
    {
        for ( mag_type::size_type i = 0; i < pos_.size(); ++i )
        {
            update_velocity_n(other, i);
        }
    }
    void update_velocity_n(moon& other, mag_type::size_type n)
    {
        if ( pos_[n] < other.pos_[n] )
        {
            ++vel_[n];
            --other.vel_[n];
        }
        else if ( pos_[n] > other.pos_[n] )
        {
            --vel_[n];
            ++other.vel_[n];
        }
    }
    void move()
    {
        for( mag_type::size_type i = 0; i < pos_.size(); ++i )
        {
            move_dim(i);
        }
    }
    void move_dim(mag_type::size_type dim)
    {
        pos_[dim] += vel_[dim];
    }
    size_t energy() const
    {
        return ( std::abs(pos_[x]) +
                 std::abs(pos_[y]) +
                 std::abs(pos_[z]) ) *
               ( std::abs(vel_[x]) +
                 std::abs(vel_[y]) +
                 std::abs(vel_[z]) );
    }
    std::ostream& to_ostream(std::ostream& os) const
    {
        return os << "pos:" << pos_ << ", vel: " << vel_;
    }
    bool equal(const moon& other) const { return pos_ == other.pos_ && vel_ == other.vel_; }

private:
    pos_type pos_;
    vel_type vel_;
};
std::ostream& operator<< (std::ostream& os, const moon& m)
{
    return m.to_ostream(os);
}
bool operator== (const moon& lhs, const moon& rhs)
{
    return lhs.equal(rhs);
}

class moon_system
{
public:
    typedef std::vector<moon> moons_type;
    typedef std::vector<moon::pos_type> positions_type;
    moon_system(const moons_type& moons) :
        origin_(moons),
        moons_(moons)
    {}
    moon_system(const positions_type& moon_positions) :
        origin_(),
        moons_()
    {
        std::copy(moon_positions.begin(), moon_positions.end(), std::back_inserter(origin_));
        moons_ = origin_;
    }
    std::ostream& to_ostream(std::ostream& os) const
    {
        for ( auto&& moon : moons_ )
        {
            os << moon << "\n";
        }
        return os;
    }
    void step()
    {
        for ( auto i = moons_.begin(); i != moons_.end(); ++i )
        {
            for ( auto j = std::next(i); j != moons_.end(); ++j )
            {
                i->update_velocity(*j);
            }
        }
        for ( auto&& moon : moons_ )
        {
            moon.move();
        }
    }
    void step_dim(mag_type::size_type dim)
    {
        for ( auto i = moons_.begin(); i != moons_.end(); ++i )
        {
            for ( auto j = std::next(i); j != moons_.end(); ++j )
            {
                i->update_velocity_n(*j, dim);
            }
        }
        for ( auto&& moon : moons_ )
        {
            moon.move_dim(dim);
        }
    }
    size_t find_period()
    {
        size_t xp = find_period_n(x);
        size_t yp = find_period_n(y);
        size_t zp = find_period_n(z);
        return std::lcm(std::lcm(xp, yp), zp);
    }
    size_t find_period_n(mag_type::size_type dim)
    {
        size_t steps = 0;
        do
        {
            step_dim(dim);
            ++steps;
        }
        while ( moons_ != origin_ );
        return steps;
    }
    size_t energy() const
    {
        size_t total = 0;
        for ( auto&& moon : moons_ )
        {
            total += moon.energy();
        }
        return total;
    }
    moons_type& moons() { return moons_; }
private:
    moons_type origin_;
    moons_type moons_;
};

std::ostream& operator<< (std::ostream& os, const moon_system& m)
{
    return m.to_ostream(os);
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
        moon_system moons(datum.first);

        std::cout << "After Step 0:\n" << moons << "\n";
        /**
        const int steps = datum.second;
        for ( int step = 0; step < steps; ++step )
        {
            moons.step();
        }
        **/
        auto steps = moons.find_period();
        std::cout << "After Step " << steps << ":\n" << moons << "\n";
        //std::cout << "total: " << total << "\n\n";
    }

    return 0;
}
