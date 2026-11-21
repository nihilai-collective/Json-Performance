
----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1650.26 | 0.203353 | 233.024ms | 3370 | 160 | 2509.43 | 1947.5 | 0 | 1.48151 | 1(Win) | true |
| simdjson (ondemand) | 1610.42 | 0.263518 | 227.745ms | 3370 | 4890 | 135242 | 1995.69 | 0.00286189 | 1.51698 | 2(Loss) | true |
| Jsonifier (two-stage) | 1581.85 | 0.266906 | 243.576ms | 3370 | 640 | 18820.2 | 2031.72 | 0.0384379 | 1.54394 | 3(Loss) | true |
| Jsonifier | 1453.22 | 0.0833935 | 265.762ms | 3370 | 320 | 1088.46 | 2211.56 | 0.408106 | 1.68276 | 4(Loss) | true |
