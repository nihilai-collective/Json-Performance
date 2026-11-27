
----
### Github Events Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1745.15 | 0.142439 | 3013.3ms | 53331 | 640 | 1.10289e+06 | 29143.8 | 0.0623083 | 1(Win) | true |
| Jsonifier (two-stage) | 1578.3 | 0.101792 | 3402.04ms | 53331 | 1280 | 1.37726e+06 | 32224.8 | 0.122491 | 2(Loss) | true |
| Glaze | 1527.03 | 0.0602309 | 3323.14ms | 53331 | 4890 | 1.96794e+06 | 33306.7 | 0.326761 | 3(Loss) | true |
| simdjson (ondemand) | 887.954 | 0.0658087 | 5817.06ms | 53331 | 4890 | 6.94792e+06 | 57278.2 | 0.176344 | 4(Loss) | true |
