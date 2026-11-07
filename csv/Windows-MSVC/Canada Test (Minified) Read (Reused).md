
----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 842.752 | 1.21644 | 9856.49ms | 2251027 | 30 | 2.8805e+10 | 2.54731e+06 | 0.0872056 | 2.93769 | 1(Win) | true |
| Jsonifier (two-stage) | 801.594 | 0.215243 | 5043.85ms | 2251027 | 40 | 1.32914e+09 | 2.6781e+06 | 2.27229 | 3.08856 | 2(Loss) | true |
| simdjson (ondemand) | 216.949 | 0.21143 | 7454.34ms | 2251027 | 30 | 1.3131e+10 | 9.89515e+06 | 0.292752 | 11.4119 | 3(Loss) | true |
| Glaze | 207.953 | 0.922379 | 7660.87ms | 2251027 | 40 | 3.62669e+11 | 1.03232e+07 | 0.287622 | 11.9057 | 4(Loss) | true |
