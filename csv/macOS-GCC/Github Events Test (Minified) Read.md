
----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1448.73 | 0.290446 | 3522.7ms | 53331 | 2560 | 2.6617e+07 | 35107 | 1.0234 | 1(Win) | true |
| Glaze | 1301.6 | 0.226854 | 4032.6ms | 53331 | 4890 | 3.84243e+07 | 39075.2 | 1.7477 | 2(Loss) | true |
| simdjson (reflection) | 1131.36 | 0.436044 | 5045.2ms | 53331 | 160 | 6.1481e+06 | 44955.2 | 0.210429 | 3(Loss) | true |
| Jsonifier (two-stage) | 1066.85 | 0.710985 | 4341.89ms | 53331 | 160 | 1.83822e+07 | 47673.6 | 0.314486 | 4(Loss) | true |
| simdjson (ondemand) | 789.228 | 0.821819 | 6321.39ms | 53331 | 320 | 8.97545e+07 | 64443.2 | 2.05752 | 5(Loss) | true |
