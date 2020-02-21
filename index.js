const { BrowserWindow } = require('electron');
const NativeExtension = require('bindings')('NativeExtension');

class Panel extends BrowserWindow {
  constructor(options) {
    super({ ...options, show: false });
    NativeExtension.MakePanel(this.getNativeWindowHandle());
    if (options.show) {
      this.show();
    }
  }

  show(animate) {
    if (animate) {
      NativeExtension.AnimatePanelEnter(this.getNativeWindowHandle());
    } else {
      NativeExtension.ShowPanel(this.getNativeWindowHandle());
    }
  }

  close(animate) {
    if (animate) {
      NativeExtension.AnimatePanelLeave(this.getNativeWindowHandle());
    } else {
      NativeExtension.DestroyPanel(this.getNativeWindowHandle());
    }
  }

  destroy() {
    NativeExtension.DestroyPanel(this.getNativeWindowHandle());
  }

  setBounds(bounds, animate) {
    // not supported
  }

  setPosition(x, y, animate) {
    // not supported
  }

  setSize(w, h, animate) {
    // not supported
  }
}

module.exports = {
  Panel,
};
