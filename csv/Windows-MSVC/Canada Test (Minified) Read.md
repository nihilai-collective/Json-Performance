
----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 29089 | 0.327487 | 7705.05ms | 2251027 | 160 | 9.34572e+06 | 73799.4 | 0.0160883 | 0.0850787 | 1(Win) | true |
| simdjson (stage-1) | 20160.4 | 0.0894323 | 5779.52ms | 2251027 | 2560 | 2.32162e+07 | 106483 | 0.240529 | 0.12277 | 2(Loss) | true |
