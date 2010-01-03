namespace Wordgrid
{
    class Solver;
}

namespace Gridgen
{
    class Options;

    class SolverFactory
    {
        public:
            SolverFactory(const Options & options);
            virtual ~SolverFactory();

            void Solve();
        
        private:
            const Options & m_options;
    };
}

