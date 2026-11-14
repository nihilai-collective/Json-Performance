
----
### Canada Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1626.4 | 0.0302538 | 1420.17ms | 11579 | 4890 | 20632.7 | 6789.59 | 0.159852 | 3.11828 | 15.4168 | 2.71267 | 0.00156893 | 4.80385e-05 | 2.39133e-05 | 1(Win) | true |
| Jsonifier (generic) | 1612.74 | 0.0688166 | 1422.37ms | 11579 | 640 | 14209.4 | 6847.08 | 0.0476481 | 3.14614 | 15.2958 | 2.87546 | 0.00163793 | 2.88777e-05 | 1.4169e-05 | 2(Loss) | true |
