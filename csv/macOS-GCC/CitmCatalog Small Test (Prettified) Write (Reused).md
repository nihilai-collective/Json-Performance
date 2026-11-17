
----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14217 | 3.01136 | 43.0351ms | 6938 | 1280 | 251414 | 465.4 | 2.42077 | 1(Win) | true |
| Glaze | 2284.88 | 0.594165 | 290.837ms | 6960 | 1280 | 381343 | 2905 | 1.71569 | 2(Loss) | true |
| simdjson (reflection) | 347.393 | 0.258271 | 2247.14ms | 6938 | 40 | 96791.6 | 19046.4 | 0.0896861 | 3(Loss) | true |
