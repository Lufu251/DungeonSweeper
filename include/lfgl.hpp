#pragma once

#include <vector>
#include <raylib.h>

namespace lfgl {
    // -------------------------------------------- GENERAL SECTION --------------------------------------------
    template<typename T>
    struct Array2D{
    private:
        int mX, mY;
        std::vector<T> mData;

    public:
        Array2D(){}
        Array2D(size_t& x, size_t& y):mX(x), mY(y), mData(x*y){}
        
        void reserve(size_t& x, size_t& y){
            mData.reserve(x * y);
            mX = x;
            mY = y;
        }

        void resize(size_t& x, size_t& y){
            mData.resize(x * y);
            mX = x;
            mY = y;
        }

        int getX(){
            return mX;
        }

        int getY(){
            return mY;
        }

        T& operator()(size_t x, size_t y){
            return mData[mX * y + x];
        }

        const T& operator()(size_t x, size_t y) const {
            return mData[mX * y + x];
        }
    };

    // -------------------------------------------- GUI SECTION --------------------------------------------
    class Button{
        public:
        Rectangle mRect;

        bool mIsHovered = false;
        bool mIsPressed = false;
        bool mIsLongPressed = false;
        bool mIsSelected = false;
        bool mIsToggled = false;

        Button(){}
        Button(const Rectangle& rect) : mRect(rect){}
        ~Button(){}

        // Update the states of the Button (Hovered, Pressed, Down)
        // States Selected and Toggled are only updated if select or toggle is true
        void update(const bool& select, const bool& toggle){
            updateHovered();
            updatePressed();
            updateDown();
            
            if(select) updateSelect();
            if(toggle) updateToggled();
        }

        void setSize(const Vector2& size){
            mRect.width = size.x;
            mRect.height = size.y;
        }
        void setPosition(const Vector2& position){
            mRect.x = position.x;
            mRect.y = position.y;
        }

        private:
        // Check if the element is hovered.
        void updateHovered(){
            Vector2 mouseP = GetMousePosition();

            if(CheckCollisionPointRec(mouseP, mRect)){
                mIsHovered = true;
            }
            else{
                mIsHovered = false;
            }
        }

        // Check if element is pressed. Hovered must always be called before this function.
        void updatePressed(){
            if(mIsHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                mIsPressed = true;
                mIsSelected = true;
            }
            else{
                mIsPressed = false;
            }
        }

        // Check if element is long pressed. Hovered must always be called before this function.
        void updateDown(){
            if(mIsHovered && IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                mIsLongPressed = true;
            }
            else{
                mIsLongPressed = false;
            }
        }

        // Check if the element is Selected. Pressed and Hovered must be called before this.
        void updateSelect(){
            if(!mIsHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                mIsSelected = false;
            }
        }

        // Check if the element is Toggled. Pressed and Hovered must be called before this.
        void updateToggled(){
            if(mIsHovered && mIsPressed){
                mIsToggled = !mIsToggled;
            }
        }
    };


}