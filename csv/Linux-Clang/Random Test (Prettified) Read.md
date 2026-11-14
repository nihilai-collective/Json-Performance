
----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1891.87 | 0.0211221 | 8921.43ms | 676745 | 1280 | 6.64584e+06 | 341140 | 0.114948 | 2.67454 | 11.9099 | 2.2509 | 0.00702893 | 0.0285989 | 3.39146e-05 | 1(Win) | true |
| simdjson (ondemand) | 1525.51 | 0.0442693 | 5458.41ms | 676745 | 640 | 2.24495e+07 | 423069 | 0.0919055 | 3.32731 | 13.2933 | 2.31081 | 0.0114967 | 0.0424679 | 6.35533e-05 | 2(Loss) | true |
