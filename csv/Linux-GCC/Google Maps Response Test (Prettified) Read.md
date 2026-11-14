
----
### Google Maps Response Test (Prettified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13343.2 | 0.142345 | 906.269ms | 25388 | 80 | 533.719 | 1814.55 | 0.103225 | 0.387489 | 1.91386 | 0.15917 | 4.82511e-05 | 4.43123e-06 | 4.92359e-07 | 1(Win) | true |
| simdjson (stage-1) | 13282.7 | 0.0491307 | 903.004ms | 25388 | 160 | 128.325 | 1822.82 | 0.0599672 | 0.396152 | 1.96975 | 0.0766504 | 4.89897e-05 | 7.1392e-06 | 0 | 2(Loss) | true |
