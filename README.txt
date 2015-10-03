This is a wrapper around the button code found here: https://www.arduino.cc/en/Tutorial/Debounce.

It makes it easy to manage multiple buttons at a time.  You simply register a callback for each button in your project,
and when you read the button your callback will be called if its state has changed.
