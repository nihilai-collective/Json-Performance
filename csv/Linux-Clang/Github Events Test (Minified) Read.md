
----
### Github Events Test (Minified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17740.2 | 0.059707 | 1004.59ms | 53331 | 2560 | 7501.27 | 2866.96 | 0.00876013 | 0.294407 | 1.56633 | 0.0780785 | 3.81462e-05 | 3.37661e-06 | 9.59515e-07 | 1(Win) | true |
| simdjson (stage-1) | 15451.1 | 0.0519368 | 1046.21ms | 53331 | 1280 | 3741.12 | 3291.71 | 0.030892 | 0.337255 | 1.56335 | 0.0662467 | 3.35903e-05 | 3.14955e-06 | 8.05699e-07 | 2(Loss) | true |
