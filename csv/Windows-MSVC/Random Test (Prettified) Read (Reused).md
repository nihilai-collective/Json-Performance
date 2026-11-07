
----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1320.44 | 0.0975825 | 7959.49ms | 728486 | 320 | 8.4353e+07 | 526142 | 0.0939315 | 1.87486 | 1(Win) | true |
| Jsonifier | 1293.75 | 0.166758 | 7980.63ms | 728486 | 80 | 6.4151e+07 | 536996 | 0.338434 | 1.91356 | 2(Loss) | true |
| Glaze | 1179.8 | 0.308241 | 8805.86ms | 728486 | 30 | 9.88383e+07 | 588860 | 0.192093 | 2.09844 | 3(Loss) | true |
| simdjson (ondemand) | 951.633 | 0.109585 | 5217.76ms | 728486 | 160 | 1.02406e+08 | 730049 | 0.0441556 | 2.60151 | 4(Loss) | true |
