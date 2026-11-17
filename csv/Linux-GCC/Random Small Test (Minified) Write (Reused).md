
----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16331.4 | 0.12396 | 756.295ms | 5094 | 640 | 87.0191 | 297.464 | 0.0467275 | 0.352461 | 1.4998 | 0.236749 | 0.000196309 | 1.59501e-05 | 2.7606e-06 | 1(Win) | true |
| simdjson (reflection) | 8965.25 | 0.0520829 | 783.617ms | 5094 | 640 | 50.9757 | 541.872 | 0.0409293 | 0.606597 | 2.29388 | 0.329211 | 0.000196309 | 1.87107e-05 | 6.13467e-07 | 2(Loss) | true |
| Glaze | 4992.07 | 0.104492 | 826.957ms | 5094 | 2560 | 2647.05 | 973.146 | 0.199655 | 1.05434 | 4.69925 | 0.724382 | 0.000200374 | 4.25593e-05 | 1.59501e-05 | 3(Loss) | true |
