
----
### Canada Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8485.21 | 0.0737836 | 7626.53ms | 5212421 | 640 | 1.19579e+08 | 585837 | 0.243454 | 0.59905 | 2.52179 | 0.32712 | 0.0021167 | 0.0590581 | 9.21237e-06 | 1(Win) | true |
| simdjson (ondemand) | 7992.08 | 0.294771 | 8044.12ms | 5212421 | 30 | 1.00844e+08 | 621985 | 0.752465 | 0.627693 | 2.77436 | 0.331073 | 0.00189232 | 0.0591685 | 1.70106e-06 | 2(Loss) | true |
