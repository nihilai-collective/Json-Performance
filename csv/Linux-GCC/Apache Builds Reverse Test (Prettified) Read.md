
----
### Apache Builds Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1441.15 | 0.0240054 | 9018.94ms | 124597 | 2560 | 1.0029e+06 | 82451.6 | 0.00174064 | 3.53575 | 16.2022 | 3.25294 | 0.00790579 | 1.23774e-05 | 8.33625e-06 | 1(Win) | true |
| simdjson (ondemand) | 914.782 | 0.0367294 | 7032.78ms | 124597 | 1280 | 2.91352e+06 | 129894 | 0.59945 | 5.55274 | 25.9927 | 5.32434 | 0.0101903 | 1.52554e-05 | 1.02957e-05 | 2(Loss) | true |
