
----
### Apache Builds Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2281.42 | 0.0957505 | 5975.27ms | 124597 | 40 | 99482.6 | 52083.8 | 0.0185564 | 2.25911 | 10.0946 | 1.93333 | 0.00584424 | 4.7754e-05 | 4.55468e-05 | 1(Win) | true |
| simdjson (ondemand) | 2065.62 | 0.0326395 | 6509.01ms | 124597 | 2560 | 902490 | 57525.2 | 0.313663 | 2.47099 | 10.3208 | 1.81516 | 0.00640872 | 1.58292e-05 | 1.19416e-05 | 2(Loss) | true |
