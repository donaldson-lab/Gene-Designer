"""Functions for FIR filter design."""

import numpy
from numpy import pi, ceil
from scipy import special


def kaiserord(ripple, width):
    """Design a Kaiser window to limit ripple and width of transition region.

    Parameters
    ----------
    ripple -- positive number specifying maximum ripple in passband (dB)
                and minimum ripple in stopband
    width  -- width of transition region (normalized so that 1 corresponds
                to pi radians / sample)

    Returns
    -------
    N, beta -- the order and beta parameter for the kaiser window.

               signal.kaiser(N,beta,sym=0) returns the window as does
               signal.get_window(beta,N)
               signal.get_window(('kaiser',beta),N)

    Uses the empirical equations discovered by Kaiser.

    Oppenheim, Schafer, "Discrete-Time Signal Processing,", p.475-476.
    """
    A = abs(ripple)  # in case somebody is confused as to what's meant
    if (A>50):
        beta = 0.1102*(A-8.7)
    elif (A>21):
        beta = 0.5842*(A-21)**0.4 + 0.07886*(A-21)
    else:
        beta = 0.0
    N = (A-8)/2.285/(pi*width)
    return ceil(N), beta

def firwin(N, cutoff, width=None, window='hamming'):
    """
    FIR Filter Design using windowed ideal filter method.

    Parameters
    ----------
    N      -- order of filter (number of taps)
    cutoff -- cutoff frequency of filter (normalized so that 1 corresponds to
              Nyquist or pi radians / sample)

    width  -- if width is not None, then assume it is the approximate width of
              the transition region (normalized so that 1 corresonds to pi)
              for use in kaiser FIR filter design.
    window -- desired window to use. See get_window for a list
              of windows and required parameters.

    Returns
    -------
    h      -- coefficients of length N fir filter.

    """

    from signaltools import get_window
    if isinstance(width,float):
        A = 2.285*N*width + 8
        if (A < 21): beta = 0.0
        elif (A <= 50): beta = 0.5842*(A-21)**0.4 + 0.07886*(A-21)
        else: beta = 0.1102*(A-8.7)
        window=('kaiser',beta)

    win = get_window(window,N,fftbins=1)
    alpha = N//2
    m = numpy.arange(0,N)
    h = win*special.sinc(cutoff*(m-alpha))
    return h / numpy.sum(h,axis=0)
