
----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22000.2 | 0.110928 | 3234.61ms | 728486 | 4890 | 6.00034e+06 | 31578.7 | 0.00853804 | 0.112441 | 1(Win) | true |
| simdjson (stage-1) | 20218.7 | 0.106804 | 3490.3ms | 728486 | 4890 | 6.58599e+06 | 34361.2 | 0.0782669 | 0.12234 | 2(Loss) | true |
