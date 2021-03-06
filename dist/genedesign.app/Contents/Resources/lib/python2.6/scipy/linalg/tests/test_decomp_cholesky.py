

from numpy.testing import TestCase, assert_array_almost_equal

from numpy import array, transpose, dot, conjugate, zeros_like
from numpy.random import rand
from scipy.linalg import cholesky, cholesky_banded, cho_solve_banded


def random(size):
    return rand(*size)


class TestCholesky(TestCase):

    def test_simple(self):
        a = [[8,2,3],[2,9,3],[3,3,6]]
        c = cholesky(a)
        assert_array_almost_equal(dot(transpose(c),c),a)
        c = transpose(c)
        a = dot(c,transpose(c))
        assert_array_almost_equal(cholesky(a,lower=1),c)

    def test_simple_complex(self):
        m = array([[3+1j,3+4j,5],[0,2+2j,2+7j],[0,0,7+4j]])
        a = dot(transpose(conjugate(m)),m)
        c = cholesky(a)
        a1 = dot(transpose(conjugate(c)),c)
        assert_array_almost_equal(a,a1)
        c = transpose(c)
        a = dot(c,transpose(conjugate(c)))
        assert_array_almost_equal(cholesky(a,lower=1),c)

    def test_random(self):
        n = 20
        for k in range(2):
            m = random([n,n])
            for i in range(n):
                m[i,i] = 20*(.1+m[i,i])
            a = dot(transpose(m),m)
            c = cholesky(a)
            a1 = dot(transpose(c),c)
            assert_array_almost_equal(a,a1)
            c = transpose(c)
            a = dot(c,transpose(c))
            assert_array_almost_equal(cholesky(a,lower=1),c)

    def test_random_complex(self):
        n = 20
        for k in range(2):
            m = random([n,n])+1j*random([n,n])
            for i in range(n):
                m[i,i] = 20*(.1+abs(m[i,i]))
            a = dot(transpose(conjugate(m)),m)
            c = cholesky(a)
            a1 = dot(transpose(conjugate(c)),c)
            assert_array_almost_equal(a,a1)
            c = transpose(c)
            a = dot(c,transpose(conjugate(c)))
            assert_array_almost_equal(cholesky(a,lower=1),c)


class TestCholeskyBanded(TestCase):
    """Tests for cholesky_banded() and cho_solve_banded."""

    def test_upper_real(self):
        # Symmetric positive definite banded matrix `a`
        a = array([[4.0, 1.0, 0.0, 0.0],
                    [1.0, 4.0, 0.5, 0.0],
                    [0.0, 0.5, 4.0, 0.2],
                    [0.0, 0.0, 0.2, 4.0]])
        # Banded storage form of `a`.
        ab = array([[-1.0, 1.0, 0.5, 0.2],
                     [4.0, 4.0, 4.0, 4.0]])
        c = cholesky_banded(ab, lower=False)
        ufac = zeros_like(a)
        ufac[range(4),range(4)] = c[-1]
        ufac[(0,1,2),(1,2,3)] = c[0,1:]
        assert_array_almost_equal(a, dot(ufac.T, ufac))

        b = array([0.0, 0.5, 4.2, 4.2])
        x = cho_solve_banded((c, False), b)
        assert_array_almost_equal(x, [0.0, 0.0, 1.0, 1.0])

    def test_upper_complex(self):
        # Hermitian positive definite banded matrix `a`
        a = array([[4.0, 1.0,  0.0,  0.0],
                    [1.0, 4.0,  0.5,  0.0],
                    [0.0, 0.5,  4.0, -0.2j],
                    [0.0, 0.0,  0.2j, 4.0]])
        # Banded storage form of `a`.
        ab = array([[-1.0, 1.0, 0.5, -0.2j],
                     [4.0, 4.0, 4.0,  4.0]])
        c = cholesky_banded(ab, lower=False)
        ufac = zeros_like(a)
        ufac[range(4),range(4)] = c[-1]
        ufac[(0,1,2),(1,2,3)] = c[0,1:]
        assert_array_almost_equal(a, dot(ufac.conj().T, ufac))

        b = array([0.0, 0.5, 4.0-0.2j, 0.2j + 4.0])
        x = cho_solve_banded((c, False), b)
        assert_array_almost_equal(x, [0.0, 0.0, 1.0, 1.0])

    def test_lower_real(self):
        # Symmetric positive definite banded matrix `a`
        a = array([[4.0, 1.0, 0.0, 0.0],
                    [1.0, 4.0, 0.5, 0.0],
                    [0.0, 0.5, 4.0, 0.2],
                    [0.0, 0.0, 0.2, 4.0]])
        # Banded storage form of `a`.
        ab = array([[4.0, 4.0, 4.0, 4.0],
                    [1.0, 0.5, 0.2, -1.0]])
        c = cholesky_banded(ab, lower=True)
        lfac = zeros_like(a)
        lfac[range(4),range(4)] = c[0]
        lfac[(1,2,3),(0,1,2)] = c[1,:3]
        assert_array_almost_equal(a, dot(lfac, lfac.T))

        b = array([0.0, 0.5, 4.2, 4.2])
        x = cho_solve_banded((c, True), b)
        assert_array_almost_equal(x, [0.0, 0.0, 1.0, 1.0])

    def test_lower_complex(self):
        # Hermitian positive definite banded matrix `a`
        a = array([[4.0, 1.0,  0.0,  0.0],
                    [1.0, 4.0,  0.5,  0.0],
                    [0.0, 0.5,  4.0, -0.2j],
                    [0.0, 0.0,  0.2j, 4.0]])
        # Banded storage form of `a`.
        ab = array([[4.0, 4.0, 4.0,  4.0],
                    [1.0, 0.5, 0.2j, -1.0]])
        c = cholesky_banded(ab, lower=True)
        lfac = zeros_like(a)
        lfac[range(4),range(4)] = c[0]
        lfac[(1,2,3),(0,1,2)] = c[1,:3]
        assert_array_almost_equal(a, dot(lfac, lfac.conj().T))

        b = array([0.0, 0.5j, 3.8j, 3.8])
        x = cho_solve_banded((c, True), b)
        assert_array_almost_equal(x, [0.0, 0.0, 1.0j, 1.0])
