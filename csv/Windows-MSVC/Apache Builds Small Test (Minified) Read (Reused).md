
----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1390.14 | 0.191743 | 232.831ms | 2632 | 160 | 1917.85 | 1805.62 | 0.103734 | 1.75461 | 1(Win) | true |
| Jsonifier | 1364.17 | 0.426339 | 233.063ms | 2632 | 40 | 2461.54 | 1840 | 0.719424 | 1.80154 | 2(Loss) | true |
| Jsonifier (two-stage) | 1274.96 | 0.186712 | 242.292ms | 2632 | 160 | 2161.95 | 1968.75 | 0.0634518 | 1.9151 | 3(Loss) | true |
| simdjson (ondemand) | 1188.37 | 0.0940077 | 253.021ms | 2632 | 320 | 1261.66 | 2112.19 | 0.162482 | 2.06216 | 4(Loss) | true |
