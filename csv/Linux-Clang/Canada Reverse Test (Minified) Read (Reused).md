
----
### Canada Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 841.125 | 0.0779137 | 8538.17ms | 2090234 | 160 | 5.45527e+08 | 2.36992e+06 | 0.0884219 | 6.01255 | 29.7599 | 5.70275 | 0.0265772 | 0.130781 | 0.000712429 | 1(Win) | true |
| simdjson (ondemand) | 806.58 | 0.0949829 | 8889.74ms | 2090234 | 160 | 8.8167e+08 | 2.47143e+06 | 0.197443 | 6.28687 | 30.7474 | 5.32063 | 0.0218063 | 0.154514 | 0.00217513 | 2(Loss) | true |
