
----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 21472.5 | 0.079912 | 871.123ms | 31235 | 160 | 196.635 | 1387.26 | 0.119984 | 0.24253 | 0.652025 | 0.0931647 | 3.20154e-05 | 6.00288e-06 | 4.00192e-07 | 1(Win) | true |
| Glaze | 7380.41 | 0.0905668 | 1140.53ms | 31235 | 4890 | 65338.4 | 4036.09 | 0.0882475 | 0.691484 | 3.62862 | 0.603938 | 0.000693679 | 1.25181e-05 | 5.66325e-06 | 2(Loss) | true |
| simdjson (reflection) | 528.27 | 0.169898 | 6391.52ms | 31235 | 2560 | 2.34957e+07 | 56387.8 | 0.117873 | 9.42019 | 38.2539 | 7.04537 | 0.0153636 | 9.83722e-05 | 6.37431e-05 | 3(Loss) | true |
