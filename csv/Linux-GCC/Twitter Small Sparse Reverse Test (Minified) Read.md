
----
### Twitter Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3978.9 | 0.123239 | 784.929ms | 2821 | 2560 | 1777.53 | 676.145 | 0.00756875 | 1.36807 | 5.50585 | 0.877349 | 0.000902135 | 3.65562e-05 | 1.08007e-05 | 1(Win) | true |
| simdjson (ondemand) | 3475.97 | 0.0582687 | 794.04ms | 2821 | 320 | 65.084 | 773.975 | 0.166626 | 1.55998 | 6.26693 | 0.917405 | 0.00076768 | 2.43708e-05 | 0 | 2(Loss) | true |
