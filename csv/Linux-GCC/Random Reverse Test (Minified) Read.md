
----
### Random Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 844.967 | 0.0777125 | 5960.81ms | 409725 | 320 | 4.13273e+07 | 462437 | 0.0112395 | 5.99771 | 27.9949 | 5.60035 | 0.0147281 | 0.0264309 | 0.000215724 | 1(Win) | true |
| simdjson (ondemand) | 454.177 | 0.0974981 | 5444.19ms | 409725 | 160 | 1.12576e+08 | 860335 | 0.193639 | 11.1717 | 46.7001 | 9.38366 | 0.0362148 | 0.0450848 | 4.72268e-05 | 2(Loss) | true |
