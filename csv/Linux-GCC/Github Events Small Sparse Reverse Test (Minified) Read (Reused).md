
----
### Github Events Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3314.62 | 0.0431638 | 760.229ms | 1691 | 2560 | 112.901 | 486.53 | 0.00746734 | 1.67887 | 6.5476 | 1.13897 | 0.000766235 | 2.44863e-05 | 2.31002e-07 | 1(Win) | true |
| simdjson (ondemand) | 2799.71 | 0.0547785 | 768.767ms | 1691 | 4890 | 486.844 | 576.01 | 0.0362741 | 1.96407 | 8.1573 | 1.37315 | 0.000610836 | 2.69682e-05 | 6.89322e-06 | 2(Loss) | true |
