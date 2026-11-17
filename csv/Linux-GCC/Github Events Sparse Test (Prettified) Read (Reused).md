
----
### Github Events Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9073.21 | 0.0437668 | 1426.34ms | 65103 | 1280 | 11481 | 6842.9 | 0.0134245 | 0.570777 | 2.72722 | 0.310401 | 0.000681456 | 2.23204e-06 | 1.20002e-08 | 1(Win) | true |
| simdjson (ondemand) | 8100.31 | 0.0301638 | 1508.45ms | 65103 | 4890 | 26138.4 | 7664.77 | 0.00582777 | 0.638674 | 2.93441 | 0.327773 | 0.000723365 | 3.00609e-06 | 1.97893e-07 | 2(Loss) | true |
