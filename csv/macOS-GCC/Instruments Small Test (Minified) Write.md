
----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14023.7 | 2.13506 | 34.2321ms | 4669 | 4890 | 224727 | 317.513 | 0.130335 | 1(Win) | true |
| simdjson (reflection) | 7672.17 | 1.2981 | 60.418ms | 4669 | 4890 | 277549 | 580.371 | 1.41475 | 2(Loss) | true |
| Glaze | 1910.7 | 0.429469 | 236.85ms | 4669 | 2560 | 256427 | 2330.4 | 0.0514668 | 3(Loss) | true |
