
----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 21907.9 | 0.0670295 | 871.951ms | 31235 | 4890 | 4061.82 | 1359.69 | 0.0464218 | 0.237467 | 0.652025 | 0.0931648 | 3.2454e-05 | 9.23797e-06 | 3.85625e-06 | 1(Win) | true |
| Glaze | 7381.97 | 0.113507 | 1137.48ms | 31235 | 2560 | 53706.3 | 4035.24 | 0.070668 | 0.689967 | 3.62862 | 0.603938 | 0.000691194 | 1.94218e-05 | 1.05301e-05 | 2(Loss) | true |
| simdjson (reflection) | 530.156 | 0.178949 | 6367.79ms | 31235 | 2560 | 2.58806e+07 | 56187.2 | 0.109048 | 9.44212 | 38.2539 | 7.04537 | 0.0151338 | 0.00011498 | 7.80124e-05 | 3(Loss) | true |
