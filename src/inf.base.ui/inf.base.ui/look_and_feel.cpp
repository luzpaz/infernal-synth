#include <inf.base/shared/support.hpp>
#include <inf.base.ui/look_and_feel.hpp>

using namespace juce;

namespace inf::base::ui {

void 
inf_look_and_feel::drawRotarySlider(
  juce::Graphics& g, int x, int y, int w, int h, 
  float pos, float start, float end, juce::Slider& s)
{
  float rx = static_cast<float>(x);
  float ry = static_cast<float>(y);
  if(h < w) rx += (w - h) * 0.5f;
  if(w < h) ry += (h - w) * 0.5f;
  float const margin_factor = 0.05f;
  float const inner_size_factor = 0.8;
  float const line_thickness_factor = 0.05f;
  float const margin = std::min(w, h) * margin_factor;
  float const size = std::min(w, h) - 2.0f * margin;
  float const radius = size / 2.0f;
  float const inner_size = size * inner_size_factor;
  float const angle = start + pos * (end - start) - pi32 * 0.5f;
  float const fx = static_cast<float>(rx + margin);
  float const fy = static_cast<float>(ry + margin);
  float const line_thickness = size * line_thickness_factor;

  // fill
  float fillx = fx + (size - inner_size) * 0.5f;
  float filly = fy + (size - inner_size) * 0.5f;
  //g.setColour(s.findColour(Slider::ColourIds::rotarySliderFillColourId));
  auto shadow = s.findColour(colors::knob_shadow);
  auto high = s.findColour(colors::knob_highlight);
  g.setGradientFill(ColourGradient(high, fillx, filly, shadow, fillx + inner_size, filly + inner_size, false));
  g.fillEllipse(fillx, filly, inner_size, inner_size);

  // thumb
  Path thumb;
  float cx = rx + margin + size / 2.0f;
  float cy = ry + margin + size / 2.0f;
  float line_end_x = cx + radius * inner_size_factor * std::cos(angle);
  float line_end_y = cy + radius * inner_size_factor * std::sin(angle);
  thumb.addLineSegment(Line<float>(cx, cy, line_end_x, line_end_y), 1.0f);
  g.setColour(s.findColour(Slider::ColourIds::thumbColourId));
  g.strokePath(thumb, PathStrokeType(line_thickness, PathStrokeType::curved, PathStrokeType::rounded));

  // outline
  Path arc;
  arc.addCentredArc(cx, cy, radius, radius, 0.0f, start, end, true);
  g.setColour(s.findColour(Slider::ColourIds::rotarySliderOutlineColourId));
  g.strokePath(arc, PathStrokeType(line_thickness, PathStrokeType::curved, PathStrokeType::rounded));

  //LookAndFeel_V4::drawRotarySlider(g, x, y, w, h, pos, start, end, s);

  /*
  
   auto outline = slider.findColour (Slider::rotarySliderOutlineColourId);
    auto fill    = slider.findColour (Slider::rotarySliderFillColourId);

    auto bounds = Rectangle<int> (x, y, width, height).toFloat().reduced (10);

    auto radius = jmin (bounds.getWidth(), bounds.getHeight()) / 2.0f;
    auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    auto lineW = jmin (8.0f, radius * 0.5f);
    auto arcRadius = radius - lineW * 0.5f;

    Path backgroundArc;
    backgroundArc.addCentredArc (bounds.getCentreX(),
                                 bounds.getCentreY(),
                                 arcRadius,
                                 arcRadius,
                                 0.0f,
                                 rotaryStartAngle,
                                 rotaryEndAngle,
                                 true);

    g.setColour (outline);
    g.strokePath (backgroundArc, PathStrokeType (lineW, PathStrokeType::curved, PathStrokeType::rounded));

    if (slider.isEnabled())
    {
        Path valueArc;
        valueArc.addCentredArc (bounds.getCentreX(),
                                bounds.getCentreY(),
                                arcRadius,
                                arcRadius,
                                0.0f,
                                rotaryStartAngle,
                                toAngle,
                                true);

        g.setColour (fill);
        g.strokePath (valueArc, PathStrokeType (lineW, PathStrokeType::curved, PathStrokeType::rounded));
    }

    auto thumbWidth = lineW * 2.0f;
    Point<float> thumbPoint (bounds.getCentreX() + arcRadius * std::cos (toAngle - MathConstants<float>::halfPi),
                             bounds.getCentreY() + arcRadius * std::sin (toAngle - MathConstants<float>::halfPi));

    g.setColour (slider.findColour (Slider::thumbColourId));
    g.fillEllipse (Rectangle<float> (thumbWidth, thumbWidth).withCentre (thumbPoint));*/
}

} // namespace inf::base::ui