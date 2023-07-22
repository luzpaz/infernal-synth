#ifndef INF_BASE_SHARED_SPECTRUM_ANALYZER_HPP
#define INF_BASE_SHARED_SPECTRUM_ANALYZER_HPP

#include <inf.base/shared/fft.hpp>

#include <vector>
#include <complex>
#include <cstdint>

namespace inf::base {

// Returns spectral power at midi notes [0 .. bucket_count) in range [0..1].
class spectrum_analyzer
{
  fft _fft;
  std::vector<float> _output;  
  float power_at_note(std::vector<std::complex<float>> const& fft, std::int32_t midi, float resolution) const;

public:
  spectrum_analyzer();
  static inline std::int32_t const bucket_count = 144;
  float const* analyze(std::vector<float> const& audio, float resolution);
  float const* analyze(float const* audio, std::size_t count, float resolution);
};

inline spectrum_analyzer::spectrum_analyzer(): 
_fft(), _output() {}

inline float const* 
spectrum_analyzer::analyze(std::vector<float> const& audio, float resolution)
{ return analyze(audio.data(), audio.size(), resolution); }

} // namespace inf::base
#endif // INF_BASE_SHARED_SPECTRUM_ANALYZER_HPP