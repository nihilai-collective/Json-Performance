
----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3325.29 | 0.0516878 | 996.152ms | 9378 | 1280 | 2473.71 | 2689.56 | 0.161591 | 1.56355 | 7.11804 | 1.24462 | 0.0019872 | 3.49888e-05 | 1.47453e-05 | 1(Win) | true |
| simdjson (ondemand) | 3259.07 | 0.0428422 | 1006.43ms | 9378 | 4890 | 6759.05 | 2744.21 | 0.152239 | 1.6012 | 7.14353 | 1.13724 | 0.00206457 | 1.26258e-05 | 2.37688e-06 | 2(Loss) | true |
