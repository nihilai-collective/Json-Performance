
----
### Random Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2689.77 | 0.0518119 | 6302.95ms | 676745 | 1280 | 1.97829e+07 | 239944 | 0.00656772 | 1.88167 | 8.60809 | 1.5378 | 0.00586787 | 0.00178927 | 2.26429e-05 | 1(Win) | true |
| simdjson (ondemand) | 2225.72 | 0.0361599 | 7583.55ms | 676745 | 640 | 7.03627e+06 | 289971 | 0.262315 | 2.30059 | 9.45956 | 1.63397 | 0.00792265 | 0.00388735 | 1.29619e-05 | 2(Loss) | true |
