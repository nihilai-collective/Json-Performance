
----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20117.6 | 0.0907382 | 8036.67ms | 1439562 | 40 | 153373 | 68242.3 | 0.104079 | 0.2512 | 0.702708 | 0.104812 | 0.000437216 | 0.0186873 | 4.1332e-06 | 1(Win) | true |
| Glaze | 7933.48 | 0.226126 | 9402.2ms | 1439584 | 320 | 4.90003e+07 | 173051 | 0.563618 | 0.636806 | 3.11679 | 0.497885 | 0.000869335 | 0.0175168 | 1.54906e-05 | 2(Loss) | true |
| simdjson (reflection) | 553.255 | 0.839221 | 7800.26ms | 1439562 | 160 | 6.93879e+10 | 2.48145e+06 | 1.15002 | 9.0745 | 35.7826 | 6.43685 | 0.0158844 | 0.309344 | 0.0067948 | 3(Loss) | true |
