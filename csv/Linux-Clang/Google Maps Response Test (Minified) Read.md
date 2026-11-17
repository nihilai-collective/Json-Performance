
----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1289.82 | 0.0363236 | 1604.19ms | 11812 | 2560 | 25763.6 | 8733.62 | 0.0241224 | 3.9755 | 18.1438 | 3.54521 | 0.00612463 | 2.53318e-05 | 6.21719e-06 | 1(Win) | true |
| simdjson (ondemand) | 1037.17 | 0.0534917 | 1815.22ms | 11812 | 1280 | 43204.8 | 10861.1 | 0.10099 | 4.943 | 20.696 | 3.60307 | 0.00784127 | 3.80969e-05 | 1.60721e-05 | 2(Loss) | true |
