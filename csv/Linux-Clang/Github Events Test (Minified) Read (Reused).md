
----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1606.49 | 0.0362152 | 4443.34ms | 53331 | 2560 | 336530 | 31659.3 | 0.0205871 | 3.1895 | 11.7525 | 2.24271 | 0.0103168 | 1.73079e-05 | 6.50419e-06 | 1(Win) | true |
| simdjson (ondemand) | 1195.8 | 0.0329738 | 5560.82ms | 53331 | 2560 | 503521 | 42532.4 | 0.0465147 | 4.286 | 16.6623 | 2.99522 | 0.0156893 | 1.98349e-05 | 8.73818e-06 | 2(Loss) | true |
