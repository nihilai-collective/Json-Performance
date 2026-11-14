
----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1080.83 | 0.152397 | 4716.58ms | 53331 | 4890 | 2.51482e+07 | 47056.8 | 0.207075 | 2.81048 | 1(Win) | true |
| Glaze | 1040.43 | 0.234868 | 4885.69ms | 53331 | 2560 | 3.37462e+07 | 48884.1 | 0.0401778 | 2.91981 | 2(Loss) | true |
| Jsonifier (two-stage) | 963.039 | 0.18506 | 5290.06ms | 53331 | 4890 | 4.67097e+07 | 52812.4 | 0.0550786 | 3.15448 | 3(Loss) | true |
| simdjson (ondemand) | 725.755 | 0.130921 | 6992.55ms | 53331 | 4890 | 4.1163e+07 | 70079.3 | 0.00352032 | 4.18634 | 4(Loss) | true |
