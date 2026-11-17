
----
### Github Events Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3397.87 | 0.0562708 | 763.418ms | 1691 | 4890 | 348.779 | 474.611 | 0.0578904 | 1.64308 | 6.54761 | 1.13897 | 0.000761641 | 3.41033e-05 | 3.02334e-06 | 1(Win) | true |
| simdjson (ondemand) | 2863.08 | 0.184636 | 769.436ms | 1691 | 80 | 86.5252 | 563.263 | 0.214801 | 1.92839 | 8.16026 | 1.37374 | 0.000643111 | 1.47842e-05 | 0 | 2(Loss) | true |
