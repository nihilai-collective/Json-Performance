
----
### Apache Builds Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2337.43 | 0.0310605 | 5832.2ms | 124597 | 4890 | 1.21917e+06 | 50835.6 | 0.450079 | 2.18198 | 10.0945 | 1.9305 | 0.00548468 | 1.21947e-05 | 7.28566e-06 | 1(Win) | true |
| simdjson (ondemand) | 2072.89 | 0.0378658 | 6476.78ms | 124597 | 1280 | 603067 | 57323.3 | 0.0914418 | 2.46147 | 10.0984 | 1.86079 | 0.0071303 | 4.57726e-06 | 1.58009e-06 | 2(Loss) | true |
