<h1><b>Application Template</b></h1>
        Main template used for all my projects. Used as a learning sandbox

<b><h2> Features </h2></b>
        <ul>
                <li> A simple template designed mainly for game development </li>
                <li> GUI built with Dear ImGui </li>
                <li> Cross-platform support (Windows & Linux) </li>
                <li> Load custom images and use them in the SDL2 enviroment </li>
        </ul>

<h2><b> Usage </b></h2>
        <ul>
                <li> Clone this repository and modify it to your liking </li>
                <li> You can access the Application class by simply calling "Application::GetInstance()" and including the application.h file </li>
                <li> It is posible to add a texture by placing it on the resource folder and calling "Application::GetInstance().AddTexture("TextureName")" it is then stored and can be accesed by "Application::GetInstance().GetTexture("TextureName")"</li>
        </ul>

<h2><b> </b></h2>

<b><h2>Compile</h2></b>
        For linux users, there is a Makefile, you only need SDL2, Mingw and Make; All you need to do is run "make build Makefile" and the executable will apperar on the Bin folder.
        <br>
        As for Windows, i have a batch script that you can run, just make sure you have Mingw installed and set up on your Enviroment variables

<h2>Credits</h2>
        <ul>
                <li> SDL2: The Simple DirectMedia Layer (SDL) is used for handling graphics, events, and input. SDL is licensed under the [Zlib License](https://www.libsdl.org/license.php). </li>
                <li> Dear ImGui: Dear ImGui is used for creating the GUI elements in the project. It is a bloat-free graphical user interface library primarily used for debugging tools and applications. ImGui is licensed under the [MIT License](https://github.com/ocornut/imgui/blob/master/LICENSE.txt). </li>
                <li> C++ Standard Library: The C++ Standard Library is used for many common operations like memory management, data structures, and more. </li>
        </ul>
        <h3> Developers </h3>
        <ul>
                <li> Moises Gonzalez </li>
                <li> Emmanuel Lara </li>
        </ul>

<h2> <b> License </b> </h2>
        This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.