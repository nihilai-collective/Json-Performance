
----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17493.6 | 0.0730522 | 22.4028ms | 3643 | 1280 | 26.9423 | 198.6 | 0.0779497 | 0.122287 | 1(Win) | true |
| Glaze | 4265.45 | 0.0907657 | 84.696ms | 3682 | 40 | 22.3327 | 823.225 | 0.00101227 | 0.562371 | 2(Loss) | true |
| simdjson (reflection) | 570.101 | 0.069155 | 621.38ms | 3643 | 30 | 532.823 | 6094.07 | 0.0870455 | 4.32357 | 3(Loss) | true |
