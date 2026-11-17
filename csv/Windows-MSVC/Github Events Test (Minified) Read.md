
----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1007.44 | 0.337287 | 5077.64ms | 53331 | 2560 | 7.42273e+07 | 50485 | 0.473598 | 2.45572 | 1(Win) | true |
| Glaze | 985.219 | 0.254683 | 5297.91ms | 53331 | 4890 | 8.45287e+07 | 51623.4 | 0.730114 | 2.51137 | 2(Loss) | true |
| Jsonifier (two-stage) | 969.713 | 0.211499 | 5310.9ms | 53331 | 2560 | 3.15014e+07 | 52448.9 | 0.069439 | 2.5514 | 3(Loss) | true |
| simdjson (ondemand) | 610.128 | 0.203716 | 8415.99ms | 53331 | 2560 | 7.38254e+07 | 83360.2 | 0.245551 | 4.05644 | 4(Loss) | true |
