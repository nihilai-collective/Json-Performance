
----
### Canada Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 646.137 | 0.31749 | 9584.6ms | 2090234 | 80 | 7.6752e+09 | 3.08511e+06 | 1.18772 | 3.83173 | 1(Win) | true |
| simdjson (ondemand) | 588.819 | 0.131735 | 5112.27ms | 2090234 | 30 | 5.96691e+08 | 3.38543e+06 | 0.779781 | 4.20474 | 2(Loss) | true |
