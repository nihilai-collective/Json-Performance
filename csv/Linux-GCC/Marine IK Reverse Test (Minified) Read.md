
----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 374.883 | 0.288136 | 6982.48ms | 1834197 | 30 | 5.42274e+09 | 4.66607e+06 | 1.40212 | 6.60424 | 1(Win) | true |
| simdjson (ondemand) | 215.298 | 1.75847 | 5760.23ms | 1834197 | 30 | 6.12353e+11 | 8.12467e+06 | 0.0233184 | 11.4995 | 2(Loss) | true |
