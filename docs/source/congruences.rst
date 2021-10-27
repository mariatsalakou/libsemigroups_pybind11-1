.. Copyright (c) 2021, J. D. Mitchell

   Distributed under the terms of the GPL license version 3.

   The full license is in the file LICENSE, distributed with this software.

.. currentmodule:: libsemigroups_pybind11

Congruences
===========

``libsemigroups_pybind11`` implements serveral algorithms for computing a
congruence of a semigroup or monoid. The main algorithms implemented are
Todd-Coxeter, Knuth-Bendix, and the brute-force enumeration in parallel.  This
class is, at present, not very customisable, and lacks some of the fine grained
control offered by the classes implementing individual algorithms, such as
:class:`.ToddCoxeter` and :class:`.KnuthBendix`.

All of the classes for congruences in ``libsemigroups_pybind11`` can be used
"interactively", in the sense that they can be run for a particular amount of
time, or until some condition is met; for further details see, for example,
:py:meth:`.ToddCoxeter.run_for` and :py:meth:`.ToddCoxeter.run_until`.

The "handedness" of a congruence is determined by:

.. autoclass:: congruence_kind

The classes in ``libsemigroups_pybind11`` for congruences are:

.. toctree::
   :maxdepth: 1

   api/cong
   api/toddcoxeter
