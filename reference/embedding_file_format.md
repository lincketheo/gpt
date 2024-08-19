# Embedding File Format 

The following is the format of an embedding file. It's a collection of tokens and float vectors representing them in R. Each field is packed tight.

```
<(int) num words>
<(int) dim>
<(int) strlen>
<(char*) str>
<(float[dim])array>
<(int) strlen>
<(char*) str>
<(float[dim])array>
...
```
