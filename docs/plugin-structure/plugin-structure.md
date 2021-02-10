## Plugin structure

First of all, I spent a lot of time writing meaningful log error and warning messages. When you are writing a skin, have a Rainmeter log window open. If you have made some mistake with syntax, there is a good chance that log will have a message about it. It's very helpful.

Plugin doesn't have a fixed set of possible ways to calculate some values. Instead, it acts somewhat like a DSP-utility and provides you a set of building blocks called '[sound handlers]()' as we saw [earlier](/docs/skin-setup.md) that may be combined in any amount into any tree-like graph.

This plugin follows Parent Child paradigm.

### First, the Parent

The Parent measure is the data provider, it processes the audio and returns a value to be grabbed by Child measures. This value differs based on the [handler type]() choosen to process the audio.<br/>

### Second, the Child

The Child measure is the data retriever, it grabs the processed data from Parent measure and returns a value to be used in your skin.<br/>
Child measure can also provide other useful informations like audio devices. These informations are grabbed from Parent measure as well.

### How to determine the measure Type?

Parent measures are distinguished from Child measures by Type option, which must be either Parent or Child.

```ini
Type=Parent
```

Or

```ini
Type=Child
```

## Automatic reconfiguring

If you want your skin to react to audio device properties, this plugin provides you with some information.
For example, there is a plugin [section variable]() "device list output" that will give you a list of available audio devices, that you can parse with a Lua script, and then somehow show user a list of devices to choose from. Of there is a "current device, channels" section variable that will give you a list of available audio channels.
