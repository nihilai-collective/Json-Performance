
----
### Twitter Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 710.275 | 0.196308 | 9608.23ms | 264040 | 80 | 3.87483e+07 | 354522 | 0.0658749 | 7.21601 | 27.2615 | 5.11919 | 0.0218157 | 0.000518577 | 2.21557e-05 | 1(Win) | true |
| simdjson (ondemand) | 321.827 | 0.312433 | 5085.25ms | 264040 | 40 | 2.39039e+08 | 782433 | 0.214322 | 15.6446 | 62.9517 | 12.7655 | 0.0846923 | 4.9235e-05 | 1.4013e-05 | 2(Loss) | true |
