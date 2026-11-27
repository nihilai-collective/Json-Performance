
----
### Twitter Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5257.5 | 0.0326967 | 5594.74ms | 264040 | 320 | 78476.5 | 47895 | 0.0756487 | 0.961824 | 5.06593 | 0.84413 | 0.00171585 | 2.20019e-05 | 1.72322e-05 | 1(Win) | true |
| simdjson (ondemand) | 4076.07 | 0.0664708 | 6994.15ms | 264040 | 80 | 134899 | 61777.2 | 0.0504283 | 1.24039 | 6.24874 | 0.930581 | 0.00225146 | 4.45008e-06 | 2.41441e-06 | 2(Loss) | true |
