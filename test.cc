#include <cstdlib>
#include <iostream>
#include <list>
#include <string>

struct Ast
{
    std::string name;

    std::list< Ast * > children;

    Ast( std::string const & name, std::list< Ast * > children = std::list< Ast * >( ) )
    : name( name )
    , children( children )
    {
    }

    void print( int depth = 0 )
    {
        for ( int t = 0; t < depth; ++ t ) {
            std::cout << "\t";
        }

        std::cout << "- " << name << std::endl;

        std::list< Ast * >::iterator it = children.begin( );
        for ( ; it != children.end( ); ++ it ) {
            ( * it )->print( depth + 1 );
        }
    }
};

static Ast * root = 0;

#include "test.h"
#include "test.c"

int main( void )
{
    std::list< int > tokens;
    tokens.push_back( If );
    tokens.push_back( Expr );
    tokens.push_back( If );
    tokens.push_back( Expr );
    tokens.push_back( Ok );
    tokens.push_back( Else );
    tokens.push_back( Ok );

    yyTraceFILE = fopen("test.out", "w");
    void * pParser = ParseAlloc( malloc );

    while ( ! tokens.empty( ) ) {
        Parse( pParser, tokens.front( ), 0 );
        tokens.pop_front( );
    }

    Parse( pParser, 0, 0 );
    ParseFree( pParser, free );

    if ( root == 0 ) {
        std::cerr << "No result" << std::endl;
        return 1;
    } else {
        root->print( );
        return 0;
    }
}
