
----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 562.41 | 0.838557 | 5697.88ms | 2251027 | 40 | 4.09808e+10 | 3.81705e+06 | 0.0307487 | 5.40396 | 1(Win) | true |
| Jsonifier | 543.829 | 1.05922 | 5904.76ms | 2251027 | 30 | 5.24486e+10 | 3.94747e+06 | 0.0451563 | 5.58867 | 2(Loss) | true |
| simdjson (ondemand) | 373.465 | 0.423128 | 8673.08ms | 2251027 | 30 | 1.7747e+10 | 5.74818e+06 | 0.0892091 | 8.1382 | 3(Loss) | true |
| Glaze | 352.781 | 0.413499 | 9065.65ms | 2251027 | 40 | 2.53256e+10 | 6.0852e+06 | 0.324079 | 8.61547 | 4(Loss) | true |
