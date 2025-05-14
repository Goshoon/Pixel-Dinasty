<h1><b>Pixel Dinasty - Sandbox </b></h1>
        Small sandbox game made using C++ and SDL2, based in games lie "Powder" and "The Sandbox"

<b><h2> Features </h2></b>
        <ul>
            <li> Place Static and Dynamic pixels </li>
            <li> Use materials such as Water with basic fluid mechanics or dirt </li>
            <li> Swap colors for dynamic and static pixels </li>
            <li> Chnage background color </li>
            <li> Save and load and share your levels! (not added yet) </li>
        </ul>

<h2><b> Usage </b></h2>
        Before running the app place <b>Resources<b> folder in the Bin folder, or anywhere where the executable is creted, after that just run the application.


<b><h2>Compile</h2></b>
        On <b>linux<b> you can use make to build the project it should place everything on the Bin folder. 
        On <b>Windowsb</b> you have two options:
        <ul>
            <li> Build the project manually using G++ and place the required files into it ( all SDL2 .dll files and Resource folder containing the Assets ) </li>
            <li> Use my script "build.bat" it uses Mingw to build the project and should do everything automatically. <b> your only requirement would be to have SDL2 includes and libraries on a folder called "Dependencies" on your local disk C. </b> Or you can swap the default folder on the compile.bat file where you have your "SDL2/include" and "SDL2/lib" folder. My script also embeds descriptions, version info and game icon to the executable PixelDynasty.exe so its ready to be shipped </li>
        </ul>

In the end, you should have a Bin folder containing the Resources folder along with all the necessary .dll files.

<h2>Credits</h2>
        <ul>
                <li> SDL2: The Simple DirectMedia Layer (SDL) is used for handling graphics, events, and input. SDL is licensed under the [Zlib License](https://www.libsdl.org/license.php). </li>
                <li> Dear ImGui: Dear ImGui is used for creating the GUI elements in the project. It is a bloat-free graphical user interface library primarily used for debugging tools and applications. ImGui is licensed under the [MIT License](https://github.com/ocornut/imgui/blob/master/LICENSE.txt). </li>
                <li> C++ Standard Library: The C++ Standard Library is used for many common operations like memory management, data structures, and more. </li>
        </ul>

<h2> <b> License </b> </h2>
        This project is licensed under the AGPLv3 - see the [LICENSE](LICENSE) file for details.
