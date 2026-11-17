
----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13346.1 | 1.76905 | 51.605ms | 6938 | 4890 | 376143 | 495.771 | 1.98281 | 1(Win) | true |
| Glaze | 2487.1 | 1.44725 | 309.903ms | 6960 | 160 | 238691 | 2668.8 | 0.239234 | 2(Loss) | true |
| simdjson (reflection) | 278.823 | 0.787739 | 2235.66ms | 6938 | 320 | 1.11821e+07 | 23730.4 | 0.433002 | 3(Loss) | true |
