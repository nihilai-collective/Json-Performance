
----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3390.33 | 0.0409353 | 108.466ms | 3370 | 320 | 48.1862 | 947.956 | 0.167843 | 0.710333 | 1(Win) | true |
| Glaze | 2539.16 | 0.112196 | 136.237ms | 3370 | 40 | 80.666 | 1265.72 | 0.00855826 | 0.954933 | 2(Loss) | true |
| Jsonifier | 2399.76 | 0.0844927 | 145.622ms | 3370 | 40 | 51.2179 | 1339.25 | 0.0311023 | 1.01009 | 3(Loss) | true |
| simdjson (ondemand) | 2095.05 | 0.2274 | 200.719ms | 3370 | 30 | 365.068 | 1534.03 | 0.0434773 | 1.16113 | 4(Loss) | true |
