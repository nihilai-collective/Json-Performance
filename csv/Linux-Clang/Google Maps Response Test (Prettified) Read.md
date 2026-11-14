
----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3415.21 | 0.054504 | 1452.9ms | 25388 | 4890 | 73010.9 | 7089.42 | 0.0846479 | 1.4875 | 7.13321 | 1.13475 | 0.00291492 | 2.257e-05 | 9.81092e-06 | 1(Win) | true |
| Jsonifier | 2923.82 | 0.0584088 | 1570.14ms | 25388 | 4890 | 114399 | 8280.91 | 0.00843682 | 1.73995 | 7.8389 | 1.64377 | 0.0042974 | 2.24169e-05 | 9.50484e-06 | 2(Loss) | true |
| Glaze | 2411.31 | 0.137285 | 1753.3ms | 25388 | 320 | 60805.6 | 10041 | 0.0937667 | 2.10419 | 9.60627 | 1.88735 | 0.00464725 | 6.03139e-06 | 7.38538e-07 | 3(Loss) | true |
| simdjson (ondemand) | 2173.79 | 0.205415 | 1868.66ms | 25388 | 640 | 335017 | 11138.1 | 0.0798573 | 2.33337 | 10.1943 | 1.62014 | 0.00361865 | 1.42784e-05 | 6.03139e-06 | 4(Loss) | true |
