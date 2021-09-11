
#include <cmath>
#include <sudoku/solver.hpp>
#include <sudoku/util.hpp>
#include <iostream>

namespace evilquinn
{
namespace sudoku
{
namespace util
{

using candidate_coord_map = std::map<size_t, std::set<coord> >;
void cache_coord_for_candidates( square& sq,
                                 candidate_coord_map& cand_coord_cache )
{
    for ( auto&& candidate : sq.candidates() )
    {
        cand_coord_cache[candidate].insert(sq.pos());
    }
}

using coord_candidate_map = std::map<coord, square::candidate_set>;
void cache_candidates_for_coord( square& sq,
                                 coord_candidate_map& coord_cand_cache )
{
    coord_cand_cache[sq.pos()] = sq.candidates();
}

size_t nonet_from_coord ( coord pos )
{
    // HACK hardcoding 9*9 grid...
    pos.x /= 3;
    pos.y /= 3;
    return (pos.x * 3) + pos.y;
}

solver::coord_sequence axis_range_from_coord( coord pos,
                                              dimensions dims,
                                              solver::axis ax )
{
    solver::coord_sequence result;
    switch ( ax )
    {
    case solver::axis::row:
    {
        for ( size_t x = 0; x < dims.x; ++x )
        {
            result.emplace_back( coord{ x, pos.y } );
        }
        break;
    }
    case solver::axis::column:
    {
        for ( size_t y = 0; y < dims.y; ++y )
        {
            result.emplace_back( coord{ pos.x, y } );
        }
        break;
    }
    case solver::axis::nonet:
    {
        size_t nonet_side_size = std::sqrt( dims.x );
        size_t x_start         = ( pos.x / nonet_side_size ) * nonet_side_size;
        size_t y_start         = ( pos.y / nonet_side_size ) * nonet_side_size;
        size_t x_lim           = x_start + nonet_side_size;
        size_t y_lim           = y_start + nonet_side_size;
        for ( size_t x = x_start; x < x_lim; ++x )
        {
            for ( size_t y = y_start; y < y_lim; ++y )
            {
                result.emplace_back( coord{ x, y } );
            }
        }
        break;
    }
    case solver::axis::gridwise_nonets:
    {
        size_t nonet_side_size = std::sqrt( dims.x );
        for ( size_t x = 0; x < dims.x; x += nonet_side_size )
        {
            for ( size_t y = 0; y < dims.y; y += nonet_side_size )
            {
                result.emplace_back( coord{ x, y } );
            }
        }
        break;
    }
    default:
    {
        std::ostringstream error;
        error << "unknown value for axis: " << static_cast<size_t>(ax);
        throw std::runtime_error(error.str());
    }  // end default
    }  // end switch

    return result;
}

solver::axis inverse_for_line(solver::axis axis)
{
    switch(axis)
    {
    case solver::axis::row: return solver::axis::column;
    case solver::axis::column: return solver::axis::row;
    default: throw std::runtime_error("dick");
    }
}

boost::optional<solver::axis> contained_within_inverse_of_axis(const std::set<coord>& coords, solver::axis axis)
{
    bool same_nonet = true;
    bool same_row = true;
    bool same_col = true;
    for ( auto it = coords.begin(), limit = std::prev(coords.end()); it != limit; ++it )
    {
        auto nextit = std::next(it);
        if ( it->x != nextit->x ) same_col = false;
        if ( it->y != nextit->y ) same_row = false;
        if ( nonet_from_coord(*it) != nonet_from_coord(*nextit) ) same_nonet = false;
    }
    switch(axis)
    {
    case solver::axis::row:
    case solver::axis::column:
    {
        if ( same_nonet ) return solver::axis::nonet;
        return boost::none;
    }
    case solver::axis::nonet:
    {
        if ( same_row ) return solver::axis::row;
        if ( same_col ) return solver::axis::column;
        return boost::none;
    }
    default: throw std::runtime_error("it's silly to call this function with axis=gridwise_nonet, silly.");
    }
}

bool is_x_wing_pattern(const std::set<coord>& lhs, const std::set<coord>& rhs, solver::axis axis)
{
    if ( lhs.size() != 2 ) return false;
    if ( lhs.size() != rhs.size() ) return false;
    for ( auto lhsit = lhs.begin(), rhsit = rhs.begin(); lhsit != lhs.end(); ++lhsit, ++rhsit )
    {
        switch(axis)
        {
        case solver::axis::column:
        {
            if ( lhsit->x != rhsit->x ) return false;
            break;
        }
        case solver::axis::row:
        {
            if ( lhsit->y != rhsit->y ) return false;
            break;
        }
        default: throw std::runtime_error("silly");
        }
    }
    return true;
}



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
    return op;
}

void evilquinn::sudoku::solver::hidden_tuples_in_axis( square& sq, axis ax )
{
    auto pos  = sq.pos();
    auto dims = grid_.get_dimensions();
    util::candidate_coord_map cand_coord_cache{};
    for_each( util::axis_range_from_coord( pos, dims, ax ),
              std::bind( &util::cache_coord_for_candidates,
                         std::placeholders::_1,
                         std::ref(cand_coord_cache) ) );
    std::map<std::set<coord>, square::candidate_set> coord_cand_cache{};
    for ( auto&& cand_coord_entry : cand_coord_cache )
    {
        auto& cand_set = coord_cand_cache[cand_coord_entry.second];
        cand_set.insert(cand_coord_entry.first);
    }
    for ( auto&& coord_cand_entry : coord_cand_cache )
    {
        if ( coord_cand_entry.first.size() == coord_cand_entry.second.size() )
        {
            // we've detected hidden tuples, these are the only solutions for
            // these coords
            for ( auto&& coord : coord_cand_entry.first )
            {
                grid_.at( coord ).set(coord_cand_entry.second);
            }
        }
    }

#if 1
    /*
     * can we do line by nonet interaction?
     * If there's a candidate in _this_ axis who's coordinates are entirely
     * within another axis, then this candidate can be eliminated
     * from other coords within that other axis
     */
    for ( auto&& cand_coord_entry : cand_coord_cache )
    {
        auto other_axis = util::contained_within_inverse_of_axis(cand_coord_entry.second, ax);
        if ( other_axis )
        {
            // get the coords from other_axis, minus the coords in this entry, and eliminate cand
            auto other_coords = util::axis_range_from_coord( *cand_coord_entry.second.begin(), dims, *other_axis );
            for ( auto&& coord : other_coords )
            {
                if ( cand_coord_entry.second.count(coord) > 0 ) continue; //skip
                grid_.at(coord).eliminate(cand_coord_entry.first);
            }
        }
    }
#endif

}

void evilquinn::sudoku::solver::x_wing()
{
    std::vector<axis> axises {
        axis::column,
        axis::row
    };
    for ( auto&& axis : axises )
    {
        x_wing_in_axis(axis);
    }
}

void evilquinn::sudoku::solver::x_wing_in_axis(axis ax)
{

#if 1

    auto dims = grid_.get_dimensions();
    auto axis_start_coords = util::axis_range_from_coord( { 0, 0 }, dims, ax );
    /**
     * Can we do x-wing?
     * If a canditate has only _n_ possible coords in a given row,
     * if that candidate is limited to the same columns in another row,
     * that candidate can be eliminated from the other coords in the _n_ columns.
     * (and vice-versa for columns vs rows)
     */
    std::map<coord, util::candidate_coord_map> coord_to_cand_coord_cache;
    for ( auto ax_coord_it = axis_start_coords.begin(); ax_coord_it != axis_start_coords.end(); ++ax_coord_it )
    {
        util::candidate_coord_map& cand_coord_cache = coord_to_cand_coord_cache[*ax_coord_it];
        for_each( util::axis_range_from_coord( *ax_coord_it, dims, util::inverse_for_line(ax) ),
                std::bind( &util::cache_coord_for_candidates,
                            std::placeholders::_1,
                            std::ref(cand_coord_cache) ) );
    }

    for ( auto it = coord_to_cand_coord_cache.begin(), limit = std::prev(coord_to_cand_coord_cache.end());
          it != limit;
          ++it )
    {
        for ( auto rit = std::next(it); rit != coord_to_cand_coord_cache.end(); ++rit )
        {
            for ( auto&& cand_coord_entry : it->second )
            {
                auto cand_coord_rit_entry = rit->second.find(cand_coord_entry.first);
                if ( cand_coord_rit_entry != rit->second.end() )
                {
                    if ( util::is_x_wing_pattern(cand_coord_entry.second, cand_coord_rit_entry->second, ax) )
                    {
                        for ( auto&& corner_coord : cand_coord_entry.second )
                        {
                            auto elim_cand_from_coords = util::axis_range_from_coord(corner_coord, dims, ax);
                            for ( auto&& elim_cand_from_coord : elim_cand_from_coords )
                            {
                                if ( cand_coord_entry.second.count(elim_cand_from_coord) > 0 ) continue; // skip
                                if ( cand_coord_rit_entry->second.count(elim_cand_from_coord) > 0 ) continue; // skip
                                grid_.at(elim_cand_from_coord).eliminate(cand_coord_entry.first);
                            }
                        }
                    }
                }
            }
        }
    }


#endif

}

void evilquinn::sudoku::solver::naked_hidden_tuples()
{
    auto dims = grid_.get_dimensions();
    std::vector<std::pair<axis, axis> > axis_pairs{
        { axis::column, axis::row },
        { axis::row, axis::column },
        { axis::gridwise_nonets, axis::nonet }
    };
    for ( auto&& axis_pair : axis_pairs )
    {
        for_each ( util::axis_range_from_coord( { 0, 0 }, dims, axis_pair.first ),
                   std::bind( &solver::hidden_tuples_in_axis,
                              this,
                              std::placeholders::_1,
                              axis_pair.second ) );
        for_each ( util::axis_range_from_coord( { 0, 0 }, dims, axis_pair.first ),
                   std::bind( &solver::naked_tuples_in_axis,
                              this,
                              std::placeholders::_1,
                              axis_pair.second ) );
    }
}

void evilquinn::sudoku::solver::naked_tuples_in_axis( square& sq, axis ax )
{
    auto pos  = sq.pos();
    auto dims = grid_.get_dimensions();
    util::coord_candidate_map coord_cand_cache{};
    auto axis_range = util::axis_range_from_coord( pos, dims, ax ); //re-used
    for_each( axis_range,
              std::bind( &util::cache_candidates_for_coord,
                         std::placeholders::_1,
                         std::ref(coord_cand_cache) ) );

    std::map<square::candidate_set, std::set<coord> > cand_coord_cache{};
    for ( auto it = coord_cand_cache.begin(); it != coord_cand_cache.end(); ++it )
    {
        auto& coord_set = cand_coord_cache[it->second];
        coord_set.insert(it->first);

        /*
         * BOOM!
         * this might be madness, bear with me
         *
         * .. waste of time for solved squares or squares full of candidates
         */
        if ( grid_.at(it->first).value() )
        {
            continue;
        }

#if 0
        square::candidate_set acca_cands;
        std::set<coord> acca_coords;
        for ( auto dit = coord_cand_cache.begin(); dit != coord_cand_cache.end(); ++dit )
        {
            // not interested in solved squares
            if ( grid_.at(dit->first).value() )
            {
                continue;
            }
            if ( dit->first <= it->first )
            {
                // accumulate
                acca_coords.insert(dit->first);
                for ( auto&& candidate : dit->second )
                {
                    acca_cands.insert(candidate);
                }
            }
            else if ( dit->first > it->first )
            {
                // add current row to dit and insert
                square::candidate_set cands = it->second;
                for ( auto&& candidate : dit->second )
                {
                    cands.insert(candidate);
                }
                cand_coord_cache[cands].insert(it->first);
                cand_coord_cache[cands].insert(dit->first);

                // then
                // add what we acca'd with dit to dit now and insert
                cands.clear();
                std::set_union(dit->second.begin(), dit->second.end(), acca_cands.begin(), acca_cands.end(), std::inserter(cands, cands.begin()));
                cand_coord_cache[cands].insert(dit->first);
                for ( auto&& coord : acca_coords )
                {
                    cand_coord_cache[cands].insert(coord);
                }
            }
        }
#endif

    }

    for ( auto&& cand_coord_entry : cand_coord_cache )
    {
        if ( cand_coord_entry.first.size() == cand_coord_entry.second.size() )
        {
            // we've detected naked tuples, eliminate those options from
            // others in range
            for_each( axis_range, [&](square& sq)
            {
                if ( cand_coord_entry.second.find(sq.pos()) == cand_coord_entry.second.end() )
                {
                    sq.eliminate(cand_coord_entry.first);
                }
            });
        }
    }
}

bool evilquinn::sudoku::solver::solve()
{
    bool solved = false;

    size_t a = grid_.count_remaining();
    while ( true )
    {
        naked_hidden_tuples();
        x_wing();
        size_t b = grid_.count_remaining();
        if ( b<a )
        {
            a = b;
            continue;
        }
        break;
    }

    return solved;
}
