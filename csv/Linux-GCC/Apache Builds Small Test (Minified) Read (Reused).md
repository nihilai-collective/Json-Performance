
----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2867 | 0.0520842 | 827.628ms | 2632 | 320 | 66.5392 | 875.503 | 0.0203413 | 1.84937 | 7.25342 | 1.07713 | 0.000762253 | 1.66223e-05 | 0 | 1(Win) | true |
| Glaze | 2558.61 | 0.0480059 | 835.581ms | 2632 | 640 | 141.949 | 981.028 | 0.0703486 | 2.05859 | 9.23366 | 1.68351 | 0.000978937 | 2.84954e-05 | 5.93655e-07 | 2(Loss) | true |
| Jsonifier (two-stage) | 2382.88 | 0.0878546 | 848.393ms | 2632 | 320 | 274.06 | 1053.38 | 0.12416 | 2.20742 | 9.23252 | 1.3636 | 0.00076819 | 4.39305e-05 | 4.74924e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2000.01 | 0.059585 | 864.531ms | 2632 | 2560 | 1431.6 | 1255.03 | 0.204596 | 2.61287 | 8.89894 | 1.57181 | 0.00180842 | 4.27432e-05 | 7.86593e-06 | 4(Loss) | true |
| simdjson (reflection) | 1979.04 | 0.0789316 | 866.906ms | 2632 | 2560 | 2565.7 | 1268.33 | 0.00113955 | 2.64343 | 8.59271 | 1.32409 | 0.0021094 | 4.11106e-05 | 7.12386e-06 | 5(Loss) | true |
