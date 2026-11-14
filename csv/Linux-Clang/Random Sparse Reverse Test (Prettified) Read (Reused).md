
----
### Random Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2976.27 | 0.0466265 | 6266.15ms | 676745 | 320 | 3.27131e+06 | 216847 | 0.0261594 | 1.70382 | 7.871 | 1.40914 | 0.00523433 | 0.000308633 | 6.7603e-06 | 1(Win) | true |
| simdjson (ondemand) | 2538.89 | 0.040966 | 7218.8ms | 676745 | 640 | 6.94047e+06 | 254203 | 0.0340795 | 2.00996 | 9.12554 | 1.45642 | 0.0066555 | 0.001884 | 4.00123e-06 | 2(Loss) | true |
