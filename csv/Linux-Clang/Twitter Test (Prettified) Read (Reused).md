
----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2735.83 | 0.132541 | 6670.77ms | 631514 | 320 | 2.7242e+07 | 220138 | 0.126319 | 1.84414 | 6.21056 | 0.902752 | 0.00955894 | 0.011461 | 1.84378e-05 | 1(Win) | true |
| Glaze | 2522.37 | 0.0432525 | 7094.85ms | 631514 | 1280 | 1.36515e+07 | 238767 | 0.0849169 | 2.00176 | 7.99565 | 1.41349 | 0.00726629 | 0.00348358 | 8.76985e-06 | 2(Loss) | true |
| Jsonifier | 1885.42 | 0.237402 | 9090.75ms | 631514 | 320 | 1.84023e+08 | 319430 | 0.0731588 | 2.6755 | 6.87648 | 1.28305 | 0.00583835 | 0.00646907 | 8.53653e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1385.07 | 0.167392 | 5980.53ms | 631514 | 160 | 8.47641e+07 | 434823 | 0.283004 | 3.61582 | 12.7512 | 2.12312 | 0.00758401 | 0.0136452 | 0.00014197 | 4(Loss) | true |
