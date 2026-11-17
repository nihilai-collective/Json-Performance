
----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 1107.47 | 0.0648298 | 1151.97ms | 9578 | 40 | 1143.65 | 8247.88 | 0.210821 | 1(Win) | true |
| Jsonifier (generic) | 801.373 | 0.17565 | 1452.32ms | 9578 | 4890 | 1.96014e+06 | 11398.3 | 1.58893 | 2(Loss) | true |
