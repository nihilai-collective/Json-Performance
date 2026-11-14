
----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 847.922 | 0.224377 | 5982.02ms | 53331 | 2560 | 4.63709e+07 | 59982.4 | 0.300533 | 3.5828 | 1(Win) | true |
| simdjson (ondemand) | 713.699 | 0.212481 | 7148.48ms | 53331 | 160 | 3.66851e+06 | 71263.1 | 0.0886587 | 4.25703 | 2(Loss) | true |
