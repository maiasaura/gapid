# Examine OpenGL ES Apps with GAPID

GAPID helps you analyze and debug your apps that use OpenGL ES 2.0 or 3.1.
It lets you inspect
the GPU state and helps you understand what caused a specific rendering outcome. You
can start a GPU trace from an app project in Android Studio. You can then display the GPU trace in GAPID.

To collect a GPU trace, you can run your app on a connected Android hardware device,
including a phone, tablet, Android TV, or Android Auto. Your Android Studio project must be set to
[debuggable](http://developer.android.com/guide/topics/manifest/application-element.html#banner), not release.

GAPID lets you analyze Android apps written in any language supported by Android Studio projects,
including Java, C, and C++.

##  In this document
* [Who can benefit from GAPID?](#who)
* [About GAPID display](#display)
* [Where to go next](#begin)

### See also
* [Android Monitor](/studio/profile/android-monitor.html)
* [Displaying Graphics with OpenGL ES](/training/graphics/opengl/index.html)

<a name="who"></a>
## Who can benefit from GAPID?

With GAPID, developers can analyze any Android app that uses OpenGL
ES to render graphics on an Android device, for example, a game or map app. Here
are some typical scenarios where GAPID is useful to game developers.

Many game developers use 3D computer graphics software, such as Autodesk Maya or
open-source Blender, to create models. For example, they can create models of
inanimate objects or animated characters in the game. They then import the 3D
models into a game engine, such as Unity or Unreal Engine, and create their
game. The engine generates the game app code for the platform, such as Android
or iOS. Whether game developers choose to primarily auto-generate code, or write
much of the code themselves, GAPID can help identify areas to
improve, optimize, and correct.

Some developers port games from one platform to another. For example, they might
take a game that runs on Windows using Microsoft DirectX and port it to Android.
In these cases, GAPID can help to identify and correct graphical
errors that occur due to the different rendering schemes. The fix can sometimes
be as simple as changing the parameters that a game engine uses to generate code
on a different platform.

<a name="display"></a>
## About GAPID display

After you capture a GPU trace, Android Studio opens it in GAPID. The trace file
appears in the project-specific **Captures** window, so you can open
it any time you want.
You can also open a GPU trace file stored on your computer.

<p>Figure 1 shows a GPU trace displayed in GAPID.</p>
<p>
<img src="/images/am-gpu-debugger-reorg_2-2_2x.png" alt="" width="982"/>
</p>
<p class="img-caption"><b>Figure 1</b>. GPU Debugger display.
</p>

<a name="begin"></a>
## Where to go next

To take a GPU trace from a project, see
[Capture a GPU Trace](/studio/debug/am-gpu-debugger-trace.html).

For instructions on using GAPID, see
<a href="/studio/debug/am-gpu-debugger-analysis.html">[Analyze a Trace in GAPID](/studio/debug/am-gpu-debugger-analysis.html).


