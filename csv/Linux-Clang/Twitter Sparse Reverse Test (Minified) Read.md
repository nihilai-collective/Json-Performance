
----
### Twitter Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4979.97 | 0.0304921 | 5792.22ms | 264040 | 2560 | 608554 | 50564.2 | 0.0549759 | 1.02445 | 5.31374 | 0.863506 | 0.00133077 | 5.84369e-06 | 3.5506e-06 | 1(Win) | true |
| simdjson (ondemand) | 3917.58 | 0.0929437 | 7206.03ms | 264040 | 160 | 571037 | 64276.5 | 0.0192856 | 1.30187 | 6.37773 | 0.936307 | 0.00274904 | 3.29022e-06 | 1.91732e-06 | 2(Loss) | true |
