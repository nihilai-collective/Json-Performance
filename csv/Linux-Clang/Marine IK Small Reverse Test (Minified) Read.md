
----
### Marine IK Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 326.981 | 0.0581731 | 2096.11ms | 4604 | 640 | 39052.6 | 13428.1 | 0.0472783 | 15.7719 | 68.8691 | 14.9241 | 0.0203044 | 5.1925e-05 | 1.90052e-05 | 1(Win) | true |
| simdjson (ondemand) | 241.472 | 0.0845992 | 2540.5ms | 4604 | 80 | 18930.4 | 18183.2 | 0.177539 | 21.3741 | 110.6 | 22.2106 | 0.021761 | 0.000244353 | 0.000152042 | 2(Loss) | true |
