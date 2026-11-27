
----
### Twitter Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4242.9 | 0.258088 | 783.607ms | 2821 | 640 | 1713.94 | 634.075 | 0.164339 | 1.2736 | 5.24566 | 0.867069 | 0.00141904 | 3.10174e-05 | 8.30822e-06 | 1(Win) | true |
| simdjson (ondemand) | 3683.57 | 0.0648784 | 792.364ms | 2821 | 640 | 143.697 | 730.355 | 0.195796 | 1.47804 | 6.25629 | 0.901453 | 0.000851316 | 3.37868e-05 | 1.71703e-05 | 2(Loss) | true |
