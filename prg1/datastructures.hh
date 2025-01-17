// Datastructures.hh
//
// Student name:
// Student email:
// Student number:

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <exception>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <map>

using namespace std;
// Types for IDs

//Käytetään asemanyksilöivänä tunnisteena
using StationID = std::string;

//Käytetään asemien ja alueiden nimenä
using Name = std::string;

//Ei-negatiivinen kokonaisluku, jota käytetään alueen yksilöivänä tunnisteena
using RegionID = unsigned long long int;

// käytetään junan yksilöivänä tunnisteena
using TrainID = std::string;

//Kokonaisluku, joka kuvaa kellonaikaa muodossa HHMM.
using Time = unsigned short int;


// Return values for cases where required thing was not found
StationID const NO_STATION = "---";
TrainID const NO_TRAIN = "---";
RegionID const NO_REGION = -1;
Name const NO_NAME = "!NO_NAME!";
Time const NO_TIME = 9999;

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();


// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};

// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Type for a distance (in metres)
using Distance = int;

// Return value for cases where Distance is unknown
Distance const NO_DISTANCE = NO_VALUE;

// This exception class is there just so that the user interface can notify
// about operations which are not (yet) implemented
class NotImplemented : public std::exception
{
public:
    NotImplemented() : msg_{} {}
    explicit NotImplemented(std::string const& msg) : msg_{msg + " not implemented"} {}

    virtual const char* what() const noexcept override
    {
        return msg_.c_str();
    }
private:
    std::string msg_;
};


// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance: O(1)
    // Short rationale for estimate: size() is O(1)
    unsigned int station_count();

    // Estimate of performance: O(n)
    // Short rationale for estimate: clear() is linear in all containers
    void clear_all();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Complexity grader won´t accept O(1), only returns one datastructure
    std::vector<StationID> all_stations();

    // Estimate of performance: O(log n)
    // Short rationale for estimate: map.insert the most expensive one
    bool add_station(StationID id, Name const& name, Coord xy);

    // Estimate of performance: O(n)
    // Short rationale for estimate: unordered_map.find(): worst case linear
    Name get_station_name(StationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: unordered_map.find(): worst case linear
    Coord get_station_coordinates(StationID id);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n log n)
    // Short rationale for estimate: sort() algorithm is  O(nlogn) according to cpppreference
    std::vector<StationID> stations_alphabetically();

    // Estimate of performance: O(n log n)
    // Short rationale for estimate: sort function is n log n according to cppreference
    std::vector<StationID> stations_distance_increasing();

    // Estimate of performance: O(log n)
    // Short rationale for estimate: map.find() is logarithmic in the size of the container
    StationID find_station_with_coord(Coord xy);

    // Estimate of performance: O(n)
    // Short rationale for estimate: unordered_map.find most expensive, worst case linear->size of the container.
    bool change_station_coord(StationID id, Coord newcoord);

    // Estimate of performance: O(n)
    // Short rationale for estimate: unordered_map.count most expensive, worst case linear->size of the container.
    bool add_departure(StationID stationid, TrainID trainid, Time time);

    // Estimate of performance: O(n)
    // Short rationale for estimate: unordered_map.count most expensive, others logarithmic.
    bool remove_departure(StationID stationid, TrainID trainid, Time time);

    // Estimate of performance: O(n)
    // Short rationale for estimate: unordered_map and for-loop worst case linear->size of the container
    std::vector<std::pair<Time, TrainID>> station_departures_after(StationID stationid, Time time);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n)
    // Short rationale for estimate: unordered_map.insert worst case linear
    bool add_region(RegionID id, Name const& name, std::vector<Coord> coords);

    // Estimate of performance: O(1)
    // Short rationale for estimate: Only returns an already-built datastructure
    std::vector<RegionID> all_regions();

    // Estimate of performance: O(n)
    // Short rationale for estimate: unordered_map.find() worst case linear->size of the container.
    Name get_region_name(RegionID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: unordered_map.find() worst case linear->size of the container.
    std::vector<Coord> get_region_coords(RegionID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: unrdered_map.count&unordered_set.insert: worst case O(size())
    bool add_subregion_to_region(RegionID id, RegionID parentid);

    // Estimate of performance: O(n)
    // Short rationale for estimate: unrdered_map.count&unordered_set.insert: worst case O(size())
    bool add_station_to_region(StationID id, RegionID parentid);

    // Estimate of performance: O(n log n)
    // Short rationale for estimate: Uses recursive function which makes it n log n
    std::vector<RegionID> station_in_regions(StationID id);



    // EI-PAKOLLISET Non-compulsory operations

    // Estimate of performance: O(n log n)
    // Short rationale for estimate: recursive function with for-loop
    std::vector<RegionID> all_subregions_of_region(RegionID id);

    // Estimate of performance: O(n log n)
    // Short rationale for estimate: sort function is O(n log n) according to cppreference
    std::vector<StationID> stations_closest_to(Coord xy);

    // Estimate of performance: O(n)
    // Short rationale for estimate: single for-loops multiple times
    bool remove_station(StationID id);

    // Estimate of performance: O(n log n)
    // Short rationale for estimate: recursive function called twice
    RegionID common_parent_of_regions(RegionID id1, RegionID id2);


private:


    struct station_struct{
                                  Name name;
                          Coord coordinates;
        set<pair<Time, TrainID>> trains_set;
                     RegionID parent_region;

    };

    struct region_struct{
                                  Name name;
           vector<Coord> coordinates_vector;
        unordered_set <RegionID> subregions;
         unordered_set <StationID> stations;
                            RegionID parent;
    };

                                            //Station related
     unordered_map <StationID, station_struct> stations_umap_;
                            vector<StationID> station_vector_;
                      map<Coord, StationID> coord_as_key_map_;
                                bool stations_alphabetically_;
                               bool stations_distance_sorted_;

                                             //Region related
        unordered_map <RegionID, region_struct> regions_umap_;
                              vector<RegionID> region_vector_;
                     unordered_set <RegionID> all_subregions_;
          unordered_set <StationID> all_stations_for_regions_;


                         //recursive function, called from station_in_regions
       void recursive_parent_regions(RegionID const& id, vector<RegionID>& v);

                   //recursive function, called from all_subregions_of_region
void recursive_subregions_to_regions(RegionID const& id, vector<RegionID>& v);

                            //recursive function for common_parent_of_regions
 RegionID recursive_parentregions(RegionID const& id, set<RegionID>& parents);

};

#endif // DATASTRUCTURES_HH
