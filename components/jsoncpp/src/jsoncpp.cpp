// cpd - Coherent Point Drift
// Copyright (C) 2017 Pete Gadomski <pete.gadomski@gmail.com>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#include <cpd/jsoncpp.hpp>

namespace cpd {

Json::Value to_json(const Result& result) {
    Json::Value root;
    root["sigma2"] = result.sigma2;
    root["runtime"] = double(result.runtime.count()) / 1e6;
    root["iterations"] = Json::UInt64(result.iterations);
    return root;
}

Json::Value to_json(const RigidResult& result) {
    const Result* base = &result;
    Json::Value root = to_json(*base);
    root["rotation"] = cpd::to_json(result.rotation);
    root["translation"] = cpd::to_json(result.translation);
    root["scale"] = result.scale;
    return root;
}

Json::Value to_json(const AffineResult& result) {
    const Result* base = &result;
    Json::Value root = to_json(*base);
    root["transform"] = cpd::to_json(result.transform);
    root["translation"] = cpd::to_json(result.translation);
    return root;
}

Json::Value to_json(const NonrigidResult& result) {
    const Result* base = &result;
    return to_json(*base);
}

Json::Value to_json(const Matrix& matrix) {
    Json::Value root;
    for (Matrix::Index row = 0; row < matrix.rows(); ++row) {
        root[Json::ArrayIndex(row)] = Json::Value(Json::ValueType::arrayValue);
        for (Matrix::Index col = 0; col < matrix.cols(); ++col) {
            root[Json::ArrayIndex(row)][Json::ArrayIndex(col)] =
                matrix(row, col);
        }
    }
    return root;
}

std::ostream& operator<<(std::ostream& ostream, const Result& result) {
    return ostream;
}
}
