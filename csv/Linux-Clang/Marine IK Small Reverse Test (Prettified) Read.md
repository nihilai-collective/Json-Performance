
----
### Marine IK Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1240.01 | 0.0307878 | 2136.38ms | 18245 | 2560 | 47778.9 | 14032 | 0.0106108 | 4.15327 | 18.0025 | 3.83626 | 0.0047983 | 3.39134e-05 | 1.43875e-05 | 1(Win) | true |
| simdjson (ondemand) | 921.474 | 0.278295 | 2631.21ms | 18245 | 30 | 82842.7 | 18882.6 | 0.179322 | 5.59251 | 28.6774 | 5.61074 | 0.0059103 | 0.000118754 | 0.000109619 | 2(Loss) | true |
