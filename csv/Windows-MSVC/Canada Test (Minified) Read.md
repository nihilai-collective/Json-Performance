
----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 673.175 | 0.68788 | 9857.1ms | 2251027 | 160 | 7.69928e+10 | 3.18899e+06 | 0.477971 | 3.67774 | 1(Win) | true |
| Jsonifier (two-stage) | 634.355 | 0.730468 | 5009.83ms | 2251027 | 40 | 2.44433e+10 | 3.38414e+06 | 1.36959 | 3.90283 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 198.762 | 1.05787 | 7540.65ms | 2251027 | 40 | 5.22181e+11 | 1.08006e+07 | 0.0516063 | 12.4561 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 194.89 | 0.945699 | 7836.48ms | 2251027 | 30 | 3.25544e+11 | 1.10152e+07 | 0.408186 | 12.7036 | 3(Tie) | true |
