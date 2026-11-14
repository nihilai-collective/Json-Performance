
----
### Instruments Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 514.156 | 0.174331 | 5163.39ms | 108313 | 80 | 9.81316e+06 | 200902 | 0.108144 | 5.91072 | 1(Win) | true |
| simdjson (ondemand) | 193.01 | 0.194931 | 6809.73ms | 108313 | 320 | 3.48268e+08 | 535182 | 0.048313 | 15.7464 | 2(Loss) | true |
