
----
### Twitter Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5017.29 | 0.0691414 | 787.202ms | 3770 | 640 | 157.109 | 716.592 | 0.0098111 | 1.0839 | 4.51406 | 0.665517 | 0.000790368 | 2.11373e-05 | 1.65782e-06 | 1(Win) | true |
| simdjson (ondemand) | 4461.45 | 0.066191 | 795.575ms | 3770 | 4890 | 1391.35 | 805.871 | 0.0320972 | 1.21178 | 5.00796 | 0.692043 | 0.000569397 | 1.69241e-05 | 4.88194e-06 | 2(Loss) | true |
