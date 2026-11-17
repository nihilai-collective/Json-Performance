
----
### Google Maps Response Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 763.637 | 0.0305458 | 1267.16ms | 4390 | 4890 | 13714.1 | 5482.49 | 0.0467668 | 6.78538 | 29.4481 | 5.96606 | 0.0112035 | 4.78872e-05 | 1.15991e-05 | 1(Win) | true |
| simdjson (ondemand) | 696.831 | 0.0310319 | 1322.6ms | 4390 | 4890 | 16998.1 | 6008.1 | 0.0785969 | 7.43519 | 31.7656 | 6.19567 | 0.0111456 | 0.00013523 | 5.57597e-05 | 2(Loss) | true |
