
----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2346.83 | 0.14121 | 294.109ms | 5839 | 2560 | 28740.1 | 2372.78 | 0.0943741 | 1(Win) | true |
| Jsonifier (two-stage) | 2234.8 | 0.122296 | 316.876ms | 5839 | 40 | 371.435 | 2491.72 | 0.0538159 | 2(Loss) | true |
| Glaze | 1603.39 | 0.140018 | 409.768ms | 5839 | 80 | 1891.73 | 3472.96 | 0.0579141 | 3(Loss) | true |
| simdjson (ondemand) | 1511.85 | 0.26879 | 418.428ms | 5839 | 30 | 2940.39 | 3683.23 | 0.110532 | 4(Loss) | true |
