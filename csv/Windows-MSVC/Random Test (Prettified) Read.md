
----
### Random Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 13450.9 | 0.409408 | 5219.54ms | 728486 | 4890 | 2.18657e+08 | 51650.1 | 0.829583 | 0.225757 | 1(Win) | true |
| simdjson (stage-1) | 11239.8 | 0.497726 | 6209.07ms | 728486 | 2560 | 2.42295e+08 | 61810.4 | 0.434337 | 0.270206 | 2(Loss) | true |
