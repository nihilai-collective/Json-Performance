
----
### Github Events Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2196.79 | 0.320575 | 76.9879ms | 1691 | 40 | 221.528 | 734.1 | 0.0499228 | 1.08659 | 1(Win) | true |
| Glaze | 2007.42 | 0.0972336 | 84.5307ms | 1691 | 80 | 48.8127 | 803.35 | 0.0497667 | 1.19212 | 2(Loss) | true |
| simdjson (reflection) | 1758.9 | 0.0845186 | 94.6171ms | 1691 | 320 | 192.159 | 916.859 | 0.0508106 | 1.36534 | 3(Loss) | true |
| Jsonifier (two-stage) | 1589.61 | 0.195649 | 103.238ms | 1691 | 30 | 118.19 | 1014.5 | 0.260245 | 1.51648 | 4(Loss) | true |
| simdjson (ondemand) | 1295.08 | 0.0931081 | 132.414ms | 1691 | 320 | 430.148 | 1245.22 | 0.17321 | 1.87075 | 5(Loss) | true |
