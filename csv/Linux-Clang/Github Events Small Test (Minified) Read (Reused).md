
----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3069.21 | 0.19755 | 61.0385ms | 1691 | 30 | 32.323 | 525.433 | 0.114322 | 0.765622 | 1(Win) | true |
| Jsonifier (two-stage) | 2916.25 | 0.0921364 | 63.3411ms | 1691 | 640 | 166.142 | 552.992 | 0.0873854 | 0.809513 | 2(Loss) | true |
| Glaze | 2346.83 | 0.153198 | 76.8358ms | 1691 | 30 | 33.2471 | 687.167 | 0.00970261 | 1.01315 | 3(Loss) | true |
| simdjson (ondemand) | 1717.29 | 0.210516 | 101.955ms | 1691 | 80 | 312.653 | 939.075 | 0.410944 | 1.39969 | 4(Loss) | true |
