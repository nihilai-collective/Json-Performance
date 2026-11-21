
----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3202.01 | 0.062124 | 103.919ms | 3370 | 160 | 62.2088 | 1003.71 | 0.106367 | 0.75275 | 1(Win) | true |
| Glaze | 2318.97 | 0.251658 | 140.714ms | 3370 | 4890 | 59484 | 1385.91 | 0.0672647 | 1.04756 | 2(Loss) | true |
| Jsonifier | 2266.65 | 0.088088 | 144.662ms | 3370 | 40 | 62.4 | 1417.9 | 0.00470201 | 1.072 | 3(Loss) | true |
| simdjson (ondemand) | 1908.14 | 0.161414 | 172.213ms | 3370 | 40 | 295.651 | 1684.3 | 0.0751478 | 1.27684 | 4(Loss) | true |
