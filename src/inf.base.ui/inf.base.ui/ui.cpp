#include <inf.base.ui/ui.hpp>

using namespace juce;
using namespace inf::base;

namespace inf::base::ui {

Component*
ui_element::build(plugin_controller* controller)
{
  _component.reset(build_core(controller));
  for (auto const& color : _colors)
    _component->setColour(color.first, color.second);
  _component->setVisible(true);
  return _component.get();
}

Component* 
root_element::build_core(plugin_controller* controller)
{
  container_component* result = new container_component;
  result->fill(_fill);
  result->addChildComponent(_content->build(controller));
  result->setOpaque(true);
  return result;
}

void
root_element::layout()
{
  std::int32_t w = _width;
  std::int32_t h = _content->pixel_height(w);
  component()->setBounds(0, 0, w, h);
  _content->component()->setBounds(0, 0, w, h);
  _content->layout();
}

Component*
container_element::build_core(plugin_controller* controller)
{
  container_component* result = new container_component;
  result->fill(_fill);
  result->addChildComponent(_content->build(controller));
  return result;
}

void
container_element::layout()
{
  _content->component()->setBounds(component()->getLocalBounds());
  _content->layout();
}

Component*
param_element::build_core(plugin_controller* controller)
{
  Slider* result = new Slider;
  result->setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
  return result;
}

Component*
grid_element::build_core(plugin_controller* controller)
{
  Component* result = new Component;
  for (std::size_t i = 0; i < _cell_contents.size(); i++)
    result->addChildComponent(_cell_contents[i]->build(controller));
  return result;
}

std::int32_t 
grid_element::pixel_height(std::int32_t pixel_width)
{
  double rows = _size.y;
  double cols = _size.x;
  double ratio = rows / cols * _xy_ratio;
  return static_cast<std::int32_t>(std::ceil(pixel_width * ratio));
}

ui_element*
grid_element::add_cell(std::unique_ptr<ui_element>&& content,
  std::int32_t row, std::int32_t col, std::int32_t row_span, std::int32_t col_span)
{
  ui_element* result = content.get();
  _cell_bounds.push_back(Rectangle<std::int32_t>(col, row, col_span, row_span));
  _cell_contents.push_back(std::move(content));
  return result;
}

void
grid_element::layout()
{
  Grid grid;
  for(std::int32_t row = 0; row < _size.y; row++)
    grid.templateRows.add(Grid::TrackInfo(Grid::Fr(1)));
  for (std::int32_t col = 0; col < _size.x; col++)
    grid.templateColumns.add(Grid::TrackInfo(Grid::Fr(1)));
  for (std::size_t i = 0; i < _cell_contents.size(); i++)
  {
    GridItem item(_cell_contents[i]->component());
    Rectangle<std::int32_t> bounds = _cell_bounds[i];
    auto col_span = GridItem::Span(bounds.getWidth());
    auto row_span = GridItem::Span(bounds.getHeight());
    grid.items.add(item.withArea(bounds.getY(), bounds.getX(), row_span, col_span));
  }
  grid.performLayout(component()->getLocalBounds());
  for (std::size_t i = 0; i < _cell_contents.size(); i++)
    _cell_contents[i]->layout();
}

} // namespace inf::base::ui