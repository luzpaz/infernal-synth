#ifndef SVN_SYNTH_EFFECT_GRAPH_HPP
#define SVN_SYNTH_EFFECT_GRAPH_HPP

#include <inf.base/shared/support.hpp>
#include <inf.base/processor/graph_processor.hpp>

#include <array>
#include <vector>

namespace inf::synth {

class effect_graph_base:
public inf::base::graph_processor
{
protected:
  std::array<std::vector<float>, inf::base::stereo_channels> _audio_in;
  std::array<std::vector<float>, inf::base::stereo_channels> _audio_out;

  effect_graph_base(base::topology_info const* topology, base::part_id id);
  void process_graph(base::block_input const& input, float sample_rate);
};

inline effect_graph_base::
effect_graph_base(base::topology_info const* topology, base::part_id id):
inf::base::graph_processor(topology, id), _audio_in(), _audio_out() {}

} // namespace inf::synth
#endif // SVN_SYNTH_EFFECT_GRAPH_HPP