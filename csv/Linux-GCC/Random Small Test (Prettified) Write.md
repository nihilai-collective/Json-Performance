
----
### Random Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20939.3 | 0.109847 | 760.991ms | 9255 | 640 | 137.211 | 421.517 | 0.914928 | 0.272698 | 0.991464 | 0.125122 | 0.000108219 | 2.12723e-05 | 3.37655e-06 | 1(Win) | true |
| Glaze | 4591.59 | 0.080335 | 916.391ms | 9255 | 2560 | 6104.86 | 1922.26 | 0.240998 | 1.15363 | 4.8228 | 0.815451 | 0.000110413 | 3.83661e-05 | 7.68166e-06 | 2(Loss) | true |
| simdjson (reflection) | 531.062 | 0.134711 | 2401.18ms | 9255 | 2560 | 1.28325e+06 | 16620 | 0.036434 | 9.65563 | 38.078 | 7.2845 | 0.015656 | 0.000108007 | 5.63462e-05 | 3(Loss) | true |
