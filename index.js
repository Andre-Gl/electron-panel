const { BrowserWindow } = require('electron');
const NativeExtension = require('bindings')('NativeExtension');

// Only darwin supported for now
var isDarwin = process.platform === "darwin";

class Panel extends BrowserWindow {
  constructor(options) {
    super({ ...options, show: false });
    NativeExtension.MakePanel(this.getNativeWindowHandle());
    if (options.show) {
      this.show();
    }
  }

  show(animate) {
    NativeExtension.ShowPanel(this.getNativeWindowHandle(), animate);
  }

  close(animate) {
    NativeExtension.ClosePanel(this.getNativeWindowHandle(), animate);
  }

  destroy() {
    NativeExtension.ClosePanel(this.getNativeWindowHandle(), false);
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
  Panel: isDarwin ? Panel : BrowserWindow,
};
