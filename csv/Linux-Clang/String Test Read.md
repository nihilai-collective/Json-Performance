
----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1788.52 | 0.0684811 | 1250.21ms | 9578 | 4890 | 59815.5 | 5107.18 | 0.123526 | 2.8528 | 14.0799 | 2.70854 | 0.00126585 | 4.9043e-05 | 1.9835e-05 | 1(Win) | true |
| Glaze | 1418.37 | 0.05083 | 1391.66ms | 9578 | 4890 | 52398.2 | 6439.97 | 0.0982458 | 3.58551 | 17.8633 | 3.53947 | 0.00132273 | 5.24592e-05 | 1.94293e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1412.01 | 0.209434 | 1399.93ms | 9578 | 160 | 29369.1 | 6469.02 | 0.0389507 | 3.60238 | 17.5818 | 2.96628 | 0.00379907 | 1.56609e-05 | 3.26269e-06 | 3(Loss) | true |
| Jsonifier (two-stage) | 1343.19 | 0.119284 | 1432.76ms | 9578 | 640 | 42113.2 | 6800.43 | 0.16289 | 3.78751 | 18.2534 | 3.09835 | 0.00161731 | 3.40951e-05 | 1.28876e-05 | 4(Loss) | true |
