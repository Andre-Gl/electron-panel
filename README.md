# electron-panel
## About
Enables creating a browser window in Electron that behaves like a Panel.

Panels are typically used for auxillary windows and do not activate the application – as such they can appear ontop of other apps in the same way as Spotlight or 1Password, for example.

NOTE: Only MacOS implementation for now.

## Usage
Base Api is based on BrowserWindow.
```javascript
const { Panel } = require('electron-panel');
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

## BrowserWindow API extension
### show(animate: bool)
If true animates slide in and fade in the panel.
```javascript
win.show(true)
```
### close(animate: bool)
If true fades out the penal.
```javascript
win.close(true)
```
