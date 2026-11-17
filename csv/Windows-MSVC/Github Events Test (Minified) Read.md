
----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 790.905 | 0.257629 | 6502.58ms | 53331 | 1280 | 3.51326e+07 | 64306.6 | 0.101668 | 3.12902 | 1(Win) | true |
| simdjson (ondemand) | 619.531 | 0.46315 | 8501.33ms | 53331 | 80 | 1.15655e+07 | 82095 | 0.164174 | 3.99491 | 2(Loss) | true |
