# Electron

## Basics

- Electrons main process is a nodejs process controlled by electron framework.
- The Windows created by electron are chromium windows that are created and controlled by electron framework in the background.
- So when electron is downloaded and bundled into an application the chromium browser also gets bundled with the app.

## Processes in Electron

### Main process (Node JS)

The main process contains -

- Create Window/Interact with electron.
- System APIs
- Node Modules like fs, os and any other that can be installed as packages.
- 
