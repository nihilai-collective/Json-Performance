
----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1435.33 | 0.117398 | 4487.76ms | 56369 | 40 | 77331.3 | 37453.2 | 0.0142643 | 3.59088 | 15.578 | 3.10793 | 0.00688543 | 9.44668e-05 | 7.89441e-05 | 1(Win) | true |
| simdjson (ondemand) | 1238.45 | 0.0381695 | 5095.98ms | 56369 | 640 | 175685 | 43407.1 | 0.0694248 | 4.15196 | 16.9805 | 2.84656 | 0.0101714 | 1.56613e-05 | 7.31785e-06 | 2(Loss) | true |
