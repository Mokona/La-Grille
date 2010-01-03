#ifndef WORDGRID_SQUARECONTENT
#define WORDGRID_SQUARECONTENT

namespace Wordgrid
{
    /** A grid square.
     *
     * It can contain the letter, a space (letter not set),
     * be a black square.
     *
     * It can also contain annotations (start of words
     * for example).
     *
     */
    class Square
    {
        public:
            Square();
            Square(char letter);

            void SetChar(char letter);
            char GetChar() const;
            bool IsCharSet() const;
            bool IsEmpty() const;
            bool IsBlack() const;
            
            static char BlackSquare();
            static char EmptySquare();

        private:
            char m_char;
    };

    bool operator == (const Square & first, const Square & second);
    bool operator != (const Square & first, const Square & second);

} // namespace

#endif // guard

