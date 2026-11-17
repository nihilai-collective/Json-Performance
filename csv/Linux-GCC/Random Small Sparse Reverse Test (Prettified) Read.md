
----
### Random Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2802.94 | 0.093579 | 998.931ms | 8150 | 640 | 4309.47 | 2772.96 | 0.0561539 | 1.86004 | 8.13362 | 1.4362 | 0.00161522 | 1.64877e-05 | 3.45092e-06 | 1(Win) | true |
| simdjson (ondemand) | 2354.09 | 0.0548479 | 1053.51ms | 8150 | 80 | 262.349 | 3301.68 | 0.101567 | 2.21441 | 8.94626 | 1.51926 | 0.00419479 | 1.07362e-05 | 0 | 2(Loss) | true |
