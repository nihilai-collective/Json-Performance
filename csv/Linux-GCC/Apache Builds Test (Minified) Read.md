
----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1565.21 | 0.0231019 | 6506.29ms | 94653 | 2560 | 454421 | 57671.6 | 0.0267941 | 3.24148 | 14.8731 | 2.85132 | 0.00885107 | 1.32763e-05 | 8.66652e-06 | 1(Win) | true |
| simdjson (ondemand) | 1240.08 | 0.0166565 | 8023.77ms | 94653 | 4890 | 718861 | 72792.3 | 0.00278093 | 4.09264 | 15.8667 | 3.10348 | 0.0118896 | 1.70335e-05 | 1.17856e-05 | 2(Loss) | true |
