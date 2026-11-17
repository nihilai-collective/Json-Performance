
----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3209.82 | 0.0253668 | 3966.01ms | 108313 | 2560 | 170597 | 32181 | 0.00325904 | 1.57228 | 7.40082 | 1.50827 | 0.00210218 | 3.16971e-05 | 2.26845e-05 | 1(Win) | true |
| Glaze | 2221.45 | 0.068295 | 5417.53ms | 108313 | 640 | 645427 | 46499.1 | 0.0297834 | 2.26378 | 10.0551 | 1.92674 | 0.00310338 | 3.99306e-05 | 2.75821e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2160.37 | 0.0598005 | 5518.99ms | 108313 | 160 | 130808 | 47813.6 | 0.0716854 | 2.34023 | 10.3059 | 1.84188 | 0.0027634 | 7.4437e-06 | 4.09692e-06 | 3(Loss) | true |
| simdjson (reflection) | 1665.35 | 0.018885 | 6959.73ms | 108313 | 4890 | 670960 | 62026.3 | 0.0138481 | 3.03302 | 13.1045 | 2.04129 | 0.00220551 | 3.79175e-05 | 2.77485e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1441.24 | 0.0330375 | 7915.65ms | 108313 | 4890 | 2.74167e+06 | 71671.3 | 0.0330191 | 3.49067 | 14.907 | 2.64242 | 0.0027942 | 4.89153e-05 | 3.46606e-05 | 5(Loss) | true |
