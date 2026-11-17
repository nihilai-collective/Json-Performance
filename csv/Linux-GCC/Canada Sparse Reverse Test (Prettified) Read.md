
----
### Canada Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8940.42 | 0.220181 | 7200.98ms | 5212421 | 80 | 1.19899e+08 | 556009 | 0.414866 | 0.566356 | 2.54445 | 0.309603 | 0.00225188 | 0.0590724 | 3.54202e-06 | 1(Win) | true |
| simdjson (ondemand) | 7826.32 | 0.0953822 | 8199.52ms | 5212421 | 320 | 1.17449e+08 | 635158 | 0.2085 | 0.649412 | 2.85498 | 0.331081 | 0.00218947 | 0.059067 | 8.04449e-06 | 2(Loss) | true |
