
// Author: Pierce Brooks

package com.piercelbrooks.sfml.app;

import com.piercelbrooks.sfml.SFMLActivity;

public class MainActivity extends SFMLActivity {
    public MainActivity() {
        super();
    }

    private native String getBaseNativeClass();

    @Override
    protected String getNativeClass() {
        return getBaseNativeClass();
    }
}
