
----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2440.18 | 0.0563746 | 1716.42ms | 25388 | 640 | 20024.4 | 9922.17 | 0.0123918 | 2.11793 | 9.32047 | 1.6961 | 0.00333782 | 3.68653e-05 | 2.32639e-05 | 1(Win) | true |
| simdjson (ondemand) | 2136.27 | 0.0428422 | 1855.05ms | 25388 | 1280 | 30178.6 | 11333.7 | 0.00574921 | 2.41842 | 10.2585 | 1.70147 | 0.00391056 | 2.71413e-05 | 1.4063e-05 | 2(Loss) | true |
