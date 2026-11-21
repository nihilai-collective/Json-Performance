
----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) DID NOT CONVERGE | 1879.92 | 0.503369 | 5724.14ms | 7351818 | 40 | 1.40975e+10 | 3.72954e+06 | 2.568 | 1.31688 | -(Win) | false |
| Jsonifier DID NOT CONVERGE | 1692.05 | 1.12899 | 5878.56ms | 7351818 | 30 | 6.56546e+10 | 4.14364e+06 | 10.4357 | 1.46275 | -(Loss) | false |
| Glaze | 647.764 | 1.55802 | 7417.59ms | 7351818 | 30 | 8.53147e+11 | 1.08238e+07 | 0.865508 | 3.82194 | 3(Loss) | true |
| simdjson (ondemand) | 441.657 | 1.87876 | 10840ms | 7351818 | 30 | 2.6686e+12 | 1.58748e+07 | 0.853744 | 5.6055 | 4(Loss) | true |
