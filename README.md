# electron-panel
## About
Enables creating a browser window in Electron that behaves like a Panel.

Panels are typically used for auxillary windows and do not activate the application – as such they can appear ontop of other apps in the same way as Spotlight or 1Password, for example.

NOTE: Only MacOS implementation for now.

## Usage
Base Api is based on BrowserWindow.
```javascript
const win = new Panel({
  center: true,
  width: 320,
  height: 240,
  minHeight: 100,
  minWidth: 100,
  show: false,
  webPreferences: {
    preload: `${__dirname}/preload.js`,
  },
});
win.loadURL(`file://${__dirname}/index.html`);
win.on('ready-to-show', () => {
  win.show();
});
...
win.close();
```

## Additional Api
### animatePanelEnter
Animate slide in and fade in the panel.
```javascript
win.animatePanelEnter()
```
### animatePanelLeaveAndClose
Fade out the penal.
```javascript
win.animatePanelLeaveAndClose()
```