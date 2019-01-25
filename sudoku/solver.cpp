
#include <cmath>
#include <sudoku/solver.hpp>

namespace evilquinn
{
namespace sudoku
{
namespace util
{
std::pair<dimensions, dimensions> nonet_from_coord( const coord coord,
                                                    const dimensions dims )
{
    if ( dims.x != dims.y )
    {
        std::ostringstream error;
        error << "can't calc nonet from non-square grid with dimensions: "
              << to_string( dims );
        throw std::runtime_error( error.str() );
    }

    size_t nonet_side_size = static_cast<size_t>( std::sqrt( dims.x ) );
    size_t x_start         = ( coord.x / nonet_side_size ) * nonet_side_size;
    size_t y_start         = ( coord.y / nonet_side_size ) * nonet_side_size;
    return std::pair<dimensions, dimensions>(
        { x_start, y_start },
        { x_start + nonet_side_size, y_start + nonet_side_size } );
}

using candidate_coord_map = std::map<size_t, std::set<coord> >;
void cache_coord_for_candidates( square& sq,
                                 candidate_coord_map& cand_coord_cache )
{
    auto candidates = sq.candidates();
    if ( candidates.size() > 1 )
    {
        std::for_each( candidates.begin(),
                       candidates.end(),
                       [&sq, &cand_coord_cache]( const size_t value ) {
                           cand_coord_cache[value].insert( sq.pos() );
                       } );
    }
}

solver::coord_variant axis_range_from_coord( coord pos,
                                             dimensions dims,
                                             solver::axis ax )
{
    switch ( ax )
    {
    case solver::axis::row:
    {
        return solver::coord_variant(
            solver::coord_range{ { 0, pos.y }, { dims.x, pos.y + 1 } } );
        break;
    }
    case solver::axis::column:
    {
        return solver::coord_variant(
            solver::coord_range{ { pos.x, 0 }, { pos.x + 1, dims.y } } );
        break;
    }
    case solver::axis::nonet:
    {
        return solver::coord_variant( nonet_from_coord( pos, dims ) );
        break;
    }
    case solver::axis::gridwise_nonets:
    {
        solver::coord_sequence coords{};
        size_t nonet_size = std::sqrt( dims.x );
        for ( size_t x = 0; x < dims.x; x += nonet_size )
        {
            for ( size_t y = 0; y < dims.y; y += nonet_size )
            {
                coords.emplace_back( coord{ x, y } );
            }
        }
        return solver::coord_variant( coords );
        break;
    }
    default:
    {
        // should probably throw instead...meh
        return solver::coord_variant( solver::coord_sequence{} );

    }  // end default
    }  // end switch
}

class for_each_resolver
{
public:
    for_each_resolver( solver& s, solver::square_operation op )
        : solver_( s ), op_( std::move( op ) )
    {
    }
    solver::square_operation operator()( solver::coord_range range )
    {
        return solver_.for_each( range, std::move( op_ ) );
    }
    solver::square_operation operator()( solver::coord_sequence sequence )
    {
        return solver_.for_each( sequence, std::move( op_ ) );
    }

private:
    solver& solver_;
    solver::square_operation op_;
};

}  // end namespace util
}  // end namespace sudoku
}  // end namespace evilquinn

evilquinn::sudoku::solver::solver( grid& grid ) : grid_( grid ) {}

evilquinn::sudoku::solver::square_operation
evilquinn::sudoku::solver::for_each( const coord_sequence& sequence,
                                     square_operation op )
{
    for ( auto&& coord : sequence )
    {
        op( grid_.at( coord ) );
    }
    return std::move( op );
}

evilquinn::sudoku::solver::square_operation
evilquinn::sudoku::solver::for_each( coord_range range, square_operation op )
{
    for ( size_t x = range.first.x; x < range.second.x; ++x )
    {
        for ( size_t y = range.first.y; y < range.second.y; ++y )
        {
            op( grid_.at( { x, y } ) );
        }
    }
    return std::move( op );
}

