
----
### Instruments Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5004.98 | 0.0283548 | 4241.26ms | 183677 | 1280 | 126058 | 34998.8 | 0.0659923 | 1.02803 | 5.28637 | 0.868405 | 0.000746283 | 2.49249e-06 | 1.38235e-06 | 1(Win) | true |
| simdjson (ondemand) | 4216.19 | 0.0298913 | 4902.83ms | 183677 | 2560 | 394822 | 41546.6 | 0.00687904 | 1.21487 | 6.3194 | 0.953467 | 0.00194198 | 2.02461e-06 | 7.95384e-07 | 2(Loss) | true |
