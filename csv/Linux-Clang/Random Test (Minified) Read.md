
----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21361.4 | 0.108003 | 2060.88ms | 461466 | 2560 | 1.26746e+06 | 20602.1 | 0.13743 | 0.115747 | 1(Win) | true |
| simdjson (stage-1) | 17633.5 | 0.381311 | 2430.31ms | 461466 | 320 | 2.89808e+06 | 24957.5 | 0.404199 | 0.14025 | 2(Loss) | true |
