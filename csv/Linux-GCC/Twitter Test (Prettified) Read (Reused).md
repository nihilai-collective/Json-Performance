
----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2961.45 | 0.0494147 | 7055.38ms | 360584 | 1280 | 4.21431e+06 | 116119 | 0.119743 | 1.71667 | 6.98846 | 1.16951 | 0.00339208 | 3.93286e-05 | 3.02591e-05 | 1(Win) | true |
| simdjson (ondemand) | 2484.45 | 0.0826889 | 8240.03ms | 360584 | 640 | 8.38351e+06 | 138413 | 0.118809 | 2.04487 | 7.23574 | 1.13215 | 0.00926534 | 7.20316e-05 | 4.77091e-06 | 2(Loss) | true |
