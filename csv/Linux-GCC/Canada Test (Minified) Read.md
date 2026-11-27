
----
### Canada Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 804.626 | 0.115841 | 7792.99ms | 2090234 | 30 | 2.47085e+08 | 2.47743e+06 | 0.0852699 | 3.07692 | 1(Win) | true |
| simdjson (ondemand) | 739.749 | 0.126116 | 8384.94ms | 2090234 | 30 | 3.46485e+08 | 2.6947e+06 | 0.136522 | 3.34674 | 2(Loss) | true |
