
----
### Discord Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1653.24 | 0.104197 | 4014.01ms | 56369 | 2560 | 2.93874e+06 | 32516.6 | 0.172617 | 3.10918 | 13.3828 | 2.65095 | 0.0055054 | 6.55973e-05 | 4.86194e-05 | 1(Win) | true |
| simdjson (ondemand) | 1299.39 | 0.0512555 | 4896.14ms | 56369 | 1280 | 575565 | 41371.6 | 0.349089 | 3.92575 | 15.8049 | 2.81499 | 0.00953278 | 3.36095e-05 | 2.00409e-05 | 2(Loss) | true |
