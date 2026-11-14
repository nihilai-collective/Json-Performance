
----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1780.72 | 0.201764 | 120.733ms | 1691 | 160 | 534.198 | 905.625 | 0.764951 | 1.67316 | 1(Win) | true |
| Glaze | 1639.35 | 0.616023 | 127.77ms | 1691 | 4890 | 179575 | 983.722 | 0.943082 | 1.81381 | 2(Loss) | true |
| Jsonifier (two-stage) | 1457.23 | 0.418559 | 147.373ms | 1691 | 30 | 643.678 | 1106.67 | 1.19048 | 2.04766 | 3(Loss) | true |
| simdjson (ondemand) | 852.134 | 0.222861 | 220.898ms | 1691 | 40 | 711.538 | 1892.5 | 0.569177 | 3.52519 | 4(Loss) | true |
