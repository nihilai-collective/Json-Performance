
----
### Discord Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2537.4 | 0.122907 | 3865.73ms | 83958 | 160 | 240668 | 31555.4 | 0.176796 | 2.02157 | 9.36803 | 1.71623 | 0.0029782 | 3.32011e-05 | 2.87346e-05 | 1(Win) | true |
| simdjson (ondemand) | 1910.43 | 0.0405646 | 4918.82ms | 83958 | 1280 | 369971 | 41911.3 | 0.00771778 | 2.68472 | 11.504 | 1.99609 | 0.00846822 | 8.19792e-06 | 3.0149e-06 | 2(Loss) | true |
