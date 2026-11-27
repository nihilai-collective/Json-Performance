
----
### Instruments Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 656.46 | 0.0945012 | 8473.49ms | 108313 | 160 | 3.53785e+06 | 157352 | 0.0448718 | 7.73149 | 36.0328 | 7.19408 | 0.00944981 | 2.56779e-05 | 1.66762e-05 | 1(Win) | true |
| simdjson (ondemand) | 241.39 | 0.135461 | 5579.65ms | 108313 | 160 | 5.37617e+07 | 427920 | 0.0246062 | 21.1081 | 99.2364 | 17.9269 | 0.0761577 | 4.87014e-05 | 3.37563e-05 | 2(Loss) | true |
