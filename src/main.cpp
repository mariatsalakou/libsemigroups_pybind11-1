//
// libsemigroups - C++ library for semigroups and monoids
// Copyright (C) 2021 James D. Mitchell
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#include "main.hpp"

// C std headers....
#include <stddef.h>  // for size_t

// C++ stl headers....
#include <initializer_list>  // for initializer_list

// libsemigroups....
#include <libsemigroups/cong-intf.hpp>  // for congruence_kind, congruence_kind:...
#include <libsemigroups/constants.hpp>  // for PositiveInfinity, Undefined, POSI...
#include <libsemigroups/kbe.hpp>        // for KBE, operator<<
#include <libsemigroups/report.hpp>     // for ReportGuard
#include <libsemigroups/string.hpp>     // for to_string
#include <libsemigroups/tce.hpp>        // for TCE
#include <libsemigroups/types.hpp>      // for tril, tril::FALSE, tril::TRUE

// pybind11....
#include <pybind11/operators.h>  // for self, operator<, operator==, self_t
#include <pybind11/pybind11.h>   // for module_, class_, enum_, init

namespace py = pybind11;

namespace libsemigroups {

  PYBIND11_MODULE(_libsemigroups_pybind11, m) {
    ////////////////////////////////////////////////////////////////////////
    // Enums
    ////////////////////////////////////////////////////////////////////////

    py::enum_<congruence_kind>(m, "congruence_kind", R"pbdoc(
      The values in this class can be used to indicate that a congruence should
      be 2-sided, left, or right.
    )pbdoc")
        .value("left", congruence_kind::left)
        .value("right", congruence_kind::right)
        .value("twosided", congruence_kind::twosided)
        .export_values();

    py::enum_<tril>(m, "tril")
        .value("true", tril::TRUE)
        .value("false", tril::FALSE)
        .value("unknown", tril::unknown)
        .export_values();

    py::class_<ReportGuard>(m,
                            "ReportGuard",
                            R"pbdoc(
      Objects of this type can be used to enable printing of some information
      during various of the computation in ``libsemigroups_pybind11``. Reporting
      is enable (or not) at construction time, and disable when the
      :py:class:`ReportGuard` goes out of scope.
    )pbdoc")
        .def(py::init<bool>(),
             py::arg("val") = true,
             R"pbdoc(
     Constructs a :py:class:`ReportGuard` with reporting enabled by default.

     :param val: whether to report or not (default: ``True``).
     :type val: bool
    )pbdoc");

    ////////////////////////////////////////////////////////////////////////
    // Constants
    ////////////////////////////////////////////////////////////////////////

    // TODO(later) do this properly
    m.attr("UNDEFINED") = py::int_(static_cast<size_t>(UNDEFINED));

    m.attr("POSITIVE_INFINITY")
        = py::int_(static_cast<size_t>(POSITIVE_INFINITY));

    ////////////////////////////////////////////////////////////////////////
    // Things so short they don't merit their own file
    ////////////////////////////////////////////////////////////////////////

    using TCE = detail::TCE;
    py::class_<TCE>(m, "TCE")
        .def("__repr__", &detail::to_string<TCE>)
        .def(pybind11::self == pybind11::self)
        .def(pybind11::self < pybind11::self);

    using KBE = detail::KBE;
    py::class_<KBE>(m, "KBE")
        .def("__repr__", &detail::to_string<KBE>)
        .def(pybind11::self == pybind11::self)
        .def(pybind11::self < pybind11::self);

    ////////////////////////////////////////////////////////////////////////
    // Init
    ////////////////////////////////////////////////////////////////////////

    init_forest(m);
    init_action_digraph(m);
    init_bipart(m);
    init_bmat8(m);
    init_cong(m);
    init_fpsemi(m);
    init_knuth_bendix(m);
    init_matrix(m);
    init_pbr(m);
    init_todd_coxeter(m);
    init_transf(m);
    init_words(m);

    init_froidure_pin(m);

#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
  }
}  // namespace libsemigroups
