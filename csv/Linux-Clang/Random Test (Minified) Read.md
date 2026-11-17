
----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22427.1 | 0.174563 | 1986.91ms | 461466 | 1280 | 1.50193e+06 | 19623.1 | 0.0477606 | 0.11021 | 1(Win) | true |
| simdjson (stage-1) | 19038.5 | 0.157545 | 2348.85ms | 461466 | 640 | 848797 | 23115.8 | 0.264647 | 0.129903 | 2(Loss) | true |
