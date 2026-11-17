
----
### Random Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 816.114 | 0.330875 | 6095.57ms | 409725 | 80 | 2.00771e+08 | 478787 | 0.813423 | 3.03344 | 1(Win) | true |
| simdjson (ondemand) | 380.306 | 0.158827 | 6655.89ms | 409725 | 30 | 7.98896e+07 | 1.02745e+06 | 0.336413 | 6.50992 | 2(Loss) | true |
