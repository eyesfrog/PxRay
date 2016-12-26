//
// Created by eyesfrog on 2016-12-25.
//

#ifndef PBRT_EFLOAT_H
#define PBRT_EFLOAT_H

#ifndef PBRT_CORE_EFLOAT_H
#define PBRT_CORE_EFLOAT_H

// core/efloat.h*
#include "pbrt.h"
#include "stringprint.h"

// EFloat Declarations
class EFloat {
public:
    // EFloat Public Methods
    EFloat() {}
    EFloat(float v, float err = 0.f) : v(v) {
        if (err == 0.)
            low = high = v;
        else {
            // Compute conservative bounds by rounding the endpoints away
            // from the middle. Note that this will be over-conservative in
            // cases where v-err or v+err are exactly representable in
            // floating-point, but it's probably not worth the trouble of
            // checking this case.
            low = NextFloatDown(v - err);
            high = NextFloatUp(v + err);
        }
// Store high precision reference value in _EFloat_
#ifndef NDEBUG
        vPrecise = v;
        Check();
#endif  // NDEBUG
    }
#ifndef NDEBUG
    EFloat(float v, long double lD, float err) : EFloat(v, err) {
        vPrecise = lD;
        Check();
    }
#endif  // DEBUG
    EFloat operator+(EFloat ef) const {
        EFloat r;
        r.v = v + ef.v;
#ifndef NDEBUG
        r.vPrecise = vPrecise + ef.vPrecise;
#endif  // DEBUG
        // Interval arithemetic addition, with the result rounded away from
        // the value r.v in order to be conservative.
        r.low = NextFloatDown(LowerBound() + ef.LowerBound());
        r.high = NextFloatUp(UpperBound() + ef.UpperBound());
        r.Check();
        return r;
    }
    explicit operator float() const { return v; }
    explicit operator double() const { return v; }
    float GetAbsoluteError() const { return high - low; }
    float UpperBound() const { return high; }
    float LowerBound() const { return low; }
#ifndef NDEBUG
    float GetRelativeError() const {
        return std::abs((vPrecise - v) / vPrecise);
    }
    long double PreciseValue() const { return vPrecise; }
#endif
    EFloat operator-(EFloat ef) const {
        EFloat r;
        r.v = v - ef.v;
#ifndef NDEBUG
        r.vPrecise = vPrecise - ef.vPrecise;
#endif
        r.low = NextFloatDown(LowerBound() - ef.UpperBound());
        r.high = NextFloatUp(UpperBound() - ef.LowerBound());
        r.Check();
        return r;
    }
    EFloat operator*(EFloat ef) const {
        EFloat r;
        r.v = v * ef.v;
#ifndef NDEBUG
        r.vPrecise = vPrecise * ef.vPrecise;
#endif
        Float prod[4] = {
                LowerBound() * ef.LowerBound(), UpperBound() * ef.LowerBound(),
                LowerBound() * ef.UpperBound(), UpperBound() * ef.UpperBound()};
        r.low = NextFloatDown(
                std::min(std::min(prod[0], prod[1]), std::min(prod[2], prod[3])));
        r.high = NextFloatUp(
                std::max(std::max(prod[0], prod[1]), std::max(prod[2], prod[3])));
        r.Check();
        return r;
    }
    EFloat operator/(EFloat ef) const {
        EFloat r;
        r.v = v / ef.v;
#ifndef NDEBUG
        r.vPrecise = vPrecise / ef.vPrecise;
#endif
        if (ef.low < 0 && ef.high > 0) {
            // Bah. The interval we're dividing by straddles zero, so just
            // return an interval of everything.
            r.low = -Infinity;
            r.high = Infinity;
        } else {
            Float div[4] = {
                    LowerBound() / ef.LowerBound(), UpperBound() / ef.LowerBound(),
                    LowerBound() / ef.UpperBound(), UpperBound() / ef.UpperBound()};
            r.low = NextFloatDown(
                    std::min(std::min(div[0], div[1]), std::min(div[2], div[3])));
            r.high = NextFloatUp(
                    std::max(std::max(div[0], div[1]), std::max(div[2], div[3])));
        }
        r.Check();
        return r;
    }
    EFloat operator-() const {
        EFloat r;
        r.v = -v;
#ifndef NDEBUG
        r.vPrecise = -vPrecise;
#endif
        r.low = -high;
        r.high = -low;
        r.Check();
        return r;
    }
    inline bool operator==(EFloat fe) const { return v == fe.v; }
    inline void Check() const {
        if (!std::isinf(low) && !std::isnan(low) && !std::isinf(high) &&
            !std::isnan(high))
            assert(low <= high);
#ifndef NDEBUG
        if (!std::isinf(v) && !std::isnan(v))
            assert(LowerBound() <= vPrecise && vPrecise <= UpperBound());
#endif
    }
    EFloat(const EFloat &ef) {
        ef.Check();
        v = ef.v;
        low = ef.low;
        high = ef.high;
#ifndef NDEBUG
        vPrecise = ef.vPrecise;
#endif
    }
    EFloat &operator=(const EFloat &ef) {
        ef.Check();
        if (&ef != this) {
            v = ef.v;
            low = ef.low;
            high = ef.high;
#ifndef NDEBUG
            vPrecise = ef.vPrecise;
#endif
        }
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const EFloat &ef) {
        os << StringPrintf("v=%f (%a) - [%f, %f]",
                           ef.v, ef.v, ef.low, ef.high);
#ifndef NDEBUG
        os << StringPrintf(", precise=%.30Lf", ef.vPrecise);
#endif // !NDEBUG
        return os;
    }

private:
    // EFloat Private Data
    float v, low, high;
#ifndef NDEBUG
    long double vPrecise;
#endif  // NDEBUG
    friend inline EFloat sqrt(EFloat fe);
    friend inline EFloat abs(EFloat fe);
    friend inline bool Quadratic(EFloat A, EFloat B, EFloat C, EFloat *t0,
                                 EFloat *t1);
};

