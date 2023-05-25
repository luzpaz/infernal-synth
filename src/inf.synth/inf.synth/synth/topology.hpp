#ifndef INF_SYNTH_SYNTH_TOPOLOGY_HPP
#define INF_SYNTH_SYNTH_TOPOLOGY_HPP

#include <inf.base/plugin/audio_processor.hpp>
#include <inf.base/plugin/graph_processor.hpp>
#include <inf.base/topology/part_descriptor.hpp>

#include <memory>
#include <cstdint>

namespace inf::synth {

extern base::part_descriptor const part_descriptors[];
  
// global topo
struct part_type_t { enum value { 
  vosc, veffect, geffect, vaudio_bank, gaudio_bank, 
  voice, master, venv, vlfo, glfo, vcv_bank, gcv_bank, 
  vcv_plot, gcv_plot, active, output, count }; };
typedef part_type_t::value part_type;

struct active_param_t { enum value { 
  vosc, veffect, geffect, venv, vlfo, 
  glfo, vcv_bank, gcv_bank, count }; };
typedef active_param_t::value active_param;

// plugin entry
struct synth_topology : 
public base::topology_info
{
  bool const _is_instrument;

  void init_fx_clear_patch(base::param_value* state) const;
  void init_fx_factory_preset(base::param_value* state) const;
  void init_instrument_clear_patch(base::param_value* state) const;
  void init_instrument_factory_preset(base::param_value* state) const;

protected:
  synth_topology(bool is_instrument): 
  _is_instrument(is_instrument) {}

public:
  void init_clear_patch(base::param_value* state) const override;
  void init_factory_preset(base::param_value* state) const override;
  bool is_instrument() const override { return _is_instrument; }

  std::unique_ptr<base::audio_processor> 
  create_audio_processor(
    base::param_value* state, std::int32_t* changed, 
    float sample_rate, std::int32_t max_sample_count) const override;
  std::unique_ptr<base::graph_processor>
  create_graph_processor(base::part_id id, std::int32_t graph_type) const override;
  base::param_value convert_param(
    std::int32_t index, base::param_value old_value,
    std::string const& old_text, std::uint16_t old_major, std::uint16_t old_minor) const override;

private:
  std::unique_ptr<base::graph_processor>
    create_graph_processor_effect(base::part_id id, std::int32_t graph_type) const;
  std::unique_ptr<base::graph_processor>
    create_graph_processor_oscillator(base::part_id id, std::int32_t graph_type) const;
};
 
} // namespace inf::synth
#endif // INF_SYNTH_SYNTH_TOPOLOGY_HPP