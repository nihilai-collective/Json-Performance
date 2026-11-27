
----
### Discord Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2294.74 | 0.0556026 | 3107.57ms | 56369 | 2560 | 434356 | 23426.5 | 0.0158666 | 2.21147 | 10.0055 | 1.77549 | 0.00428419 | 3.81069e-05 | 2.48571e-05 | 1(Win) | true |
| simdjson (ondemand) | 2142.51 | 0.0705149 | 3245.76ms | 56369 | 320 | 100172 | 25091 | 0.144638 | 2.3592 | 10.4228 | 1.69842 | 0.00412938 | 1.9736e-05 | 1.22519e-05 | 2(Loss) | true |
