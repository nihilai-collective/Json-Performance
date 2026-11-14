
----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2275.12 | 0.088668 | 1186.17ms | 9739 | 640 | 8385.56 | 4082.34 | 0.012629 | 2.24407 | 9.56347 | 1.66958 | 0.00131527 | 3.04831e-05 | 1.12306e-05 | 1(Win) | true |
| simdjson (ondemand) | 2264.53 | 0.0408569 | 1178.7ms | 9739 | 4890 | 13731.3 | 4101.44 | 0.0949151 | 2.24784 | 9.50539 | 1.46274 | 0.00193122 | 4.34447e-05 | 2.34127e-05 | 2(Loss) | true |
