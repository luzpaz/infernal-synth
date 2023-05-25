#include <inf.base.ui/shared/look_and_feel.hpp>
#include <inf.base.ui/controls/selector_label.hpp>

using namespace juce;

namespace inf::base::ui {

void 
inf_selector_label::mouseDown(MouseEvent const& event)
{
  inf_label::mouseDown(event);
}

void
inf_selector_label::paint(Graphics& g)
{
  // config
  int const vpad = 2;
  int const hpadl = 1;
  int const hpadr = 3;
  float const corner_size_fixed = 5.0f;
  float const outline_size_fixed = 1.0f;

  auto& lnf = dynamic_cast<inf_look_and_feel&>(getLookAndFeel());
  auto area = Rectangle<int>(
    getBounds().getX() + hpadl,
    getBounds().getY() + vpad / 2,
    getBounds().getWidth() - hpadl - hpadr,
    getBounds().getHeight() - vpad);

  // fill
  std::int32_t background_low = inf_look_and_feel::colors::selector_label_background_low;
  std::int32_t background_high = inf_look_and_feel::colors::selector_label_background_high;
  lnf.fill_gradient_rounded_rectangle(
    g, *this, area.toFloat(), background_low,
    background_high, corner_size_fixed, 0.25f);

  // outline
  lnf.stroke_gradient_rounded_rectangle(
    g, *this, area.toFloat(), inf_look_and_feel::colors::selector_label_outline_low,
    inf_look_and_feel::colors::selector_label_outline_high, corner_size_fixed, 0.25f, outline_size_fixed);

  // text
  g.setFont(getFont());
  g.setColour(findColour(inf_look_and_feel::colors::selector_label_text));
  g.drawText(getText(), area, Justification::centred, false);
}

} // namespace inf::base::ui