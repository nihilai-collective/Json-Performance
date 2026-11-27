
----
### Twitter Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7300.26 | 0.0836251 | 4314.03ms | 264040 | 80 | 66561.8 | 34493 | 0.144892 | 0.693006 | 3.34709 | 0.464407 | 0.00125322 | 2.51382e-05 | 2.18243e-05 | 1(Win) | true |
| simdjson (ondemand) | 6336.19 | 0.0703475 | 4793.56ms | 264040 | 160 | 125055 | 39741.3 | 0.0118251 | 0.798025 | 3.80157 | 0.41635 | 0.00100515 | 3.71629e-06 | 2.69845e-06 | 2(Loss) | true |
