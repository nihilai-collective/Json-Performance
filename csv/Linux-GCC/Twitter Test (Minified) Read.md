
----
### Twitter Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1849.11 | 0.0993351 | 7335.83ms | 264040 | 320 | 5.8556e+06 | 136178 | 0.0336368 | 2.76108 | 9.4995 | 1.73761 | 0.0127764 | 0.000425516 | 9.6813e-05 | 1(Win) | true |
| simdjson (ondemand) | 1726.34 | 0.0479117 | 7850.4ms | 264040 | 2560 | 1.25028e+07 | 145862 | 0.118355 | 2.94134 | 10.6576 | 1.82896 | 0.00892881 | 0.00151681 | 5.229e-05 | 2(Loss) | true |
