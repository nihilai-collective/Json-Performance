
----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1055.28 | 0.573112 | 7611.2ms | 676745 | 640 | 7.86271e+09 | 611584 | 0.286977 | 2.34588 | 1(Win) | true |
| simdjson (ondemand) | 943.625 | 0.180689 | 9059.87ms | 676745 | 320 | 4.88722e+08 | 683952 | 0.525496 | 2.62355 | 2(Loss) | true |
