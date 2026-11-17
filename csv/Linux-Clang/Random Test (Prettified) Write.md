
----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15798.6 | 0.129413 | 5853.5ms | 837491 | 160 | 684856 | 50554.8 | 0.148091 | 0.319284 | 1.35607 | 0.257744 | 0.000462833 | 0.0166646 | 6.00006e-06 | 1(Win) | true |
| Glaze | 3918.21 | 0.119991 | 5443.57ms | 837491 | 640 | 3.82882e+07 | 203842 | 0.162913 | 1.28578 | 4.56914 | 0.770723 | 0.00620305 | 0.0572316 | 3.27354e-05 | 2(Loss) | true |
