
----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14501 | 0.147696 | 19.8184ms | 2632 | 320 | 20.9154 | 173.097 | 0.091988 | 0.145717 | 1(Win) | true |
| simdjson (reflection) | 9093.22 | 0.114669 | 29.731ms | 2632 | 320 | 32.0613 | 276.038 | 0.205617 | 0.246985 | 2(Loss) | true |
| Glaze | 4575.83 | 0.209887 | 58.1377ms | 2632 | 40 | 53.0231 | 548.55 | 0.0516247 | 0.51609 | 3(Loss) | true |
