package com.arvos.arviewer.viewer.opengl;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import com.arvos.arviewer.GL2JNILib;

import android.content.res.AssetManager;
import android.opengl.GLSurfaceView;
import android.view.Surface;

class GL2JNIRenderer implements GLSurfaceView.Renderer
{
	private GLSurfaceView mView;
	private AssetManager mAssetManager;
	private String mExternalFilesDir;
	private Surface mSurface;

	public GL2JNIRenderer(GLSurfaceView view, String externalFilesDir)
	{
		super();
		mView = view;
		mExternalFilesDir = externalFilesDir;
	}

	public void onDrawFrame(GL10 gl)
	{
		GL2JNILib.step();
	}

	public void onSurfaceChanged(GL10 gl, int width, int height)
	{
		if (mAssetManager == null)
		{
			mAssetManager = mView.getResources().getAssets();
		}
		mSurface = mView.getHolder().getSurface();
		
		GL2JNILib.init(width, height, mAssetManager, mExternalFilesDir, mSurface);
	}

	public void onSurfaceCreated(GL10 gl, EGLConfig config)
	{
		// Do nothing.
	}
}