
----
### Discord Test (Prettified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6218.99 | 0.247062 | 1347.03ms | 83958 | 4890 | 4.94773e+06 | 12874.9 | 1.60067 | 1(Win) | true |
| simdjson (stage-1) | 5981.7 | 0.531451 | 1387.33ms | 83958 | 1280 | 6.47757e+06 | 13385.6 | 1.38795 | 2(Loss) | true |
