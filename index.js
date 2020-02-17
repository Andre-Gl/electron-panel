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

  show() {
    NativeExtension.ShowPanel(this.getNativeWindowHandle());
  }

  close() {
    NativeExtension.DestroyPanel(this.getNativeWindowHandle());
  }

  destroy() {
    NativeExtension.DestroyPanel(this.getNativeWindowHandle());
  }

  animatePanelEnter() {
    NativeExtension.AnimatePanelEnter(this.getNativeWindowHandle());
  }

  animatePanelLeaveAndClose() {
    NativeExtension.AnimatePanelLeave(this.getNativeWindowHandle());
  }
}

module.exports = {
  Panel,
};
