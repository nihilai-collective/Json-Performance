
----
### Discord Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 930.677 | 0.0378082 | 9349.87ms | 83958 | 1280 | 1.35428e+06 | 86032.7 | 0.141341 | 5.46277 | 24.1563 | 5.06228 | 0.00723369 | 7.53818e-05 | 5.8437e-05 | 1(Win) | true |
| simdjson (ondemand) | 285.91 | 0.117471 | 7319.62ms | 83958 | 640 | 6.92636e+07 | 280048 | 0.0446169 | 17.6753 | 89.3846 | 18.9348 | 0.0235121 | 0.000139095 | 8.61294e-05 | 2(Loss) | true |
