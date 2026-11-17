
----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2201.92 | 0.281745 | 831.38ms | 2158 | 4890 | 33909.4 | 934.651 | 0.156944 | 2.39861 | 8.25626 | 1.36237 | 0.000478838 | 0.00010585 | 2.07531e-05 | 1(Win) | true |
| Glaze | 1990.25 | 0.161155 | 842.576ms | 2158 | 4890 | 13579.6 | 1034.06 | 0.330817 | 2.64799 | 9.8772 | 1.8962 | 0.000477038 | 0.000207247 | 8.72769e-05 | 2(Loss) | true |
| Jsonifier | 1806.03 | 0.461374 | 851.674ms | 2158 | 2560 | 70761.6 | 1139.53 | 0.320068 | 2.89848 | 8.92586 | 1.70621 | 0.00170785 | 0.000103177 | 1.3938e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1721.46 | 0.25094 | 856.92ms | 2158 | 2560 | 23040.5 | 1195.52 | 0.140074 | 3.03975 | 9.91242 | 1.62929 | 0.000633906 | 0.000104082 | 1.70152e-05 | 4(Loss) | true |
