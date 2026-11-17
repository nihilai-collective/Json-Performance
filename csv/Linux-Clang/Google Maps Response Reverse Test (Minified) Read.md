
----
### Google Maps Response Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 784.926 | 0.0301757 | 2167.82ms | 11812 | 2560 | 48011.3 | 14351.4 | 0.129404 | 6.55482 | 30.0242 | 6.03353 | 0.0159962 | 3.01269e-05 | 1.23021e-05 | 1(Win) | true |
| simdjson (ondemand) | 688.266 | 0.0431417 | 2365.28ms | 11812 | 640 | 31908.8 | 16366.9 | 0.0444392 | 7.48907 | 33.5745 | 6.19501 | 0.0124765 | 1.36249e-05 | 9.25965e-07 | 2(Loss) | true |
