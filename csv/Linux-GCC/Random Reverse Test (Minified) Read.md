
----
### Random Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 806.423 | 0.160856 | 6258.68ms | 409725 | 320 | 1.94393e+08 | 484540 | 0.253952 | 6.30547 | 28.7764 | 5.82013 | 0.0129993 | 0.0216277 | 7.67359e-05 | 1(Win) | true |
| simdjson (ondemand) | 482.109 | 0.0537861 | 5149.02ms | 409725 | 320 | 6.08113e+07 | 810490 | 0.0646136 | 10.5403 | 46.7606 | 9.42332 | 0.0318291 | 0.0494045 | 8.70325e-05 | 2(Loss) | true |
