
----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2465.36 | 0.0879039 | 7502.72ms | 360584 | 2560 | 3.84864e+07 | 139484 | 0.358662 | 2.05152 | 7.99539 | 1.39907 | 0.00422531 | 0.000475901 | 1.52195e-05 | 1(Win) | true |
| simdjson (ondemand) | 2164.37 | 0.0818469 | 8513.15ms | 360584 | 640 | 1.08227e+07 | 158882 | 0.224782 | 2.34251 | 8.23825 | 1.36027 | 0.00868448 | 0.00255113 | 9.27315e-06 | 2(Loss) | true |
