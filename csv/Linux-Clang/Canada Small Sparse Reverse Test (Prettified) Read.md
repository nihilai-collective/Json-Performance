
----
### Canada Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10181.3 | 0.0426365 | 829.043ms | 11579 | 40 | 8.55385 | 1084.6 | 0.0737055 | 0.527021 | 2.69635 | 0.36048 | 0.000263408 | 2.15908e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 8505.17 | 0.105275 | 847.1ms | 11579 | 2560 | 4782.63 | 1298.34 | 0.101079 | 0.619411 | 2.96286 | 0.362294 | 0.000259967 | 6.44351e-06 | 1.07954e-06 | 2(Loss) | true |
