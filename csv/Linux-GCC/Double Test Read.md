
----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1297.12 | 0.0462819 | 854.261ms | 1811 | 640 | 243.039 | 1331.49 | 0.0548896 | 4.10878 | 17.7747 | 3.6212 | 0.000980984 | 7.50621e-05 | 1.12162e-05 | 1(Win) | true |
| Glaze | 1037.82 | 0.0471959 | 883.835ms | 1811 | 2560 | 1579.23 | 1664.17 | 0.209079 | 5.08273 | 25.402 | 3.69188 | 0.000556064 | 0.000201891 | 5.52181e-05 | 2(Loss) | true |
| simdjson (ondemand) | 433.379 | 0.0596612 | 1118.14ms | 1811 | 2560 | 14471.9 | 3985.2 | 0.10667 | 11.9577 | 57.7504 | 11.4776 | 0.00150879 | 0.00024956 | 9.3612e-05 | 3(Loss) | true |
| simdjson (reflection) | 426.721 | 0.0823226 | 1126.13ms | 1811 | 2560 | 28420.1 | 4047.38 | 0.164565 | 12.1784 | 59.9023 | 11.9056 | 0.00134529 | 0.000257109 | 0.000119495 | 4(Loss) | true |
