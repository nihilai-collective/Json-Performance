
----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4605.97 | 0.052724 | 7793.09ms | 699405 | 1280 | 7.46177e+06 | 144813 | 0.00436913 | 1.09436 | 4.43374 | 0.719304 | 0.00289605 | 0.00107679 | 4.45691e-06 | 1(Win) | true |
| Glaze | 3538.91 | 0.105384 | 5006.53ms | 699405 | 160 | 6.31227e+06 | 188477 | 0.0196714 | 1.42781 | 5.2208 | 1.16228 | 0.00225935 | 0.000701141 | 3.47617e-06 | 2(Loss) | true |
| simdjson (ondemand) | 2291.82 | 0.139841 | 8372.64ms | 767297 | 320 | 6.37947e+07 | 319288 | 0.498877 | 2.18072 | 8.67091 | 1.18232 | 0.00336919 | 0.0923796 | 2.16262e-06 | 3(Loss) | true |
