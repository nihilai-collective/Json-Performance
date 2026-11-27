
----
### Marine IK Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3090.92 | 0.131192 | 7359.07ms | 1834197 | 320 | 1.76393e+08 | 565924 | 0.312053 | 1.66252 | 8.47922 | 1.6243 | 0.00624609 | 0.113164 | 3.28482e-06 | 1(Win) | true |
| simdjson (ondemand) | 2472.29 | 0.146101 | 9180.27ms | 1834197 | 320 | 3.4194e+08 | 707533 | 0.103293 | 2.07096 | 12.6836 | 2.27007 | 0.00335851 | 0.150411 | 3.37171e-06 | 2(Loss) | true |
