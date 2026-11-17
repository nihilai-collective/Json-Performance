
----
### Google Maps Response Test (Minified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10109.9 | 0.0708518 | 825.798ms | 11812 | 1280 | 797.751 | 1114.24 | 0.00350564 | 0.526659 | 2.50364 | 0.11082 | 8.54534e-05 | 9.19351e-06 | 3.96842e-07 | 1(Win) | true |
| simdjson (stage-1) | 9363.99 | 0.0581582 | 831.159ms | 11812 | 2560 | 1253.1 | 1202.99 | 0.0538336 | 0.568775 | 2.80596 | 0.116576 | 8.48912e-05 | 1.35918e-05 | 2.81097e-06 | 2(Loss) | true |
