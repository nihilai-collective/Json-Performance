
----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15935.9 | 4.71396 | 44.7109ms | 6938 | 640 | 245170 | 415.2 | 0.581395 | 1(Win) | true |
| Glaze | 2446.94 | 0.439327 | 282.294ms | 6960 | 2560 | 363569 | 2712.6 | 0.579094 | 2(Loss) | true |
| simdjson (reflection) | 323.886 | 0.502056 | 2126.74ms | 6938 | 40 | 420775 | 20428.8 | 0.0417537 | 3(Loss) | true |
