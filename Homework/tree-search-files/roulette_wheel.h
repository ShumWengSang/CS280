#include <random>
#include <map>
#include <tuple>

// Creates a roulette wheel with the distribution provided by client:
// frequency -> action1
// frequency -> action2
// frequency -> action3
// frequencies do NOT have to add up to 1
// To create use Sector( frequency, action )
// To run    use Spin()
// see sample driver

template < typename Action >
class RouletteWheel {
    public:
        RouletteWheel( RouletteWheel const& )               = delete;
        RouletteWheel( RouletteWheel && )                   = delete;
        RouletteWheel& operator=( RouletteWheel const& )    = delete;
        RouletteWheel& operator=( RouletteWheel && )        = delete;
        ~RouletteWheel()                                    = default;

        RouletteWheel( ) : wheel( ), rd(), gen( rd() )
        { 
        }

        void Sector( double f, Action const& a )
        {
            wheel[ total_frequency += f ] = a;
        }

        Action Spin( )
        {
            std::uniform_real_distribution<double>  dis( 0, total_frequency );
            return wheel.upper_bound( dis( gen ) )->second; // find key of the first element of the map that is >= rand_value
        }
    private:
        double                      total_frequency {0};
        std::map< double, Action >  wheel;
        std::random_device          rd;
        std::mt19937                gen;
};
