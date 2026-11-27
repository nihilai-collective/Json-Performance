
----
### Discord Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3569.44 | 0.128081 | 2992.32ms | 83958 | 4890 | 4.03651e+06 | 22431.7 | 0.0323716 | 1.4222 | 6.92909 | 1.17095 | 0.00202545 | 2.80596e-05 | 1.74228e-05 | 1(Win) | true |
| simdjson (ondemand) | 3024.3 | 0.0476656 | 3417.42ms | 83958 | 2560 | 407687 | 26475.1 | 0.185414 | 1.68404 | 7.25226 | 1.1534 | 0.00284889 | 3.54623e-05 | 2.69899e-05 | 2(Loss) | true |
