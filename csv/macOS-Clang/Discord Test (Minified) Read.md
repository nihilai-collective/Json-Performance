
----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2062.43 | 0.35481 | 2535.42ms | 56369 | 1280 | 1.09477e+07 | 26065.2 | 0.989678 | 1(Win) | true |
| Glaze | 1447.84 | 0.759443 | 3998ms | 56369 | 160 | 1.27219e+07 | 37129.7 | 0.531837 | 2(Loss) | true |
| Jsonifier (two-stage) | 1129.34 | 1.80297 | 4690.83ms | 56369 | 40 | 2.94625e+07 | 47601 | 0.00770351 | 3(Loss) | true |
| simdjson (ondemand) | 699.773 | 0.134499 | 8005.84ms | 56369 | 4890 | 5.22056e+07 | 76821.6 | 1.54563 | 4(Loss) | true |
