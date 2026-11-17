
----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1041.38 | 0.0825072 | 1224.35ms | 4604 | 80 | 968.107 | 4216.24 | 0.0790956 | 4.99509 | 20.3761 | 4.46595 | 0.00383362 | 2.71503e-05 | 8.14509e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 882.051 | 0.0921114 | 1314.26ms | 4604 | 40 | 840.951 | 4977.85 | 0.103351 | 5.88903 | 24.8184 | 4.85295 | 0.00235122 | 0.000114031 | 0 | 2(Loss) | true |
| Glaze | 754.12 | 0.0344948 | 1387.74ms | 4604 | 4890 | 19724.5 | 5822.3 | 0.0145931 | 6.83246 | 29.1901 | 5.89346 | 0.0046293 | 6.07634e-05 | 3.46458e-05 | 3(Loss) | true |
| simdjson (reflection) | 711.474 | 0.0340188 | 1433.31ms | 4604 | 4890 | 21552.6 | 6171.29 | 0.0966133 | 7.24837 | 27.1229 | 5.09622 | 0.00489994 | 0.000107446 | 3.74885e-05 | 4(Loss) | true |
| simdjson (ondemand) | 547.492 | 0.0752656 | 1633.93ms | 4604 | 2560 | 93271.3 | 8019.69 | 0.0784721 | 9.4252 | 33.0173 | 6.61556 | 0.0156979 | 0.000135242 | 6.71122e-05 | 5(Loss) | true |
