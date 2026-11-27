
----
### Apache Builds Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2037.08 | 0.120894 | 6664.82ms | 124597 | 40 | 198913 | 58330.9 | 0.0201682 | 2.52772 | 11.2751 | 2.14485 | 0.00697729 | 1.32427e-05 | 7.82523e-06 | 1(Win) | true |
| simdjson (ondemand) | 1642.13 | 0.0799256 | 7964.64ms | 124597 | 160 | 535171 | 72360.2 | 0.0405445 | 3.0943 | 12.3801 | 2.37419 | 0.00945137 | 5.06633e-06 | 2.30744e-06 | 2(Loss) | true |