// EFloat Inline Functions
inline EFloat operator*(float f, EFloat fe) { return EFloat(f) * fe; }

inline EFloat operator/(float f, EFloat fe) { return EFloat(f) / fe; }

inline EFloat operator+(float f, EFloat fe) { return EFloat(f) + fe; }

inline EFloat operator-(float f, EFloat fe) { return EFloat(f) - fe; }

inline EFloat sqrt(EFloat fe) {
    EFloat r;
    r.v = std::sqrt(fe.v);
#ifndef NDEBUG
    r.vPrecise = std::sqrt(fe.vPrecise);
#endif
    r.low = NextFloatDown(std::sqrt(fe.low));
    r.high = NextFloatUp(std::sqrt(fe.high));
    r.Check();
    return r;
}

inline EFloat abs(EFloat fe) {
    if (fe.low >= 0)
        // The entire interval is greater than zero, so we're all set.
        return fe;
    else if (fe.high <= 0) {
        // The entire interval is less than zero.
        EFloat r;
        r.v = -fe.v;
#ifndef NDEBUG
        r.vPrecise = -fe.vPrecise;
#endif
        r.low = -fe.high;
        r.high = -fe.low;
        r.Check();
        return r;
    } else {
        // The interval straddles zero.
        EFloat r;
        r.v = std::abs(fe.v);
#ifndef NDEBUG
        r.vPrecise = std::abs(fe.vPrecise);
#endif
        r.low = 0;
        r.high = std::max(-fe.low, fe.high);
        r.Check();
        return r;
    }
}

inline bool Quadratic(EFloat A, EFloat B, EFloat C, EFloat *t0, EFloat *t1);
inline bool Quadratic(EFloat A, EFloat B, EFloat C, EFloat *t0, EFloat *t1) {
    // Find quadratic discriminant
    double discrim = (double)B.v * (double)B.v - 4. * (double)A.v * (double)C.v;
    if (discrim < 0.) return false;
    double rootDiscrim = std::sqrt(discrim);

    EFloat floatRootDiscrim(rootDiscrim, MachineEpsilon * rootDiscrim);

    // Compute quadratic _t_ values
    EFloat q;
    if ((float)B < 0)
        q = -.5 * (B - floatRootDiscrim);
    else
        q = -.5 * (B + floatRootDiscrim);
    *t0 = q / A;
    *t1 = C / q;
    if ((float)*t0 > (float)*t1) std::swap(*t0, *t1);
    return true;
}

#endif //PBRT_EFLOAT_H
