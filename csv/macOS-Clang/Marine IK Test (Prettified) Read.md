
----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2005.14 | 0.437656 | 5271.4ms | 7351818 | 30 | 7.02567e+09 | 3.49664e+06 | 0.108957 | 1(Win) | true |
| Jsonifier (two-stage) | 1819.28 | 0.764378 | 5743.39ms | 7351818 | 30 | 2.60331e+10 | 3.85385e+06 | 0.607439 | 2(Loss) | true |
| Glaze | 1403.9 | 0.309044 | 7586.95ms | 7351818 | 30 | 7.14628e+09 | 4.99412e+06 | 1.41183 | 3(Loss) | true |
| simdjson (ondemand) | 1322.7 | 0.503319 | 8053.89ms | 7351818 | 30 | 2.13538e+10 | 5.30071e+06 | 0.442134 | 4(Loss) | true |
