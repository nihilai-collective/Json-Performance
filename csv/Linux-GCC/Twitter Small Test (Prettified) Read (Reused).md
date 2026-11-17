
----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3142.04 | 0.038514 | 850.177ms | 3808 | 4890 | 968.983 | 1155.81 | 0.139778 | 1.67449 | 6.02048 | 0.79438 | 0.000263679 | 6.498e-05 | 2.43272e-05 | 1(Win) | true |
| simdjson (reflection) | 2697.81 | 0.08445 | 871.858ms | 3808 | 2560 | 3308.34 | 1346.12 | 0.176816 | 1.93986 | 6.96928 | 0.905462 | 0.0003141 | 8.56544e-05 | 3.06714e-05 | 2(Loss) | true |
| Jsonifier | 2663.38 | 0.0649182 | 872.056ms | 3808 | 80 | 62.6829 | 1363.53 | 0.00183345 | 1.99123 | 5.84034 | 1.03598 | 0.000262605 | 2.29779e-05 | 0 | 3(Loss) | true |
| Glaze | 2475.99 | 0.0492752 | 877.384ms | 3808 | 320 | 167.148 | 1466.72 | 0.13596 | 2.09922 | 7.97637 | 1.4073 | 0.000262605 | 1.64128e-05 | 1.64128e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1844.19 | 0.0453349 | 936.122ms | 3808 | 4890 | 3897.21 | 1969.2 | 0.304393 | 2.81104 | 9.23582 | 1.77101 | 0.000269103 | 0.000118468 | 6.45504e-05 | 5(Loss) | true |
