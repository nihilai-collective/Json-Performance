
----
### Github Events Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1157.55 | 0.0375325 | 5737.91ms | 53331 | 2560 | 696196 | 43937.8 | 0.0762793 | 4.40401 | 16.6218 | 3.3176 | 0.0131 | 3.99187e-05 | 2.43761e-05 | 1(Win) | true |
| simdjson (ondemand) | 480.017 | 0.0582729 | 6136.16ms | 53331 | 2560 | 9.75934e+06 | 105955 | 0.0208412 | 10.6072 | 38.4905 | 6.84006 | 0.061343 | 0.000121141 | 9.4655e-05 | 2(Loss) | true |
