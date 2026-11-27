
----
### Instruments Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3549.81 | 0.190555 | 841.764ms | 4669 | 640 | 3656.45 | 1254.35 | 0.125096 | 1.49582 | 7.02613 | 1.2538 | 0.00132456 | 1.20475e-05 | 1.33862e-06 | 1(Win) | true |
| simdjson (ondemand) | 2785.48 | 0.0463498 | 881.785ms | 4669 | 160 | 87.8346 | 1598.54 | 0.0442004 | 1.89538 | 9.20732 | 1.49025 | 0.00257282 | 9.37031e-06 | 1.33862e-06 | 2(Loss) | true |
