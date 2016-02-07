# SimCache
A Microsoft Flight like Aerocache experience for Microsoft Flight Simulator X and Lockheed Martin Prepar3D.

# Installation
1. Open `SimCache.sln` in Visual Studio 2013 or later and build in either Debug or Release configuration. Copy the resulting DLL to the FSX/ESP/P3D root directory.
2. Run cabdir on the `Gauges` folder, naming the resulting file `SimCache.cab` and place it in the `gauges` folder inside your FSX/ESP/P3D root directory.
3. Add the following entry to your `DLL.XML` file:

    ```
        <Launch.Addon>
            <Name>SimCache</Name>
            <Disabled>False</Disabled>
            <ManualLoad>False</ManualLoad>
            <Path>SimCache.dll</Path>
            <DllStartName>module_init</DllStartName>
            <DllStopName>module_deinit</DllStopName>
        </Launch.Addon>
    ```
    
4. Add the following entries to any aircraft `panel.cfg` file, replacing `XX` with the next window number in the sequence.

    ```
    [Window Titles]
    ...
    WindowXX=SimCache
    ...

    [WindowXX]
    size_mm=250,70
    position=6
    windowsize_ratio=1.000
    pixel_size=250,70
    visible=0
    sizable=0
    gauge01=SimCache!SimCache, 0,0
    ```

5. Launch the simulator and accept any security warnings related to `SimCache.dll`.
