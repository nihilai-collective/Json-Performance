
----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2767.22 | 0.0366473 | 846.549ms | 3770 | 4890 | 1108.64 | 1299.27 | 0.0589814 | 1.91687 | 7.1947 | 1.21989 | 0.000386867 | 3.4716e-05 | 2.33248e-06 | 1(Win) | true |
| simdjson (ondemand) | 2668.47 | 0.0463822 | 851.033ms | 3770 | 4890 | 1909.72 | 1347.35 | 0.0171147 | 1.98524 | 7.41671 | 1.16499 | 0.000307074 | 6.34652e-05 | 1.75207e-05 | 2(Loss) | true |
