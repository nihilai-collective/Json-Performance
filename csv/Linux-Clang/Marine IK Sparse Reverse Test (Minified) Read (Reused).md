
----
### Marine IK Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3328.67 | 0.709223 | 6759.61ms | 1834197 | 40 | 5.55617e+08 | 525503 | 0.25958 | 1.54556 | 8.73462 | 1.53929 | 0.00258692 | 0.113125 | 8.17797e-07 | 1(Win) | true |
| simdjson (ondemand) | 2487.39 | 0.125746 | 9259.32ms | 1834197 | 30 | 2.34592e+07 | 703236 | 0.19612 | 2.06172 | 12.6413 | 2.27007 | 0.00339089 | 0.150648 | 2.83503e-06 | 2(Loss) | true |
