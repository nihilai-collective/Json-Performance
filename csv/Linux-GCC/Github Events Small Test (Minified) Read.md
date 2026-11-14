
----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2143.74 | 0.115243 | 796.333ms | 1691 | 30 | 22.5471 | 752.267 | 0.0221602 | 2.54177 | 8.88232 | 1.44412 | 0.000591366 | 7.88488e-05 | 0 | 1(Win) | true |
| Glaze | 1973.89 | 0.102483 | 806.022ms | 1691 | 4890 | 3428.09 | 816.997 | 0.114897 | 2.72876 | 10.0727 | 1.97575 | 0.0011242 | 0.000160237 | 6.65136e-05 | 2(Loss) | true |
| simdjson (reflection) | 1828.68 | 0.282444 | 821.393ms | 1691 | 40 | 248.163 | 881.875 | 0.25864 | 2.94509 | 9.87226 | 1.64281 | 0.0015819 | 0.000221762 | 7.39208e-05 | 3(Loss) | true |
| Jsonifier (two-stage) | 1725.17 | 0.125076 | 819.859ms | 1691 | 160 | 218.722 | 934.788 | 0.160207 | 3.06276 | 10.4181 | 1.65405 | 0.000591366 | 0.00017741 | 4.06564e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1568.74 | 0.203041 | 830.133ms | 1691 | 80 | 348.532 | 1028 | 0.024325 | 3.41445 | 10.6268 | 1.71023 | 0.000591366 | 0.000162626 | 2.95683e-05 | 5(Loss) | true |
