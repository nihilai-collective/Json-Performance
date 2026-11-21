
----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1201.55 | 0.313859 | 971.954ms | 11579 | 640 | 532488 | 9190.31 | 0.115745 | 2.05333 | 1(Win) | true |
| Jsonifier | 1175.74 | 0.150106 | 969.515ms | 11579 | 4890 | 971915 | 9392.07 | 0.200819 | 2.09919 | 2(Loss) | true |
| simdjson (ondemand) | 421.561 | 0.0801167 | 2696.46ms | 11579 | 4890 | 2.15366e+06 | 26194.6 | 0.147454 | 5.86632 | 3(Loss) | true |
| Glaze | 402.036 | 0.202321 | 2796.91ms | 11579 | 30 | 92643.7 | 27466.7 | 0.463302 | 6.15019 | 4(Loss) | true |
