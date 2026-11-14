
----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2383.53 | 0.0527622 | 3942.08ms | 65103 | 4890 | 923664 | 26048.3 | 0.0441661 | 2.12297 | 7.39511 | 1.0931 | 0.00684274 | 4.78022e-05 | 2.92191e-05 | 1(Win) | true |
| Jsonifier | 2262.48 | 0.0194703 | 3973.71ms | 65103 | 4890 | 139600 | 27442 | 0.108493 | 2.2365 | 7.42154 | 1.27603 | 0.00272898 | 3.11949e-05 | 1.95537e-05 | 2(Loss) | true |
| simdjson (reflection) | 2224.17 | 0.0390633 | 4114.14ms | 65103 | 2560 | 304399 | 27914.7 | 0.0351333 | 2.27115 | 7.6383 | 1.22 | 0.00749577 | 6.10151e-05 | 3.75307e-05 | 3(Loss) | true |
| Glaze | 2007.55 | 0.0572444 | 4451.32ms | 65103 | 2560 | 802370 | 30926.7 | 0.0398995 | 2.51761 | 8.9377 | 1.70282 | 0.0123772 | 5.05389e-05 | 3.19746e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1943.75 | 0.0246406 | 4483.69ms | 65103 | 4890 | 302923 | 31941.9 | 0.031816 | 2.60361 | 7.82981 | 1.35344 | 0.00780063 | 2.89929e-05 | 1.48074e-05 | 5(Loss) | true |
