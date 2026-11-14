
----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14379.3 | 0.0975204 | 5521.65ms | 728486 | 160 | 355205 | 48315.3 | 0.305643 | 0.351319 | 1.88741 | 0.0866016 | 0.000357574 | 1.5014e-06 | 1.08959e-06 | 1(Win) | true |
| simdjson (stage-1) | 13782.7 | 0.0513843 | 5761.87ms | 728486 | 1280 | 858711 | 50406.7 | 0.0956485 | 0.371385 | 1.77437 | 0.0748814 | 1.10632e-05 | 2.87626e-06 | 2.34969e-06 | 2(Loss) | true |
