
----
### Github Events Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5972.24 | 0.0274317 | 1761.86ms | 65103 | 2560 | 20819.7 | 10395.9 | 0.0759298 | 0.865559 | 3.95613 | 0.606393 | 0.00155171 | 6.83412e-06 | 3.40806e-06 | 1(Win) | true |
| simdjson (ondemand) | 4738.99 | 0.0331745 | 2036.3ms | 65103 | 1280 | 24179.6 | 13101.3 | 0.0709229 | 1.0896 | 5.07872 | 0.788105 | 0.00195291 | 3.50406e-06 | 1.10402e-06 | 2(Loss) | true |
