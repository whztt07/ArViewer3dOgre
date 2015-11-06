/*
 Copyright (C) 2013, Peter Graf

   This file is part of Arvos - AR Viewer Open Source for Android.
   Arvos is free software.

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
    
   For more information on the AR Viewer Open Source or Peter Graf,
   please see: http://www.mission-base.com/.
 */

package com.arvos.arviewer.viewer;

import com.arvos.arviewer.Arvos;
import com.arvos.arviewer.ArvosLocationListener;
import com.arvos.arviewer.GL2JNILib;
import com.arvos.arviewer.IArvosLocationReceiver;
import com.arvos.arviewer.R;

import android.app.ActionBar;
import android.app.Activity;
import android.content.Context;
import android.content.res.AssetManager;
import android.location.Location;
import android.location.LocationManager;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.FrameLayout;
import android.widget.Toast;

/**
 * The augment viewer application.
 * <p>
 * Shows the camera view, overlays it with the augment being shown an opengl
 * view and overlays both with the radar view.
 * 
 * @author peter
 *
 */
public class ArvosViewer extends Activity implements IArvosLocationReceiver, IArvosViewer, SurfaceHolder.Callback
{
	public ArvosCameraView mCameraView = null;
	public GLSurfaceView mGLSurfaceView = null;
	public ArvosTextView mTextView = null;
	public ArvosRadarView mRadarView = null;

	private Arvos mInstance;
	private ArvosLocationListener mLocationListener;

	private static final String TAG = "ArvosViewer";

	@Override
	protected void onDestroy()
	{
		super.onDestroy();

		// TODO free EGL stuff
	}

	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		Log.i(TAG, "ArvosViewer onCreate");

		super.onCreate(savedInstanceState);

		mInstance = Arvos.getInstance(this);
		mLocationListener = new ArvosLocationListener((LocationManager) getSystemService(Context.LOCATION_SERVICE),
				this);

		createFrameLayout();
	}

	@Override
	protected void onStart()
	{
		super.onStart();
		Log.i(TAG, "ArvosViewer onStart()");
		AssetManager assetManager = getResources().getAssets();
		String externalFilesDir = getExternalFilesDir(null).getPath();
		
		GL2JNILib.nativeOnStart(assetManager, externalFilesDir);
	}

	@Override
	protected void onStop()
	{
		super.onStop();
		Log.i(TAG, "ArvosViewer onStop()");
		GL2JNILib.nativeOnStop();
	}

	@Override
	protected void onResume()
	{
		super.onResume();
		Log.i(TAG, "ArvosViewer onResume()");

		mLocationListener.onResume();
		mInstance.onResume();

		GL2JNILib.nativeOnResume();

		if (mRadarView != null)
		{
			mRadarView.onResume();
		}
	}

	@Override
	protected void onPause()
	{
		super.onPause();
		Log.i(TAG, "ArvosViewer onPause()");
		
		mLocationListener.onPause();
		Arvos.getInstance().onPause();

		GL2JNILib.nativeOnPause();

		if (mRadarView != null)
		{
			mRadarView.onPause();
		}
	}

	public void surfaceChanged(SurfaceHolder holder, int format, int w, int h)
	{
		Log.i(TAG, "ArvosViewer surfaceChanged");
		GL2JNILib.nativeSetSurface(holder.getSurface());
	}

	public void surfaceCreated(SurfaceHolder holder)
	{
		Log.i(TAG, "ArvosViewer surfaceCreated");
	}

	public void surfaceDestroyed(SurfaceHolder holder)
	{
		Log.i(TAG, "ArvosViewer surfaceDestroyed");
		GL2JNILib.nativeSetSurface(null);
	}

	private void createFrameLayout()
	{
		ActionBar actionBar = getActionBar();
		actionBar.setTitle(mInstance.mAugment.mName);
		actionBar.setSubtitle(String.format("Lon %.6f, Lat %.6f", mInstance.mLongitude, mInstance.mLatitude));

		FrameLayout frame = new FrameLayout(this);

		mCameraView = new ArvosCameraView(this);
		frame.addView(mCameraView);

		// mGLSurfaceView = new ArvosGLView(this);
		//mGLSurfaceView = new GL2JNIView(this);
		//frame.addView(mGLSurfaceView);

		SurfaceView surfaceView = new SurfaceView(this);
		Log.i(TAG, "createFrameLayout new SurfaceView");
		
		frame.addView(surfaceView);
		
		surfaceView.getHolder().addCallback(this);
		surfaceView.setOnClickListener(new OnClickListener()
		{
			@Override
			public void onClick(View v)
			{
				Toast toast = Toast.makeText(ArvosViewer.this,
						"This demo combines Java UI and native EGL + OpenGL renderer", Toast.LENGTH_LONG);
				toast.show();

			}
		});

		mRadarView = new ArvosRadarView(this);
		frame.addView(mRadarView);

		mTextView = new ArvosTextView(this);
		frame.addView(mTextView);

		setContentView(frame);

		if (mTextView != null)
		{
			mTextView.updateWithNewLocation();
		}
		if (mRadarView != null)
		{
			mRadarView.onResume();
		}
	}

	@Override
	public void onLocationChanged(boolean isNew, Location location)
	{
		ActionBar actionBar = getActionBar();
		actionBar.setSubtitle(String.format("Lon %.6f, Lat %.6f", mInstance.mLongitude, mInstance.mLatitude));
	}

	static final private int MENU_ITEM_CLOSE = Menu.FIRST;

	@Override
	public boolean onCreateOptionsMenu(Menu menu)
	{
		super.onCreateOptionsMenu(menu);

		int groupId = 0;
		int menuItemId = MENU_ITEM_CLOSE;
		int menuItemOrder = Menu.NONE;
		int menuItemText = R.string.menu_close;

		// Create the Menu Item and keep a reference to it
		MenuItem menuItem = menu.add(groupId, menuItemId, menuItemOrder, menuItemText);
		menuItem = menu.add(groupId, menuItemId++, menuItemOrder, menuItemText);
		// menuItem.setIcon(R.drawable.ic_action_refresh_white);
		menuItem.setShowAsAction(MenuItem.SHOW_AS_ACTION_ALWAYS);

		return true;
	}

	public boolean onOptionsItemSelected(MenuItem item)
	{
		super.onOptionsItemSelected(item);

		switch (item.getItemId())
		{
		case (MENU_ITEM_CLOSE):
			finish();
			return true;
		}
		return false;
	}

	@Override
	public ArvosTextView getTextView()
	{
		return mTextView;
	}
}
