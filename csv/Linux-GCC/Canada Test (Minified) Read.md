
----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 737.625 | 0.202588 | 8260.85ms | 2090234 | 160 | 4.79584e+09 | 2.70246e+06 | 1.33788 | 3.35643 | 1(Win) | true |
| simdjson (ondemand) | 694.12 | 0.142903 | 8770.97ms | 2090234 | 80 | 1.3474e+09 | 2.87184e+06 | 0.255431 | 3.5668 | 2(Loss) | true |
