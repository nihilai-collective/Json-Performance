
----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1017.93 | 0.13502 | 8707.19ms | 728486 | 40 | 3.39674e+07 | 682502 | 0.29716 | 2.98554 | 1(Win) | true |
| Jsonifier | 931.472 | 0.226758 | 9493.84ms | 728486 | 80 | 2.28832e+08 | 745850 | 0.210606 | 3.26267 | 2(Loss) | true |
| Glaze | 866.31 | 0.231731 | 5071.3ms | 728486 | 160 | 5.52567e+08 | 801951 | 0.10298 | 3.50824 | 3(Loss) | true |
| simdjson (ondemand) | 769.026 | 0.21333 | 5731.74ms | 728486 | 40 | 1.48567e+08 | 903400 | 0.171869 | 3.95202 | 4(Loss) | true |
