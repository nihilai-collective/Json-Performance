
----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1787.68 | 0.0476542 | 7607.64ms | 264040 | 1280 | 5.76731e+06 | 140858 | 0.00158458 | 2.86274 | 10.392 | 1.96386 | 0.0100046 | 4.86935e-05 | 1.06725e-05 | 1(Win) | true |
| simdjson (ondemand) | 1580.93 | 0.21126 | 8514.16ms | 264040 | 160 | 1.81164e+07 | 159279 | 0.111415 | 3.19021 | 11.2944 | 1.85093 | 0.0122709 | 0.000105287 | 2.06171e-05 | 2(Loss) | true |
