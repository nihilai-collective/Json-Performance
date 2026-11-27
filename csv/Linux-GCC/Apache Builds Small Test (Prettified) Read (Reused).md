
----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2890.18 | 0.208796 | 123.871ms | 3370 | 30 | 161.724 | 1112 | 0.0329628 | 0.836528 | 1(Win) | true |
| Jsonifier (two-stage) | 2646.13 | 0.0296127 | 133.254ms | 3370 | 320 | 41.3946 | 1214.56 | 0.256379 | 0.914724 | 2(Loss) | true |
| simdjson (reflection) | 2513.4 | 0.154288 | 139.082ms | 3370 | 320 | 1245.51 | 1278.7 | 0.965031 | 0.964152 | 3(Loss) | true |
| simdjson (ondemand) | 2449.67 | 0.239936 | 142.959ms | 3370 | 30 | 297.275 | 1311.97 | 0.154744 | 0.989565 | 4(Loss) | true |
| Glaze | 2315.27 | 0.633854 | 150.047ms | 3370 | 640 | 49546.6 | 1388.12 | 0.273115 | 1.04874 | 5(Loss) | true |
