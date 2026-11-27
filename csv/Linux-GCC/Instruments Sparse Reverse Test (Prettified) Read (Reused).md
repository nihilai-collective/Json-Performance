
----
### Instruments Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5542.24 | 0.0236293 | 3904.21ms | 183677 | 2560 | 142785 | 31606 | 0.0326389 | 0.924895 | 5.11288 | 0.853439 | 0.000454972 | 2.56905e-06 | 1.25475e-06 | 1(Win) | true |
| simdjson (ondemand) | 4223.81 | 0.0449216 | 4888.26ms | 183677 | 640 | 222121 | 41471.6 | 0.0561241 | 1.21016 | 6.30925 | 0.949798 | 0.00206305 | 3.74298e-06 | 2.33086e-06 | 2(Loss) | true |
