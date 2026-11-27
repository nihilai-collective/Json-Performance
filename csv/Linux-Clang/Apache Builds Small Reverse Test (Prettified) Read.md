
----
### Apache Builds Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1595.2 | 0.115371 | 920.715ms | 3370 | 1280 | 6915.64 | 2014.72 | 0.121092 | 3.2921 | 13.278 | 2.59881 | 0.00330513 | 8.27615e-05 | 3.61647e-05 | 1(Win) | true |
| simdjson (ondemand) | 921.814 | 0.0700485 | 1071.07ms | 3370 | 160 | 954.314 | 3486.47 | 0.0459127 | 5.65552 | 24.0774 | 4.55935 | 0.00995734 | 2.59644e-05 | 3.7092e-06 | 2(Loss) | true |
