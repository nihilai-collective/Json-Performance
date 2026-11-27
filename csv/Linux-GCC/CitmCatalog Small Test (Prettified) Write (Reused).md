
----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16799.2 | 0.208828 | 41.8486ms | 6938 | 80 | 54.1201 | 393.863 | 0.502084 | 0.137648 | 1(Win) | true |
| Glaze | 4583.41 | 0.0831481 | 171.589ms | 6960 | 80 | 115.994 | 1448.17 | 0.229073 | 0.530442 | 2(Loss) | true |
| simdjson (reflection) | 553.982 | 0.134768 | 1204.95ms | 6938 | 2560 | 663269 | 11943.7 | 0.662093 | 4.45905 | 3(Loss) | true |
