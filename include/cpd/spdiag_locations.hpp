#include <armadillo>


namespace cpd
{


inline arma::umat spdiag_locations(arma::uword n)
{
    arma::umat locations = arma::linspace<arma::umat>(0, n - 1, n).t();
    locations.insert_rows(1, locations);
    return locations;
}


}
