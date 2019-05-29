Clear description of what your audio plugin
• Key features
• Demo screenshot of GUI
• Simple install/usage instructions
• Links to media assets such as video, or audio
• Appropriate referencing for DSP techniques and algorithms
• Links to further reading 

# Noisifier
![screenshot](https://github.com/nerble/Dromgool-A2/blob/master/markdown-files/noisifier.png)

Noisifier is a simple, freeware, open-source VST3 audio plugin developed in C++ using the [JUCE](https://juce.com/) framework.  It provides an easy way to transform audio signals using single-slider controls for ring modulation, bit crushing, and foldback distortion.

## Key features

* Ring modulator (0-9000Hz)
* Bit crusher (16- to 1-bit)
* Fold back distortion with gain compensation
* Wet/Dry ("FRANKER/DANKER") slider mix control
* Resizeable GUI
* DAW Automation and state-saving implemented

## Installation and usage

Use the package manager [pip](https://pip.pypa.io/en/stable/) to install foobar.

```bash
pip install foobar
```

## Media

```python
import foobar

foobar.pluralize('word') # returns 'words'
foobar.pluralize('goose') # returns 'geese'
foobar.singularize('phenomena') # returns 'phenomenon'
```

## References

1. [JUCE](https://juce.com/). 
2. Bitcrusher algorithm based on [moc.noicratse@ajelak](mailto:moc.noicratse@ajelak)'s 'fractional-bit-depth decimation' code [here](https://www.musicdsp.org/en/latest/Effects/124-decimator.html?highlight=decimator#comments).
3. Fold back distortion algorithm based on [ed.bpu@eriflleh](mailto:ed.bpu@eriflleh)'s code [here](https://www.musicdsp.org/en/latest/Effects/203-fold-back-distortion.html).

## Contributing
At this early point of development, feature-based pull requests are discouraged (though bug-fixes or DSP efficiency upgrades are definitely welcome). 


## Further reading

## License
[MIT](https://choosealicense.com/licenses/mit/)
