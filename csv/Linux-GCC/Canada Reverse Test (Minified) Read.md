
----
### Canada Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 642.096 | 0.0728564 | 9533.71ms | 2090234 | 30 | 1.53478e+08 | 3.10452e+06 | 0.110171 | 3.85578 | 1(Win) | true |
| simdjson (ondemand) | 617.099 | 0.185459 | 10219ms | 2090234 | 160 | 5.74241e+09 | 3.23028e+06 | 0.47313 | 4.01197 | 2(Loss) | true |
