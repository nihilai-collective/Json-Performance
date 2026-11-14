
----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1595.03 | 0.085932 | 3929.27ms | 65103 | 4890 | 5.47123e+06 | 38925.4 | 0.0323539 | 1(Win) | true |
| Glaze STATISTICAL TIE | 1514.79 | 0.0897173 | 4118.79ms | 65103 | 4890 | 6.61235e+06 | 40987.1 | 0.162912 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1510.28 | 0.262826 | 4256.21ms | 65103 | 320 | 3.7357e+06 | 41109.6 | 0.0874942 | 2(Tie) | true |
| simdjson (reflection) | 1341.6 | 0.267517 | 4652.33ms | 65103 | 320 | 4.90468e+06 | 46278.4 | 0.211343 | 4(Loss) | true |
| simdjson (ondemand) | 1136.73 | 0.365314 | 5481.4ms | 65103 | 160 | 6.37006e+06 | 54619.2 | 0.190047 | 5(Loss) | true |
