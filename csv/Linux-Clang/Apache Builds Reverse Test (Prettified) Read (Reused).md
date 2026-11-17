
----
### Apache Builds Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1841.62 | 0.0234408 | 8382.44ms | 124597 | 1280 | 292800 | 64522 | 0.159653 | 2.74665 | 13.6215 | 2.63298 | 0.00555587 | 1.05089e-05 | 5.90654e-06 | 1(Win) | true |
| simdjson (ondemand) | 1078.95 | 0.0561709 | 6630.73ms | 124597 | 320 | 1.22457e+06 | 110130 | 0.0208971 | 4.69815 | 23.7634 | 4.66178 | 0.00858849 | 4.81553e-06 | 1.32929e-06 | 2(Loss) | true |
