
----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 29337.2 | 0.228741 | 7485.92ms | 2251027 | 320 | 8.96521e+06 | 73174.8 | 0.0786324 | 0.084359 | 1(Win) | true |
| simdjson (stage-1) | 19108.5 | 0.0715076 | 5800.79ms | 2251027 | 2560 | 1.65216e+07 | 112345 | 0.121997 | 0.129531 | 2(Loss) | true |
