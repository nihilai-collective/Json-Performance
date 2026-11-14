
----
### Random Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2822.62 | 0.0422585 | 993.707ms | 8150 | 2560 | 3466.4 | 2753.63 | 0.0385294 | 1.85042 | 8.13362 | 1.4362 | 0.00185822 | 1.16469e-05 | 1.38995e-06 | 1(Win) | true |
| simdjson (ondemand) | 2308.93 | 0.0318364 | 1051.24ms | 8150 | 2560 | 2940.23 | 3366.26 | 0.0265896 | 2.25585 | 8.93448 | 1.51472 | 0.00478413 | 1.54812e-05 | 2.58819e-06 | 2(Loss) | true |
