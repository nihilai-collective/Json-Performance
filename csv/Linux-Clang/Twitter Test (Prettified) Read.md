
----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2193.61 | 0.12014 | 7233.47ms | 631514 | 640 | 6.96309e+07 | 274551 | 0.0766975 | 2.30362 | 7.29787 | 1.15148 | 0.0121835 | 0.0326418 | 0.00028016 | 1(Win) | true |
| Glaze | 2012.1 | 0.073868 | 7844.52ms | 631514 | 1280 | 6.25736e+07 | 299319 | 0.0525372 | 2.51133 | 9.08986 | 1.66399 | 0.0107692 | 0.0148292 | 0.000156449 | 2(Loss) | true |
| Jsonifier | 1576.27 | 0.121186 | 5006.09ms | 631514 | 320 | 6.86054e+07 | 382078 | 0.0382743 | 3.20448 | 7.96941 | 1.53312 | 0.0104958 | 0.0233714 | 0.000271288 | 3(Loss) | true |
| simdjson (ondemand) | 1221.3 | 0.094821 | 6384.14ms | 631514 | 640 | 1.39929e+08 | 493127 | 0.247084 | 4.10437 | 13.7961 | 2.36414 | 0.010406 | 0.0411905 | 0.000504153 | 4(Loss) | true |
