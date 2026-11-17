
----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2292.95 | 0.296457 | 7802.57ms | 360584 | 40 | 7.90693e+06 | 149973 | 0.0183678 | 1.07949 | 1(Win) | true |
| Jsonifier (generic) | 2235.71 | 0.309906 | 7869.47ms | 360584 | 80 | 1.81774e+07 | 153813 | 0.880757 | 1.10706 | 2(Loss) | true |
