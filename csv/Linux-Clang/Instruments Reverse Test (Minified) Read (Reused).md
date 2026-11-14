
----
### Instruments Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 646.921 | 0.0292511 | 8649.49ms | 108313 | 640 | 1.39613e+06 | 159672 | 0.0698783 | 7.96098 | 37.3482 | 7.42665 | 0.0122304 | 6.23194e-06 | 9.95379e-07 | 1(Win) | true |
| simdjson (ondemand) | 251.902 | 0.0536547 | 5336.32ms | 108313 | 640 | 3.09809e+07 | 410062 | 0.0816209 | 20.3111 | 99.3922 | 17.9694 | 0.0662405 | 2.5952e-05 | 1.21177e-05 | 2(Loss) | true |
