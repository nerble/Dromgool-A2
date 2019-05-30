
# Noisifier
<img src="https://github.com/nerble/Dromgool-A2/blob/master/markdown-files/noisifier.png" 
alt="Noisifier VST"/>

Noisifier is a simple, freeware, open-source VST3 audio plugin developed in C++ using the [JUCE](https://juce.com/) framework.  It provides an easy way to transform (read: obliterate) audio signals using single-slider controls for  (chained) ring modulation, bit crushing, and foldback distortion effects.

## Key features

* Ring modulator (0-9000Hz)
* Bit crusher (16- to 1-bit)
* Fold back distortion with gain compensation
* Wet/Dry ("FRANKER/DANKER") slider mix control
* Resizeable GUI
* DAW Automation and state-saving implemented

## Installation and usage

For Macs, you can just use the pre-built package installer [here](https://github.com/nerble/Dromgool-A2/blob/master/Noisifier/build/Noisifier.pkg).

If you want to compile from source, create a non-VST3 or standalone version, or compile for other platforms, grab the source files from the [Source folder](https://github.com/nerble/Dromgool-A2/tree/master/Source), install [JUCE](https://juce.com/) for your OS and follow the usual build steps for your OS/architecture and IDE.

## Media

Brief video demonstration of plugin

<a href="https://www.youtube.com/watch?v=at6CPTo6ZLU
" target="_blank"><img src="https://img.youtube.com/vi/at6CPTo6ZLU/sddefault.jpg" 
alt="Brief video demonstration of plugin" /></a>

<br/>
Example audio for ring modulation effect

<a href="https://github.com/nerble/Dromgool-A2/blob/master/markdown-files/ringmod_demo.wav
" target="_blank"><img src="https://github.com/nerble/Dromgool-A2/blob/master/markdown-files/audio_widget.png" 
alt="Example audio for ring modulation effect" width="300"/></a>

<br/>
Example audio for bit crusher effect

<a href="https://github.com/nerble/Dromgool-A2/blob/master/markdown-files/bitcrusher%20demo.wav
" target="_blank"><img src="https://github.com/nerble/Dromgool-A2/blob/master/markdown-files/audio_widget.png" 
alt="Example audio for ring modulation effect" width="300"/></a>

<br/>
Example audio for fold back distortion effect

<a href="https://github.com/nerble/Dromgool-A2/blob/master/markdown-files/foldback%20demo.wav
" target="_blank"><img src="https://github.com/nerble/Dromgool-A2/blob/master/markdown-files/audio_widget.png" 
alt="Example audio for ring modulation effect" width="300"/></a>


## References

1. [JUCE](https://juce.com/). 
2. Bitcrusher algorithm based on [moc.noicratse@ajelak](mailto:moc.noicratse@ajelak)'s 'fractional-bit-depth decimation' code [here](https://www.musicdsp.org/en/latest/Effects/124-decimator.html?highlight=decimator#comments).
3. Fold back distortion algorithm based on [ed.bpu@eriflleh](mailto:ed.bpu@eriflleh)'s code [here](https://www.musicdsp.org/en/latest/Effects/203-fold-back-distortion.html).

## Contributing
At this early point of development, feature-based pull requests are discouraged (though bug-fixes or DSP efficiency upgrades are definitely welcome!)


## Further reading

If you're interested in learning how to develop audio VSTs in C++ using the JUCE framework (and you should be!) I would strongly recommend the following resources:

* TheChernoProject's [C++ tutorial series](https://www.youtube.com/watch?v=18c3MTX0PK0&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb) on YouTube.

* Juce.com's [tutorials](https://juce.com/learn/tutorials).

* The Audio Programmer's [JUCE framework tutorial series](https://www.youtube.com/watch?v=7n16Yw51xkI&list=PLLgJJsrdwhPxa6-02-CeHW8ocwSwl2jnu) on YouTube.

## License
[MIT](https://choosealicense.com/licenses/mit/)
