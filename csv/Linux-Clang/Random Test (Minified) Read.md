
----
### Random Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1145.11 | 0.0320948 | 8935.55ms | 409725 | 1280 | 1.53523e+07 | 341229 | 0.0594755 | 4.45435 | 18.6831 | 3.58053 | 0.0137409 | 0.0252009 | 0.000114404 | 1(Win) | true |
| simdjson (ondemand) | 937.933 | 0.122057 | 5388.74ms | 409725 | 640 | 1.65482e+08 | 416602 | 0.0852707 | 5.40469 | 21.0167 | 3.75124 | 0.0194966 | 0.0382981 | 0.00013805 | 2(Loss) | true |
