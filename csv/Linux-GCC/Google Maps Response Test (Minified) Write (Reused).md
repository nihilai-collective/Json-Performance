
----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16821.8 | 0.0740933 | 790.53ms | 11812 | 640 | 157.557 | 669.653 | 0.136545 | 0.319171 | 1.58297 | 0.24636 | 8.49242e-05 | 5.95263e-06 | 6.61404e-07 | 1(Win) | true |
| simdjson (reflection) | 10406.4 | 0.0844495 | 837.436ms | 11812 | 4890 | 4086.48 | 1082.49 | 0.00283115 | 0.505892 | 2.34459 | 0.348718 | 0.000105643 | 1.59105e-05 | 2.94318e-06 | 2(Loss) | true |
| Glaze | 5173.1 | 0.143966 | 954.626ms | 11812 | 2560 | 25159.6 | 2177.57 | 0.0209925 | 0.996063 | 4.35083 | 0.655943 | 9.77555e-05 | 1.59398e-05 | 7.24237e-06 | 3(Loss) | true |
