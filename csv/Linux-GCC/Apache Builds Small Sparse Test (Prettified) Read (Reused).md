
----
### Apache Builds Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4974.8 | 0.0839332 | 781.431ms | 3370 | 640 | 188.173 | 646.033 | 0.324729 | 1.10385 | 4.63769 | 0.686647 | 0.000765022 | 1.20549e-05 | 4.17285e-06 | 1(Win) | true |
| simdjson (ondemand) | 3531.74 | 0.131721 | 810.127ms | 3370 | 30 | 43.1034 | 910 | 0.182815 | 1.52372 | 5.65045 | 0.865875 | 0.000702275 | 0 | 0 | 2(Loss) | true |
