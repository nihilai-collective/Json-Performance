
----
### Github Events Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1523.1 | 0.0838481 | 858.875ms | 2158 | 4890 | 6276.85 | 1351.21 | 0.0589749 | 3.47893 | 12.1209 | 2.32577 | 0.000468794 | 0.000163751 | 4.74764e-05 | 1(Win) | true |
| simdjson (ondemand) | 1502.24 | 0.112281 | 860.341ms | 2158 | 80 | 189.291 | 1369.97 | 0.0748749 | 3.53145 | 13.3346 | 2.27016 | 0.000926784 | 6.95088e-05 | 0 | 2(Loss) | true |
