
----
### Marine IK Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2662.98 | 0.0547318 | 880.449ms | 4604 | 40 | 32.5744 | 1648.8 | 0.00202171 | 1.98102 | 9.34687 | 1.65595 | 0.00091768 | 8.6881e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2076.51 | 0.115106 | 930.895ms | 4604 | 640 | 3791.21 | 2114.47 | 0.0897027 | 2.52623 | 13.1857 | 2.33536 | 0.00111554 | 6.78758e-06 | 6.78758e-07 | 2(Loss) | true |