evilquinn::sudoku::solver::square_operation
evilquinn::sudoku::solver::for_each( square_operation op )
{
    return for_each( coord_range{ { 0, 0 }, grid_.get_dimensions() },
                     std::move( op ) );
}

void evilquinn::sudoku::solver::if_value_known_eliminate( square& sq )
{
    auto value = sq.value();
    if ( value )
    {
        auto dims            = grid_.get_dimensions();
        auto eliminate_value = std::bind(
            static_cast<void ( square::* )( size_t )>( &square::eliminate ),
            std::placeholders::_1,
            *value );
        auto pos = sq.pos();
        // update the column
        for_each( boost::get<coord_range>( util::axis_range_from_coord(
                      pos, dims, axis::column ) ),
                  eliminate_value );
        // update the row
        for_each( boost::get<coord_range>(
                      util::axis_range_from_coord( pos, dims, axis::row ) ),
                  eliminate_value );
        // update the nonet
        for_each( boost::get<coord_range>(
                      util::axis_range_from_coord( pos, dims, axis::nonet ) ),
                  std::move( eliminate_value ) );
    }
}

void evilquinn::sudoku::solver::if_candidate_unique_in_axis_solve( square& sq,
                                                                   axis ax )
{
    auto pos  = sq.pos();
    auto dims = grid_.get_dimensions();
    std::map<size_t, std::set<coord> > value_pos_stats;
    for_each( boost::get<coord_range>(
                  util::axis_range_from_coord( pos, dims, ax ) ),
              std::bind( &util::cache_coord_for_candidates,
                         std::placeholders::_1,
                         value_pos_stats ) );
    std::map<std::set<coord>, std::pair<std::set<size_t>, size_t> > coord_value_counts;
    for ( auto&& value_pos_stat : value_pos_stats )
    {
        auto& value_count = coord_value_counts[value_pos_stat.second];
        value_count.first.insert(value_pos_stat.first);
        value_count.second += 1;
    }
    for ( auto&& coord_value_count : coord_value_counts )
    {
        if ( coord_value_count.first.size() == coord_value_count.second.first.size() &&
             coord_value_count.first.size() == coord_value_count.second.second )
        {
            for_each( boost::get<coord_range>(
                          util::axis_range_from_coord( pos, dims, ax )),
                      [&coord_value_count](square& sq)
                      {
                          if ( coord_value_count.first.find(sq.pos()) ==
                               coord_value_count.first.end() )
                          {
                              sq.eliminate(coord_value_count.second.first);
                          }
                      });
        }
    }
}

void evilquinn::sudoku::solver::eliminate_knowns_from_ranges()
{
    for_each( std::bind(
        &solver::if_value_known_eliminate, this, std::placeholders::_1 ) );
}

void evilquinn::sudoku::solver::solve_if_candidate_unique_in_ranges()
{
    auto dims = grid_.get_dimensions();
    std::vector<std::pair<axis, axis> > axis_pairs{
        { axis::column, axis::row },
        { axis::row, axis::column },
        { axis::gridwise_nonets, axis::nonet }
    };
    for ( auto&& axis_pair : axis_pairs )
    {
        util::for_each_resolver resolver(
            *this,
            std::bind( &solver::if_candidate_unique_in_axis_solve,
                       this,
                       std::placeholders::_1,
                       axis_pair.second ) );
        boost::apply_visitor(
            resolver,
            util::axis_range_from_coord( { 0, 0 }, dims, axis_pair.first ) );
    }
}

bool evilquinn::sudoku::solver::solve()
{
    bool solved = false;

    const size_t limit = 10;
    for ( size_t i = 0; i < limit; ++i )
    {
        eliminate_knowns_from_ranges();
        solve_if_candidate_unique_in_ranges();
    }

    return solved;
}
