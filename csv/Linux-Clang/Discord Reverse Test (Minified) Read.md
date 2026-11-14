
----
### Discord Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 706.748 | 0.0281327 | 8350.54ms | 56369 | 4890 | 2.23916e+06 | 76063.4 | 0.176208 | 7.24386 | 35.3631 | 7.26097 | 0.0116265 | 6.3727e-05 | 3.9707e-05 | 1(Win) | true |
| simdjson (ondemand) | 209.465 | 0.0611225 | 6755.2ms | 56369 | 640 | 1.57485e+07 | 256643 | 0.0185628 | 24.4592 | 139.872 | 28.1085 | 0.0380251 | 8.50146e-05 | 4.84531e-05 | 2(Loss) | true |
