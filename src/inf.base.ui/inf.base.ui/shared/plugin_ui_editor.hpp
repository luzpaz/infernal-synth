#ifndef INF_BASE_UI_PLUGIN_UI_EDITOR_HPP
#define INF_BASE_UI_PLUGIN_UI_EDITOR_HPP

#include <inf.base/topology/topology_info.hpp>
#include <inf.base.ui/controls/graph_plot.hpp>
#include <inf.base/plugin/plugin_controller.hpp>

#include <vstgui/plugin-bindings/vst3editor.h>
#include <vector>

namespace inf::base::ui {

class public_ui_editor
{
  plugin_controller* const _controller;
  topology_info const* const _topology;
  std::vector<base::ui::graph_plot*> _graphs;
  std::vector<std::vector<VSTGUI::CControl*>> _controls;

protected:
  using CView = VSTGUI::CView;
  using CFrame = VSTGUI::CFrame;
  using CControl = VSTGUI::CControl;
  using PlatformType = VSTGUI::PlatformType;
  using UTF8StringPtr = VSTGUI::UTF8StringPtr;

public:
  topology_info const* topology() const { return _topology; }
  plugin_controller* controller() const { return _controller; }

protected:
  void view_added(CFrame* view_frame, CView* view);
  void void_removed(CFrame* view_frame, CView* view);
  void update_dependent_visibility(std::int32_t tag);
  public_ui_editor(plugin_controller* controller, topology_info const* topology);
};

} // namespace inf::base::vst::ui
#endif // INF_BASE_UI_PLUGIN_UI_EDITOR_HPP
