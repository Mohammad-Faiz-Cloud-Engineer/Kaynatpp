/**
 * @file gui_system.hpp
 * @brief Simple GUI system for Kaynat++
 * 
 * Basic GUI implementation that can be extended with SDL2/ImGui later
 */

#pragma once

#include <string>
#include <memory>
#include <vector>
#include <map>
#include <functional>

namespace kaynat {

/**
 * @brief GUI Widget base class
 */
class Widget {
public:
    virtual ~Widget() = default;
    virtual void render() = 0;
    virtual std::string get_type() const = 0;
    
    std::string id;
    int x = 0;
    int y = 0;
    int width = 100;
    int height = 30;
};

/**
 * @brief Window widget
 */
class Window : public Widget {
public:
    Window(const std::string& title, int w, int h);
    void render() override;
    std::string get_type() const override { return "window"; }
    
    void add_widget(std::shared_ptr<Widget> widget);
    void show();
    void hide();
    
    std::string title;
    std::string background_color = "white";
    bool visible = false;
    std::vector<std::shared_ptr<Widget>> children;
};

/**
 * @brief Label widget
 */
class Label : public Widget {
public:
    Label(const std::string& text);
    void render() override;
    std::string get_type() const override { return "label"; }
    
    std::string text;
    std::string font = "default";
    int font_size = 12;
};

/**
 * @brief Button widget
 */
class Button : public Widget {
public:
    Button(const std::string& text);
    void render() override;
    std::string get_type() const override { return "button"; }
    void click();
    
    std::string text;
    std::function<void()> on_click;
};

/**
 * @brief Text input widget
 */
class TextInput : public Widget {
public:
    TextInput(const std::string& placeholder = "");
    void render() override;
    std::string get_type() const override { return "input"; }
    
    std::string value;
    std::string placeholder;
};

/**
 * @brief GUI Manager
 */
class GUIManager {
public:
    static GUIManager& instance();
    
    void register_window(const std::string& name, std::shared_ptr<Window> window);
    std::shared_ptr<Window> get_window(const std::string& name);
    void register_widget(const std::string& name, std::shared_ptr<Widget> widget);
    std::shared_ptr<Widget> get_widget(const std::string& name);
    void render_all();
    
private:
    GUIManager() = default;
    std::map<std::string, std::shared_ptr<Window>> windows_;
    std::map<std::string, std::shared_ptr<Widget>> widgets_;
};

} // namespace kaynat
