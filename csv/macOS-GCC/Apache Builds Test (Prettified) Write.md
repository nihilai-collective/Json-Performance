
----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12330.5 | 0.299863 | 1089.25ms | 136037 | 2560 | 2.54824e+06 | 10521.5 | 0.48709 | 1(Win) | true |
| Glaze | 3616.23 | 0.650831 | 3523.68ms | 136076 | 640 | 3.49113e+07 | 35886 | 0.032335 | 2(Loss) | true |
| simdjson (reflection) | 314.039 | 0.446332 | 5256.6ms | 136037 | 640 | 2.17592e+09 | 413117 | 3.71689 | 3(Loss) | true |
