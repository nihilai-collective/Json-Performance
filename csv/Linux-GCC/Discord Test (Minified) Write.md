
----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15132.2 | 0.0393484 | 1096.13ms | 56369 | 4890 | 9555.2 | 3552.53 | 0.168849 | 0.337375 | 1.41947 | 0.224485 | 0.000204434 | 1.11847e-05 | 5.80458e-06 | 1(Win) | true |
| simdjson (reflection) | 13054.8 | 0.117547 | 1149.81ms | 56369 | 320 | 7497.4 | 4117.84 | 0.137777 | 0.390869 | 1.69984 | 0.277546 | 0.000169198 | 7.04066e-06 | 2.6056e-06 | 2(Loss) | true |
| Glaze | 6357.31 | 0.0721628 | 1591.31ms | 56369 | 640 | 23830.9 | 8456.04 | 0.00105325 | 0.80029 | 3.0545 | 0.466338 | 7.87223e-05 | 7.95539e-06 | 2.52244e-06 | 3(Loss) | true |
