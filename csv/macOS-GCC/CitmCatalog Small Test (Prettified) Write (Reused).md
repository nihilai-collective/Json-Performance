
----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 17988.5 | 1.92237 | 40.7831ms | 6938 | 4890 | 244490 | 367.823 | 0.388459 | 1(Win) | true |
| Glaze | 2879.19 | 0.316343 | 234.007ms | 6960 | 4890 | 260078 | 2305.36 | 0.386244 | 2(Loss) | true |
| simdjson (reflection) | 343.902 | 0.0766235 | 2016.4ms | 6938 | 4890 | 1.06276e+06 | 19239.8 | 0.518729 | 3(Loss) | true |
