#ifndef WORDGRID_GRIDOUTPUTSTREAM
#define WORDGRID_GRIDOUTPUTSTREAM

#include <ostream>

namespace Wordgrid
{
    class Grid;

    /** GridOutputStream writes a formatted grid content on an output stream.
     */
    class GridOutputStream
    {
        public:
            GridOutputStream(std::ostream & st);
            virtual ~GridOutputStream();

            std::ostream & operator()(Wordgrid::Grid & grid);
        
        private:
            std::ostream & m_stream;
    };
    
    // TODO : grid parameter could be const if the operator for Output accepted a const parameter too
    std::ostream & operator << (std::ostream & stream, Wordgrid::Grid & grid);

} /* GridOutputStream */

#endif

