
----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 401.111 | 0.159028 | 6648.64ms | 1834197 | 30 | 1.44288e+09 | 4.36095e+06 | 0.546737 | 12.6876 | 62.6232 | 13.5019 | 0.0392354 | 0.344248 | 0.000179624 | 1(Win) | true |
| simdjson (ondemand) | 270.43 | 0.195416 | 9699.96ms | 1834197 | 40 | 6.39092e+09 | 6.46832e+06 | 0.0871948 | 18.7846 | 105.346 | 21.2147 | 0.047124 | 0.789032 | 0.0100976 | 2(Loss) | true |
