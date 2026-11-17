
----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12411.3 | 0.0355364 | 5604.88ms | 728486 | 1280 | 506480 | 55976.1 | 0.0159083 | 0.244707 | 1(Win) | true |
| simdjson (stage-1) | 11954.8 | 0.0379548 | 5822.96ms | 728486 | 4890 | 2.37904e+06 | 58113.8 | 0.112603 | 0.25404 | 2(Loss) | true |
