
----
### Twitter Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 633.908 | 0.146329 | 5170.8ms | 264040 | 320 | 1.08118e+08 | 397231 | 0.173675 | 3.90526 | 1(Win) | true |
| simdjson (ondemand) | 244.969 | 0.0779551 | 6536.37ms | 264040 | 160 | 1.02737e+08 | 1.02792e+06 | 0.123502 | 10.1064 | 2(Loss) | true |
