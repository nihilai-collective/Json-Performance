
----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8232.13 | 0.0543311 | 6220.41ms | 466906 | 2560 | 2.21091e+06 | 54090.1 | 0.0544969 | 0.614258 | 3.02526 | 0.38415 | 0.00110656 | 1.80669e-05 | 1.58256e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 8187.54 | 0.0760861 | 6236.62ms | 466906 | 1280 | 2.19166e+06 | 54384.6 | 0.110534 | 0.613743 | 3.02392 | 0.383833 | 0.00111285 | 1.74185e-06 | 1.04578e-06 | 2(Loss) | true |
| simdjson (ondemand) | 7008.29 | 0.0300275 | 7198.38ms | 466906 | 4890 | 1.77985e+06 | 63535.7 | 0.071681 | 0.719972 | 3.43081 | 0.369827 | 0.00083059 | 9.09262e-06 | 7.13044e-06 | 3(Loss) | true |
| Glaze | 3432.39 | 0.0396104 | 7100.19ms | 466906 | 640 | 1.68992e+06 | 129728 | 0.0292931 | 1.4731 | 5.69145 | 0.985458 | 0.00170351 | 6.41524e-06 | 3.94887e-06 | 4(Loss) | true |
