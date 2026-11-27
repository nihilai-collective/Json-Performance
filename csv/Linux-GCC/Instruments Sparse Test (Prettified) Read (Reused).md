
----
### Instruments Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7817.72 | 0.0188254 | 2974.29ms | 183677 | 4890 | 87005.9 | 22406.5 | 0.0784384 | 0.651181 | 3.5845 | 0.476717 | 0.000412896 | 1.51083e-06 | 4.56478e-07 | 1(Win) | true |
| simdjson (ondemand) | 6657.31 | 0.0174274 | 3381.22ms | 183677 | 4890 | 102822 | 26312.1 | 0.28594 | 0.768225 | 3.96569 | 0.451064 | 0.000983339 | 1.02329e-05 | 8.3157e-06 | 2(Loss) | true |
