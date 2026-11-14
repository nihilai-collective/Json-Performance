
----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2090.32 | 0.0901408 | 936.355ms | 4630 | 1280 | 4640.77 | 2112.36 | 0.453181 | 2.50829 | 7.69287 | 0.4108 | 0.000219695 | 2.10921e-05 | 2.53105e-06 | 1(Win) | true |
| Glaze | 1473.15 | 0.0780056 | 1029.27ms | 4630 | 640 | 3498.62 | 2997.32 | 0.0900514 | 3.50269 | 9.97883 | 0.714039 | 0.000216658 | 5.73704e-05 | 1.68737e-05 | 2(Loss) | true |
| simdjson (reflection) | 1086.19 | 0.0289163 | 1121.22ms | 4630 | 80 | 110.541 | 4065.12 | 0 | 4.79023 | 15.3685 | 1.44384 | 0.000647948 | 6.2095e-05 | 3.23974e-05 | 3(Loss) | true |
