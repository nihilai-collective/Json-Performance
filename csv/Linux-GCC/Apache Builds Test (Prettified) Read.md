
----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1957.92 | 0.0411218 | 6818.03ms | 124597 | 640 | 398611 | 60689.4 | 0.00726495 | 2.59305 | 11.671 | 2.17247 | 0.00718291 | 3.26051e-06 | 7.39885e-07 | 1(Win) | true |
| simdjson (ondemand) | 1596.65 | 0.0314865 | 8156.85ms | 124597 | 1280 | 702838 | 74421.6 | 0.0124707 | 3.1832 | 12.3701 | 2.36885 | 0.00924659 | 6.21378e-06 | 2.87803e-06 | 2(Loss) | true |
