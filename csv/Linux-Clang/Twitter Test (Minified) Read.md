
----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1775.4 | 0.419291 | 7370.26ms | 264040 | 40 | 1.41461e+07 | 141832 | 0.027942 | 1.3941 | 1(Win) | true |
| Jsonifier (generic) | 1718.25 | 0.228704 | 7525.33ms | 264040 | 160 | 1.79735e+07 | 146549 | 0.387389 | 1.44043 | 2(Loss) | true |
