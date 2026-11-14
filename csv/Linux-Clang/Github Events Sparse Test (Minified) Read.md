
----
### Github Events Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7879.05 | 0.0296356 | 1368.16ms | 53331 | 2560 | 9368.67 | 6455.14 | 0.0141824 | 0.657563 | 2.99372 | 0.41985 | 0.000853551 | 3.03236e-06 | 5.05393e-07 | 1(Win) | true |
| simdjson (ondemand) | 6753.23 | 0.0525516 | 1478.94ms | 53331 | 1280 | 20050.1 | 7531.27 | 0.0828173 | 0.765025 | 3.34413 | 0.415462 | 0.000919728 | 3.76481e-06 | 5.42016e-07 | 2(Loss) | true |
