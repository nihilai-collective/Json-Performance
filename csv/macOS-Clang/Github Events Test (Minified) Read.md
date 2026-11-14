
----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1213.77 | 0.0499031 | 4218.29ms | 53331 | 4890 | 2.13819e+06 | 41902.7 | 0.0107234 | 1(Win) | true |
| simdjson (ondemand) | 819.054 | 0.0602116 | 6227.53ms | 53331 | 4890 | 6.83603e+06 | 62096.5 | 0.0529576 | 2(Loss) | true |
