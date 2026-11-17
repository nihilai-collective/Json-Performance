
----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1250.36 | 0.0529236 | 8155.87ms | 409725 | 640 | 1.75063e+07 | 312505 | 0.128062 | 4.05541 | 18.6337 | 3.68751 | 0.0101636 | 0.0171612 | 3.63048e-06 | 1(Win) | true |
| simdjson (ondemand) | 928.047 | 0.145719 | 5439.76ms | 409725 | 40 | 1.50569e+07 | 421039 | 0.168852 | 5.44255 | 21.1462 | 3.7874 | 0.0216492 | 0.0354222 | 0.000163768 | 2(Loss) | true |
