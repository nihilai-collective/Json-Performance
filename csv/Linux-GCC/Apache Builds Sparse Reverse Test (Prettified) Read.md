
----
### Apache Builds Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2478.72 | 0.0215091 | 5521.15ms | 124597 | 2560 | 272173 | 47938.1 | 0.265811 | 2.04883 | 9.80569 | 1.85829 | 0.00507236 | 7.73431e-06 | 4.56472e-06 | 1(Win) | true |
| simdjson (ondemand) | 2109.09 | 0.0390374 | 6351.33ms | 124597 | 640 | 309577 | 56339.5 | 0.119736 | 2.40647 | 10.1071 | 1.86408 | 0.0067609 | 8.85354e-06 | 5.45509e-06 | 2(Loss) | true |
