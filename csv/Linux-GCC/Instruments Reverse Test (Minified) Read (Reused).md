
----
### Instruments Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 617.694 | 0.0561618 | 8988.7ms | 108313 | 640 | 5.64517e+06 | 167227 | 0.0252677 | 8.29755 | 37.7606 | 7.55848 | 0.011268 | 1.57241e-05 | 7.21289e-06 | 1(Win) | true |
| simdjson (ondemand) | 256.623 | 0.11322 | 5243.13ms | 108313 | 80 | 1.66154e+07 | 402518 | 0.00420495 | 19.996 | 90.0324 | 18.3571 | 0.0872873 | 2.63126e-05 | 1.25793e-05 | 2(Loss) | true |
