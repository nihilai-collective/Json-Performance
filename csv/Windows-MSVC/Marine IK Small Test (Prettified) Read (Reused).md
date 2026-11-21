
----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2136.69 | 0.240489 | 986.083ms | 18245 | 30 | 11505.7 | 8143.33 | 0.328542 | 1.1559 | 1(Win) | true |
| Jsonifier | 1852.5 | 0.26233 | 1104.76ms | 18245 | 2560 | 1.5542e+06 | 9392.62 | 0.157035 | 1.33247 | 2(Loss) | true |
| simdjson (ondemand) | 805.919 | 0.107311 | 2424.05ms | 18245 | 30 | 16103.4 | 21590 | 0.613779 | 3.06978 | 3(Loss) | true |
| Glaze | 640.961 | 0.170137 | 2897.28ms | 18245 | 1280 | 2.73043e+06 | 27146.4 | 0.0408831 | 3.85903 | 4(Loss) | true |
