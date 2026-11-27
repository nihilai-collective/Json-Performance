
----
### Random Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3311.38 | 0.144167 | 5691.43ms | 676745 | 80 | 6.31612e+06 | 194902 | 0.266053 | 1.53856 | 7.41174 | 1.32069 | 0.00574278 | 0.000444314 | 1.57925e-05 | 1(Win) | true |
| simdjson (ondemand) | 2455.76 | 0.142033 | 7432.19ms | 676745 | 30 | 4.18004e+06 | 262809 | 0.348982 | 2.08702 | 8.82335 | 1.48867 | 0.00843823 | 0.000370942 | 1.22153e-05 | 2(Loss) | true |
