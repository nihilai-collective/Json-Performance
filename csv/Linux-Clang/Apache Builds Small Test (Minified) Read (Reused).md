
----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3002.6 | 0.122272 | 92.4263ms | 2632 | 30 | 31.3437 | 835.967 | 0.12776 | 0.799468 | 1(Win) | true |
| Jsonifier (two-stage) | 2981.88 | 0.103625 | 94.618ms | 2632 | 40 | 30.4353 | 841.775 | 0.373797 | 0.805528 | 2(Loss) | true |
| Glaze | 2357.15 | 0.227318 | 112.321ms | 2632 | 640 | 3750.12 | 1064.88 | 0.71732 | 1.02349 | 3(Loss) | true |
| simdjson (ondemand) | 1723.96 | 0.0933903 | 155.254ms | 2632 | 160 | 295.83 | 1455.99 | 0.06572 | 1.40973 | 4(Loss) | true |
