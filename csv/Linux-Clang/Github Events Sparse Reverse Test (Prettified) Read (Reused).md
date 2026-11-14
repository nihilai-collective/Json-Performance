
----
### Github Events Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6313.22 | 0.0345641 | 1724.39ms | 65103 | 2560 | 29579.5 | 9834.46 | 0.0375376 | 0.816936 | 3.81883 | 0.57598 | 0.00128611 | 4.51208e-06 | 1.32002e-06 | 1(Win) | true |
| simdjson (ondemand) | 4929.89 | 0.0372419 | 1998.15ms | 65103 | 320 | 7039.5 | 12594 | 0.00424327 | 1.04816 | 4.94298 | 0.75806 | 0.00188264 | 2.44804e-06 | 2.88005e-07 | 2(Loss) | true |
