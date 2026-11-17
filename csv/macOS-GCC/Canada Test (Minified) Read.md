
----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 634.053 | 1.23588 | 5140.63ms | 2251027 | 40 | 7.00369e+10 | 3.38575e+06 | 0.302784 | 1(Win) | true |
| Glaze | 543.334 | 1.70921 | 5730.33ms | 2251027 | 40 | 1.82422e+11 | 3.95106e+06 | 1.32567 | 2(Loss) | true |
| Jsonifier (two-stage) | 519.35 | 1.45711 | 6553.44ms | 2251027 | 30 | 1.08829e+11 | 4.13353e+06 | 0.321015 | 3(Loss) | true |
| simdjson (reflection) | 499.003 | 1.08885 | 6228.7ms | 2251027 | 30 | 6.58285e+10 | 4.30207e+06 | 1.56416 | 4(Loss) | true |
| simdjson (ondemand) | 464.659 | 1.53431 | 6819.23ms | 2251027 | 40 | 2.00993e+11 | 4.62004e+06 | 0.44293 | 5(Loss) | true |
