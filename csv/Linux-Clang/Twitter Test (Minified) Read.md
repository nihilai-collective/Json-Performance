
----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1870.49 | 0.145257 | 6899.84ms | 264040 | 160 | 6.11817e+06 | 134621 | 0.325653 | 1.32323 | 1(Win) | true |
| simdjson (ondemand) | 1699.44 | 0.0726272 | 7541.74ms | 264040 | 2560 | 2.96459e+07 | 148171 | 0.137169 | 1.45646 | 2(Loss) | true |
