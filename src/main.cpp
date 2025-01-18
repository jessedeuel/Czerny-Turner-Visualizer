#include "raylib.h"
#include <iostream>
#include "serial.h"

#define MAX_INPUT_CHARS 100

int main() 
{
    InitWindow(800, 450, "Czerny Turner Visualizer");
    SetTargetFPS(60);

    Font aptos = LoadFontEx("resources/Aptos.ttf", 36, 0, 250);

    char port[MAX_INPUT_CHARS + 1] = "\0";
    int letterCount = 0;
    serial_port serial(port);
    bool validPort = false;

    Rectangle textBox = { 100.0, 15.0, 255, 50 };
    bool mouseOnText = false;

    int framesCounter = 0;

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (CheckCollisionPointRec(GetMousePosition(), textBox)) 
            mouseOnText = true;
        else
            mouseOnText = false;

        if (mouseOnText)
        {
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            // Get char pressed (unicode) on the queue
            int key = GetCharPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {
                // Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
                {
                    port[letterCount] = (char)key;
                    port[letterCount + 1] = '\0';
                    letterCount++;
                }

                key = GetCharPressed(); // Check next char in queue
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                port[letterCount] = '\0';
            }

            if (IsKeyPressed(KEY_ENTER))
            {
                serial.set_port(port);

                if (serial.open_serial() == 0)
                {
                    std::printf("Found %s.\n", port);
                    validPort = true;
                    
                    int ret = serial.setup_serial();

                    if (ret == 0)
                        std::cout << "Successfully setup COM4." << std::endl;
                    else if (ret == 1)
                        std::cout << "Error getting state." << std::endl;
                    else if (ret == 2)
                        std::cout << "Error setting state." << std::endl;
                    else if (ret == 3)
                        std::cout << "Error setting timeouts." << std::endl;


                }
                else
                {
                    std::printf("Didnt find %s.\n", port);
                    validPort = false;
                }
            }
        }
        else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        if (mouseOnText) framesCounter++;
        else framesCounter = 0;

        if (validPort)
        {
            const int bytes_to_read = 12;
            char buff[bytes_to_read + 1] = {0};
            int ret = serial.read_bytes(buff, bytes_to_read);

            if (ret == 0)
            {
                std::cout << "Read " << bytes_to_read << " bytes: ";

                for (char i : buff)
                {
                    std::cout << i;
                }
                std::cout << std::endl;
            }
            else
                std::cout << "Error reading data." << std::endl;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawTextEx(aptos, "Port: ", (Vector2){ 20.0, 22.0 }, aptos.baseSize, 2, GRAY);

            DrawRectangleRec(textBox, LIGHTGRAY);
            if (mouseOnText)
                DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, BLUE);
            else
                DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

            if (validPort)
            {
                DrawTextEx(aptos, port, (Vector2){ (float)textBox.x + 5, (float)textBox.y + 8}, aptos.baseSize, 2, DARKGREEN);
            }
            else
            {
                DrawTextEx(aptos, port, (Vector2){ (float)textBox.x + 5, (float)textBox.y + 8}, aptos.baseSize, 2, MAROON);
            }

            if (mouseOnText)
            {
                if (letterCount < MAX_INPUT_CHARS)
                {
                    // Draw blinking pipe char
                    if (((framesCounter/20)%2) == 0)
                    {
                        Vector2 cursor_pos = MeasureTextEx(aptos, port, aptos.baseSize, 2);
                        if (letterCount == 0)
                            cursor_pos.x += textBox.x + 5;
                        else
                            cursor_pos.x += textBox.x + 2;
                        
                        cursor_pos.y = cursor_pos.y - aptos.baseSize + 20;
                        DrawTextEx(aptos, "|", cursor_pos, aptos.baseSize, 2, BLACK);
                    }
                }
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    UnloadFont(aptos);

    CloseWindow();

    /*

    int ret = serial.setup_serial();

    if (ret == 0)
        std::cout << "Successfully setup COM4." << std::endl;
    else if (ret == 1)
        std::cout << "Error getting state." << std::endl;
    else if (ret == 2)
        std::cout << "Error setting state." << std::endl;
    else if (ret == 3)
        std::cout << "Error setting timeouts." << std::endl;

    const int bytes_to_read = 12;
    char buff[bytes_to_read + 1] = {0};
    ret = serial.read_bytes(buff, bytes_to_read);

    if (ret == 0)
    {
        std::cout << "Read " << bytes_to_read << " bytes: ";

        for (char i : buff)
        {
            std::cout << i;
        }
        std::cout << std::endl;
    }
    else
        std::cout << "Error reading data." << std::endl;
    */

    return 0;
}

bool IsAnyKeyPressed()
{
    bool keyPressed = false;
    int key = GetKeyPressed();

    if ((key >= 32) && (key <= 126)) keyPressed = true;

    return keyPressed;
}