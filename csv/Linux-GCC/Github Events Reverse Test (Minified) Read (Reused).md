
----
### Github Events Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1081.5 | 0.0335019 | 6002.25ms | 53331 | 1280 | 317729 | 47027.8 | 0.165888 | 4.76403 | 17.5103 | 3.42537 | 0.0138014 | 1.6949e-05 | 4.64376e-06 | 1(Win) | true |
| simdjson (ondemand) | 522.969 | 0.174853 | 5693.29ms | 53331 | 160 | 4.62674e+06 | 97253.1 | 0.159774 | 9.81953 | 34.7677 | 6.98684 | 0.0674051 | 6.23465e-05 | 4.03143e-05 | 2(Loss) | true |
