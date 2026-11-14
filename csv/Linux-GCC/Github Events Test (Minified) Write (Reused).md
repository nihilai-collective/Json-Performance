
----
### Github Events Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15032 | 0.0770536 | 1112.22ms | 58581 | 1280 | 10497.3 | 3716.56 | 0.11481 | 0.339934 | 1.04838 | 0.165549 | 3.42074e-05 | 3.24337e-05 | 2.1258e-05 | 1(Win) | true |
| simdjson (reflection) | 11311.9 | 0.0622788 | 1239.99ms | 58581 | 30 | 283.821 | 4938.8 | 0.0445254 | 0.4508 | 1.4875 | 0.210171 | 5.12111e-05 | 1.36563e-05 | 7.96618e-06 | 2(Loss) | true |
| Glaze | 8582.1 | 0.14436 | 1397.64ms | 58581 | 1280 | 113040 | 6509.73 | 0.0125309 | 0.592245 | 2.36218 | 0.354176 | 3.14602e-05 | 1.39897e-05 | 7.66834e-06 | 3(Loss) | true |
