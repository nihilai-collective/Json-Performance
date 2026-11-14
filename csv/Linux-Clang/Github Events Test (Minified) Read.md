
----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1290.08 | 0.0327359 | 4680.31ms | 53331 | 2560 | 426397 | 39424.2 | 0.0301649 | 3.96976 | 13.984 | 2.75474 | 0.0129809 | 2.99647e-05 | 9.08243e-06 | 1(Win) | true |
| simdjson (ondemand) | 1012.33 | 0.0313156 | 5752.91ms | 53331 | 2560 | 633690 | 50240.8 | 0.105525 | 5.07477 | 18.8423 | 3.49368 | 0.0193669 | 4.56246e-05 | 2.44127e-05 | 2(Loss) | true |
