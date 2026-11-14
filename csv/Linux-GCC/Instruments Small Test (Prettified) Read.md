
----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2428.85 | 0.0401172 | 1032.97ms | 7932 | 4890 | 7633.67 | 3114.45 | 0.0826737 | 2.15574 | 9.52272 | 1.48954 | 0.000638118 | 2.05736e-05 | 6.00709e-06 | 1(Win) | true |
| Jsonifier (generic) | 2368.25 | 0.0702202 | 1061.08ms | 7932 | 1280 | 6439.37 | 3194.14 | 0.0375546 | 2.20301 | 8.73777 | 1.6765 | 0.0011963 | 1.5365e-05 | 2.46234e-06 | 2(Loss) | true |
