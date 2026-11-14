
----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1836.31 | 0.0583627 | 6398.4ms | 466906 | 640 | 1.2818e+07 | 242485 | 0.250078 | 2.75385 | 8.31705 | 1.47308 | 0.0121145 | 0.0148243 | 3.87257e-05 | 1(Win) | true |
| Glaze | 1828.13 | 0.126603 | 6393.57ms | 466906 | 640 | 6.08571e+07 | 243570 | 0.0682584 | 2.75972 | 10.0645 | 1.80276 | 0.0125169 | 0.0107994 | 3.60418e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1692.56 | 0.126952 | 6892.89ms | 466906 | 320 | 3.56942e+07 | 263078 | 0.121232 | 2.96884 | 9.25619 | 1.53472 | 0.0171041 | 0.0278745 | 0.000165317 | 3(Loss) | true |
| simdjson (ondemand) | 932.52 | 0.145659 | 6170.85ms | 466906 | 160 | 7.73995e+07 | 477498 | 0.0461105 | 5.38851 | 18.198 | 3.17399 | 0.0140242 | 0.0394664 | 8.08514e-05 | 4(Loss) | true |
