
----
### Twitter Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6207.67 | 0.0411886 | 6312.58ms | 360584 | 2560 | 1.33275e+06 | 55395.9 | 0.0934076 | 0.81797 | 4.24637 | 0.659148 | 0.0013494 | 5.82172e-06 | 3.86634e-06 | 1(Win) | true |
| simdjson (ondemand) | 4972.51 | 0.034481 | 7677.88ms | 360584 | 2560 | 1.45566e+06 | 69156.1 | 0.0296174 | 1.01656 | 5.0332 | 0.713514 | 0.00194152 | 1.58879e-05 | 1.1794e-05 | 2(Loss) | true |
