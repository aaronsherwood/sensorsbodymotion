SuperDirt.start

//https://tidalcycles.org/index.php/SuperDirt_MIDI_Tutorial

MIDIClient.init;

// if on a mac you'll have to enable IAC bus in AudioMidi Setup
// if on windows you'll have to choose your own from the list and put in below
~midiOut = MIDIOut.newByName("IAC Driver", "Bus 1");

~dirt.soundLibrary.addMIDI(\midi, ~midiOut);

~midiOut.latency = 0.83;