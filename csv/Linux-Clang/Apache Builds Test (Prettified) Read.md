
----
### Apache Builds Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1854.57 | 0.0405434 | 7188.71ms | 124597 | 640 | 431866 | 64071.4 | 0.0935501 | 2.73377 | 11.8564 | 2.23221 | 0.00698043 | 1.39951e-05 | 1.00323e-05 | 1(Win) | true |
| simdjson (ondemand) | 1611.3 | 0.0450022 | 8118.13ms | 124597 | 640 | 704874 | 73744.9 | 0.0186043 | 3.15616 | 12.9152 | 2.36968 | 0.00898256 | 6.93486e-06 | 3.83737e-06 | 2(Loss) | true |
