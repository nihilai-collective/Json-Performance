
----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 545.94 | 0.33223 | 172.355ms | 905 | 2560 | 70619.7 | 1580.9 | 0.219428 | 4.45678 | 1(Win) | true |
| Glaze | 511.705 | 0.277657 | 171.138ms | 905 | 4890 | 107247 | 1686.67 | 0.141844 | 4.76457 | 2(Loss) | true |
| Jsonifier (two-stage) | 172.105 | 0.241559 | 512.534ms | 905 | 2560 | 375658 | 5014.8 | 0.182717 | 14.2598 | 3(Loss) | true |
| simdjson (ondemand) | 71.3089 | 0.0482469 | 1239.62ms | 905 | 30 | 1022.99 | 12103.3 | 0.137893 | 34.5898 | 4(Loss) | true |
