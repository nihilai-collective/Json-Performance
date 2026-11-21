
----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3096.9 | 0.0874494 | 3529.19ms | 108313 | 2560 | 2.17802e+06 | 33354.5 | 0.0358835 | 0.798833 | 1(Win) | true |
| Jsonifier (two-stage) | 2651.25 | 0.111061 | 4143.37ms | 108313 | 1280 | 2.39658e+06 | 38960.9 | 0.392299 | 0.933194 | 2(Loss) | true |
| Glaze | 1865.75 | 0.06902 | 5817.64ms | 108313 | 1280 | 1.86901e+06 | 55363.9 | 0.0515963 | 1.32637 | 3(Loss) | true |
| simdjson (ondemand) | 664.381 | 0.0705031 | 8201.81ms | 108313 | 640 | 7.68996e+06 | 155476 | 0.0700992 | 3.72585 | 4(Loss) | true |
