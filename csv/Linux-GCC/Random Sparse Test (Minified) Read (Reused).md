
----
### Random Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3150.13 | 0.0400086 | 7618.89ms | 409725 | 320 | 788106 | 124041 | 0.296508 | 1.60475 | 8.00165 | 1.41425 | 0.00366425 | 6.53487e-05 | 2.08905e-05 | 1(Win) | true |
| simdjson (ondemand) | 2252.26 | 0.12156 | 5078.58ms | 409725 | 80 | 3.55809e+06 | 173490 | 0.0120742 | 2.26777 | 9.72675 | 1.59842 | 0.006838 | 0.000598328 | 2.21185e-05 | 2(Loss) | true |
