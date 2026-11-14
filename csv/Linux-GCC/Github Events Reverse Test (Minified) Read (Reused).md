
----
### Github Events Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1087.01 | 0.0630407 | 5970.87ms | 53331 | 320 | 278411 | 46789.4 | 0.139542 | 4.73987 | 17.5305 | 3.43058 | 0.013914 | 1.002e-05 | 2.98841e-06 | 1(Win) | true |
| simdjson (ondemand) | 529.261 | 0.0877647 | 5609.96ms | 53331 | 640 | 4.55239e+06 | 96097.1 | 0.216966 | 9.6884 | 34.7767 | 6.9882 | 0.0661322 | 1.49128e-05 | 4.13104e-06 | 2(Loss) | true |
