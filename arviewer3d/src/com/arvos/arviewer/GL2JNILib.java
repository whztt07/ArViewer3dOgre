/*
 Copyright (C) 2015, Peter Graf

   This file is part of Arvos-App - AR Viewer Open Source App for Android.
   Arvos-App is free software.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    
   For more information on the AR Viewer Open Source - App,
   please see: http://www.arvos-app.com/.
 */

package com.arvos.arviewer;

import android.view.Surface;

/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

public class GL2JNILib
{
	static
	{
		System.loadLibrary("gl2jni");
	}

	/**
	 * Initialize
	 * 
	 * @param width
	 *            the current view width
	 * @param height
	 *            the current view height
	 * @param assetManager
	 *            the asset manager
	 * @param externalFilesDir
	 *            the external files directory
	 * @param surface
	 *            the surface
	 */
	public static native <jobject, jstring> void init(int width, int height, jobject assetManager,
			jstring externalFilesDir, jobject surface);

	/**
	 * Render one frame.
	 */
	public static native void step();

	public static native <jobject, jstring> void nativeOnStart(jobject assetManager, jstring externalFilesDir);

	public static native void nativeOnResume();

	public static native void nativeOnPause();

	public static native void nativeOnStop();

	public static native void nativeSetSurface(Surface surface);

}
