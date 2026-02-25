/**
 * @file gui_system.cpp
 * @brief GUI system implementation
 */

#include "gui_system.hpp"
#include <iostream>

namespace kaynat {

// Window implementation
Window::Window(const std::string& title, int w, int h) 
    : title(title) {
    width = w;
    height = h;
}

void Window::render() {
    if (!visible) return;
    
    std::cout << "\n╔══════════════════════════════════════════════════╗\n";
    std::cout << "║ " << title;
    for (size_t i = title.length(); i < 48; i++) std::cout << " ";
    std::cout << "║\n";
    std::cout << "╠══════════════════════════════════════════════════╣\n";
    
    for (auto& child : children) {
        child->render();
    }
    
    std::cout << "╚══════════════════════════════════════════════════╝\n";
}

void Window::add_widget(std::shared_ptr<Widget> widget) {
    children.push_back(widget);
}

void Window::show() {
    visible = true;
    render();
}

void Window::hide() {
    visible = false;
}

// Label implementation
Label::Label(const std::string& text) : text(text) {}

void Label::render() {
    std::cout << "║ [Label] " << text;
    for (size_t i = text.length() + 9; i < 48; i++) std::cout << " ";
    std::cout << "║\n";
}

// Button implementation
Button::Button(const std::string& text) : text(text) {}

void Button::render() {
    std::cout << "║ [Button: " << text << "]";
    for (size_t i = text.length() + 10; i < 48; i++) std::cout << " ";
    std::cout << "║\n";
}

void Button::click() {
    if (on_click) {
        on_click();
    }
}

// TextInput implementation
TextInput::TextInput(const std::string& placeholder) 
    : placeholder(placeholder) {}

void TextInput::render() {
    std::cout << "║ [Input: ";
    if (value.empty()) {
        std::cout << placeholder;
        for (size_t i = placeholder.length() + 9; i < 48; i++) std::cout << " ";
    } else {
        std::cout << value;
        for (size_t i = value.length() + 9; i < 48; i++) std::cout << " ";
    }
    std::cout << "]║\n";
}

// GUIManager implementation
GUIManager& GUIManager::instance() {
    static GUIManager instance;
    return instance;
}

void GUIManager::register_window(const std::string& name, std::shared_ptr<Window> window) {
    windows_[name] = window;
}

std::shared_ptr<Window> GUIManager::get_window(const std::string& name) {
    auto it = windows_.find(name);
    if (it != windows_.end()) {
        return it->second;
    }
    return nullptr;
}

void GUIManager::register_widget(const std::string& name, std::shared_ptr<Widget> widget) {
    widgets_[name] = widget;
}

std::shared_ptr<Widget> GUIManager::get_widget(const std::string& name) {
    auto it = widgets_.find(name);
    if (it != widgets_.end()) {
        return it->second;
    }
    return nullptr;
}

void GUIManager::render_all() {
    for (auto& [name, window] : windows_) {
        window->render();
    }
}

} // namespace kaynat
