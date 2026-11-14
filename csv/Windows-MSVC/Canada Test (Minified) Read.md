
----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12941.4 | 0.397515 | 8481.28ms | 2251027 | 2560 | 1.11313e+09 | 165882 | 0.0348166 | 0.234692 | 1(Win) | true |
| simdjson (stage-1) | 10306.9 | 0.667843 | 5352.68ms | 2251027 | 30 | 5.8047e+07 | 208283 | 0.72215 | 0.294774 | 2(Loss) | true |
