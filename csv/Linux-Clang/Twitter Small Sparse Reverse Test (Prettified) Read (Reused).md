
----
### Twitter Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5334.1 | 0.144007 | 781.513ms | 3770 | 160 | 150.747 | 674.031 | 0.0342967 | 1.02402 | 4.49576 | 0.667639 | 0.000570292 | 2.15517e-05 | 1.65782e-06 | 1(Win) | true |
| simdjson (ondemand) | 4857.97 | 0.0410689 | 788.018ms | 3770 | 4890 | 451.761 | 740.094 | 0.118733 | 1.11902 | 4.95862 | 0.67878 | 0.000642789 | 2.39757e-05 | 2.87492e-06 | 2(Loss) | true |
