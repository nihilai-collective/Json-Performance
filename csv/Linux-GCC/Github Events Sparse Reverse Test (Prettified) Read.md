
----
### Github Events Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6189.66 | 0.0342112 | 1727.68ms | 65103 | 4890 | 57585.8 | 10030.8 | 0.0139014 | 0.834843 | 3.93911 | 0.595011 | 0.00144464 | 4.4416e-06 | 1.1371e-06 | 1(Win) | true |
| simdjson (ondemand) | 4910.25 | 0.0191214 | 1989.35ms | 65103 | 4890 | 28585.4 | 12644.4 | 0.0807497 | 1.04959 | 5.05786 | 0.793497 | 0.00205447 | 4.12434e-06 | 1.18108e-06 | 2(Loss) | true |
