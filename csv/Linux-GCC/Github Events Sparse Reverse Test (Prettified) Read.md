
----
### Github Events Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6205.23 | 0.0417322 | 1727.69ms | 65103 | 4890 | 85258.6 | 10005.6 | 0.11102 | 0.830728 | 3.94821 | 0.596701 | 0.0014368 | 1.7735e-05 | 1.16506e-05 | 1(Win) | true |
| simdjson (ondemand) | 4835.53 | 0.0527237 | 2006.33ms | 65103 | 2560 | 117318 | 12839.8 | 0.0054941 | 1.06217 | 5.06878 | 0.795847 | 0.00223829 | 1.42803e-05 | 8.53215e-06 | 2(Loss) | true |
