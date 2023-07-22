#include <inf.base/shared/support.hpp>
#include <inf.base/shared/spectrum_analyzer.hpp>
#include <cassert>

namespace inf::base {

// https://stackoverflow.com/questions/604453/analyze-audio-using-fast-fourier-transform
// https://dsp.stackexchange.com/questions/46692/calculating-1-3-octave-spectrum-from-fft-dft
std::vector<float> const&
spectrum_analyzer::analyze(float const* audio, std::size_t count)
{
  _output.clear();
  float max = 0.0f;
  std::vector<std::complex<float>> const& fft = _fft.transform(audio, count);
  for (std::size_t i = 0; i < fft.size(); i++)
  {
    float real2 = fft[i].real() * fft[i].real();
    float imag2 = fft[i].imag() * fft[i].imag();
    _output.push_back(real2 + imag2);
  }
  for (std::size_t i = 0; i < _output.size(); i++) max = std::max(_output[i], max);
  for (std::size_t i = 0; i < _output.size(); i++) _output[i] = max == 0.0f ? 0.0f : sanity_unipolar(_output[i] / max);
  return _output;
}

} // namespace inf::base