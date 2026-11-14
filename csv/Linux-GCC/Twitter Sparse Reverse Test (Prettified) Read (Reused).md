
----
### Twitter Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5805.81 | 0.093671 | 6723.47ms | 360584 | 4890 | 1.50524e+07 | 59230.3 | 0.0198741 | 0.882735 | 4.31988 | 0.652899 | 0.00144324 | 6.68706e-06 | 3.98467e-06 | 1(Win) | true |
| simdjson (ondemand) | 5049 | 0.0764143 | 7595.62ms | 360584 | 4890 | 1.32452e+07 | 68108.5 | 0.00585688 | 1.00135 | 4.98217 | 0.702199 | 0.00185217 | 6.23336e-06 | 3.38975e-06 | 2(Loss) | true |
