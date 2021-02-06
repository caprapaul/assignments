#include <assert.h>
#include "Matrix.h"

using namespace std;

void testAll() { 
	Matrix m(4, 4);
	assert(m.nrLines() == 4);
	assert(m.nrColumns() == 4);	
	m.modify(1, 1, 5);
	assert(m.element(1, 1) == 5);
	TElem old = m.modify(1, 1, 6);
    assert(m.element(1, 1) == 6);
	assert(m.element(1, 2) == NULL_TELEM);
	assert(old == 5);
    assert(m.modify(3, 3, 1) == NULL_TELEM);

    m.resize(3, 3);

    try {
        m.element(3, 3);
        assert(false);
    }
    catch (exception&) {
        assert(true);
    }

    m.resize(4, 4);

    assert(m.element(3, 3) == NULL_TELEM);

    Matrix m2(3, 3);
    for (int i = m2.nrLines() - 1; i >= 0; i--)
    {
        for (int j = m2.nrColumns() - 1; j >= 0; j--)
        {
            if (i % 2 == 0)
            {
                m2.modify(i, j, i * j);
            }
            else if (i % 3 == 0)
            {
                m2.modify(i, j, i * 3);
            }
            else 
            {
                m2.modify(i, j, i + j);
            }
        }
    }

    for (int i = m2.nrLines() - 1; i >= 0; i--)
    {
        for (int j = m2.nrColumns() - 1; j >= 0; j--)
        {
            int el = m2.element(i, j);

            if (i % 2 == 0)
            {
                assert(el == i * j);
            }
            else if (i % 3 == 0)
            {
                assert(el == i * 3);
            }
            else
            {
                assert(el == i + j);
            }
        }
    }
}