
----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 697.49 | 0.113431 | 8930.61ms | 2090234 | 30 | 3.15284e+08 | 2.85797e+06 | 0.575948 | 3.54955 | 1(Win) | true |
| simdjson (ondemand) | 673.964 | 0.118252 | 9177.51ms | 2090234 | 30 | 3.66989e+08 | 2.95773e+06 | 1.70097 | 3.67297 | 2(Loss) | true |
