
----
### Instruments Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 570.759 | 0.0383961 | 1505.2ms | 4669 | 2560 | 22969.8 | 7801.37 | 0.00642957 | 9.04235 | 38.296 | 7.63418 | 0.0104952 | 4.75209e-05 | 1.19639e-05 | 1(Win) | true |
| simdjson (ondemand) | 245.862 | 0.0181954 | 2540.17ms | 4669 | 4890 | 53100.8 | 18110.6 | 0.169427 | 20.9145 | 94.0159 | 19.1902 | 0.050243 | 3.12727e-05 | 6.0881e-06 | 2(Loss) | true |
