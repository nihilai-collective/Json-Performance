
----
### Twitter Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4886.16 | 0.0433406 | 785.985ms | 3770 | 1280 | 130.181 | 735.824 | 0.013061 | 1.11272 | 4.56764 | 0.67878 | 0.000600133 | 1.65782e-05 | 2.48674e-06 | 1(Win) | true |
| simdjson (ondemand) | 4369.52 | 0.110869 | 797.513ms | 3770 | 80 | 66.5766 | 822.825 | 0.0607294 | 1.23789 | 5.06393 | 0.70504 | 0.000573607 | 1.98939e-05 | 3.31565e-06 | 2(Loss) | true |
