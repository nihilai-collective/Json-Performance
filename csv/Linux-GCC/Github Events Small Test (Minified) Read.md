
----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1839.73 | 0.0759461 | 92.7837ms | 1691 | 640 | 283.641 | 876.575 | 0.232609 | 1.30116 | 1(Win) | true |
| simdjson (reflection) | 1769.63 | 0.165806 | 94.1714ms | 1691 | 30 | 68.4931 | 911.3 | 0.222628 | 1.35407 | 2(Loss) | true |
| Jsonifier (two-stage) | 1589.04 | 0.191541 | 104.885ms | 1691 | 30 | 113.361 | 1014.87 | 0.131208 | 1.51549 | 3(Loss) | true |
| Glaze | 1521.68 | 0.0258851 | 118.97ms | 1691 | 640 | 48.1636 | 1059.79 | 0.113543 | 1.58473 | 4(Loss) | true |
| simdjson (ondemand) | 1409.39 | 0.102144 | 127.465ms | 1691 | 320 | 437.125 | 1144.23 | 0.364632 | 1.71732 | 5(Loss) | true |
