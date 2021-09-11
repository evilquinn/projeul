
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
                   std::bind( &solver::naked_tuples_in_axis,
                              this,
                              std::placeholders::_1,
                              axis_pair.second ) );
    }
    for ( auto&& axis_pair : axis_pairs )
    {
        for_each ( util::axis_range_from_coord( { 0, 0 }, dims, axis_pair.first ),
                   std::bind( &solver::hidden_tuples_in_axis,
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
    }

    //for ( auto&& coord_cand_entry : coord_cand_cache )
    //{
    //    auto& coord_set = cand_coord_cache[coord_cand_entry.second];
    //    coord_set.insert(coord_cand_entry.first);
    //}
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
