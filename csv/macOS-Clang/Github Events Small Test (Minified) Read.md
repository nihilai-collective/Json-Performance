
----
### Github Events Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1549.93 | 0.0821786 | 106.454ms | 1691 | 320 | 233.956 | 1040.48 | 0.538601 | 1(Win) | true |
| Glaze | 1375.27 | 0.0865463 | 120.311ms | 1691 | 4890 | 5036.35 | 1172.61 | 0.298168 | 2(Loss) | true |
| Jsonifier (two-stage) | 1363.17 | 0.196909 | 120.046ms | 1691 | 2560 | 13891.8 | 1183.03 | 0.507457 | 3(Loss) | true |
| simdjson (ondemand) | 1000.72 | 0.283741 | 197.978ms | 1691 | 40 | 836.308 | 1611.5 | 0.405834 | 4(Loss) | true |
