
----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12123.8 | 2.42844 | 44.6892ms | 5094 | 2560 | 242401 | 400.7 | 2.88415 | 1(Win) | true |
| simdjson (reflection) | 8673.31 | 1.2754 | 58.562ms | 5094 | 4890 | 249547 | 560.111 | 1.47559 | 2(Loss) | true |
| Glaze | 1949.08 | 0.326547 | 247.776ms | 5094 | 4890 | 323936 | 2492.47 | 1.05334 | 3(Loss) | true |
