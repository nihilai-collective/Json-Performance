
----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13920.8 | 0.163127 | 8336.94ms | 2251027 | 40 | 2.53132e+06 | 154211 | 0.25031 | 0.366748 | 1.70348 | 0.0747921 | 0.00176277 | 0.0249944 | 8.10741e-07 | 1(Win) | true |
| simdjson (stage-1) | 11252.3 | 0.130679 | 5085.7ms | 2251027 | 160 | 9.94514e+06 | 190783 | 0.0509483 | 0.457455 | 2.09408 | 0.0806446 | 0.00165438 | 0.024947 | 1.07729e-06 | 2(Loss) | true |
