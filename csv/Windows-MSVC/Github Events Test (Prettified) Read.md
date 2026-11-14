
----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 989.504 | 0.247901 | 6272.99ms | 65103 | 2560 | 6.1939e+07 | 62745.7 | 0.0617331 | 3.07034 | 1(Win) | true |
| simdjson (ondemand) | 863.744 | 0.126198 | 7201.28ms | 65103 | 4890 | 4.02387e+07 | 71881.3 | 0.310964 | 3.5175 | 2(Loss) | true |
