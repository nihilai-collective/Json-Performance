
----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12401.1 | 0.142124 | 5736.12ms | 728486 | 40 | 253583 | 56022.5 | 0.244836 | 0.244945 | 1(Win) | true |
| simdjson (stage-1) | 11671 | 0.196624 | 5928.27ms | 728486 | 4890 | 6.69897e+07 | 59527 | 0.125701 | 0.260218 | 2(Loss) | true |
