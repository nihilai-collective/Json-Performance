
----
### Canada Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5337.68 | 0.0463911 | 795.275ms | 4630 | 2560 | 377.021 | 827.234 | 0.0468648 | 1.01 | 5.09482 | 0.800864 | 0.000648539 | 1.99109e-05 | 2.69978e-06 | 1(Win) | true |
| simdjson (ondemand) | 4154.07 | 0.11978 | 816.861ms | 4630 | 320 | 518.723 | 1062.94 | 0.00411578 | 1.28644 | 5.58553 | 0.820086 | 0.000647948 | 1.2824e-05 | 1.34989e-06 | 2(Loss) | true |
