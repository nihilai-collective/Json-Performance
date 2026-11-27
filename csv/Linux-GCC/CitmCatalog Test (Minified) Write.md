
----
### CitmCatalog Test (Minified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 9513.09 | 0.297753 | 5037.34ms | 500299 | 160 | 3.56819e+06 | 50154.3 | 0.33352 | 0.260094 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 9490.25 | 0.105922 | 5099.85ms | 500299 | 1280 | 3.62986e+06 | 50275 | 0.00832539 | 0.260724 | 1(Tie) | true |
| Glaze | 3715.75 | 0.288595 | 6842.08ms | 500299 | 30 | 4.11969e+06 | 128405 | 0.0168968 | 0.666108 | 3(Loss) | true |
