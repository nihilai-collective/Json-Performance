
----
### Random Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 839.167 | 0.0512182 | 6010.34ms | 409725 | 640 | 3.64012e+07 | 465633 | 0.0886349 | 6.06716 | 28.3116 | 5.7895 | 0.0123691 | 0.0271238 | 3.79523e-05 | 1(Win) | true |
| simdjson (ondemand) | 452.788 | 0.0636674 | 5492ms | 409725 | 320 | 9.66004e+07 | 862973 | 0.00150825 | 11.2082 | 50.4861 | 9.25541 | 0.0351991 | 0.0417366 | 5.62878e-05 | 2(Loss) | true |
