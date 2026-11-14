
----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 649.994 | 0.165213 | 9066.99ms | 1834197 | 80 | 1.58144e+09 | 2.69114e+06 | 0.184515 | 7.80458 | 31.9518 | 5.63055 | 0.0441458 | 0.117786 | 0.000682036 | 1(Win) | true |
| Jsonifier (generic) | 643.217 | 0.125893 | 9133.38ms | 1834197 | 160 | 1.87544e+09 | 2.71949e+06 | 0.0597271 | 7.90003 | 31.1627 | 6.4691 | 0.0359463 | 0.11763 | 0.00107678 | 2(Loss) | true |
