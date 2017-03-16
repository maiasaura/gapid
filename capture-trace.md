# Capture a GPU Trace

## In this document
* [GPU trace files](#files)
* [Trace libraries](#libraries)
* [Tips for successfully capturing a GPU trace](#tips)
* [Restrictions](#restrictions)
* [Capture a GPU trace for an Android Studio project](#project)
* [View a saved GPU trace file](#saved)

### See also
* [Examine OpenGL ES Apps with GAPID](index.html)

## Dependencies and prerequisites
* OpenGL ES 2.0 or 3.1
* Latest available GPU Debugging tools
* Android hardware device connected through USB (phone, tablet, Android TV, or Android Auto)
* [USB Debugging](http://developer.android.com/studio/run/device.html#developer-device-options) in Developer Options enabled on the device
* Project set to [debuggable](https://developer.android.com/studio/run/device.html#setting-up)

After you set a certain run/debug configuration option and then run an app
project, Android Studio launches a dialog that lets you start a GPU trace.
<!-- Android Studio lets you take a GPU trace in two ways:
</p><ul>
<li>After you set a certain run/debug configuration option and then run an app
project, Android Studio launches a dialog that lets you start a GPU trace.
<li>After you install an APK on a hardware device, Android Studio lets
you begin a GPU trace from the <a href="/studio/profile/am-gpu.html">GPU Monitor</a>.</li>
</ul> -->

Before starting the GPU trace, Android Studio either determines the activity to launch,
or asks you for it. GPU tracing always starts at the beginning of your app. If you want to
trace a later portion of your app, you should modify your app to launch directly into that
later portion.

<a name="files"></a>
## GPU trace files

After you capture a GPU trace, Android Studio opens it in GAPID. The trace file
appears in the **Captures** window, so you can open
it any time you want. The GPU trace list in the **Captures** window
is project-specific. Android Studio stores the trace file in the project
`captures/` directory.

You can also open a GPU trace file stored on your computer, even if it's not listed in
the **Captures** window for a particular project.

<a name="libraries"></a>
## Trace libraries

GPU tracing doesn't modify your APK. Instead, it launches your app in debug
mode and, at startup, attaches the trace libraries to the running process.
Android Studio copies the trace libraries into the files
directory for the app on the device. (If needed, you can discover the files directory by using
the [`getFilesDir()`](https://developer.android.com/reference/android/content/Context.html#getFilesDir()) method.) Once loaded, the trace libraries capture OpenGL ES commands from your app and send them back to Android Studio so
you can analyze them. When you’re finished tracing the app, you can optionally
delete the trace libraries.

<a name="tips"></a>
## Tips for successfully capturing a GPU trace

Many apps load a large number of graphics at the beginning when you start them.
When you first begin a GPU trace for an app that’s just starting up, you need to
be patient while it loads this information. After loading, the tool starts to
capture frames.

The performance and memory of your development computer can influence how large
of a GPU trace you can display in GAPID. If your computer has trouble
displaying a large GPU trace, try capturing a smaller trace. For a typical
Android Studio configuration, we recommend keeping the capture to a maximum of
about 1000 frames and 500,000 calls.

To increase the amount of memory that Android Studio is allowed to use, follow
these steps:
1. Select **Help** > **Edit Custom VM Options**.
2. In the `studio.vmoptions` file, change the `-Xmx` option to `-Xmx2G` for 32-bit or `-Xmx4G` for 64-bit computers.
3. Save the file, and then restart Android Studio.

For more information, see [Customize your VM options](http://developer.android.com/studio/intro/studio-config.html#customize_vm).

<a name="restrictions"></a>
## Restrictions

Note the following GPU tracing behaviors:

* After you enable GPU tracing in your current run/debug configuration,
Android Studio traces your app every time you run it using that run/debug
configuration. If you want to stop GPU tracing, you should select a different
run/debug configuration or disable the option.
<!-- If you’re instead capturing a trace from the GPU Monitor, the
tool starts a trace whenever you click  **Launch**
  <img src="/images/tools/am-ilaunchgpu_2-2_2x.png"
    style="vertical-align:sub;margin:0;height:17px" alt="" />. -->
* You can’t take a GPU trace while debugging the app. If you select
**Run** > **Debug**, Android Studio disables GPU
  tracing automatically.

<a name="project"></a>
## Capture a GPU trace for an Android Studio project

To capture a GPU trace for an app in an Android Studio project, follow these
steps:

<ol>
<li>Open your Android Studio project. </li>
<li>Set the <a
href="/studio/run/rundebugconfig.html#profiling-tab">run/debug
configuration settings</a> for GAPID as follows: </li>
<ol type="a">
 <li>Select **Run** > **Edit Configurations**.
 <li>Click the **Profiling** tab.
 <li>Make sure that **Capture GPU Commands** is selected so you can
perform GPU tracing.</li>


<p>
If the **GPU Tools Missing** dialog appears, you need to install the GPU Debugging
tools as follows. In the dialog, click **OK**. In the **Install Missing
Components** dialog, click **Finish** to complete the installation.
</p>

  <li>In the **Run/Debug Configurations**
dialog, click **OK**.</li>
</ol>
<p>
<p class="note">**Tip:** You can define separate <a
href="/studio/run/rundebugconfig.html">run/debug
configurations</a> for tracing, running, and debugging your app. This helps
you to quickly switch between operations.
</p>
<li>Connect an Android hardware device to your USB port.</li>
<li>
If the **Allow USB Debugging** dialog appears on the device, click
**OK**.
</li>
<p>
This dialog typically appears on your home screen (for example, after you log
in), not on the boot screen. If you don’t allow USB debugging, Android Studio
shows your device as **OFFLINE**, and you can’t perform a GPU
trace.
</p>
<li>Run your project on the hardware device as follows:
<ol type="a">
 <li>Select **Run** > **Run**, or click
**Run**
<img src="/studio/images/buttons/toolbar-run.png" class="inline-icon" alt="" />.
 <li>In the **Select Deployment Target **dialog, select the
hardware device, and then click **OK**.</li>
</li>
<p>
The **Graphics Trace** dialog appears in Android Studio.
</p>

<p>
The **Waiting For Debugger** dialog appears on the device.
</p></ol>

<li>In the **Graphics Trace** dialog, optionally change the GPU trace file name
(without an extension), and then click **Trace**.</li>
<p>
The **Graphics Trace** dialog appears. First, the tool attaches the
trace library.
Next, it starts the trace.
</p>

<p>
If your device doesn’t support GPU tracing, you receive an error:
</p>
<p>
**GAPID does not currently support tracing on this
device**.
</p>

<li>Interact with your app on the hardware device.</li>
<p>
As long as the **MB** value in the **Graphics Trace** dialog
keeps rising while you interact with the
app, the GPU trace is proceeding normally.
</p>
<li>To end the GPU trace, in the **Graphics Trace** dialog, click
**Stop**.</li>
<p>
The trace opens in the <a href="/studio/debug/am-gpu-debugger-analysis.html">GPU Debugger</a>.
</p>
<p>
Android Studio creates a GPU trace file with an extension of
`.gfxtrace`.
</p>
<!-- SEEMS TO VARY Android Studio creates the GPU trace file with the file name
`<em>project_yyyy.mm.dd_hh.mm.ss</em>.gfxtrace` using the project
name, year, month, day, hour, minute, and second of the capture, for example,
`Teapot_2016.08.18_18.44`.`gfxtrace`. -->

<li>To take another GPU trace, you can run your app again.
<!-- , or
<a href="#monitor">start the trace from the GPU
Monitor</a>. -->
</li>
<p>
You can view your saved GPU traces in the **Captures** window. See
<a href="#saved">View a saved GPU trace file</a>.
</p>
</ol>
<!-- <h2 id="apk">Prepare to trace an APK</h2>

<p>
To capture a GPU trace from an APK, follow these steps:
</p><ol>
<li>Open an Android Studio project.</li>
<p>
Although the APK doesn’t need to be associated with a project, Android Studio
lists GPU traces in the **Captures** window for a project. It
stores the trace in the project `captures/` directory.
</p>
<p>
You can create an empty project for the purpose of capturing GPU traces. If you
develop and run within Android Studio, we recommend that you instead follow the
steps for <a href="#project">Capturing a GPU Trace for an Android Studio
Project</a>.
</p>
<li>Connect an Android hardware device to your USB port.</li>
<li>
If the **Allow USB Debugging** dialog appears on the device, click
**OK**.
</li>
<p>
This dialog typically appears on your home screen (for example, after you log
in), not on the boot screen. If you don’t allow USB debugging, Android Monitor
shows your device as **OFFLINE**, and you can’t perform a trace.
</p>
<li>Install the APK on your hardware device.</li>
<p>
If the APK is on your development computer, you can transfer it to your device
with <a
href="https://developer.android.com/studio/command-line/adb.html#move">adb</a>.
For example:
</p>
<pre
class="no-pretty-print">adb install /Users/me/Downloads/myapp.apk
</pre>
<li><a href="#monitor">Start the trace from the GPU
Monitor</a>.
</li>
</ol>

<h2 id="monitor">Capture a GPU trace from the GPU Monitor</h2>
<p>After you install your app on a connected hardware device, as described in the previous
sections, you can use the GPU Monitor to capture a trace.
</p>

<p>
To start a GPU trace from the GPU Monitor, follow these steps:
</p><ol>
<li><a
href="https://developer.android.com/studio/profile/am-basics.html#displaying">Open
Android Monitor</a>.
<li>In the Device menu, <a
href="/studio/profile/am-basics.html#switching">select the hardware device</a>.
<li>Click the **Monitors** tab and <a
href="/studio/profile/am-basics.html#rearranging">display
the GPU Monitor</a>.
<li>To start tracing, click **Launch**
  <img src="/images/tools/am-ilaunchgpu_2-2_2x.png"
    style="vertical-align:sub;margin:0;height:17px" alt="" />.</li>
<p>
If the **GPU Tools Missing** dialog appears, you need to install the GPU Debugging
tools as follows. In the dialog, click **OK**. In the **Install Missing
Components** dialog, click **Finish** to complete the installation.
</p>
<p>
The **Launch Activity** dialog appears.
</p>

<li>In the dialog, select the app process.</li>
<p>
For example, the <a href="http://google.github.io/zooshi/" class="external-link">Zooshi app</a> has
a `com.google.fpl.zooshi` process that you can select.
</p>
<li>Optionally type a different GPU trace file name
(without an extension).</li>
<li>Click **Trace**.</li>
<p>
The **Graphics Trace** dialog appears. First, the tool launches the app and attaches
the trace library. Then it starts the trace.
</p>
<p>
If your device doesn’t support GPU tracing, you receive an error:
</p>
<p>
**GAPID does not currently support tracing on this
device**.
</p>

<li>Interact with your app on the hardware device.</li>
<p>
As long as the **MB** value in the **Graphics Trace** dialog
keeps rising while you interact with the
app, the GPU trace is proceeding normally.
</p>
<li>To end the GPU trace, in the **Graphics Trace** dialog, click
**Stop**.</li>
<p>
The trace opens in the <a href="/studio/debug/am-gpu-debugger-analysis.html">GPU Debugger</a>.
</p>
<p>
Android Studio creates a GPU trace file with an extension of
`.gfxtrace`.
</p></ol> -->
<!-- SEEMS TO VARY. Android Studio creates the GPU trace file with the file name
`<em>project_yyyy.mm.dd_hh.mm.ss</em>.gfxtrace` using the project
name, year, month, day, hour, minute, and second of the capture, for example,
`Teapot_2016.08.18_18.44`.`gfxtrace`.-->


<h2 id="saved">View a saved GPU trace file</h2>
<p>
After you perform a GPU trace, Android Studio automatically stores it so you can view
it again. It places the file in the `captures/` directory of the
project where you took the GPU trace. You can open a GPU trace file from the
**Captures** window for a project, or by selecting the file on
disk.
</p>
<p>
To open a GPU trace file from the **Captures** window, follow these
steps:
</p><ol>
<li>Open an Android Studio project.
<li>Select **View** > **Tools Windows** >
**Captures**.</li>
<p>
The **Captures** window appears.
</p>
<li>Open the **GFX Trace** folder.
<li>Double-click the trace file to view it in GAPID.</li>
<p>
The <a href="/studio/debug/am-gpu-debugger-analysis.html">GPU Debugger</a> appears.
</p>
</ol>
<p>
To open a GPU trace file stored on your development computer, follow these
steps:
</p><ol>
<li>Open an Android Studio project.
<li>Select **File** > **Open**.
<li>In the **Open File or Project** dialog, select the GPU trace,
and then click **OK**.</li>
<p>
Android Studio typically places GPU trace files in the
`AndroidStudioProjects/<em>project-name</em>/captures/` directory.

<li>Open the **GFX Trace** folder.
<li>Double-click the trace file to view it in GAPID.</li>
<p>
The <a href="/studio/debug/am-gpu-debugger-analysis.html">GPU Debugger</a> appears.
</p>
</ol>


