
----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1950.22 | 0.0416805 | 1048.51ms | 6701 | 4890 | 9121.9 | 3276.84 | 0.129202 | 2.67119 | 10.7172 | 1.99224 | 0.00107859 | 3.68348e-05 | 1.01014e-05 | 1(Win) | true |
| simdjson (ondemand) | 1922.17 | 0.0346821 | 1050.62ms | 6701 | 4890 | 6501.55 | 3324.67 | 0.0297723 | 2.70974 | 10.7763 | 1.85942 | 0.000362123 | 3.39051e-05 | 9.97928e-06 | 2(Loss) | true |
