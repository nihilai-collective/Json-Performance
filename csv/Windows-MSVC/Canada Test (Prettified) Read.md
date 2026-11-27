
----
### Canada Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) DID NOT CONVERGE | 1365.23 | 0.740974 | 5685.63ms | 5373214 | 80 | 6.18808e+10 | 3.75344e+06 | 3.73995 | 2.22579 | -(Win) | false |
| Jsonifier | 1235.71 | 2.26923 | 6051.05ms | 5373214 | 30 | 2.65652e+11 | 4.14684e+06 | 0.0130237 | 2.45934 | 2(Loss) | true |
| simdjson (ondemand) | 962.133 | 0.784106 | 8175.02ms | 5373214 | 30 | 5.23201e+10 | 5.32597e+06 | 0.153635 | 3.15883 | 3(Loss) | true |
| Glaze | 787.166 | 1.03239 | 9708.5ms | 5373214 | 30 | 1.35502e+11 | 6.50981e+06 | 1.97669 | 3.86109 | 4(Loss) | true |
