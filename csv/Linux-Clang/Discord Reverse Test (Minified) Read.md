
----
### Discord Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 683.114 | 0.126945 | 8576.19ms | 56369 | 2560 | 2.55484e+07 | 78695 | 0.0127017 | 7.43411 | 35.3914 | 7.26188 | 0.0114364 | 4.26112e-05 | 1.72274e-05 | 1(Win) | true |
| simdjson (ondemand) | 200.108 | 0.0447251 | 7045.81ms | 56369 | 1280 | 1.84785e+07 | 268644 | 0.0801534 | 25.4521 | 139.931 | 28.1377 | 0.0343825 | 6.68308e-05 | 3.4843e-05 | 2(Loss) | true |
