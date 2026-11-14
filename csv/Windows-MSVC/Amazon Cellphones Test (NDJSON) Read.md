
----
### Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3565.47 | 0.34574 | 7519.42ms | 277673 | 1280 | 8.44001e+07 | 74270.6 | 0.130475 | 0.852139 | 1(Win) | true |
| Jsonifier (generic) | 3497.34 | 0.123071 | 7688.64ms | 277673 | 640 | 5.55749e+06 | 75717.3 | 0.0785612 | 0.868719 | 2(Loss) | true |
